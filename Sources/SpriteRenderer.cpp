﻿#include"SpriteRenderer.h"
#include"Actor.h"
#include"Transform.h"
#include"Stage.h"
Sprite::Sprite(String _path, u_int16 _size_x, u_int16 _size_y, Ptr<Actor> _ptr) :DrawComponent(_ptr),m_name(_path),m_size_x(_size_x),m_size_y(_size_y) {
	auto path = Const::SPRITE_PATH + m_name + U".png";
	m_texture=Texture{path};
	if(not m_texture) {
		throw Error(U"Can'tRead"+path);
	}
	u_int16 Y_size = m_texture.size().y / _size_y;
	u_int16 X_size = m_texture.size().x / _size_x;
	m_tex_regions.resize(Y_size * X_size);
	for (u_int16 y = 0; y < Y_size; ++y) {
		for (u_int16 x = 0; x < X_size; ++x) {
			u_int16 id = y * X_size + x;
			m_tex_regions[id] = m_texture(x * m_size_x, y * m_size_y, m_size_x, m_size_y);
		}
	}
}
Sprite::~Sprite() {

}
void Sprite::Draw() const{
	Transform transform=Component::mactorptr->GetTransform();
	Vec2 position = mactorptr->GetStage()->GamePositiontoWorldPosition(transform.m_position);
	m_tex_regions[m_tex_id].draw(Arg::bottomCenter(position.x, position.x));
}
