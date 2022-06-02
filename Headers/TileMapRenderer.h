#pragma once
#include"Def.h"
#include"DrawComponent.h"
#include"UpdateComponent.h"
class TileMapCollision {
public:
	std::vector<std::vector<u_int16>> *m_Tile_ID;
	Texture collisiontexture;
	void CreateCollisionTexture(Ptr<Actor> actor);
	Image collisionimage;
	std::vector<std::vector<u_int16>> collision_type;
};

class TileMap: public DrawComponent  {

	Size m_map_size;
	String m_mapname;
	RenderTexture rendertexture;
	std::vector<std::vector<u_int16>> m_Tile_ID;
	//Actorに対してコリジョンの追加も行う
	TileMapCollision collision;
	void CreateMapTexture(Texture const& _tile, std::vector<std::vector<u_int16 >> const& ids);
	void CreateMapCollision(std::vector<std::vector<u_int16>> collision_csv);
public:
	TileMap(String _mapname,Ptr<Actor> _mactorptr);
	virtual ~TileMap();
	void Draw() override;
	Size GetTextureSize() const;
	u_int16 GetColID(Vec2 position) const;
	inline GameSize GetMapSize() const { return GameSize{m_map_size.x,m_map_size.y };
}
};

