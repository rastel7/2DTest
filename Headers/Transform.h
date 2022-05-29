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
	inline void Update(GameSize stage_size) {
		if (m_position.x < 0) {
			m_position.x = stage_size.x;
		}
		if (m_position.y < 0) {
			m_position.y = stage_size.y;
		}
		if (m_position.x > stage_size.x) {
			m_position.x = 0;
		}
		if (m_position.y > stage_size.y) {
			m_position.y = 0;
		}
	}
	friend Component;
};
