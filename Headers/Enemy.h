#pragma once
#include"Def.h"
#include"DrawComponent.h"
class Actor;
class Enemy :public DrawComponent{
	int hp = 0;
protected:
public:
	inline int GetHP() const { return hp; }
	void DecreseHP(int _hp);
	Enemy(const int _HP, Ptr<Actor> _ptr);
};
