#pragma once
#include"Def.h"
class Component;
class Transform {
public:
	GameVec2 m_position;
	Transform();
	inline Transform(GameVec2 _gv2):m_position(_gv2) {}
	template<class T>
	inline Transform(T x, T y) :m_position(float(x), float(y)) {

	}

	friend Component;
};
