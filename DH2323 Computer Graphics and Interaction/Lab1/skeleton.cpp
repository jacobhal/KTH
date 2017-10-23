/*
 * SDL2 skeleton for lab assignments 1–3 of the KTH course DH2323,
 * Computer Graphics and Interaction (and also SU DA3001, Datalogi II).
 *
 * See README.md for details.
 */

#include <iostream>
#include "glm/glm.hpp"
#include "headers/SDL2Auxiliary.h"
#include <vector>


using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float f = SCREEN_HEIGHT/2;
const float VELOCITY = 0.001;
SDL2Aux *sdlAux;
vector<vec3> stars(1000);
int t;
float dt;
int trailDef = 25;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Draw2();
void Update();
void Interpolate(float, float, vector<float>&);
void Interpolate(vec3, vec3, vector<vec3>&);
float randomNumber(float, float);


// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[]) {

	// Seeding required to generate random numbers every execution
	srand (time(NULL)); // Remove this line if you want to run with the same random numbers every time

	// Generate star locations
	for(int i = 0; i < stars.size(); ++i) {
		stars[i].x = randomNumber(-1, 1);
		stars[i].y = randomNumber(-1, 1);
		stars[i].z = randomNumber(0, 1);
	}


	sdlAux = new SDL2Aux(SCREEN_WIDTH, SCREEN_HEIGHT);

	t = SDL_GetTicks();
	while (!sdlAux->quitEvent()) {
		Update();
		Draw();
		//Draw2();

	}

	sdlAux->saveBMP("screenshot.bmp");
	return 0;
}

void Draw() {

		sdlAux->clearPixels();

		int x, tx;
		int y, ty;
		for (size_t s = 0; s<stars.size(); ++s) {

			if (f * stars[s].x / stars[s].z + SCREEN_WIDTH / 2 > SCREEN_WIDTH || f * stars[s].y / stars[s].z + SCREEN_HEIGHT / 2 > SCREEN_HEIGHT) {

			}
			else
			{

				// Set color and convert 3d points to 2d
				vec3 color = 0.2f * vec3(1,1,1) / (stars[s].z*stars[s].z);

				x = (f * (stars[s].x / (stars[s].z))) + (SCREEN_WIDTH / 2);
				tx = (f * (stars[s].x / (stars[s].z + trailDef*0.01))) + (SCREEN_WIDTH / 2);

				y = (f * (stars[s].y / (stars[s].z))) + (SCREEN_HEIGHT / 2);
				ty = (f * (stars[s].y / (stars[s].z + trailDef*0.01))) + (SCREEN_HEIGHT / 2);

				vector<float> xtrail(trailDef);
				vector<float> ytrail(trailDef);

				Interpolate(x, tx, xtrail);
				Interpolate(y, ty, ytrail);

				for (int i = 0; i < trailDef; ++i) {
					sdlAux->putPixel(xtrail[i], ytrail[i], color);
				}
			}
		}

		sdlAux->render();
}

void Draw2() {

	vec3 topLeft(1, 0, 0); // red
	vec3 topRight(0, 0, 1); // blue
	vec3 bottomLeft(1, 1, 0); // yellow
	vec3 bottomRight(0, 1, 0); // green

	/*
	topLeft = vec3(0,0.001,0.9);
	topRight = vec3(0.9,0.7,0.999);
	bottomRight = vec3(0.9,0.1,0.4);
	bottomLeft = vec3(0,0.7,0.4);
*/

	vector<vec3> leftSide(SCREEN_HEIGHT);
	vector<vec3> rightSide(SCREEN_HEIGHT);
	Interpolate(topLeft, bottomLeft, leftSide); // Red to Yellow
	Interpolate(topRight, bottomRight, rightSide); // Blue to Green


	vector<vec3> color3(SCREEN_WIDTH);
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		Interpolate(leftSide[y], rightSide[y], color3); // Interpolate every row
		for (int x = 0; x < SCREEN_WIDTH; ++x) {

			sdlAux->putPixel(x, y, color3[x]);
		}
	}
	sdlAux->render();
}

void Update() {
	int t2 = SDL_GetTicks();
	dt = float(t2-t);
	t = t2;

	for(int i = stars.size(); i > 0; --i) {
		// Update star locations
		stars[i].z = stars[i].z - (VELOCITY * dt);

		// Check if new value for z is within the range 0 to 1, if not, increment/decrement
		if( stars[i].z <= 0 )
			stars[i].z += 1;
		if( stars[i].z > 1 )
			stars[i].z -= 1;


	}
}

void Interpolate(float a, float b, vector<float>& result) {

	int limit = result.size()-1;
	if(limit == 0) {
		result[0] = a;
	} else {
		for (int i = 0; i < result.size(); ++i) {
			result[i] = a + ((b - a) / limit) * i;
		}
	}

}

void Interpolate(vec3 a, vec3 b, vector<vec3>& result) {

	float size = result.size();
	float incx = a.x;
	float incy = a.y;
	float incz = a.z;

	if (size > 1) {
		incx = (b.x - a.x) / (size - 1);
		incy = (b.y - a.y) / (size - 1);
		incz = (b.z - a.z) / (size - 1);
	}

	for (int i = 0; i < result.size(); ++i) {
		result[i].x = a.x + i*incx;
		result[i].y = a.y + i*incy;
		result[i].z = a.z + i*incz;
	}
}

float randomNumber(float min, float max) {
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

