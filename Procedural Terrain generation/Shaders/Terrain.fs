uniform Sampler2D noiseMap;

vec3 CalcSlopeNormal(vec2 texCoord)
{   
	float textureDelta = 1/256.0;

	float left = SampleLvlTex2D(Get(NoiseText), Get(NoiseSampler), texCoord + float2(-textureDelta,0),0).r;
	float right = SampleLvlTex2D(Get(NoiseText), Get(NoiseSampler), texCoord + float2(textureDelta,0),0).r;
    float up = SampleLvlTex2D(Get(NoiseText), Get(NoiseSampler), texCoord + float2(0,textureDelta),0).r;
	float down = SampleLvlTex2D(Get(NoiseText), Get(NoiseSampler), texCoord + float2(0,-textureDelta),0).r;
	
	float3 normal = float3(left - right,textureDelta * 2, up - down );
	return normalize(normal);
}

float3 CalcNormal(float2 texCoord)
{   
	int textureDelta = 1;

	float left = SampleLvlOffsetTex2D(Get(NoiseText), Get(NoiseSampler), texCoord, 0, int2(-1,0)).r;
	float right = SampleLvlOffsetTex2D(Get(NoiseText), Get(NoiseSampler),texCoord, 0, int2(1,0)).r;
    float up = SampleLvlOffsetTex2D(Get(NoiseText), Get(NoiseSampler),   texCoord, 0, int2(0,1)).r;
	float down = SampleLvlOffsetTex2D(Get(NoiseText), Get(NoiseSampler), texCoord, 0, int2(0,-1)).r;
	
	float3 normal = float3((left - right),2,(up - down));
	return normalize(normal);
}