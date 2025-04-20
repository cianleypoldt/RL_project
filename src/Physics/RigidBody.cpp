#include "RigidBody.h"

RigidBody::RigidBody(sf::Vector2f starting_position, sf::Vector2f starting_velocity, float mass, float angle, float inertia)
	: m_starting_position(starting_position), m_starting_velocity(starting_velocity), m_starting_angle(angle), m_starting_inertia(inertia),
	position(starting_position), previous_position(starting_position - starting_velocity), mass(mass), angle(angle), inertia(inertia)
{
}

void RigidBody::applyForce(sf::Vector2f force)
{
	previous_position -= force / mass;
}

void RigidBody::reset()
{
	position = m_starting_position;
	previous_position = m_starting_position - m_starting_velocity;
	angle = m_starting_angle;
	inertia = m_starting_inertia;
}