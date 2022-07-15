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
	m_length = 0.4f;
}

void HandGun::Update() {
	Equip::Update();
	
	if (inputmanager.GetPressed(PadButtonNumber::Ok)&&m_bullet_interval<=0.0f) {
		remain_bullet--;
		if (remain_bullet < 0)remain_bullet = default_max_bullet;
		m_bullet_interval = 1.0f;
		float angle=m_angle;
		auto dir = GameVec2(Math::Cos(angle), -Math::Sin(angle));
		float speed = 5.0f;
		float damage = 1;
		GameVec2 bulletposition = GetBulletFirePosition();
		HandGunBullet::CreateBullet(bulletposition,dir, speed, damage, mactorptr.lock()->GetStage());
		CreateGunEffect(bulletposition, angle);
	}
}

void HandGun::EquipHandGun(WPtr<Actor> _player, Stage* _stage) {
	
	auto gun = std::make_shared<Actor>(_stage);
	gun->name = U"HandGun";
	auto handgun_ptr = (std::make_shared<HandGun>(_player.lock(), gun));
	handgun_ptr->default_max_bullet = handgun_ptr->remain_bullet = 6;
	gun->AddComponent(handgun_ptr);
	gun->AddComponent(Ptr<Component>(std::make_shared<BulletGauge>(handgun_ptr,gun)));
	_stage->AddActor(gun);
}
