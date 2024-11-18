#include "ASprite.h"

ASprite::ASprite() :
	m_pos(0,0),
	m_size(0,0)
{
	//Constructor
}

ASprite::~ASprite()
{
	//Destroy
}

void ASprite::SetPositionSprite(Vector2 vect2D)
{
	m_pos.m_x = vect2D.m_x;
	m_pos.m_y = vect2D.m_y;
}

void ASprite::SetSizeSprite(Vector2 size2D)
{
	m_size.m_x = size2D.m_x;
	m_size.m_y = size2D.m_y;
}
