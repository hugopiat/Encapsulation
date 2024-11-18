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

void ASprite::SetPositionSprite(Maths::Vector2 vect2D)
{
	m_pos.SetX(vect2D.GetX() - (m_size.GetX() / 2));
	m_pos.SetY(vect2D.GetY() - (m_size.GetY() / 2));
}

void ASprite::SetSizeSprite(Maths::Vector2 size2D)
{
	m_size.SetX(size2D.GetX());
	m_size.SetY(size2D.GetY());
}
