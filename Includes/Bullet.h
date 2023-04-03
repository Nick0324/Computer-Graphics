#pragma once

#include "Main.h"
#include "Sprite.h"
#include <vector>

class Bullet
{
private:
	float					m_fDelta;
	std::vector<Vec2>		m_lpBulletPosList;
	std::vector<Vec2>		m_lpBulletVelList;
	const BackBuffer*		mpBackBuffer;

public:
	Bullet(const BackBuffer* pBackbuffer);
	~Bullet();

	void					AddBullet(Vec2 pos);
	void					Draw();
	void					Update(float dt);
	
};

