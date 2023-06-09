//-----------------------------------------------------------------------------
// File: CPlayer.cpp
//
// Desc: This file stores the player object class. This class performs tasks
//       such as player movement, some minor physics as well as rendering.
//
// Original design by Adam Hoult & Gary Simmons. Modified by Mihai Popescu.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CPlayer Specific Includes
//-----------------------------------------------------------------------------
#include "CPlayer.h"
//-----------------------------------------------------------------------------
// Name : CPlayer () (Constructor)
// Desc : CPlayer Class Constructor
//-----------------------------------------------------------------------------
CPlayer::CPlayer(const BackBuffer *pBackBuffer)
{
	//m_pSprite = new Sprite("data/planeimg.bmp", "data/planemask.bmp");
	m_pSprite = new Sprite("data/planeimgandmask.bmp", RGB(0xff,0x00, 0xff));
	m_pSprite->setBackBuffer( pBackBuffer );
	m_eSpeedState = SPEED_STOP;
	m_fTimer = 0;
	lives = 3;
	score = 0;
	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	m_pExplosionSprite	= new AnimatedSprite("data/explosion.bmp", "data/explosionmask.bmp", r, 16);
	m_pExplosionSprite->setBackBuffer( pBackBuffer );
	m_bExplosion		= false;
	m_iExplosionFrame	= 0;
}

//-----------------------------------------------------------------------------
// Name : ~CPlayer () (Destructor)
// Desc : CPlayer Class Destructor
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
	delete m_pSprite;
	delete m_pExplosionSprite;
}

void CPlayer::Update(float dt)
{
	// Update sprite
	m_pSprite->update(dt);


	// Get velocity
	double v = m_pSprite->mVelocity.Magnitude();

	// NOTE: for each async sound played Windows creates a thread for you
	// but only one, so you cannot play multiple sounds at once.
	// This creation/destruction of threads also leads to bad performance
	// so this method is not recommanded to be used in complex projects.

	// update internal time counter used in sound handling (not to overlap sounds)
	m_fTimer += dt;

	// A FSM is used for sound manager 
	switch(m_eSpeedState)
	{
	case SPEED_STOP:
		if(v > 35.0f)
		{
			m_eSpeedState = SPEED_START;
			//PlaySound("data/jet-start.wav", NULL, SND_FILENAME | SND_ASYNC);
			m_fTimer = 0;
		}
		break;
	case SPEED_START:
		if(v < 25.0f)
		{
			m_eSpeedState = SPEED_STOP;
			//PlaySound("data/jet-stop.wav", NULL, SND_FILENAME | SND_ASYNC);
			m_fTimer = 0;
		}
		else
			if(m_fTimer > 1.f)
			{
				//PlaySound("data/jet-cabin.wav", NULL, SND_FILENAME | SND_ASYNC);
				m_fTimer = 0;
			}
		break;
	}

	// NOTE: For sound you also can use MIDI but it's Win32 API it is a bit hard
	// see msdn reference: http://msdn.microsoft.com/en-us/library/ms711640.aspx
	// In this case you can use a C++ wrapper for it. See the following article:
	// http://www.codeproject.com/KB/audio-video/midiwrapper.aspx (with code also)
}

void CPlayer::Draw()
{
	if(!m_bExplosion)
		m_pSprite->draw();
	else
		m_pExplosionSprite->draw();
}

