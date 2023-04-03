#pragma once

#include "Main.h"
#include "Sprite.h"
#include <vector>
#include "Bullet.h"

class Crate
{
public:
	Sprite*				m_pSprite;
	std::vector<Crate>  crateList;
	bool				canShoot = true;
	Sprite*				bulletSprite;

	Crate(const BackBuffer* pBackBuffer);

	void					Update(float dt);
	void					Draw();
	void					AddCrate(Crate crate);
	void					Shoot();
	Vec2&					Position();
	Vec2&					Velocity();
};

