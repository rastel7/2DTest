#include"Def.h"
#include"FontManager.h"

Font FontManager::Get(String s_name) {
	if (!m_fontmap.count(s_name)) {
		m_fontmap[s_name]=Font(Const::DEFAULT_FONT_SIZE);
	}
	return m_fontmap[s_name];
}

void FontManager::Set(String s_name, int size) {
	m_fontmap[s_name] = Font(size);
}
