#include"Slime.h"
#include"Stage.h"
#include"Actor.h"
#include"BasicSprite.h"
#include"SpriteRenderer.h"
#include"FollowPlayer.h"
void Slime::CreateSlime(Stage* _stage) {
	if (_stage == nullptr)return;
	auto actor = _stage->CreateActor();
	actor->name = U"Slime";
	actor.get()->AddComponent(Ptr<Component>(std::make_shared<Sprite>(U"Slime",48,64,actor)));
	actor.get()->AddComponent(Ptr<Component>(std::make_shared<BasicSprite>(actor)));
	actor.get()->AddComponent(Ptr<Component>(std::make_shared<Collision>(0.5f,_stage->col_manager,actor)));
	actor.get()->AddComponent(Ptr<Component>(std::make_shared<FollowPlayer>( actor)));
	actor.get()->AddComponent(Ptr<Component>(std::make_shared<Slime>(actor,10)));
	actor.get()->CanRemove = true;
}
