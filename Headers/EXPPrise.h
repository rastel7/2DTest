#pragma once
#include"Def.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
class Stage;
class Collision;
class EXPPrise :public UpdateComponent {
	EXPPrise();
	WPtr<Collision> m_col;
	const float SPEED = 2.0f;
	const float GETDIST = 0.2f;
public:
	static const float EXP_APPEARANCE_DIST;
	static void GenerateEXPPrise(Stage* _stage, GameVec2 _position,int _n);
	EXPPrise(Ptr<Actor> _mactorptr);
	virtual void Update() override final;
	virtual ~EXPPrise() final;
	int GetEXP() const;
	float GetSpeed() const;
	float GetGetDist() const;
};