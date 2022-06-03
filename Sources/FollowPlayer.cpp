#include"FollowPlayer.h"
#include"Actor.h"
#include"Stage.h"
#include"PlayerComponent.h"
void FollowPlayer::Update() {
	auto player = mactorptr.lock()->GetStage()->GetComponent<Player>();
	if (player == nullptr)return;
	auto player_position = player->GetTransform().m_position;
	auto position = mactorptr.lock()->GetTransform().m_position;
	auto direction = player_position - position;
	if (direction.isZero())return;
	direction.normalize();
	auto next = direction * speed * Scene::DeltaTime() + position;
	SetTransform(next);
}
