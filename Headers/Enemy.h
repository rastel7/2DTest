#pragma once
#include"Def.h"
#include"DrawComponent.h"
class Actor;
class Enemy :public DrawComponent{
	int hp = 0;
protected:
	void DecreseHP(int _hp);
public:
	Enemy(const int _HP, Ptr<Actor> _ptr);
};
