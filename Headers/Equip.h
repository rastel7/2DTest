#pragma once
#include"Def.h"
#include"UpdateComponent.h"
class Stage;
class Equip :public UpdateComponent {
	WPtr<Actor> m_player;
	GameVec2 m_relativelaunch={0.0f,0.0f};//相対的な発射座標
protected:
	float m_angle = 0;
public:
	Equip(Ptr<Actor> _player_ptr,Ptr<Actor> _actor_ptr);
	virtual void Update();
	static bool DestroyNowEquip(Stage* _stage);//すでに武器を装備していた場合，それを削除
};
