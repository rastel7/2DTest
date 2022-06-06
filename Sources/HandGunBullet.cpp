#include"HandGunBullet.h"
#include"Actor.h"
#include"Stage.h"
#include"SpriteRenderer.h"
#include"Collision.h"
#include"Enemy.h"
HandGunBullet::HandGunBullet(GameVec2 _position,GameVec2 _direction, float _speed, int _damage, Ptr<Actor> _actor)
	:Bullet(_actor),
	m_direction(_direction),
	m_speed(_speed)
{
	//todo collisionを持たせる
	m_damage = _damage;
	mactorptr.lock()->AddComponent(Ptr<Component>(std::make_shared<Sprite>(U"Bullet_0",20,20,mactorptr.lock())));
	mactorptr.lock()->SetTransform(_position);
}

void HandGunBullet::Update() {
	auto position = GetTransform().m_position;
	position += m_direction * m_speed * Scene::DeltaTime();
	SetTransform(position);
	UpdateEnemyDamege();
}

void HandGunBullet::CreateBullet(GameVec2 _position,GameVec2 _direction, float _speed, int damage,Stage *stage) {
	if (stage == nullptr) {
		throw U"nullptrが渡されています";
	}
	auto actor = std::make_shared<Actor>(stage);
	actor->AddComponent(Ptr<Component>(std::make_shared<HandGunBullet>(_position,_direction, _speed, damage, actor)));
	stage->AddActor(actor);
}

void HandGunBullet::UpdateEnemyDamege() {
	if (auto enemy = m_target_enemy.lock()) {
		auto enemy_comp = enemy->GetComponent<Enemy>();
		if (enemy_comp->GetHP() <= 0)return;
	}
}
