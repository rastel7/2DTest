#include"Equip.h"
#include"Stage.h"
#include"Actor.h"
#include"SpriteRenderer.h"
Equip::Equip(Ptr<Actor> _player_ptr, Ptr<Actor> _actor_ptr):UpdateComponent(_actor_ptr),m_player(_player_ptr) {

}

void Equip::Update() {
	mactorptr.lock()->SetTransform(m_player.lock()->GetTransform());

	if (inputmanager.GetRightPad().length() >= 0.2f) {
		auto sprite = mactorptr.lock()->GetComponent<Sprite>();
		if (sprite != nullptr) {
			auto angle = inputmanager.GetRightPad().getAngle()-Math::PiF/2.0f;
			sprite->SetAngle(angle);
		}
		Print << inputmanager.GetRightPad().getAngle() ;
	}
}

bool Equip::DestroyNowEquip(Stage* _stage) {
	auto equips = _stage->GetActors(ActorType::EQUIP);
	for (auto ptr : equips) {
		ptr.lock()->CanRemove = true;
	}
	return true;
}
