#include"Collision.h"
#include"Actor.h"
#include"Stage.h"
Collision::Collision(Vec2 _size, Ptr<Actor> _ptr):DrawComponent(_ptr) ,m_size(_size) {
	mpriority = 100;
}

void Collision::Draw()const {
#ifdef DEBUG
	{
		auto transform = mactorptr->GetTransform();
		auto stage = mactorptr->GetStage()->GamePositiontoWorldPosition(transform.m_position);
		auto _scale = m_size * Const::TILE_MASU_SIZE;
		Rect(stage.x- _scale.x/2,stage.y- _scale.y, (float)_scale.x, (float)_scale.y).draw(ColorF(0.2,0.8,0.2,0.3f));
		Circle(stage.x, stage.y, 3.0f).draw();
	}
#endif // DEBUG

}
