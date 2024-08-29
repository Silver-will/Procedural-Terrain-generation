#version 450 core
out vec4 FragColor;

uniform sampler2D meadowDiffuse;
uniform sampler2D meadowHeight;
uniform sampler2D meadowNormal;
uniform sampler2D sandDiffuse;
uniform sampler2D sandHeight;
uniform sampler2D sandNormal;
uniform sampler2D noiseMap;

uniform vec3 cameraPos;
uniform vec3 lightDirection;
uniform vec3 lightColor;

in TES_OUT
{
    vec4 fragPosLightSpace;
	vec4 fragPos;	
    vec2 texCoord;
    float height;
}tes_in;


vec3 CalcSlopeNormal(vec2 texCoord)
{   
	float textureDelta = 1/256.0;
	
	float left = texture(noiseMap, texCoord + vec2(-textureDelta,0)).r;
	float right = texture(noiseMap, texCoord + vec2(textureDelta,0)).r;
	float up = texture(noiseMap, texCoord + vec2(0,textureDelta)).r;
	float down = texture(noiseMap, texCoord + vec2(0,-textureDelta)).r;
	
	vec3 normal = normalize(vec3(left - right,textureDelta * 2, up - down));
	return normalize(normal);
}

vec3 CalcNormal(vec2 texCoord)
{   
	int textureDelta = 1;

	float left = textureOffset(noiseMap, texCoord,  ivec2(-1,0)).r;
	float right = textureOffset(noiseMap,texCoord,  ivec2(1,0)).r;
	float up = textureOffset(noiseMap,   texCoord,  ivec2(0,1)).r;
	float down = textureOffset(noiseMap, texCoord,  ivec2(0,-1)).r;
	
	vec3 normal = vec3(left - right, 2.0, up - down);
	return normalize(normal);
}

vec3 triplanar_sample(vec3 N, vec3 uvw, sampler2D tex)
{
	float tighten = 0.4679;
	vec3 blending = normalize(clamp(abs(N) - tighten,0.0,1.0));
	
	float b = blending.x + blending.y + blending.z;
	blending /= vec3(b,b,b);
	
	vec3 x = texture(tex, uvw.yz/10.0f).rgb;
	vec3 y = texture(tex, uvw.xz/10.0f).rgb;
	vec3 z = texture(tex, uvw.xy/10.0f).rgb;

	return x * blending.x + y * blending.y + blending.z * z;
}

vec3 GetDiffuse(vec3 texCoord,float height, vec3 N, vec2 tex,float slope)
{
	vec3 color;
	if(height < 0.2f || slope < 0.3f)
	{	
	color = texture(meadowDiffuse,tex * 32.0f).rgb;
	return color;
	}
	else if(slope <= 0.6f)
	{
	vec3 col1 = texture(meadowDiffuse, tex * 32.0f).rgb;
	vec3 col2 =  triplanar_sample(N, texCoord, sandDiffuse);
	float delta = 0.6 - 0.3;
	float factor = (slope - 0.3)/delta;
	color = mix(col1,col2,factor);
	return color;
	}
	else if(slope > 0.6f)
	{
	color =  triplanar_sample(N, texCoord, sandDiffuse);
	return color;
	}
	return color;
}

vec3 GetNormal(vec3 texCoord, float height, vec3 N,vec2 tex,float slope)
{
	vec3 color;
	if(height < 0.2f || slope < 0.3f)
	{	
	color = texture(meadowNormal,tex * 32.0f).rgb;
	return color;
	}
	else if(slope <= 0.6f)
	{
	vec3 col1 = texture(meadowNormal, tex * 32.0f).rgb;
	vec3 col2 =  triplanar_sample(N, texCoord, sandNormal);
	float delta = 0.6 - 0.3;
	float factor = (slope - 0.3)/delta;
	color = mix(col1,col2,factor);
	return color;
	}
	else if(slope > 0.6f)
	{
	color =  triplanar_sample(N, texCoord, sandNormal);
	return color;
	}
	return color;
}

vec3 getNormalFromMap(vec3 normal,vec2 TexCoords, vec3 WorldPos, vec3 N)
{
	vec3 tangentNormal = normal * 2.0f - 1.0f;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 Q2perp = cross(Q2,N);
	vec3 Q1perp = cross(N,Q1);

	vec3 T = Q2perp * st1.x + Q1perp * st2.x;
	vec3 B = Q2perp * st1.y + Q1perp * st2.y;

	float InvMax = inversesqrt(max(dot(T,T),dot(B,B)));
	mat3 TBN = mat3(T * InvMax, B* InvMax, N);
    return normalize(TBN * tangentNormal);
}

float ShadowCalc(vec4 fragLight, vec3 normal, vec3 lightDir)
{
	return 0.1f;
}

void main()
{
	vec3 N = CalcSlopeNormal(tes_in.texCoord);
	float slope = 1.0f - N.y;

	vec3 color = GetDiffuse(tes_in.fragPos.xyz,tes_in.height,N,tes_in.texCoord,slope);
	vec3 normalTex = GetNormal(tes_in.fragPos.xyz,tes_in.height,N,tes_in.texCoord,slope);
	
	vec3 viewDir = normalize(cameraPos.xyz - tes_in.fragPos.xyz);
	float specv = 0.1f;

	vec3 ambient = 0.3 * lightColor;

	vec3 lightDir = normalize(lightDirection);

	vec3 normal = getNormalFromMap(normalTex, tes_in.texCoord, tes_in.fragPos.xyz,N);
	float diff = max(dot(lightDir,normal),0.0);

	vec3 diffuse = diff * lightColor;
	
	vec3 reflectDir = reflect(-lightDir, normal);
	
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);

	vec3 lightSpec = vec3(0.3,0.3,0.3);
	vec3 specular = lightSpec * spec * 0.0001;
	float shadow = ShadowCalc(tes_in.fragPosLightSpace, N, lightDir);

	//float3 col = float3(ambient + shadow * (diffuse + specular)) * color;
	vec3 col = vec3(ambient + diffuse + shadow) * color;
	FragColor = vec4(col.xyz, 1.0f);
	//FragColor = texture(meadowDiffuse, tes_in.texCoord * 32.0f);
	FragColor *= 15.0f;
	FragColor = vec4(N.xyz,1.0f);
}