#pragma once
#include"Def.h"
#include"Transform.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
class Actor;
class Collision :public DrawComponent {
	Collision(Ptr<Actor> _actor) :DrawComponent(_actor) {

	}
};
