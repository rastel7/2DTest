#pragma once
#include"Def.h"
#include"Enemy.h"
class Actor;
class Stage;
class Slime:public Enemy {
public:
	inline Slime(Ptr<Actor> _ptr,int HP=1,int EXP=1) :Enemy(HP, EXP,_ptr) {};
	static void CreateSlime(Stage* _stage);
};
