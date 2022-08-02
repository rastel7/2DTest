#pragma once
#include"Def.h"
class CardParameter;
//カードの効果を保存するクラス
//カードパラメーターを渡すことで更新
class CardEffects {
	int max_bullet = 0;
	float EXP_Range = 0.5f;
public:
	void ObtainEffect(CardParameter* _cardparam);
	inline int GetMaxBullet() { return max_bullet; }
	inline float GetEXP_Range() { return EXP_Range; }
};