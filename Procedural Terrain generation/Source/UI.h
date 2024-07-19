#ifndef UI_H
#define UI_H
#include"../External/imgui/imgui.h"
#include"../External/imgui/imgui_impl_opengl3.h"
#include"../External/imgui/imgui_impl_glfw.h"
#include "General_utility.h"
void SetupUI(bool* p_open);
//opens a native file explorer context to enable anyone to load models
std::string GetPathFromFileDialog();
static void HelpMarker(const char* desc);
#endif