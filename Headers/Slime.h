#pragma once
#include"Def.h"
#include"Enemy.h"
class Actor;
class Stage;
class Slime:public Enemy {
public:
	inline Slime(Ptr<Actor> _ptr,int HP=10) :Enemy(HP,_ptr) {};
	static void CreateSlime(Stage* _stage);
};
