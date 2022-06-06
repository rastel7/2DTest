#pragma once
#include"Def.h"
#include"Equip.h"
class Stage;
class Actor;
class HandGun : public Equip {
public:
	HandGun(Ptr<Actor> _player_ptr, Ptr<Actor> _actor_ptr);
	void Update() override;
	static void EquipHandGun(WPtr<Actor> _player,Stage* _stage);
};
