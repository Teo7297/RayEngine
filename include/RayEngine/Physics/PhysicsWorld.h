#pragma once

#include "RayEngine/Export.h"
#include <memory>
#include <vector>

// Forward declarations for Bullet types to avoid exposing Bullet headers to clients
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btCollisionShape;
class btRigidBody;

namespace RayEngine {
    namespace Physics {

        class RAYENGINE_API PhysicsWorld {
        public:
            PhysicsWorld();
            ~PhysicsWorld();

            // Update the physics simulation
            void Update(float deltaTime);

            // Create a box collision shape with the given dimensions
            btCollisionShape* CreateBoxShape(float width, float height, float depth);

            // Create a sphere collision shape with the given radius
            btCollisionShape* CreateSphereShape(float radius);

            // Add a rigid body to the world with the given shape, mass, and position
            btRigidBody* AddRigidBody(btCollisionShape* shape, float mass, float x, float y, float z);

            // Remove a rigid body from the world
            void RemoveRigidBody(btRigidBody* body);

            // Get the position and rotation of a rigid body
            void GetTransform(btRigidBody* body, float& x, float& y, float& z, float& rotX, float& rotY, float& rotZ);

        private:
            // Bullet physics components
            std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
            std::unique_ptr<btCollisionDispatcher> dispatcher;
            std::unique_ptr<btBroadphaseInterface> broadphase;
            std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
            std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld;

            // Keep track of shapes and bodies for cleanup
            std::vector<std::unique_ptr<btCollisionShape>> shapes;
            std::vector<std::unique_ptr<btRigidBody>> bodies;
        };

    } // namespace Physics
} // namespace RayEngine