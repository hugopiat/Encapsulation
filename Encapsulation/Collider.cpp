#include "Collider.h"

Collider::Collider() :
	m_owner(nullptr),
	m_velocity(0.0f)
{
	m_collisionTypeTargets = std::vector<CollisionType>();
}

void* Collider::GetOwner() const
{
	return m_owner;
}

void Collider::SetOwner(void* owner)
{
	m_owner = owner;
}

void Collider::SetOnCollisionEnterCallback(CollisionCallback callback)
{
	m_onCollisionEnter = callback;
}

void Collider::TriggerOnCollisionEnter(Collider& other)
{
	if (m_onCollisionEnter) 
	{
		m_onCollisionEnter(other);
	}
}

void Collider::InitAllCollisionTypeTarget()
{
	for(int i = 0; i < (int)CollisionType::Size; i++)
	{
		AddCollisionTypeTarget((CollisionType)i);
	}
}

void Collider::RemovedAllTypeTarget()
{
	for (int i = 0; i < m_collisionTypeTargets.size(); i++)
	{
		RemovedCollisionTypeTarget((CollisionType)i);
	}
}

void Collider::RemovedCollisionTypeTarget(CollisionType collisionType)
{
	m_collisionTypeTargets.erase(
		std::remove(m_collisionTypeTargets.begin(), m_collisionTypeTargets.end(), collisionType),
		m_collisionTypeTargets.end());
}

void Collider::AddCollisionTypeTarget(CollisionType collisionType)
{
	m_collisionTypeTargets.push_back(collisionType);
}

bool Collider::IsACollisionTypeTarget(CollisionType collisionType)
{
	for (int i = 0; i < m_collisionTypeTargets.size(); i++)
	{
		if (m_collisionTypeTargets[i] == collisionType) 
		{
			return true;
		}
	}
	return false;
}

Maths::Vector2 Collider::GetNormal()
{
	return m_normalIntersection;
}

void Collider::SetNormal(const Maths::Vector2& normal)
{
	m_normalIntersection = normal;
}

void Collider::SetNormalBounds(int dx, int dy)
{
	Maths::Vector2 direction = Maths::Vector2(0, 0);
	if (dx >= 0)
	{
		direction += Maths::Vector2(1.0f, 0);
	}
	else if (dx < 0)
	{
		direction += Maths::Vector2(-1.0f, 0);
	}

	if (dy >= 0)
	{
		direction += Maths::Vector2(0, 1.0f);
	}
	else if (dy < 0)
	{
		direction += Maths::Vector2(0, -1.0f);
	}

	SetNormal(direction);
}
