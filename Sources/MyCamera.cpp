#include"MyCamera.h"
#include"TileMapRenderer.h"
#include"Actor.h"
#include"Stage.h"
void MyCamera::Update() {
	camera.update();
	Ptr<TileMap> tilemap = stage->GetComponent<TileMap>();
	if (tilemap == nullptr)return;
	//カメラが領域外を移していたら変更
	Size texture_size = tilemap.get()->GetTextureSize();
	auto now_camera_center = camera.getCenter();
	if (now_camera_center.x < SystemNum::WindowWidth / 2) {
		now_camera_center.x = SystemNum::WindowWidth / 2;
	}
	if (now_camera_center.y > -SystemNum::WindowHeight / 2) {
		now_camera_center.y = -SystemNum::WindowHeight / 2;
	}
	if (now_camera_center.x > texture_size.x - SystemNum::WindowWidth / 2) {
		now_camera_center.x = texture_size.x - SystemNum::WindowWidth / 2;
	}
	if (now_camera_center.y < -texture_size.y + SystemNum::WindowHeight / 2) {
		now_camera_center.y = -texture_size.y + SystemNum::WindowHeight / 2;
	}
	Print << U"Camera_Center:{}"_fmt(now_camera_center);
	if (now_camera_center != camera.getCenter()) {
		camera.setTargetCenter(now_camera_center);

	}
}

Camera2D MyCamera::GetCamera() const {
	return camera;
}

MyCamera::MyCamera(Stage* _stage):stage(_stage) {

}
