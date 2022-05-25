#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
void Actor::Draw() const {
	
	for (auto &ptr : components) {
		auto draw_component = std::dynamic_pointer_cast<DrawComponent>(ptr);

		if (draw_component != nullptr) {
			draw_component->Draw();
		}
		
	}
	
}

void Actor::Update() {
	UpdateComponentOrder();
	for (auto ptr : components) {
		auto pri =ToString(ptr->GetPriority());
		Print << U"{} {}"_fmt(ptr->name, pri);
	}
}

Actor::Actor() {

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
