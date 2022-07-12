#include"Def.h"
#include"Card.h"

void CardParameter::ReadIniParameter(String const& section, Array<INIKey> const& keys) {
	if (section == U"DESCRIPTION") {
		for (const auto& key : keys) {
			if (key.name == U"name") {
				name = key.value;
			}
			if (key.name == U"name") {
				description = key.value;
			}
		}
	}
}