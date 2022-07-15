#include"Def.h"
#include"CardSelecter.h"
#include"Card.h"
CardSelecter::CardSelecter(Stage* _stage):UI(_stage) {
	//ƒJ[ƒh–¼‚Ìˆê——‚ğæ“¾
	for (const auto& path : FileSystem::DirectoryContents(Const::CARD_PATH))
	{
		auto name = mySystem::split(path, '/');
		m_cardnames.emplace_back(name.back());
	}
	
}

void CardSelecter::CardGeneration() {
	for (int i = 0; i < CARD_NUM; ++i) {
		int target_id = RandomInt32() % m_cardnames.size();
		m_elements.emplace_back(std::make_shared<Card>(m_cardnames[target_id], shared_from_this(), Vec2{ 0.2+0.3*i,0.5 }, 0));
	}
}

void CardSelecter::Draw() const {
	for (auto card : m_elements) {
		card.get()->Draw();
	}
}

void CardSelecter::Update() {
	if (inputmanager.GetEdgePressed(PadButtonNumber::Left)) {
		x--;
	}
	if (inputmanager.GetEdgePressed(PadButtonNumber::Right)) {
		x++;
	}
	x = (x + CARD_NUM) % CARD_NUM;
	for (int i = 0; i < m_elements.size(); ++i) {
		auto card = std::dynamic_pointer_cast<Card>(m_elements[i]);
		if (card) {
			if (i == x) {
				card->isSelected = true;
			}
			else {
				card->isSelected = false;
			}
		}
	}
	if (inputmanager.GetEdgePressed(PadButtonNumber::Ok)) {
		auto card = std::dynamic_pointer_cast<Card>(m_elements[x]);
		if (card) {
			card->Update();
		}
		m_candelete = true;
	}
}