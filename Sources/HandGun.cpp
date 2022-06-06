#include"HandGun.h"
#include"Actor.h"
#include"SpriteRenderer.h"
#include"Stage.h"
#include"HandGunBullet.h"
HandGun::HandGun(Ptr<Actor> _player_ptr, Ptr<Actor> _actor_ptr)
	:Equip(_player_ptr,_actor_ptr)
{
	auto sprite_component = (std::make_shared<Sprite>(U"HandGun", 48, 64, mactorptr.lock()));
	sprite_component->mpriority = 100;
	sprite_component->SetisRotated(true);
	mactorptr.lock()->AddComponent(Ptr<Component>(sprite_component));
	mactorptr.lock()->name = U"HandGunBullet";
}

void HandGun::Update() {
	Equip::Update();
	if (inputmanager.GetPressed(PadButtonNumber::Ok)) {
		float angle=m_angle;
		auto dir = GameVec2(Math::Cos(angle), -Math::Sin(angle));
		float speed = 5.0f;
		float damage = 1;
		GameVec2 position = GetTransform().m_position;
		HandGunBullet::CreateBullet(position,dir, speed, damage, mactorptr.lock()->GetStage());
	}
}

void HandGun::EquipHandGun(WPtr<Actor> _player, Stage* _stage) {
	
	auto gun = std::make_shared<Actor>(_stage);
	gun->name = U"HandGun";
	gun->AddComponent(Ptr<Component>(std::make_shared<HandGun>(_player.lock(), gun)));
	_stage->AddActor(gun);
}
