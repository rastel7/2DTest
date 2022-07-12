#pragma once
#include"UIElement.h"
#include"UI.h"
struct CardParameter {
	String name=U"NONE", description = U"NONE";
	void ReadIniParameter(String const& section, Array<INIKey> const& keys);
};

class Card :public UIElement {
	const float WIDTH = 0.2f, HEIGHT = 0.4f;
	Ptr<CardParameter> m_cardparam;
	void Draw() const override;
	Card() = delete;
	String m_path;
public:
	Card(String _path,WPtr<UI> _parent,Vec2 _screen_position,int _priority=0);
};