void CPlayer::Move(ULONG ulDirection)
{
	if (ulDirection & CPlayer::DIR_LEFT) {
		m_pSprite->mVelocity.x -= .1;
	}
	if (m_pSprite->mPosition.x - m_pSprite->width() / 2 < 0) {
		m_pSprite->mVelocity.x = 0;
		m_pSprite->mPosition.x += 1;
	}
	
	if (ulDirection & CPlayer::DIR_RIGHT) {
		m_pSprite->mVelocity.x += .1;
	}
	if (m_pSprite->mPosition.x + m_pSprite->width() / 2 > 780) {
		m_pSprite->mVelocity.x = 0;
		m_pSprite->mPosition.x -= 1;
	}
	
	if (ulDirection & CPlayer::DIR_FORWARD) {
		m_pSprite->mVelocity.y -= .1;
	}
	if (m_pSprite->mPosition.y - m_pSprite->height() / 2 < 0) {
		m_pSprite->mVelocity.y = 0;
		m_pSprite->mPosition.y += 1;
	}
	
	if (ulDirection & CPlayer::DIR_BACKWARD) {
		m_pSprite->mVelocity.y += .1;
	}
	if (m_pSprite->mPosition.y + m_pSprite->height() / 2 > 560) {
		m_pSprite->mVelocity.y = 0;
		m_pSprite->mPosition.y -= 1;
	}
}


Vec2& CPlayer::Position()
{
	return m_pSprite->mPosition;
}

Vec2& CPlayer::Velocity()
{
	return m_pSprite->mVelocity;
}

void CPlayer::Shoot(Bullet* bullet, CPlayer::DIRECTION direction) {
	Vec2 playerDir;
	int dir = 0;
	switch (direction) {
	case DIR_FORWARD:
		playerDir.x = 0;
		playerDir.y = -m_pSprite->height() / 2;
		dir = 0;
		break;
	case DIR_BACKWARD:
		playerDir.x = 0;
		playerDir.y = m_pSprite->height() / 2;
		dir = 1;
		break;
	case DIR_LEFT:
		playerDir.x = -m_pSprite->width() / 2;
		playerDir.y = 0;
		dir = 2;
		break;
	case DIR_RIGHT:
		playerDir.x = m_pSprite->width() / 2;
		playerDir.y = 0;
		dir = 3;
		break;
	}
	bullet->AddBullet(m_pSprite->mPosition + playerDir, dir);
}

void CPlayer::Explode()
{
	lives--;
	m_pExplosionSprite->mPosition = m_pSprite->mPosition;
	m_pExplosionSprite->SetFrame(0);
	//PlaySound("data/explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	m_bExplosion = true;
}

bool CPlayer::AdvanceExplosion()
{
	if(m_bExplosion)
	{
		m_pExplosionSprite->SetFrame(m_iExplosionFrame++);
		if(m_iExplosionFrame==m_pExplosionSprite->GetFrameCount())
		{
			m_bExplosion = false;
			m_iExplosionFrame = 0;
			m_pSprite->mVelocity = Vec2(0,0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}

	return true;
}

void CPlayer::Rotate(DIRECTION direction) {
	auto position = m_pSprite->mPosition;
	auto velocity = m_pSprite->mVelocity;
	auto backbuffer = m_pSprite->getBackBuffer();

	delete m_pSprite;

	switch (direction)
	{
	case DIRECTION::DIR_FORWARD:
		m_pSprite = new Sprite("data/planeimgandmask.bmp", RGB(0xff, 0x00, 0xff));
		curentDirection = DIR_FORWARD;
		break;
	case DIRECTION::DIR_BACKWARD:
		m_pSprite = new Sprite("data/planeimgandmaskdown.bmp", RGB(0xff, 0x00, 0xff));
		curentDirection = DIR_BACKWARD;
		break;
	case DIRECTION::DIR_LEFT:
		m_pSprite = new Sprite("data/planeimgandmaskleft.bmp", RGB(0xff, 0x00, 0xff));
		curentDirection = DIR_LEFT;
		break;
	case DIRECTION::DIR_RIGHT:
		m_pSprite = new Sprite("data/planeimgandmaskright.bmp", RGB(0xff, 0x00, 0xff));
		curentDirection = DIR_RIGHT;
		break;
	}
	m_pSprite->mPosition = position;
	m_pSprite->mVelocity = velocity;
	m_pSprite->setBackBuffer(backbuffer);
}
