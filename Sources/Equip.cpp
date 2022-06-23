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