#include <fstream>
#include <time.h>
#include <chrono>
#include <iostream>

#include "Maths.h"
#include "World.h"

#include "RenderObjects/Sphere.h"
#include "RenderObjects/Plane.h"

#define WIDTH 100
#define HEIGHT 100

#define SAMPLES_PER_PIXEL 100

float aspectRatio = (float)WIDTH / (float)HEIGHT;
float fov = 45.0f;

int main() {
    srand(time(NULL));

    World* world = new World();

    Material* whiteDiffuse = new Material(vec3f(0.8f, 0.8f, 0.8f), MaterialType::DIFFUSE, 0.0f);

    world->addRenderObject(new Sphere(vec3f(1.0f, 0.0f, -1.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(1.0f, 1.0f, 1.0f), whiteDiffuse));
    world->addRenderObject(new Sphere(vec3f(-1.0f, 0.5f, -3.0f), vec3f(0.0f, 0.0f, 0.0f), vec3f(1.0f, 1.0f, 1.0f), whiteDiffuse));
    //Floor
    world->addRenderObject(new Plane(vec3f(0.0f, -2.0f, 1.0f), vec3f(0.0f, 1.0f, 0.0f), vec3f(1.0f, 1.0f, 1.0f), new Material(vec3f(1.0f, 1.0f, 1.0f), MaterialType::DIFFUSE, 0.0f)));
    //Ceiling
    world->addRenderObject(new Plane(vec3f(0.0f, 3.1f, 0.0f), vec3f(0.0f, -1.0f, 0.0f), vec3f(1.0f, 1.0f, 1.0f), whiteDiffuse));
    //Light
    //world->addRenderObject(new Sphere(vec3f(0.0f, 2.0f, 0.0f), vec3f(0.0f, -1.0f, 0.0f), vec3f(1.0f, 1.0f, 1.0f), new Material(vec3f(1.0f, 1.0f, 1.0f), MaterialType::DIFFUSE, 5.0f)));
    world->addRenderObject(new Plane(vec3f(0.0f, 3.0f, -3.0f), vec3f(0.0f, -1.0f, 0.0f), vec3f(0.6f, 0.6f, 0.6f), new Material(vec3f(1.0f, 1.0f, 1.0f), MaterialType::DIFFUSE, 5.0f)));
    //Left wall
    world->addRenderObject(new Plane(vec3f(-3.0f, 0.0f, 0.0f), vec3f(1.0f, 0.0f, 0.0f), vec3f(1.0f, 1.0f, 1.0f), new Material(vec3f(1.0f, 0.0f, 0.0f), MaterialType::DIFFUSE, 0.0f)));
    //Right Wall
    world->addRenderObject(new Plane(vec3f(3.0f, 0.0f, 0.0f), vec3f(-1.0f, 0.0f, 0.0f), vec3f(1.0f, 1.0f, 1.0f), new Material(vec3f(0.0f, 1.0f, 0.0f), MaterialType::DIFFUSE, 0.0f)));
    //Back wall
    world->addRenderObject(new Plane(vec3f(0.0f, 0.0f, -5.0f), vec3f(0.0f, 0.0f, 1.0f), vec3f(1.0f, 1.0f, 1.0f), new Material(vec3f(0.0f, 0.0f, 1.0f), MaterialType::DIFFUSE, 0.0f)));

    vec3f* image = new vec3f[WIDTH * HEIGHT];

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < WIDTH * HEIGHT; i ++) {
        int xIndex = i % WIDTH;
        int yIndex = i / HEIGHT;
        float x = (2 * (xIndex + 0.5f) / (float)WIDTH - 1) * tan(fov / 2.f) * aspectRatio;
        float y = -(2 * (yIndex + 0.5f) / (float)HEIGHT - 1) * tan(fov / 2.f) / aspectRatio;

        vec3f pos = vec3f(0.0f, 0.0f, 3.0f);
        vec3f dir = vec3f(x, y, -1.f).normalise();
        vec3f col = vec3f(0.0f, 0.0f, 0.0f);

        #pragma omp parrallel for
        for (int j = 0; j < SAMPLES_PER_PIXEL; j++) {
            vec3f temp = vec3f(0.0f, 0.0f, 0.0f);
            world->render(pos, dir, 0, temp);
            col = col + temp;
            
        }
        col = col / SAMPLES_PER_PIXEL;
        col = vec3<float>::clamp(col, 0.0f, 1.0f);

        image[i] = col;
    }

    std::ofstream ofs;
    ofs.open("./image.ppm");
    ofs << "P3\n" << WIDTH << " " << HEIGHT << "\n255";
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (i % WIDTH == 0) ofs << "\n";
        ofs << (int)(image[i].x * 255) << " ";
        ofs << (int)(image[i].y * 255) << " ";
        ofs << (int)(image[i].z * 255) << " ";
    }
    ofs.close();

    auto endTime = std::chrono::high_resolution_clock::now();
    auto timeTook = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count();

    std::cout << "Took: " << timeTook << " mins" << std::endl;
    std::cin.get();
}