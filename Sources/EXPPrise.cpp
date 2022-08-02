#include"EXPPrise.h"
#include"Actor.h"
#include"Stage.h"
#include"Collision.h"
#include"SpriteRenderer.h"
const float EXPPrise::EXP_APPEARANCE_DIST = 1;
EXPPrise::EXPPrise(Ptr<Actor> _mactorptr):UpdateComponent(_mactorptr) {
	mactorptr.lock()->SetActorType(ActorType::EXP_PRISE);
	mactorptr.lock()->AddComponent(Ptr<Component>(new Sprite(U"Exp", 32, 32, _mactorptr)));
	auto collision = (std::make_shared<Collision>(0.5f, _mactorptr->GetStage()->col_manager, _mactorptr));
	m_col = collision;
	mactorptr.lock()->AddComponent(Ptr<Component>(collision));
}
EXPPrise::~EXPPrise() {

}

void EXPPrise::GenerateEXPPrise(Stage* _stage, GameVec2 _position,int _n) {
	for (int i = 0; i < _n; ++i) {
		GameVec2 target_position = _position + RandomVec2() * EXP_APPEARANCE_DIST;
		Ptr<Actor> actor = std::make_shared<Actor>(_stage);
		actor->SetTransform(Transform(target_position));
		actor->AddComponent(std::make_shared<EXPPrise>(actor));
		_stage->AddActor(actor);
	}
}
void EXPPrise::Update() {
	if (auto col = m_col.lock()) {
		col->SetRadius(mactorptr.lock()->GetStage()->m_cardeffects->GetEXP_Range());
	}
}
int EXPPrise::GetEXP() const { return 1; }