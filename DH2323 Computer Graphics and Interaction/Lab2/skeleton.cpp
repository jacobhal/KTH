#include <iostream>
#include "glm/glm.hpp"
#include <SDL.h>
#include "SDL2auxiliary.h"
#include "TestModel.h"
#include <algorithm>
#include <math.h>

using namespace std;
using glm::vec3;
using glm::mat3;

// ----------------------------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 200;
const int SCREEN_HEIGHT = 200;
SDL2Aux *sdlAux;

vector<Triangle> triangles;
float focalLength = SCREEN_HEIGHT / 2;
vec3 cameraPos(0, 0, -2);
mat3 cameraRot;
float yaw;

float m = std::numeric_limits<float>::max();

int t;

// Light sources
vec3 lightPos(0, -0.5, -0.7);
vec3 lightColor = 14.f * vec3( 1, 1, 1 ); // Describes the power P, energy per time unit of emitted light for each color component.
vec3 indirectLight = 0.5f*vec3( 1, 1, 1 );

// ----------------------------------------------------------------------------
// Structs

struct Ray {
	vec3 start;
	vec3 direction;

	Ray(vec3 s, vec3 d)
			: start(s), direction(d) {}

};

struct Intersection {
	vec3 position;
	float distance;
	int triangleIndex;

	Intersection(vec3 pos, float d, int i)
			: position(pos), distance(d), triangleIndex(i) {}

	void print() {
		cout << "Position: " << position.x << ", " << position.y << ", " << position.z << "\n"
		<< "Distance: " << distance << "\n"
		<< "Index: " << triangleIndex << "\n";
	}

};

// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();
vec3 ComputePosition(Triangle, float, float);
vec3 ComputeIntersection(const Triangle&, const Ray&, Intersection&);
bool ClosestIntersection(Ray, const vector<Triangle>&, Intersection&);
vec3 DirectLight(const Intersection& i);

// Helper functions
float determinant(const vec3& v1, const vec3& v2, const vec3& v3);

float dot(vec3, vec3);


int main(int argc, char* argv[])
{
	sdlAux = new SDL2Aux(SCREEN_WIDTH, SCREEN_HEIGHT);
	t = SDL_GetTicks();	// Set start value for timer.

	LoadTestModel(triangles);

	while (!sdlAux->quitEvent()) {
		Update();
		Draw();
	}

	sdlAux->saveBMP("screenshot.bmp");
	return 0;
}
/*
 * Update every frame.
 */
void Update()
{
	// Compute frame time:
	int t2 = SDL_GetTicks();
	float dt = float(t2 - t);
	t = t2;
	cout << "Render time: " << dt << " ms." << endl;

	float x = cameraPos.x;
	float y = cameraPos.y;
	float z = cameraPos.z;

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_UP]) {
		// Move camera forward
		z += 0.1;
	}
	if (keystate[SDL_SCANCODE_DOWN]) {
		// Move camera backward
		z -= 0.1;

	}
	if (keystate[SDL_SCANCODE_LEFT]) {
		// Move camera to the left
		yaw -= 5;
		cameraRot[0][0] = cos(yaw*0.0174533);
		cameraRot[0][1] = 0;
		cameraRot[0][2] = sin(yaw*0.0174533);

		cameraRot[1][0] = 0;
		cameraRot[1][1] = 1;
		cameraRot[1][2] = 0;

		cameraRot[2][0] = -sin(yaw*0.0174533);
		cameraRot[2][1] = 0;
		cameraRot[2][2] = cos(yaw*0.0174533);

	}
	if (keystate[SDL_SCANCODE_RIGHT]) {
		// Move camera to the right
		yaw += 5;
		cameraRot[0][0] = cos(yaw*0.0174533);
		cameraRot[0][1] = 0;
		cameraRot[0][2] = sin(yaw*0.0174533);

		cameraRot[1][0] = 0;
		cameraRot[1][1] = 1;
		cameraRot[1][2] = 0;

		cameraRot[2][0] = -sin(yaw*0.0174533);
		cameraRot[2][1] = 0;
		cameraRot[2][2] = cos(yaw*0.0174533);
	}
	if(keystate[SDL_SCANCODE_W]) {
		lightPos.z += 0.1;
	}
	if(keystate[SDL_SCANCODE_S]) {
		lightPos.z -= 0.1;
	}
	if(keystate[SDL_SCANCODE_A]) {
		lightPos.x -= 0.1;
	}
	if(keystate[SDL_SCANCODE_D]) {
		lightPos.x += 0.1;
	}
	if(keystate[SDL_SCANCODE_Q]) {
		lightPos.y -= 0.1;
	}
	if(keystate[SDL_SCANCODE_E]) {
		lightPos.y += 0.1;
	}

	cameraPos = vec3(x, y, z);
}
/*
 * Draw function.
 */
