#pragma once
#include"Def.h"
#include"UpdateComponent.h"
class Actor;
class Bullet :public UpdateComponent{
protected:
	WPtr<Actor> m_target_enemy;
	int m_damage = 1;
	virtual bool isDelete();
public:
	Bullet(Ptr<Actor> _actor);
	void Update();
};
