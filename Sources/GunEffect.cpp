#pragma once
#include"GunEffect.h"
#include"Actor.h"
#include"SpriteRenderer.h"
GunEffect::GunEffect(GameVec2 _position, float _rotate, Ptr<Actor> _mactorptr):UpdateComponent(_mactorptr) {
	auto sprite = mactorptr.lock()->GetComponent<Sprite>();
	if (sprite == nullptr) {
		sprite = std::make_shared<Sprite>(U"Gun_Effect", 16, 16, mactorptr.lock());
		sprite->SetAngle(_rotate);
		sprite->SetisRotated(true);
		mactorptr.lock()->AddComponent(sprite);
		
	}
	mactorptr.lock()->SetTransform(Transform{ _position.x,_position.y });
	sprite->mpriority = 10;

}

void GunEffect::Update() {
	m_time += Scene::DeltaTime();
	if (m_time > m_interval) {
		m_time = 0;
		auto sprite = mactorptr.lock()->GetComponent<Sprite>();
		if (sprite == nullptr)return;
		auto max_id = sprite->GetTextureIDSize();
		id++;
		if (id >= max_id) {
			mactorptr.lock()->CanRemove = true;
		}
		sprite->SetTextureID(id);
	}
}