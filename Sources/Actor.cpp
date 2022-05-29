#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
#include"Stage.h"
std::vector<Ptr<DrawComponent>>  Actor::Draw() const {
	std::vector<Ptr<DrawComponent>> draw_events;
	for (auto &ptr : components) {
		auto draw_component = std::dynamic_pointer_cast<DrawComponent>(ptr);

		if (draw_component != nullptr) {
			draw_events.emplace_back(std::dynamic_pointer_cast<DrawComponent>(ptr));
		}
		
	}
	return draw_events;
}

Actor::~Actor() {

}
void Actor::Update() {
	UpdateComponentOrder();
	for (auto& ptr : components) {
		auto update_component = std::dynamic_pointer_cast<UpdateComponent>(ptr);

		if (update_component != nullptr) {
			update_component->Update();
		}
	}
	//Transformの更新
	m_transform.Update(m_stage->GetMapSize());
}

Actor::Actor(Ptr<Stage> _m_stage):m_stage(_m_stage) {

}

void Actor::AddComponent(Ptr<Component> _component) {
	components.emplace_back(_component);
	UpdateComponentOrder();
	
}

void Actor::UpdateComponentOrder() {
	if (_componentNum != components.size()) {
		_componentNum = (int)components.size();
		sort(components.begin(), components.end(), [](Ptr<Component> const& l, Ptr<Component> const& r) {
			return l->GetPriority() < r->GetPriority();
		});
	}
}

