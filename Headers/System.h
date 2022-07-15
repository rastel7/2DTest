#pragma once
#include"Def.h"
//システム関係

namespace mySystem {
	void Initialize();
	Point GetViewportPoint(float x, float y);
	std::vector<String> split(String _str, char32_t deli);
};
