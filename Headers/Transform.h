#pragma once
#include"Def.h"
class Component;
class Transform {
public:
	Vector2D<float> m_position;
	Transform();
	template<class T>
	inline Transform(T x, T y) :m_position(float(x), float(y)) {

	}

	friend Component;
};
