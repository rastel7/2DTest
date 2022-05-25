#pragma once
#include"Def.h"
class Component;
class Actor {
	int _componentNum=-1;
	std::vector<Ptr<Component>> components;
	void UpdateComponentOrder();//コンポーネントの優先順位をソート
 public:
	Actor();
	void Update();
	void Draw() const;
	void AddComponent(Ptr<Component> _component);
}; 
