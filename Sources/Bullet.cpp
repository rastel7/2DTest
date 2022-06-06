#include"Bullet.h"
#include"Actor.h"
Bullet::Bullet(Ptr<Actor> _actor) :UpdateComponent(_actor) {
	mactorptr.lock()->SetActorType(ActorType::PLAYER_BULLET);
}
void Bullet::Update() {

}

bool Bullet::isDelete() {
	return false;
}
