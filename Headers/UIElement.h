#pragma once
#include"Def.h"
#include"UI.h"

class UIElement {
protected:
	WPtr<UI> m_parent;
	int m_priority=0;
	Vec2 screen_position;
public:
	virtual void Draw() const=0;
	inline virtual void Update(){}
	inline UIElement(WPtr<UI> _parent,Vec2 _screen_position,int m_priority = 0 ):m_parent(_parent), screen_position(_screen_position), m_priority(m_priority) {

	}
};