#include "raylib.h"
#include "raymath.h"
#include "RayEngine/Physics/PhysicsWorld.h"
#include <vector>
#include <iostream>

// Structure to store physics object and its visual representation
struct PhysicsObject {
    btRigidBody* body;
    Color color;
    Vector3 size; // for box (width, height, depth) or for sphere (radius, 0, 0)
    bool isSphere;
};

// Main game loop
void RunPhysicsExample() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "RayEngine - Physics Example");

    // Initialize camera
    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 10.0f, 20.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Initialize physics
    RayEngine::Physics::PhysicsWorld physicsWorld;

    // Create ground
    btCollisionShape* groundShape = physicsWorld.CreateBoxShape(20.0f, 1.0f, 20.0f);
    btRigidBody* groundBody = physicsWorld.AddRigidBody(groundShape, 0.0f, 0.0f, -0.5f, 0.0f); // Mass 0 = static

    // List of objects for rendering
    std::vector<PhysicsObject> objects;

    // Add ground to objects
    objects.push_back({ groundBody, DARKGREEN, {20.0f, 1.0f, 20.0f}, false });

    // Create some falling boxes
    for(int i = 0; i < 5; i++) {
        float size = 1.0f;
        btCollisionShape* boxShape = physicsWorld.CreateBoxShape(size, size, size);
        btRigidBody* boxBody = physicsWorld.AddRigidBody(boxShape, 1.0f,
            (float)(i - 2) * 2.0f,
            10.0f + i * 2.0f,
            0.0f);
        objects.push_back({ boxBody, RED, {size, size, size}, false });
    }

    // Create some falling spheres
    for(int i = 0; i < 5; i++) {
        float radius = 0.7f;
        btCollisionShape* sphereShape = physicsWorld.CreateSphereShape(radius);
        btRigidBody* sphereBody = physicsWorld.AddRigidBody(sphereShape, 1.0f,
            (float)(i - 2) * 2.0f,
            5.0f + i * 2.0f,
            -5.0f);
        objects.push_back({ sphereBody, BLUE, {radius, 0.0f, 0.0f}, true });
    }

    SetTargetFPS(60);

    // Main game loop
    while(!WindowShouldClose()) {
        // Update physics
        physicsWorld.Update(1.0f / 60.0f);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw all objects
        for(const auto& obj : objects) {
            float x, y, z, rotX, rotY, rotZ;
            physicsWorld.GetTransform(obj.body, x, y, z, rotX, rotY, rotZ);

            // Draw the object based on its type
            if(obj.isSphere) {
                DrawSphere(Vector3{ x, y, z }, obj.size.x, obj.color);
            }
            else {
                // Convert Bullet's rotation to a matrix
                Matrix rotMatrix = MatrixRotateXYZ(Vector3{ rotX, rotY, rotZ });

                // Create a transformation matrix
                Vector3 position = { x, y, z };
                Vector3 scale = { obj.size.x, obj.size.y, obj.size.z };
                Matrix transform = MatrixMultiply(
                    MatrixMultiply(
                        MatrixScale(scale.x, scale.y, scale.z),
                        rotMatrix
                    ),
                    MatrixTranslate(position.x, position.y, position.z)
                );

                // Draw the box
                DrawCubeWires(position, obj.size.x, obj.size.y, obj.size.z, BLACK);
                DrawCube(position, obj.size.x, obj.size.y, obj.size.z, obj.color);
            }
        }

        // Draw coordinate system
        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Controls: Arrow keys to navigate, Space to add sphere", 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
}

int main() {
    RunPhysicsExample();
    return 0;
}