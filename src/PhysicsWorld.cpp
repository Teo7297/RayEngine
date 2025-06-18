#include "RayEngine/Physics/PhysicsWorld.h"

// Include Bullet Physics headers
#include <btBulletDynamicsCommon.h>

namespace RayEngine {
namespace Physics {

PhysicsWorld::PhysicsWorld() {
    // Initialize Bullet Physics
    collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    dispatcher = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());
    broadphase = std::make_unique<btDbvtBroadphase>();
    solver = std::make_unique<btSequentialImpulseConstraintSolver>();
    dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(
        dispatcher.get(),
        broadphase.get(),
        solver.get(),
        collisionConfiguration.get()
    );

    // Set gravity
    dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

PhysicsWorld::~PhysicsWorld() {
    // Clear all bodies first
    for (auto& body : bodies) {
        dynamicsWorld->removeRigidBody(body.get());
    }
    bodies.clear();
    
    // Then clear shapes
    shapes.clear();
    
    // The unique_ptrs will handle the rest of cleanup
}

void PhysicsWorld::Update(float deltaTime) {
    // Step the physics simulation
    dynamicsWorld->stepSimulation(deltaTime, 10);
}

btCollisionShape* PhysicsWorld::CreateBoxShape(float width, float height, float depth) {
    auto shape = std::make_unique<btBoxShape>(btVector3(width/2.0f, height/2.0f, depth/2.0f));
    btCollisionShape* shapePtr = shape.get();
    shapes.push_back(std::move(shape));
    return shapePtr;
}

btCollisionShape* PhysicsWorld::CreateSphereShape(float radius) {
    auto shape = std::make_unique<btSphereShape>(radius);
    btCollisionShape* shapePtr = shape.get();
    shapes.push_back(std::move(shape));
    return shapePtr;
}

btRigidBody* PhysicsWorld::AddRigidBody(btCollisionShape* shape, float mass, float x, float y, float z) {
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(x, y, z));
    
    btVector3 localInertia(0, 0, 0);
    if (mass > 0.0f) {
        shape->calculateLocalInertia(mass, localInertia);
    }
    
    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
    auto body = std::make_unique<btRigidBody>(rbInfo);
    
    dynamicsWorld->addRigidBody(body.get());
    btRigidBody* bodyPtr = body.get();
    bodies.push_back(std::move(body));
    
    return bodyPtr;
}

void PhysicsWorld::RemoveRigidBody(btRigidBody* body) {
    // Find and remove the body
    for (auto it = bodies.begin(); it != bodies.end(); ++it) {
        if (it->get() == body) {
            dynamicsWorld->removeRigidBody(body);
            bodies.erase(it);
            return;
        }
    }
}

void PhysicsWorld::GetTransform(btRigidBody* body, float& x, float& y, float& z, float& rotX, float& rotY, float& rotZ) {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    
    // Position
    btVector3 position = transform.getOrigin();
    x = position.x();
    y = position.y();
    z = position.z();
    
    // Rotation (Euler angles)
    btQuaternion rotation = transform.getRotation();
    btScalar yaw, pitch, roll;
    transform.getBasis().getEulerYPR(yaw, pitch, roll);
    
    rotX = roll;
    rotY = pitch;
    rotZ = yaw;
}

} // namespace Physics
} // namespace RayEngine