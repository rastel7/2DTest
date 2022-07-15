#include"CardEffects.h"
#include"Card.h"
void CardEffects::ObtainEffect(CardParameter* _cardparam) {
	max_bullet += _cardparam->max_bullet;
}