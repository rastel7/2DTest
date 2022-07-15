#include"Bullet.h"
#include"Actor.h"
#include"Enemy.h"
Bullet::Bullet(Ptr<Actor> _actor) :UpdateComponent(_actor) {
	mactorptr.lock()->SetActorType(ActorType::PLAYER_BULLET);
}
void Bullet::Update() {

}

bool Bullet::isDelete() {
	return false;
}

void Bullet::AddDamage(Ptr<Actor> _enemy){
	if (auto enemy_component = _enemy->GetComponent<Enemy>()) {
		enemy_component->DecreseHP(m_damage);
	}
	mactorptr.lock()->CanRemove = true;
}