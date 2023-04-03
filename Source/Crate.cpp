#include "Crate.h"

Crate::Crate(const BackBuffer* pBackBuffer) {
	m_pSprite = new Sprite("data/crate.bmp", RGB(0xff, 0x00, 0xff));
	m_pSprite->setBackBuffer(pBackBuffer);
}

void Crate::Update(float dt)
{
	for (auto i : crateList) {
		i.m_pSprite->update(dt);
	}
}

void Crate::Draw()
{
	for (auto i : crateList) {
		i.m_pSprite->draw();
	}
}

void Crate::AddCrate(Crate crate)
{
	crate.Position() = Vec2(rand() % 800, 0);
	crate.Velocity() = Vec2(0, 50);
	crateList.push_back(crate);
}

Vec2& Crate::Position()
{
	return m_pSprite->mPosition;
}

Vec2& Crate::Velocity()
{
	return m_pSprite->mVelocity;
}