#include"Equip.h"
#include"Stage.h"
#include"Actor.h"
#include"SpriteRenderer.h"
#include"GunEffect.h"
#include"Transform.h"
Equip::Equip(Ptr<Actor> _player_ptr, Ptr<Actor> _actor_ptr):UpdateComponent(_actor_ptr),m_player(_player_ptr) {

}

void Equip::Update() {
	mactorptr.lock()->SetTransform(m_player.lock()->GetTransform());
	if (m_bullet_interval > 0) {
		m_bullet_interval -= Scene::DeltaTime();
	}
	if (inputmanager.GetRightPad().length() >= 0.2f) {
		auto sprite = mactorptr.lock()->GetComponent<Sprite>();
		if (sprite != nullptr) {
			auto angle = inputmanager.GetRightPad().getAngle()-Math::PiF/2.0f;
			m_angle = angle;
			sprite->SetAngle(angle);
		}
	}

	{//エフェクト配列の削除
		auto ptr = std::remove_if(m_effetcts.begin(),m_effetcts.end(), [&](Ptr<GunEffect> l) {
			try {
				auto actor = l->GetActor().lock();
				if (!actor) {
					return true;
				}
				if (actor->CanRemove) {
					return true;
				}
			}
			catch (...) {
				return true;
			}
			l->SetTransform(GetBulletFirePosition());
			return false;
		});
		m_effetcts.erase(ptr, m_effetcts.end());
	}
	//最大弾数の更新
	SetMaxBullet();
}

bool Equip::DestroyNowEquip(Stage* _stage) {
	auto equips = _stage->GetActors(ActorType::EQUIP);
	for (auto ptr : equips) {
		ptr.lock()->CanRemove = true;
	}
	return true;
}

void Equip::CreateGunEffect(GameVec2 position,float angle) {
	auto obj= std::make_shared<Actor>(m_player.lock()->GetStage());
	auto effect = std::make_shared<GunEffect>(position, angle, obj);
	m_effetcts.emplace_back(effect);
	obj->AddComponent(effect);
	m_player.lock()->GetStage()->AddActor(obj);
}

void Equip::DrawRemainBullet() const {
	Transform player_position;
	if (auto ptr = m_player.lock()) {
		player_position = ptr->GetTransform();
	}
	else {
		return;
	}
	//左上にずらす
	player_position.m_position -= GameVec2(0.5f, -0.5f);
	auto screen_position = m_player.lock()->GetStage()->GamePositiontoWorldPosition(player_position.m_position);
	float radius = 10.0f;
	float deg = Math::TwoPiF;
	if (max_bullet != 0) {
		deg = Math::TwoPiF *((float)remain_bullet / max_bullet);
	}
	Print << remain_bullet;
	Print << deg;
	Circle{ screen_position,radius }.drawArc(0, 360.0f, 0, radius*0.05f,ColorF(0.0f,0.0f,0.0f));
	Circle{ screen_position,radius }.drawArc(0, 360.0f, radius * 0.2, 0);
	Circle{ screen_position,radius }.drawArc(0, deg,radius*0.2,0,ColorF(0.2f,0.8f,0.2f));
}

void  Equip::SetMaxBullet() {
	float per = (float)(mactorptr.lock()->GetStage()->m_cardeffects->GetMaxBullet()*0.1f +1.0f) ;
	float _mx_bulletf = default_max_bullet * per;
	max_bullet = round(_mx_bulletf);
}

BulletGauge::BulletGauge(Ptr<Equip> _equip, Ptr<Actor> _mactorptr):DrawComponent(_mactorptr),m_equip(_equip) {
	DrawComponent::mpriority = 10;
}

void BulletGauge::Draw() {
	if (auto ptr = m_equip.lock()) {
		ptr->DrawRemainBullet();
	}
}