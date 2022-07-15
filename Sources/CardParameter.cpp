#include"Def.h"
#include"Card.h"

void CardParameter::ReadIniParameter(String const& section, Array<INIKey> const& keys) {
	if (section == U"DESCRIPTION") {
		for (const auto& key : keys) {
			if (key.name == U"name") {
				name = key.value;
			}
			if (key.name == U"description") {
				description = key.value;
			}
		}
	}
	if (section == U"EFFECTS") {
		for (const auto& key : keys) {
			if (key.name == U"max_bullet") {
				max_bullet = ParseInt(key.value);
			}
		}
	}
}
void CardParameter::GiveEffect() {
	Ptr<CardEffects> cardeffectsptr;
	if (!( cardeffectsptr = m_cardeffects.lock())) {
		return;
	}
	cardeffectsptr->ObtainEffect(this);
}

int CardParameter::ParseInt(String const& str) {
	int ret = 0;
	try {
		ret = Parse<int>(str);
	}
	catch (...) {

	}
	return ret;
}