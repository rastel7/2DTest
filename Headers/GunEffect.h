#pragma once
#include"Def.h"
#include"UpdateComponent.h"
class Actor;
class GunEffect :public UpdateComponent {
	const float m_interval = 0.04f;
	float m_time = 0.0f;
	u_int16 id = 0;
public:
	GunEffect(GameVec2 _position,float _rotate,Ptr<Actor> _mactorptr);
	void Update() override;
};