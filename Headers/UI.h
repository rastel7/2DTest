#pragma once
#include"Def.h"
class UIElement;
class UI {
	std::vector<Ptr<UIElement>> elements;
	inline void Draw() {

	}
	virtual void Update() = 0;
};