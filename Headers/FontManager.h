#pragma once
#include"Def.h"

class FontManager {
	std::map<String, Font> m_fontmap;
public:
	Font Get(String s_type);
	void Set(String font_name, int size);
};
