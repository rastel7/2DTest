#include"Title.h"

Title::Title(const InitData& init): IScene{ init }
{

}

Title::~Title() {
	Logger << U"Title::~Title()";
}
void Title::update() {
	if (inputmanager.GetEdgePressed(PadButtonNumber::Ok)) {
		changeScene(SceneState::Stage);
	}
	if (inputmanager.GetEdgePressed(PadButtonNumber::Jump)) {
		System::Exit();
	}
}
void Title::draw() const {
	auto point = mySystem::GetViewportPoint(0.5, 0.3);
	Print << point;
	auto f = fontmanager.Get(U"normal");
	f(U"Title").drawAt(point, Palette::Black);
}
