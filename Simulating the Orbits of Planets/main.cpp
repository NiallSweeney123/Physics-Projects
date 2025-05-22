#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <filesystem>

const double G = 6.67430e-11; // gravitational constant
const double TIME_STEP = 1000; // seconds per step
const int STEPS = 10000;

struct Vector2D {
    double x, y;

    Vector2D operator+(const Vector2D& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2D operator-(const Vector2D& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2D operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D normalized() const {
        double mag = magnitude();
        return {x / mag, y / mag};
    }
};

struct Body {
    std::string name;
    double mass;
    Vector2D position;
    Vector2D velocity;
    Vector2D force;
};

void computeForces(std::vector<Body>& bodies) {
    for (auto& body : bodies) {
        body.force = {0, 0};
    }
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            Vector2D delta = bodies[j].position - bodies[i].position;
            double dist = delta.magnitude() + 1e-5;
            double forceMagnitude = G * bodies[i].mass * bodies[j].mass / (dist * dist);
            Vector2D forceDirection = delta.normalized();
            Vector2D force = forceDirection * forceMagnitude;

            bodies[i].force = bodies[i].force + force;
            bodies[j].force = bodies[j].force - force;
        }
    }
}

void updateBodies(std::vector<Body>& bodies, double dt) {
    for (auto& body : bodies) {
        Vector2D acceleration = body.force * (1.0 / body.mass);
        body.velocity = body.velocity + acceleration * dt;
        body.position = body.position + body.velocity * dt;
    }
}

int main() {
    std::vector<Body> bodies = {
        {"Sun", 1.989e30, {0, 0}, {0, 0}},
        {"Earth", 5.972e24, {1.496e11, 0}, {0, 29780}},
        {"Mars", 6.39e23, {2.279e11, 0}, {0, 24077}}
    };

    // Use an absolute path to force saving in your project folder:
    std::string filename = "H:/Physics-Projects/Simulating the Orbits of Planets/orbits.csv";

    std::cout << "Saving data to: " << std::filesystem::absolute(filename) << std::endl;

    std::ofstream file(filename);
    file << "step,name,x,y\n";

    for (int step = 0; step < STEPS; ++step) {
        computeForces(bodies);
        updateBodies(bodies, TIME_STEP);

        for (const auto& body : bodies) {
            file << step << "," << body.name << "," << body.position.x << "," << body.position.y << "\n";
        }
    }

    file.close();

    std::cout << "Simulation complete. Data saved to '" << filename << "'." << std::endl;

    return 0;
}
