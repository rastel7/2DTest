#pragma once
#include"Def.h"
class Component;
class Transform {
	Vector2D<float> m_position;
public:
	Transform();
	template<class T>
	Transform(T x, T y);
	friend Component;
};
