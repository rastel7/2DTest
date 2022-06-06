#pragma once
#include"Def.h"
class Component;
class Transform {
public:
	GameVec2 m_position={0,0};
	Transform();
	inline Transform(GameVec2 _gv2):m_position(_gv2) {}
	template<class T>
	inline Transform(T x, T y) :m_position(float(x), float(y)) {

	}
	inline void Update(GameSize const& stage_size) {
		m_position.x = fmod(m_position.x+ stage_size.x, stage_size.x);
		m_position.y = fmod(m_position.y + stage_size.y, stage_size.y);
	}
	friend Component;
};
