#include<vector>
#include"UI.h"
#include "Terrain.h"
#include"Shadow.h"

using namespace std::literals::string_literals;

//directly read display and edit lighting values
void setLights(glm::vec3& lightValues);

void SetupUI(bool* p_open, Terrain& terrain)
{
    ImGuiWindowFlags window_flags = 0;

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, main_viewport->WorkSize.y - main_viewport->WorkSize.y/2.0f), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Procedural terrain demo", p_open, window_flags))
    {
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("FBMs"))
    {
        if (ImGui::TreeNode("Noise Texture 1"))
        {
            GLfloat offset[2] = { terrain.map.noise1._offset.r,terrain.map.noise1._offset.g };
            ImGui::SliderInt("Octaves", &terrain.map.noise1.octaves, 1, 8);
            ImGui::SliderFloat("Persistence", &terrain.map.noise1.scale, 0.0001, 10.0f);
            ImGui::SliderFloat("Lacunarity", &terrain.map.noise1.scale, 0.0001, 10.0f);
            ImGui::SliderFloat2("Offset", offset, -100.0f, 100.0f);
            ImGui::SliderInt("Seed", &terrain.map.noise1.seed, 1, 8);
            ImGui::SliderFloat("Scale", &terrain.map.noise1.scale, 0.0, 50.0f);
            terrain.map.noise1._offset = glm::vec2(offset[0], offset[1]);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Noise Texture 2"))
        {
            GLfloat offset[2] = { terrain.map.noise2._offset.r,terrain.map.noise2._offset.g };
            ImGui::SliderInt("Octaves", &terrain.map.noise2.octaves, 1, 8);
            ImGui::SliderFloat("Persistence", &terrain.map.noise2.scale, 0.0001, 10.0f);
            ImGui::SliderFloat("Lacunarity", &terrain.map.noise2.scale, 0.0001, 10.0f);
            ImGui::SliderFloat2("Offset", offset, -100.0f, 100.0f);
            ImGui::SliderInt("Seed", &terrain.map.noise2.seed, 1, 8);
            ImGui::SliderFloat("Scale", &terrain.map.noise2.scale, 0.0, 50.0f);
            terrain.map.noise2._offset = glm::vec2(offset[0], offset[1]);
            ImGui::TreePop();
        }
    }
    if (ImGui::CollapsingHeader("Erosion"))
    {
        ImGui::SliderFloat("Inertia", &terrain.erosion.inertia, .1f,3.0f);
        ImGui::SliderFloat("Sediment capacity", &terrain.erosion.sedimentCapacityFactor, .1f, 7.0f);
        ImGui::SliderFloat("Min sediment capacity", &terrain.erosion.minSedimentCapacity, .001f, 3.0f);
        ImGui::SliderFloat("Deposit speed", &terrain.erosion.depositSpeed, .1f, 3.0f);
        ImGui::SliderFloat("Erode speed", &terrain.erosion.erodeSpeed, .1f, 3.0f);
        ImGui::SliderFloat("Evaporate speed", &terrain.erosion.evaportateSpeed, .001f, 1.0f);
        ImGui::SliderFloat("Gravity", &terrain.erosion.gravity, .1f, 8.0f);
        ImGui::SliderFloat("Start speed", &terrain.erosion.startSpeed, .1f, 3.0f);
        ImGui::SliderFloat("Start water", &terrain.erosion.startWater, .1f, 3.0f);
    }

    ImGui::End();

    /*if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::BeginMenu("Open"))
            {
                ImGui::MenuItem("Default", NULL, &openDefault);
                ImGui::MenuItem("New", NULL, &openNew);
                ImGui::EndMenu();
            }
            ImGui::MenuItem("reset", NULL, &reset);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if (ImGui::CollapsingHeader("Shading models"))
    {
        static std::vector<string> models{ "none", "blinn-phong", "pbr" };
        if (ImGui::TreeNode("Active model"))
        {
            static int selected = -1;
            for (int i = 0; i < models.size(); i++)
            {
                if (ImGui::Selectable(models.at(i).c_str(), selected == i))
                {
                    selected = i;
                    Glob::active = active_shading_model{ i };
                }
            }
            ImGui::TreePop();
        }
    }
    if (ImGui::CollapsingHeader("Blinn-phong"))
    {
        string index{};
        if (ImGui::TreeNode("Point Lights"))
        {
            for (size_t i = 0; i < points.size(); i++)
            {
                index = std::to_string(i);
                if (ImGui::TreeNode(("Point "s + index).c_str()))
                {
                    if (ImGui::TreeNode("Positions"))
                    {
                        GLfloat pos[3] = { points[i].position.x, points[i].position.y, points[i].position.z };
                        ImGui::InputFloat3("x,y,z", pos);
                        points[i].position = vec3(pos[0], pos[1], pos[2]);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("ambient"))
                    {
                        //couldn't set a maximum and minimum value for InputFloat3() so this will have to do
                        auto& amb = points[i].ambient;
                        setLights(amb);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("diffuse"))
                    {
                        auto& diff = points[i].diffuse;
                        setLights(diff);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("specular"))
                    {
                        auto& spec = points[i].specular;
                        setLights(spec);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("attenuation"))
                    {
                        //move this declaration to a higher scope later
                        ImGui::SliderFloat("Constant", &points[i].constant, 0.0f, 1.0f);
                        ImGui::SliderFloat("Linear", &points[i].linear, 0.0f, 1.0f);
                        ImGui::SliderFloat("quadratic", &points[i].quadratic, 0.0f, 2.0f );
                        ImGui::TreePop();
                        ImGui::Spacing();

                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Spot Lights"))
        {
            for (size_t i = 0; i < spots.size(); i++)
            {
                index = std::to_string(i);
                if (ImGui::TreeNode(("Spots "s + index).c_str()))
                {
                    if (ImGui::TreeNode("Positions and Direction"))
                    {
                        GLfloat pos[6] = { spots[i].position.x, spots[i].position.y, spots[i].position.z, spots[i].direction.x,
                            spots[i].direction.y, spots[i].direction.z };
                            ImGui::InputFloat3("pos", pos);
                            ImGui::InputFloat3("dir", &pos[3]);
                            spots[i].position = glm::vec3(pos[0], pos[1], pos[2]);
                            spots[i].direction = glm::vec3(pos[3], pos[4], pos[5]);
                            ImGui::TreePop();
                            ImGui::Spacing();
                    }
                    if (ImGui::TreeNode(("ambient"s + index).c_str()))
                    {
                        //couldn't set a maximum and minimum value for InputFloat3() so this will have to do
                        auto& amb = spots[i].ambient;
                        setLights(amb);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("diffuse"))
                    {
                        auto& diff = spots[i].diffuse;
                        setLights(diff);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("specular"))
                    {
                        auto& spec = spots[i].specular;
                        setLights(spec);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("attenuation"))
                    {
                        //move this declaration to a higher scope later
                        ImGui::SliderFloat("Constant", &spots[i].constant, 0.0f, 1.0f, "&.05f");
                        ImGui::SliderFloat("Linear", &spots[i].linear, 0.0f, 1.0f, "&.05f");
                        ImGui::SliderFloat("quadratic", &spots[i].quadratic, 0.0f, 1.0f, "&.05f");
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    if (ImGui::TreeNode("Cutoff"))
                    {
                        ImGui::SliderFloat("Cutoff", &spots[i].cutOff, 0.0f, 1.0f);
                        ImGui::SliderFloat("outerCutoff", &spots[i].OuterCutoff, 0.0f, 1.0f);
                        ImGui::TreePop();
                        ImGui::Spacing();
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Direct Light"))
        {
            static GLfloat pos[3] = { direct.direction.x, direct.direction.y, direct.direction.z };
            ImGui::InputFloat3("x,y,z", pos);
            direct.direction = vec3(pos[0], pos[1], pos[2]);
            ImGui::SeparatorText("ambient");

            static std::vector<GLfloat> amb{ 0.2f,0.2f,0.2f };
            ImGui::InputFloat3("R,G,B amb", amb.data());
            direct.diffuse = vec3(amb.at(0), amb.at(1), amb.at(2));
            

            ImGui::SeparatorText("diffuse");
            static std::vector<GLfloat> diff{0.5f,0.5f,0.5f};
            ImGui::InputFloat3("R,G,B diff", diff.data());
            direct.diffuse = vec3(diff.at(0), diff.at(1), diff.at(2));

            ImGui::SeparatorText("specular");
            static std::vector<GLfloat> spec{1.0f,1.0f,1.0f};
            ImGui::InputFloat3("R,G,B spec", spec.data());
            direct.specular = vec3(spec.at(0), spec.at(1), spec.at(2));
            ImGui::Spacing();
            ImGui::Checkbox("Display shadow", &Shadow_values::shadow);
            ImGui::TreePop();
            ImGui::Spacing();
        }
        if (ImGui::TreeNode("Material"))
        {
            ImGui::InputFloat("Shine", &shine, 0.0, 512.0);
            ImGui::TreePop();
            ImGui::Spacing();
        }
    }
    if (ImGui::CollapsingHeader("Advanced Options"))
    {
        ImGui::SeparatorText("Gamma correction");
        ImGui::SliderFloat("Gamma", &Light_values::gamma, 2.0, 3.0f);
        ImGui::Spacing();
        ImGui::SeparatorText("HDR");
        ImGui::Checkbox("HDR", &Light_values::hdr);
        ImGui::Spacing();
        ImGui::SeparatorText("Bloom");
        ImGui::Checkbox("Bloom", &Light_values::bloom);
        ImGui::Spacing();
        ImGui::SliderFloat("Exposure", &Light_values::exposure, 0.0, 15.0f);
        ImGui::Spacing();
    }
    ImGui::End();
    */
}

/*string GetPathFromFileDialog()
{
   nfdchar_t* path = nullptr;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &path);

    if (result == NFD_OKAY)
    {
        string ret = path;
    }
    else if(result == NFD_CANCEL)
    {

    }
    else
    {
        Log(string(NFD_GetError()));
        return "E";
    }
    
}
*/

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void setLights(glm::vec3& lightValues)
{
    ImGui::InputFloat("R", &lightValues[0], 0.00f, 1.0f);
    ImGui::InputFloat("G", &lightValues[1], 0.00f, 1.0f);
    ImGui::InputFloat("B", &lightValues[2], 0.00f, 1.0f);
}