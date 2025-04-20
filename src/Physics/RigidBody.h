#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

struct RigidBody
{
private:
	const sf::Vector2f m_starting_position;
	const sf::Vector2f m_starting_velocity;
	const float m_starting_angle;
	const float m_starting_inertia;

public:
	const float mass;
	sf::Vector2f position;
	sf::Vector2f previous_position;
	float angle;
	float inertia;

public:
	RigidBody(sf::Vector2f starting_position, sf::Vector2f starting_velocity, float mass, float angle = 0, float inertia = 0);

	void applyForce(sf::Vector2f force);

	void reset();
};

