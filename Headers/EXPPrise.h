#pragma once
#include"Def.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
class Stage;
class Collision;
class EXPPrise :public UpdateComponent {
	EXPPrise();
	WPtr<Collision> m_col;
public:
	static const float EXP_APPEARANCE_DIST;
	static void GenerateEXPPrise(Stage* _stage, GameVec2 _position,int _n);
	EXPPrise(Ptr<Actor> _mactorptr);
	virtual void Update() override final;
	virtual ~EXPPrise() final;
	int GetEXP() const;
};