#include <raylib.h>
#include <raymath.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int numberOfCircles = 2;
const float FPS = 60;
const float TIMESTEP = 1 / FPS; // Sets the timestep to 1 / FPS. But timestep can be any very small value.
const float FRICTION = 0.5;


struct Ball {
    Vector2 position;
    float radius;
    Color color;

    float mass;
    float inverse_mass; // A variable for 1 / mass. Used in the calculation for acceleration = sum of forces / mass
    Vector2 acceleration;
    Vector2 velocity;
};

int main() {
    Ball ball;
    ball.position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    ball.radius = 50.0f;
    ball.color = RED;
    ball.mass = 1.0f;
    ball.inverse_mass = 1 / ball.mass;
    ball.acceleration = Vector2Zero();
    ball.velocity = Vector2Zero();

    Ball ball2;
    ball2.position = {WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4};
    ball2.radius = 50.0f;
    ball2.color = BLUE;
    ball2.mass = 3.0f;
    ball2.inverse_mass = 1 / ball.mass;
    ball2.acceleration = Vector2Zero();
    ball2.velocity = Vector2Zero();

    Ball ballArray[numberOfCircles] = {ball, ball2};

    int elasticityCoefficient = 1;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Physics Demo");

    SetTargetFPS(FPS);

    float accumulator = 0;

    while (!WindowShouldClose()) {
        float delta_time = GetFrameTime();
        Vector2 forces = Vector2Zero(); // every frame set the forces to a 0 vector

        // Adds forces with the magnitude of 100 in the direction given by WASD inputs
        if(IsKeyDown(KEY_W)) {
            forces = Vector2Add(forces, {0, -100});
        }
        if(IsKeyDown(KEY_A)) {
            forces = Vector2Add(forces, {-100, 0});
        }
        if(IsKeyDown(KEY_S)) {
            forces = Vector2Add(forces, {0, 100});
        }
        if(IsKeyDown(KEY_D)) {
            forces = Vector2Add(forces, {100, 0});
        }

        // Does Vector - Scalar multiplication with the sum of all forces and the inverse mass of the ball
        ball.acceleration = Vector2Scale(forces, ball.inverse_mass);
        
        // Physics step
        accumulator += delta_time;
        while(accumulator >= TIMESTEP) {
            // Computes for velocity using v(t + dt) = v(t) + (a(t) * dt)
            ball.velocity = Vector2Add(ball.velocity, Vector2Scale(ball.acceleration, TIMESTEP));
            ball.velocity = Vector2Subtract(ball.velocity, Vector2Scale(ball.velocity, FRICTION * ball.inverse_mass * TIMESTEP));
            // Computes for change in position using x(t + dt) = x(t) + (v(t + dt) * dt)
            ball.position = Vector2Add(ball.position, Vector2Scale(ball.velocity, TIMESTEP));
            Vector2 n = Vector2Subtract(ball.position, ball2.position);
            float collisionMag = Vector2Length(ball.position);
            float j = -( (1+elasticityCoefficient)*(Vector2DotProduct(Vector2Subtract(ball.velocity, ball2.velocity), n)
                        / (Vector2DotProduct(n,n))*(1/ball.mass)+(1/ball2.mass) ));
            // Negates the velocity at x and y if the object hits a wall. (Basic Collision Detection)
            if(ball.position.x + ball.radius >= WINDOW_WIDTH || ball.position.x - ball.radius <= 0) {
                ball.velocity.x *= -1;
            }
            if(ball.position.y + ball.radius >= WINDOW_HEIGHT || ball.position.y - ball.radius <= 0) {
                ball.velocity.y *= -1;
            }
            if(/*ball.position.x + ball.radius >= ball2.position.x - ball2.radius ||
            ball.position.x - ball.radius <= ball2.position.x + ball2.radius*/
            CheckCollisionCircles(ball.position, ball.radius, ball2.position, ball2.radius)){
                ball.velocity = Vector2Add(ball.velocity, Vector2Scale(n, (j/ball.mass) ));
            }



            ball2.velocity = Vector2Add(ball2.velocity, Vector2Scale(ball2.acceleration, TIMESTEP));
            ball2.velocity = Vector2Subtract(ball2.velocity, Vector2Scale(ball2.velocity, FRICTION * ball2.inverse_mass * TIMESTEP));
            ball2.position = Vector2Add(ball2.position, Vector2Scale(ball2.velocity, TIMESTEP));
            if(ball2.position.x + ball2.radius >= WINDOW_WIDTH || ball2.position.x - ball2.radius <= 0) {
                ball2.velocity.x *= -1;
            }
            if(ball2.position.y + ball2.radius >= WINDOW_HEIGHT || ball2.position.y - ball2.radius <= 0) {
                ball2.velocity.y *= -1;
            }
            if(CheckCollisionCircles(ball2.position, ball2.radius, ball.position, ball.radius)){
                ball2.velocity = Vector2Add(ball2.velocity, Vector2Scale(n, (j/ball2.mass) ));
            }
            // ------ SEMI-IMPLICIT EULER INTEGRATION -------
            // Computes for velocity using v(t + dt) = v(t) + (a(t) * dt)
            

            accumulator -= TIMESTEP;
        }

        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircleV(ball.position, ball.radius, ball.color);
        DrawCircleV(ball2.position, ball2.radius, ball2.color);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}