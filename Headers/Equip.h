#pragma once
#include"Def.h"
#include"UpdateComponent.h"
class Equip :public UpdateComponent {
	WPtr<Actor> m_player,m_sprite;
public:
	Equip(Ptr<Actor> _player_ptr, Ptr<Actor> _sprite_ptr,Ptr<Actor> _actor_ptr);
	virtual void Update();
	static bool DestroyNowEquip();//すでに武器を装備していた場合，それを削除
};
