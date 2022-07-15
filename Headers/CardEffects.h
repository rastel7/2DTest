#pragma once
#include"Def.h"
class CardParameter;
class CardEffects {
	int max_bullet = 0;
public:
	void ObtainEffect(CardParameter* _cardparam);
	inline int GetMaxBullet() { return max_bullet; }
};