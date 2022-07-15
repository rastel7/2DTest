#include"Def.h"
#include"UI.h"
#include"CardSelecter.h"
void UIManager::Draw() const {
	for (auto const& ptr : m_uis) {
		ptr->Draw();
	}
}
void UIManager::Update() {
	if (!HasUI())return;
	m_uis.back()->Update();
	if (m_uis.back()->m_candelete) {
		m_uis.pop_back();
	}
}

void UIManager::DebugUpdate() {
#ifndef DEBUG
	return;
#endif // !DEBUG
	Print << U"Q:Card";
	if (KeyQ.pressed())
	{
		auto ptr = std::make_shared<CardSelecter>(m_stage);
		ptr->CardGeneration();
		m_uis.emplace_back(ptr);
	}
}
void UIManager::DebugDraw() const{
#ifndef DEBUG
	return;
#endif // !DEBUG
	
}