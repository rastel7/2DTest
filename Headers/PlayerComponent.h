#pragma once
#include"Def.h"
#include"UpdateComponent.h"
#include"Transform.h"
class Actor;
class Player : public UpdateComponent {

public:
	Player(Transform _transform,Ptr<Actor> _ptr);
	virtual ~Player() {};
	void Update() override;
};
