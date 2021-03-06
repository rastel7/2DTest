#include"TileMapRenderer.h"
#include"Actor.h"
#include"Stage.h"
#include"Collision.h"
TileMap::TileMap(String _mapname, Ptr<Actor> _mactorptr):DrawComponent(_mactorptr),m_mapname(_mapname) {
	const String image_path = Const::TILEMAP_IMAGE_PATH + m_mapname + U".png";
	const Texture tilemap_image(image_path);
	if (not tilemap_image) {
		throw Error{ U"Failed to open :"+image_path };
	}
	{//マップID
		String CSV_path = Const::TILEMAP_CSV_PATH + m_mapname + U".csv";
		const CSV csv(CSV_path);
		if (!csv) // もし読み込みに失敗したら
		{
			throw Error(U"Failed to load `config.csv`");
		}
		std::vector<std::vector<u_int16>> tmp_Tile_ID;

		for (int y = 0; y < csv.rows(); ++y) {
			std::vector<u_int16> tmp_column;
			auto colmun = csv[y];
			for (int x = 0; x < colmun.size(); ++x) {
				auto str = colmun[x];
				u_int16 id = Parse<u_int16>(str);
				tmp_column.emplace_back(id);
			}
			tmp_Tile_ID.emplace_back(tmp_column);
		}
		m_Tile_ID = tmp_Tile_ID;
	}
	
	CreateMapTexture(tilemap_image, m_Tile_ID);
	{//Collision
		String CSV_path = Const::TILEMAP_COLISION_PATH + m_mapname + U".csv";
		const CSV csv(CSV_path);
		if (!csv) // もし読み込みに失敗したら
		{
			throw Error(U"Failed to load `config.csv`");
		}
		std::vector<std::vector<u_int16>> tmp_Tile_ID;

		for (int y = 0; y < csv.rows(); ++y) {
			std::vector<u_int16> tmp_column;
			auto colmun = csv[y];
			for (int x = 0; x < colmun.size(); ++x) {
				auto str = colmun[x];
				u_int16 id = Parse<u_int16>(str);
				tmp_column.emplace_back(id);
			}
			tmp_Tile_ID.emplace_back(tmp_column);
		}
		
		CreateMapCollision(tmp_Tile_ID);
		collision.m_Tile_ID = &m_Tile_ID;
		collision.CreateCollisionTexture(mactorptr.lock());
	}
	mpriority = -10;
}

void TileMap::CreateMapTexture(Texture const& _tile, std::vector<std::vector<u_int16 >> const& ids) {
	m_map_size.y = ids.size();
	for (auto vec : ids) {
		m_map_size.x = Max(m_map_size.x, (int32)vec.size());
	}
	rendertexture = RenderTexture(m_map_size * Const::TILE_MASU_SIZE);
	// レンダーターゲットを renderTexture に変更
	const ScopedRenderTarget2D target{ rendertexture };
	for (int y = 0; y < m_map_size.y; ++y) {
		for (int x = 0; x < ids[y].size(); ++x) {
			u_int16 id = ids[y][x];
			int t_x = id % ids[y].size();
			int t_y = id / ids[y].size();
			Size tilesize(Const::TILE_MASU_SIZE, Const::TILE_MASU_SIZE);
			
			_tile(t_x* Const::TILE_MASU_SIZE,t_y* Const::TILE_MASU_SIZE,tilesize.y,tilesize.x).draw(x * Const::TILE_MASU_SIZE, y * Const::TILE_MASU_SIZE);
		}
	}
}
void TileMap::CreateMapCollision(std::vector<std::vector<u_int16>> collision_csv) {
	collision.collision_type.resize(m_Tile_ID.size());
	for (int y = 0; y < m_Tile_ID.size(); ++y) {
		int MAX_X = m_Tile_ID[y].size();
		collision.collision_type[y].resize(MAX_X);
		for (int x = 0; x < m_Tile_ID[y].size(); ++x) {
			int id = m_Tile_ID[y][x];
			int tile_y = id / collision_csv[0].size();
			int tile_x = id % collision_csv[0].size();
			collision.collision_type[y][x] = collision_csv[tile_y][tile_x];
		}
	}
}
TileMap::~TileMap() {
	
}
void TileMap::Draw()  {
	rendertexture.draw(Arg::bottomLeft(0,0));
	
	#ifdef DEBUG
	{
		//collision.collisiontexture.draw(Arg::bottomLeft(0, 0));
	}
	#endif // !DEBUG
	#ifdef LOOP_MAP
	Vec2 size = mactorptr->GetStage()->GamePositiontoWorldPosition(mactorptr->GetStage()->GetMapSize());
	int dd[3] = { -1,0,1 };
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == 1 && j == 1)continue;
			rendertexture.draw(Arg::bottomLeft(0+size.x*dd[i], 0+size.y*dd[j]));
		}
	}
	#endif
	
}

Size TileMap::GetTextureSize() const {
	return rendertexture.size();
}

//通行不可:1 通行可能:0
u_int16 TileMap::GetColID(Vec2 position) const {
	position.x *= Const::TILE_MASU_SIZE, position.y *= Const::TILE_MASU_SIZE;
	if (position.x < 0 || position.y || position.x >= collision.collisiontexture.size().x || position.y >= collision.collisiontexture.size().y) {
		return 1;
	}
	Color color = collision.collisionimage.getPixel(position.x, position.x, ImageAddressMode::BorderWhite);
	float max = Max({color.r,color.g,color.b});
	return max > 0.5;
}
//Collision

void TileMapCollision::CreateCollisionTexture(Ptr<Actor> actor) {
	auto stage = actor->GetStage();

	
	collisionimage = { collision_type[0].size() * Const::TILE_MASU_SIZE, collision_type.size() * Const::TILE_MASU_SIZE };
	int tl_id = 0;
	// レンダーターゲットを renderTexture に変更
	for (int y = 0; y < collision_type.size(); ++y) {
		for (int x = 0; x < collision_type[y].size(); ++x) {
			//int tile_id = (*m_Tile_ID)[y][x];
			//int t_y = tile_id / (collision_type[0].size());
			//int t_x = tile_id % (collision_type[0].size());
			auto id = collision_type[y][x];
			int pos_y = y * Const::TILE_MASU_SIZE;
			int pos_x = x * Const::TILE_MASU_SIZE;
			ColorF color=ColorF(0,0,0,0);
			switch (id) {
			case 1:
				color = ColorF(0.9, 0.2, 0.2, 0.2);
				{//ステージにコリジョンをもったアクターを追加
					Ptr<Actor> new_actor(new Actor(stage));
					new_actor->name = U"Stage_{}"_fmt(tl_id);
					tl_id++;
					//auto screenpositon = pos_x + pos_x * 0.5, pos_y + pos_y * 0.5;
					new_actor->SetTransform(Transform{(float)x+0.5f,collision_type.size()-((float)y+0.5f)});
					new_actor->AddComponent(std::make_shared<Collision>(0.5f, new_actor->GetStage()->col_manager, new_actor));
					stage->AddActor(new_actor);
				}
				break;
			default:
				break;
			}
			Rect(pos_x, pos_y, Const::TILE_MASU_SIZE, Const::TILE_MASU_SIZE).overwrite(collisionimage,color);
			
		}
	}
	collisiontexture = Texture{ collisionimage };
}
