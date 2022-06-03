#include"Equip.h"

Equip::Equip(Ptr<Actor> _player_ptr, Ptr<Actor> _sprite_ptr, Ptr<Actor> _actor_ptr):UpdateComponent(_actor_ptr),m_player(_player_ptr),m_sprite(_sprite_ptr) {

}

void Equip::Update() {

}

bool Equip::DestroyNowEquip() {

}
