//全部のソースで読み込むヘッダ
#pragma once
#include<Siv3D.hpp>
#include"System.h"
#include"FontManager.h"
#include"InputManager.h"
//定数
namespace Const {
	extern const int DEFAULT_FONT_SIZE;
	extern const String TILEMAP_IMAGE_PATH;//タイルマップの画像が入っているフォルダへのパス
	extern const String TILEMAP_CSV_PATH;//タイルマップのCSVが入っているフォルダへのパス
	extern const String TILEMAP_COLISION_PATH;//タイルマップのCSVが入っているフォルダへのパス
	extern const int TILE_MASU_SIZE;
}

namespace SystemNum {
	extern int WindowWidth;
	extern int WindowHeight;
	extern int RerolutionRate;
}

extern FontManager fontmanager;
extern InputManager inputmanager;

using u_int16 = unsigned __int16;
using App = SceneManager<String>;

template <class T>
using Ptr = std::shared_ptr<T>;
