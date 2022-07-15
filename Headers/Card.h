#pragma once
#include"UIElement.h"
#include"UI.h"
#include"CardEffects.h"
struct CardParameter {
	int max_bullet=0;
	String name=U"NONE", description = U"NONE";
	inline CardParameter(Ptr<CardEffects> _cardeffects):m_cardeffects(_cardeffects) {}
	void ReadIniParameter(String const& section, Array<INIKey> const& keys);
	void GiveEffect();//カード効果を適用
private:
	WPtr<CardEffects> m_cardeffects;
	int ParseInt(String const& str);
};

class Card :public UIElement {
	const float WIDTH = 0.20f, HEIGHT = 0.4f,CURSOR_THICK=3.0f;
	Ptr<CardParameter> m_cardparam;
	Card() = delete;
	String m_path;
public:
	bool isSelected = true;
	Card(String _path,WPtr<UI> _parent,Vec2 _screen_position,int _priority=0);
	void Draw() const override;
	void Update() override;
};