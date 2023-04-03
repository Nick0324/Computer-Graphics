#pragma once

#include "Main.h"
#include "Sprite.h"
#include <vector>

class Bullet
{
private:
	float					m_fDelta;

	const BackBuffer*		mpBackBuffer;

public:
	std::vector<Vec2>		m_lpBulletPosList;
	std::vector<Vec2>		m_lpBulletVelList;

	Bullet(const BackBuffer* pBackbuffer);
	~Bullet();

	void					AddBullet(Vec2 pos, int direction);
	void					Draw();
	void					Update(float dt);
	
};

