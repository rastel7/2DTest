#pragma once
#include"Def.h"
#include"DrawComponent.h"

class Sprite:public DrawComponent {
	Texture m_texture;
	std::vector<TextureRegion> m_tex_regions;
	u_int16 m_tex_id;
	String m_name;
	u_int16 m_size_x, m_size_y;
public:
	friend Component;
	Sprite(String _path,u_int16 _size_x,u_int16 _size_y,Ptr<Actor> _ptr);
	virtual ~Sprite();
	void Draw()  override;
	inline void SetTextureID(u_int16 _id) {
		m_tex_id = _id;
		m_tex_id %= m_tex_regions.size();
	}
	inline u_int16 SetTextureID()const {
		return m_tex_id;
	}
};
