#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

namespace geometry {

	constexpr float pi = 3.14159265358979323846f;

	sf::Vector2f pointOnSphere(float angle);

	std::vector<sf::Vector2f> roundedBoxPArray(sf::Vector2f dimensions, float cornerRadius, int pointsPerCorner);

}
