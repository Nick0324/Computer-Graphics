#pragma once

#include "Main.h"
#include "Sprite.h"
#include <vector>

class Crate
{
public:
	Sprite* m_pSprite;
	std::vector<Crate> crateList;

	Crate(const BackBuffer* pBackBuffer);

	void					Update(float dt);
	void					Draw();
	void					AddCrate(Crate crate);
	Vec2&					Position();
	Vec2&					Velocity();
};

