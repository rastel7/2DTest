#pragma once
#include"Def.h"
#include"Component.h"
//描画を行うコンポーネントはこれを継承する
class DrawComponent : public Component {
public:
	virtual ~DrawComponent();
	DrawComponent(Ptr<Actor> _mactorptr);
	virtual void Draw();
};
