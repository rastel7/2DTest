﻿#pragma once
#include"Def.h"
class Actor;
class Transform;
class Component {
protected:
	Ptr<Actor> mactorptr;
	Component();
public:
	Component(Ptr<Actor> _mactorptr);
	virtual ~Component();
	bool operator>(Component const& r);
	bool operator<(Component const& r);
	String name;
	__int8  mpriority=0;
	__int8 GetPriority() const;
	Transform GetTransform() const;
};

