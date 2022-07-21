#pragma once
#include"Def.h"
class UIElement;
class Stage;
class UI {
protected:
	Stage* m_stage;
	std::vector<Ptr<UIElement>> m_elements;
public:
	inline Stage* GetStage()const { return m_stage; }
	inline UI(Stage* _stage):m_stage(_stage) {}
	bool m_candelete = false;
	virtual void Draw() const = 0;
	virtual void Update() = 0;
};
class UIManager {
protected:
	Stage* m_stage;
	std::vector<Ptr<UI>> m_uis;
public:
	inline void AddElement(Ptr<UI> _ptr) { m_uis.emplace_back(_ptr); }
	inline UIManager(Stage*_stage):m_stage(_stage) {}
	inline bool HasUI()const { return !m_uis.empty(); }
	void CreateCard();
	void DebugUpdate();
	void DebugDraw() const;
	virtual void Draw() const;
	virtual void Update();
};