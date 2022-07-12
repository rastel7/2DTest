#include"Def.h"
#include"Card.h"
#include"UIElement.h"
#include"UI.h"
void Card::Draw() const{

}

Card::Card(String _path, WPtr<UI> _parent, Vec2 _screen_position, int _priority):m_path(_path),UIElement(_parent,_screen_position,_priority) {

}