#pragma once
#include"Def.h"
#include"UpdateComponent.h"
class Actor;
class FollowPlayer :public UpdateComponent {
	float speed = 1.0f;
public:
	inline FollowPlayer(Ptr<Actor> _actor):UpdateComponent(_actor) {}
	void Update() override;
};
