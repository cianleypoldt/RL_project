#pragma once
#include "Simulation.h"
#include "RigidBody.h"
#include "Constraint.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

class Simulation
{
private:
	std::vector<std::shared_ptr<RigidBody>> m_rigid_bodies;
	std::vector<std::shared_ptr<Constraint>> m_constraints;

	float time_step;

public:
	Simulation(float timestep);
	~Simulation();

	void reset();
	void update();
	void graphicsUpdate();

	std::shared_ptr<RigidBody> addRigidBody(RigidBody& body);
	std::shared_ptr<Constraint> addDistanceConstraint(RigidBody* body_a, RigidBody* body_b, float distance);
	void removeRigidBody(RigidBody& body);
	void removeConstraint(std::shared_ptr<Constraint> constraint);

	void integrate(RigidBody& body);
	bool checkCollision(RigidBody& bodyA, RigidBody& bodyB);
	void resolveCollision(RigidBody& bodyA, RigidBody& bodyB);
	void applyConstraint(RigidBody& bodyA, RigidBody& bodyB);
};
