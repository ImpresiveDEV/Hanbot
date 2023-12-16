#pragma once

#include "ImGui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "skStr.h"

class c_globals {
public:
	bool active = true;

	char user_name[255] = "Login"; 
	char pass_word[255] = "Password";
	char license[255] = "License";

	int button_opacity = 255;

} globals;