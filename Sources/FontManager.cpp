#include"Def.h"
#include"FontManager.h"

Font FontManager::Get(String s_name,int font_size) {
	if (font_size < 0) font_size = Const::DEFAULT_FONT_SIZE;
	if (!m_fontmap.count(s_name)) {
		m_fontmap[s_name]=Font(font_size);
	}
	return m_fontmap[s_name];
}

void FontManager::Set(String s_name, int size) {
	m_fontmap[s_name] = Font(size);
}
