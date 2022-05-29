#pragma once
#include"Def.h"
class Collision;
class Stage;
class CollisionManager {
	Stage* stage;
	std::vector<std::pair<double,Ptr<Collision>>> colls;
public:
	bool Cmp(const Ptr<Collision>& l, const Ptr<Collision>& r);
	inline CollisionManager(Stage* _stage) :stage(_stage) {

	}
	std::vector<Ptr<Collision>> GetNearCollision(Ptr<Collision> col) const;
	void Update();
};
