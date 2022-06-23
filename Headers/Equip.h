#pragma once
#include"Def.h"
#include"UpdateComponent.h"
#include"Transform.h"
class Stage;
class GunEffect;
class Equip :public UpdateComponent {
	WPtr<Actor> m_player;
	GameVec2 m_relativelaunch={0.0f,0.0f};//相対的な発射座標
	std::vector<Ptr<GunEffect>> m_effetcts;
protected:
	float m_bullet_interval = 0.0f;
	float m_length = 0.0f;//武器の長さ
	float m_angle = 0.0f;
	virtual void CreateGunEffect(GameVec2 position, float angle);
public:
	Equip(Ptr<Actor> _player_ptr,Ptr<Actor> _actor_ptr);
	virtual GameVec2 GetBulletFirePosition() const {
		float angle = m_angle;
		GameVec2 bulletposition = GetTransform().m_position;
		bulletposition += (m_length * GameVec2::Right()).rotate(-angle);
		return bulletposition;
	}
	virtual void Update();
	static bool DestroyNowEquip(Stage* _stage);//すでに武器を装備していた場合，それを削除
};
