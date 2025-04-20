#include "utilities.h"
#include <cmath>
#include <algorithm>
#include <iostream>

sf::Vector2f geometry::pointOnSphere(float angle) {
        return { std::cos(angle), std::sin(angle) };
    }

std::vector<sf::Vector2f> geometry::roundedBoxPArray(const sf::Vector2f dimensions, const float corner_radius, const int points_per_corner) 
{    
    std::vector<sf::Vector2f> points;
    points.resize(points_per_corner * 4);
    
    sf::Vector2f corners[4]
    {
        {dimensions.x - corner_radius, corner_radius - dimensions.y },
        {dimensions.x - corner_radius, dimensions.y - corner_radius },
        {corner_radius - dimensions.x, dimensions.y - corner_radius },
        {corner_radius - dimensions.x, corner_radius - dimensions.y },
    };
    
    float angle_step = pi * 0.5 / (points_per_corner - 1);

    for (int corner = 0; corner < 4; corner++)
    {
        float angle = corner * pi * 0.5;

        for (int i = 0; i < points_per_corner; i++)
        {
            points[i + corner * points_per_corner] = (corners[corner] + corner_radius * pointOnSphere(angle - pi * 0.5));
            angle += angle_step;
        }
    }

    return points;
}