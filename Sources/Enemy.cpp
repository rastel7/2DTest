#include"Enemy.h"

Enemy::Enemy(const int _HP, Ptr<Actor> _ptr) :DrawComponent(_ptr),hp(_HP) {

}
void Enemy::DecreseHP(int _hp) {
	hp -= _hp;
}
