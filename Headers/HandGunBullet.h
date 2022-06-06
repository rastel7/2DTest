#pragma once
#include"Def.h"
#include"Bullet.h"
class Actor;
class Stage;
class HandGunBullet :public Bullet {
	GameVec2 m_direction;
	float m_speed;
	const float m_radius = 10.0f;
	void Update() override;
	virtual void UpdateEnemyDamege();
public:
	static void CreateBullet(GameVec2 _position,GameVec2 _direction, float _speed, int damage, Stage* stage);
	HandGunBullet(GameVec2 _position,GameVec2 _direction,float _speed,int damage,Ptr<Actor> _actor);
};
