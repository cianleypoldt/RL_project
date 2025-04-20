#include "Simulation.h"

Simulation::Simulation(float timestep)
	: time_step(timestep)
{
}

Simulation::~Simulation()
{
}

void Simulation::reset()
{
	for (auto& body : m_rigid_bodies)
	{
		body.reset();
	}
}

void Simulation::update()
{
	for (auto& body : m_rigid_bodies) {
		integrate(*body);
	}

	// Handle collisions
	for (auto& body : m_rigid_bodies) {
		for (auto& otherBody : m_rigid_bodies) {
			if (&body != &otherBody && checkCollision(*body, *otherBody)) {
				resolveCollision(*body, *otherBody);
			}
		}
	}

	// Optionally apply constraints (e.g., joints, etc.)
	for (auto& constraint : m_constraints) {
		applyConstraint(*constraint->m_body_a, *constraint->m_body_b);
	}

}

void Simulation::graphicsUpdate()
{
}

std::shared_ptr<RigidBody> Simulation::addRigidBody(RigidBody& body)
{
	auto newBody = std::make_shared<RigidBody>(body);
	m_rigid_bodies.push_back(newBody);
	return newBody;
}

std::shared_ptr<Constraint> Simulation::addDistanceConstraint(RigidBody* body_a, RigidBody* body_b, float distance)
{
	auto constraint = std::make_shared<DistanceConstraint>(body_a, body_b, distance);
	m_constraints.push_back(constraint);
	return constraint;
}

void Simulation::removeRigidBody(RigidBody& body)
{
	for (auto it = m_rigid_bodies.begin(); it != m_rigid_bodies.end(); ++it)
	{
		if (it->get() == &body)
		{
			m_rigid_bodies.erase(it);
			break;
		}
	}
}

void Simulation::removeConstraint(std::shared_ptr<Constraint> constraint)
{
	for (auto it = m_constraints.begin(); it != m_constraints.end(); ++it)
	{
		if (it->get() == constraint.get())
		{
			m_constraints.erase(it);
			break;
		}
	}
}

void Simulation::integrate(RigidBody& body)
{
	sf::Vector2f velocity = body.position - body.previous_position;
	body.previous_position = body.position;
	body.position += velocity * time_step;
	body.angle += body.angular_velocity * time_step;
	body.angular_velocity = 0; // Reset angular velocity after integration
}

bool Simulation::checkCollision(RigidBody& bodyA, RigidBody& bodyB)
{
	return false;
}

void Simulation::resolveCollision(RigidBody& bodyA, RigidBody& bodyB)
{
}

void Simulation::applyConstraint(RigidBody& bodyA, RigidBody& bodyB)
{
}





