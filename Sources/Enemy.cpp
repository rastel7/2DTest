#include"Enemy.h"
#include"Actor.h"
#include"Stage.h"
#include"PlayerComponent.h"
Enemy::Enemy(const int _HP, const int _EXP, Ptr<Actor> _ptr) :DrawComponent(_ptr),hp(_HP) ,exp(_EXP) {
	mactorptr.lock()->SetActorType(ActorType::ENEMY);
	
}
void Enemy::DecreseHP(int _hp) {
	hp -= _hp;
	if (hp <= 0) {
		hp = 100000000;
		mactorptr.lock()->CanRemove = true;
		if (auto player = mactorptr.lock()->GetStage()->GetComponent<Player>()) {
			player->AddExp(exp);
		}
	}
}
