#include"Stage.h"
#include"Actor.h"
#include"Component.h"
#include"DrawComponent.h"
Stage::Stage(const InitData& init) : IScene{ init } {

}

void Stage::update() {
	for (auto ptr : actors) {
		ptr->Update();
	}
	if (inputmanager.GetEdgePressed(PadButtonNumber::Jump)) {
		changeScene(U"Title");
	}
}
void Stage::draw() const {
	for (auto ptr : actors) {
		ptr->Draw();
	}
}
