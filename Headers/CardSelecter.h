#pragma once
#include"Def.h"
#include"UI.h"
class Stage;
class CardSelecter :public UI ,public std::enable_shared_from_this<CardSelecter> {
	Array<String> m_cardnames;
	const int CARD_NUM = 3;
	int x = 0;
public:
	void CardGeneration();
	void Draw() const final;
	void Update() final;
	CardSelecter(Stage *_stage);
};