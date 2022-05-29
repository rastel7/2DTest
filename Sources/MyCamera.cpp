#include"MyCamera.h"
#include"TileMapRenderer.h"
#include"Actor.h"
#include"Stage.h"
#include"Transform.h"
#include"PlayerComponent.h"
#include"Actor.h"
void MyCamera::Update() {
	//camera.update();
	Transform* player_transform = GetPlayerTransform();
	if (player_transform == nullptr) {
		Print << U"myCamera:can't find player";
		return;
	}
	//camera.jumpTo(stage->GamePositiontoWorldPosition(player_transform->m_position),1.0f);
	camera.setCenter(stage->GamePositiontoWorldPosition(player_transform->m_position));
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
		//camera.jumpTo(now_camera_center, 1.0f);
		camera.setCenter(now_camera_center);

	}
}

Camera2D MyCamera::GetCamera() const {
	return camera;
}

MyCamera::MyCamera(Stage* _stage):stage(_stage) {

}

Transform* MyCamera::GetPlayerTransform() const {
	Transform* ret = nullptr;
	Ptr<Player> player = stage->GetComponent<Player>();
	if (player == nullptr) {
		return nullptr;
	}
	ret = new Transform(player->GetTransform());
	return ret;
}