void Draw()
{
	sdlAux->clearPixels();

	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{

			vec3 d(x - SCREEN_WIDTH / 2, y - SCREEN_HEIGHT / 2, focalLength);
			Intersection closestIntersection(vec3(0, 0, 0), m, 0);
			if (ClosestIntersection(Ray(cameraPos, d*cameraRot), triangles, closestIntersection)) {
				vec3 color1 = triangles[closestIntersection.triangleIndex].color;
				vec3 D = DirectLight(closestIntersection);
				vec3 color = color1*(D+indirectLight);
				sdlAux->putPixel(x, y, color);
			}
		}
	}


	sdlAux->render();
}

/*
 * Perform intersection computations.
 */
vec3 ComputeIntersection(const Triangle& triangle, const Ray& ray, Intersection& closestIntersection) {
	vec3 b = ray.start - triangle.v0;
	//mat3 A(-ray.direction, triangle.e1, triangle.e2);

	float D = determinant(-ray.direction, triangle.e1, triangle.e2);
	float Dx = determinant(b, triangle.e1, triangle.e2);

	float x = Dx / D;

	if (x > 0 && x < closestIntersection.distance) {

		float Dy = determinant(-ray.direction, b, triangle.e2);

		float y = Dy / D;

		float Dz = determinant(-ray.direction, triangle.e1, b);

		float z = Dz / D;

		vec3 X(x, y, z);
		return X;

	}
}
/*
 * Calculate the closest intersection for every triangle against a specific ray. If one is found, return true.
 * The intersection should occur within the triangle and after the beginning of the ray.
 */
bool ClosestIntersection(Ray ray, const vector<Triangle>& triangles, Intersection& closestIntersection) {

	for (int i = 0; i < triangles.size(); ++i) {
		// Compute intersection for this ray and every triangle
		vec3 isec = ComputeIntersection(triangles[i], ray, closestIntersection);
		// Check equation requirements
		if (isec.y >= 0.f && isec.z >= 0.f && isec.y + isec.z <= 1.f && isec.x >= 0.f) {
			// Set this one to the new closest intersection if it is greater than the previous
			if (closestIntersection.distance > Intersection(ComputePosition(triangles[i], isec.y, isec.z), isec.x, i).distance)
				closestIntersection = Intersection(ComputePosition(triangles[i], isec.y, isec.z), isec.x, i);
		}
	}

	if (closestIntersection.distance != m) {
		return true;
	}

	return false;
}

/*
 * Returns the direct illumination for a specific intersection.
 */
vec3 DirectLight(const Intersection& i) {
	float distanceBetweenPoints = glm::distance(i.position, lightPos);
	float A = 4 * M_PI * pow(distanceBetweenPoints, 2);
	float fraction = std::max(dot(triangles[i.triangleIndex].normal, glm::normalize(lightPos - i.position)), (float) 0);

	Ray r(i.position, glm::normalize(lightPos - i.position));

	Intersection closestIntersection(vec3(0,0,0), m, 0);
	ClosestIntersection(r, triangles, closestIntersection);
	if(closestIntersection.distance < distanceBetweenPoints && closestIntersection.triangleIndex != i.triangleIndex) {
		return vec3(0,0,0);
	} else {
		return (lightColor * fraction) / A;
	}
}


/**
 * ----------Helper functions------------
 */

/*
 * Any coordinate in the plane of a triangle can be described by two scalar coordinates u and v.
 */
vec3 ComputePosition(Triangle triangle, float u, float v) {
	vec3 pos = triangle.v0 + u*triangle.e1 + v*triangle.e2;
	return pos;
}
/*
 * Calculate determinant.
 */
float determinant(const vec3& v1, const vec3& v2, const vec3& v3) {
	return v1.x*v2.y*v3.z + v1.y*v2.z*v3.x + v1.z*v2.x*v3.y - v1.z*v2.y*v3.x - v1.y*v2.x*v3.z - v1.x*v2.z*v3.y;
}

float dot(vec3 one, vec3 two) {
	return (one.x * two.x +
			one.y * two.y +
			one.z * two.z);
}
