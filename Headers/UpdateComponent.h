#pragma once
#include"Def.h"
#include"Component.h"

class UpdateComponent :public Component{
	UpdateComponent();
public:
	UpdateComponent(Ptr<Actor> _mactorptr);
	virtual ~UpdateComponent();
	virtual void Update();
};
