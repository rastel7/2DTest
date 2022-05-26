#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
void Actor::Draw() const {
	
	for (auto &ptr : components) {
		auto draw_component = std::dynamic_pointer_cast<DrawComponent>(ptr);

		if (draw_component != nullptr) {
			draw_component->Draw();
		}
		
	}
	
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

