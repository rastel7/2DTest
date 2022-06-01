#pragma once
#include"Def.h"
class Collision;
class Stage;
class CollisionManager {
	Stage* stage;
	std::vector<std::pair<double,Ptr<Collision>>> colls;
	std::vector<WPtr<Collision>> collisions_wptr;
public:
	bool Cmp(const Ptr<Collision>& l, const Ptr<Collision>& r);
	inline CollisionManager(Stage* _stage) :stage(_stage) {

	}
	std::vector<Ptr<Collision>> GetNearCollision(Ptr<Collision> col) const;
	void Update();
	inline void AddCollision(WPtr<Collision> const& ptr) {
		collisions_wptr.emplace_back(ptr);
	}
	inline void EraseCollision(WPtr<Collision> const& ptr) {
		if (auto pt=ptr.lock()) {
			for (int i = 0; i < collisions_wptr.size(); ++i) {
				if (auto p = collisions_wptr[i].lock()) {
					if (pt == p) {
						collisions_wptr.erase(collisions_wptr.begin() + i);
						return;
					}
				}
			}
		}
	}

	void Update_WPtrs();
};
