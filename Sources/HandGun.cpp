#include"HandGun.h"
#include"Actor.h"
#include"SpriteRenderer.h"
#include"Stage.h"
HandGun::HandGun(Ptr<Actor> _player_ptr, Ptr<Actor> _actor_ptr)
	:Equip(_player_ptr,_actor_ptr)
{
	auto sprite_component = (std::make_shared<Sprite>(U"HandGun", 48, 64, mactorptr.lock()));
	sprite_component->mpriority = 100;
	mactorptr.lock()->AddComponent(Ptr<Component>(sprite_component));
}

void HandGun::Update() {
	Equip::Update();
}

void HandGun::EquipHandGun(WPtr<Actor> _player, Stage* _stage) {
	
	auto gun = std::make_shared<Actor>(_stage);
	gun->name = U"HandGun";
	gun->AddComponent(Ptr<Component>(std::make_shared<HandGun>(_player.lock(), gun)));
	_stage->AddActor(gun);
}
