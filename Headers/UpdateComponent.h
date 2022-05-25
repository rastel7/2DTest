#pragma once
#include"Def.h"
#include"Component.h"

class UpdateComponent :public Component{
public:
	UpdateComponent(Ptr<Actor> _mactorptr);
	virtual ~UpdateComponent();
	virtual void Update();
};
