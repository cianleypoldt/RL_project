#pragma once
#include "RigidBody.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Constraint
{
public:
	RigidBody* m_body_a;
	RigidBody* m_body_b;

};

class DistanceConstraint : public Constraint
{
public:
	float m_distance;

	DistanceConstraint(RigidBody* body_a, RigidBody* body_b, float distance) : m_distance(distance) {}

};