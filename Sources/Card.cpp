#include"Def.h"
#include"Card.h"
#include"UIElement.h"
#include"UI.h"
#include"System.h"
void Card::Draw() const{
	auto font = fontmanager.Get(U"card-normal");
	const auto center = mySystem::GetViewportPoint(screen_position.x,screen_position.y);
	const auto CARD_WIDTH= mySystem::GetViewportPoint(WIDTH, HEIGHT);
	Rect{ center.x - CARD_WIDTH.x,center.y - CARD_WIDTH.y,CARD_WIDTH.x,CARD_WIDTH.y }.draw();
	auto font_size = font.fontSize();
	font(m_cardparam->name).drawBase(center.x - WIDTH / 2.0f, center.y - HEIGHT / 2.0f - font_size);
	const auto desc_rect = Rect{ center.x - CARD_WIDTH.x,center.y - CARD_WIDTH.y - font_size,CARD_WIDTH.x,CARD_WIDTH.y - font_size };
	font(m_cardparam->description).draw(desc_rect);
}

Card::Card(String _path, WPtr<UI> _parent, Vec2 _screen_position, int _priority):m_path(_path),UIElement(_parent,_screen_position,_priority) , m_cardparam(std::make_shared<CardParameter>()) {
	const INI ini{ U"example/ini/config.ini" };
	if (not ini) {
		throw Error{ U"Failed to load" + m_path };
	}
	for (const auto& section : ini.sections()) {
		m_cardparam->ReadIniParameter(section.section, section.keys);
	}
}