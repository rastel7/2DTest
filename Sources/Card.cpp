#include"Def.h"
#include"Card.h"
#include"UIElement.h"
#include"UI.h"
#include"System.h"
#include"Stage.h"
void Card::Draw() const{

	auto font = fontmanager.Get(U"card-normal");
	const auto center = mySystem::GetViewportPoint(screen_position.x,screen_position.y);
	const auto CARD_WIDTH= mySystem::GetViewportPoint(WIDTH, HEIGHT);
	auto card_rect = Rect{ center.x - CARD_WIDTH.x / 2,center.y - CARD_WIDTH.y / 2,CARD_WIDTH.x,CARD_WIDTH.y };
	if (isSelected) {
		auto back_rect = card_rect;
		back_rect.x -= CURSOR_THICK;
		back_rect.y -= CURSOR_THICK;
		back_rect.w += 2 * CURSOR_THICK;
		back_rect.h += 2 * CURSOR_THICK;
		back_rect.rounded(5).draw(ColorF(0.7, 0.2, 0.2));
	}
	card_rect.draw(ColorF(0.3, 0.3, 0.3));
	auto font_size = font.fontSize();
	font(m_cardparam->name).draw(center.x - CARD_WIDTH.x / 2, center.y - CARD_WIDTH.y / 2 );
	auto small_font= fontmanager.Get(U"card-small",Const::DEFAULT_FONT_SIZE/2);
	const auto desc_rect = Rect{ center.x - CARD_WIDTH.x/2,center.y - CARD_WIDTH.y/2 + font_size,CARD_WIDTH.x,CARD_WIDTH.y - font_size };
	small_font(m_cardparam->description).draw(desc_rect);
}

void Card::Update() {
	m_cardparam->GiveEffect();
}

Card::Card(String _path, WPtr<UI> _parent, Vec2 _screen_position, int _priority)
	:m_path(_path),
	UIElement(_parent, _screen_position, _priority)
{
	if (auto ptr = m_parent.lock()) {
		m_cardparam = (std::make_shared<CardParameter>(ptr->GetStage()->m_cardeffects));
	}
	else {
		throw Error{ U"Card‚Ìˆø”‚Ìparent‚ª•s³‚Å‚·" };
	}
	const INI ini{ Const::CARD_PATH+m_path};
	if (not ini) {
		throw Error{ U"Failed to load" + m_path };
	}
	for (const auto& section : ini.sections()) {
		m_cardparam->ReadIniParameter(section.section, section.keys);
	}
}