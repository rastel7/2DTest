#include"Stage.h"
#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
#include"TileMapRenderer.h"
#include"SpriteRenderer.h"
#include"PlayerComponent.h"
#include"Transform.h"
#include"Enemys.h"
#include"Equips.h"
Stage::Stage(const InitData& init) : IScene{ init },camera(this){
	{
		auto actor = Ptr<Actor>(new Actor(this));
		actor->name = U"Player";
		actor->AddComponent(Ptr<Component>(new TileMap(U"TestStage",Ptr<Actor>(actor))));
		actors.insert(actor);
	}
	{
		auto actor = Ptr<Actor>(new Actor(this));
		actor->AddComponent(Ptr<Player>(new Player(Transform(0,0), actor)));
		actors.insert(actor);
		HandGun::EquipHandGun(actor, this);
	}
	col_manager = Ptr<CollisionManager>( new CollisionManager(this));
	Slime::CreateSlime(this);
}

void Stage::update() {
	//不要なオブジェクトの削除
	auto itr = actors.begin();
	while (itr != actors.end()) {
		if ((*itr)->CanRemove) {
			itr = actors.erase(itr);
		}
		else {
			itr++;
		}
	}

	for (auto ptr : actors) {
		ptr->Update();
	}
	if (inputmanager.GetEdgePressed(PadButtonNumber::Jump)) {
		System::Exit();
	}
	camera.Update();
	Print << U"ActorCount:{}"_fmt(actors.size());
	col_manager.get()->Update();
}
void Stage::draw() const {
	const auto transformer = camera.GetCamera().createTransformer();
	std::vector<Ptr<DrawComponent>> draw_events;
	for (auto ptr : actors) {
		auto vec= ptr->Draw();
		std::copy(vec.begin(), vec.end(), std::back_inserter(draw_events));
	}
	sort(draw_events.begin(), draw_events.end(), [](Ptr<DrawComponent> const& l, Ptr<DrawComponent> const& r){
		return l->GetPriority() < r->GetPriority();
	});
	for (auto draw_component : draw_events) {
		draw_component->Draw();
	}
	col_manager->DebugDraw();
}

Vec2 Stage::GamePositiontoWorldPosition(Vec2 const& _position) const {
	Vec2 ret{0,0};
	ret.x = _position.x * Const::TILE_MASU_SIZE;
	ret.y -= _position.y * Const::TILE_MASU_SIZE;
	return ret;
}
Stage::~Stage() {
	Logger << U"Stage::~Stage():{}"_fmt(zero);
	zero++;
}



GameSize Stage::GetMapSize() const {
	Ptr<TileMap> stage = GetComponent<TileMap>();
	if (stage == nullptr){
		return GameSize{0,0};
	}
	return stage->GetMapSize();
}
Ptr<Actor> Stage::CreateActor() {
	auto actor = std::make_shared<Actor>(this);
	actors.insert(actor);
	return actor;
}

std::vector<WPtr<Actor>> Stage::GetActors(ActorType _actor_type) {
	std::vector<WPtr<Actor>> ret;
	for (auto ptr : actors) {
		if (ptr->GetActorType() == _actor_type) {
			ret.emplace_back(ptr);
		}
	}
	return ret;
}
