#pragma once
#include"Def.h"
#include"UpdateComponent.h"
class Actor;
class RigidBody :public UpdateComponent {
public:
	RigidBody(Ptr<Actor> _actor);
};
