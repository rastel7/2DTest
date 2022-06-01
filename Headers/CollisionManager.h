#pragma once
#include"Def.h"
class Collision;
class Stage;
class CollisionManager {
	Stage* m_stage;
public:
	inline CollisionManager(Stage* _stage):m_stage(_stage) {}
};
