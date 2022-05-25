#pragma once
#include"Def.h"
class Actor;
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
};

bool CompPtrComponent(Ptr<Component>const& l, Ptr<Component> const& r);
