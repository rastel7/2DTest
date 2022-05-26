#pragma once
#include"Def.h"
#include"DrawComponent.h"
class Actor;
class Collision :public DrawComponent{
	Vec2 m_size;
public:
	Collision(Vec2 _size, Ptr<Actor> _ptr);
	void Draw() const override;
};
