#ifndef SHMUP_GAMEOBJECT_H
#define SHMUP_GAMEOBJECT_H

#include <memory>
#include <glm/vec2.hpp>
#include "LoaderParams.h"

typedef glm::vec2 vec2;

class GameObject {
public:
    virtual void draw() = 0;

    virtual void update() = 0;

    virtual void clean() = 0;

    virtual void load(std::unique_ptr<LoaderParams> pParams) = 0;

    virtual ~GameObject() = default;

    explicit GameObject(int id) : m_id(id) {};

    inline int getId() { return m_id; };

private:
    int m_id{0};
};

class Collidable {
public:
    virtual inline const vec2 upperLeft() = 0;

    virtual inline const vec2 lowerRight() = 0;

    virtual void collided(const Collidable &collider) = 0;
};

class Positionable {
protected:
    vec2 m_position{};

public:
    inline const vec2 &getPosition() const { return m_position; }
};

class Movable {
protected:
    vec2 m_velocity{};
    vec2 m_acceleration{};

public:

    inline const vec2 &getVelocity() const { return m_velocity; }

    inline const vec2 &getAcceleration() const { return m_acceleration; }

};

#endif  // SHMUP_GAMEOBJECT_H
