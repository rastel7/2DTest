#include"Def.h"

namespace Const {
	const int DEFAULT_FONT_SIZE=32;
	const String TILEMAP_IMAGE_PATH = U"Resources/Tilemap/Image/";
	const String TILEMAP_CSV_PATH = U"Resources/Tilemap/CSV/";
	const String TILEMAP_COLISION_PATH= U"Resources/Tilemap/Collision/";
	const String SPRITE_PATH = U"Resources/Sprites/" ;
	const String CARD_PATH= U"Resources/Cards/";
	const int TILE_MASU_SIZE = 32; 
}
namespace SystemNum {
	int WindowWidth=640;
	int WindowHeight=480;
	int RerolutionRate=1;
}
FontManager fontmanager;
InputManager inputmanager;
IndexManager<int> collision_id_manager;
