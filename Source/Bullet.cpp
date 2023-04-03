#include "Bullet.h"



Bullet::Bullet(const BackBuffer* pBackBuffer)
{
	mpBackBuffer = pBackBuffer;
}

Bullet::~Bullet()
{
	delete mpBackBuffer;
}

void Bullet::AddBullet(Vec2 pos, int direction) {
	m_lpBulletPosList.push_back(pos);

	Vec2 vel;
	switch (direction) {
	case 0:
		vel.x = 0;
		vel.y = -1.5;
		break;
	case 1:
		vel.x = 0;
		vel.y = 1.5;
		break;
	case 2:
		vel.x = -1.5;
		vel.y = 0;
		break;
	case 3:
		vel.x = 1.5;
		vel.y = 0;
		break;
	}

	m_lpBulletVelList.push_back(vel);
}

void Bullet::Draw() {
	unsigned char i = 0;
	for (i; i < m_lpBulletPosList.size(); i++) {
		Vec2 vel = m_lpBulletVelList.at(i);
		m_lpBulletPosList.at(i) += vel;

		POINT p;
		p.x = m_lpBulletPosList.at(i).x;
		p.y = m_lpBulletPosList.at(i).y;

		if (m_lpBulletPosList.at(i).x < 0 || m_lpBulletPosList.at(i).x > 800 ||
			m_lpBulletPosList.at(i).y < 0 || m_lpBulletPosList.at(i).y > 600) {
			m_lpBulletPosList.erase(m_lpBulletPosList.begin() + i);
		}
		else
		{
			Ellipse(mpBackBuffer->getDC(), p.x - 6,p.y - 6,p.x + 6,p.y + 6);
		}
	}

}

void Bullet::Update(float dt) {
	m_fDelta = dt;
}