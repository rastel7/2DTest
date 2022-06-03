#include"Enemy.h"
#include"Actor.h"
Enemy::Enemy(const int _HP, Ptr<Actor> _ptr) :DrawComponent(_ptr),hp(_HP) {
	mactorptr.lock()->SetActorType(ActorType::ENEMY);
}
void Enemy::DecreseHP(int _hp) {
	hp -= _hp;
}
