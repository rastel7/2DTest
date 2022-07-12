#pragma once
#include"UIElement.h"
#include"UI.h"
class Card :public UIElement {
	void Draw() const override;
	Card() = delete;
	String m_path;
public:
	Card(String _path,WPtr<UI> _parent,Vec2 _screen_position,int _priority=0);
};