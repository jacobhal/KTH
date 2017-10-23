#include <iostream>
#include "glm/glm.hpp"
#include <SDL.h>
#include "SDL2auxiliary.h"
#include "TestModel.h"

using namespace std;
using glm::vec3;
using glm::vec2;
using glm::ivec2;
using glm::mat3;


// ----------------------------------------------------------------------------
// STRUCTS

struct Pixel
{
	int x;
	int y;
	float zinv;
	vec3 illumination;
	vec3 pos3d;


	Pixel(int a, int b, float z, vec3 pos)
			: x(a), y(b), zinv(z), pos3d(pos) {}
	Pixel(int a, int b, float z, vec3 i, vec3 pos)
			: x(a), y(b), zinv(z), illumination(i), pos3d(pos) {}

	Pixel(const Pixel& rhs)
			: x(rhs.x), y(rhs.y), zinv(rhs.zinv), illumination(rhs.illumination), pos3d(rhs.pos3d) {}

	Pixel() = default;

	Pixel operator/(float scalar) {
		return Pixel( x / scalar,
					  y / scalar,
					  zinv / scalar,
		              illumination / scalar,
					  pos3d / scalar);
	}

	Pixel operator-(const Pixel& rhs) {
		return Pixel( x - rhs.x,
					  y - rhs.y,
					  zinv - rhs.zinv,
		              illumination - rhs.illumination,
		   			  pos3d - rhs.pos3d);
	}

	Pixel operator+(const Pixel& rhs) {
		return Pixel( x + rhs.x,
					  y + rhs.y,
					  zinv + rhs.zinv,
					  illumination + rhs.illumination,
					  pos3d + rhs.pos3d);
	}

	Pixel& operator+=(const Pixel& rhs)
	{
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		this->zinv = this->zinv + rhs.zinv;
		this->illumination = this->illumination + rhs.illumination;
		this->pos3d = this->pos3d + rhs.pos3d;


		return *this; // return the result by reference
	}

	Pixel& operator=(const Pixel& rhs) {
		this->x = 		rhs.x;
		this->y = 		rhs.y;
		this->zinv = 	rhs.zinv;
		this->illumination = 	rhs.illumination;
		this->pos3d = rhs.pos3d;

		return *this;
	}

	Pixel& abs() {
		Pixel p(std::abs(x), std::abs(y), zinv, illumination, pos3d);
		return p;
	}

};

struct Vertex
{
	vec3 position;

	Vertex() = default;
	Vertex(vec3 v, vec3 norm, vec3 ref)
			: position(v){}
};

// ----------------------------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;
SDL2Aux *sdlAux;

vector<Triangle> triangles;
float depthBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
int t;

float f = SCREEN_HEIGHT / 2;

vec3 cameraPos(0, 0, -3.001);
mat3 R;
float yaw = 0; // Yaw angle controlling camera rotation around y-axis
vec3 currentColor;

vec3 lightPos(0,-0.5,-0.7);
vec3 lightPower = 14.f*vec3( 1, 1, 1 );
vec3 indirectLightPowerPerArea = 0.5f*vec3( 1, 1, 1 );

vec3 currentNormal;
vec3 currentReflectance;


// ----------------------------------------------------------------------------
// FUNCTIONS

void Update();
void Draw();

void VertexShader(const vec3& v, ivec2& p);
void Interpolate(ivec2, ivec2, vector<ivec2>&);

void DrawLineSDL(ivec2, ivec2, vec3);
void DrawPolygonEdges(const vector<vec3>&);
void DrawPolygon( const vector<vec3>&);
void ComputePolygonRows(const vector<ivec2>&, vector<ivec2>&, vector<ivec2>&);
void DrawRows(const vector<ivec2>&, const vector<ivec2>&);


/*
 * Using Pixel instead of ivec2
 */
void ComputePolygonRows2(const vector<Pixel>&, vector<Pixel>&, vector<Pixel>&);
void DrawRows2(const vector<Pixel>&, const vector<Pixel>&);
void VertexShader2(const Vertex&, Pixel& p);
void DrawPolygon2( const vector<Vertex>& vertices );
void Interpolate2(Pixel, Pixel, vector<Pixel>&);
void PixelShader( const Pixel& p );
vec3 ReflectedLight(const vec3& v);

/*
 * Helper functions declarations
 */
int getPixelSize(const ivec2&, const ivec2&);
int getPixelSize2(Pixel, Pixel);

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

	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	float convert = 0.0174533;
	float x = cameraPos.x;
	float y = cameraPos.y;
	float z = cameraPos.z;

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
		yaw -= 1;
		R[0][0] = cos(yaw*convert);
		R[0][1] = 0;
		R[0][2] = sin(yaw*convert);

		R[1][0] = 0;
		R[1][1] = 1;
		R[1][2] = 0;

		R[2][0] = -sin(yaw*convert);
		R[2][1] = 0;
		R[2][2] = cos(yaw*convert);
	}
	if (keystate[SDL_SCANCODE_RIGHT]) {
		// Move camera to the right
		yaw += 1;
		R[0][0] = cos(yaw*convert);
		R[0][1] = 0;
		R[0][2] = sin(yaw*convert);

		R[1][0] = 0;
		R[1][1] = 1;
		R[1][2] = 0;

		R[2][0] = -sin(yaw*convert);
		R[2][1] = 0;
		R[2][2] = cos(yaw*convert);
	}
	if(keystate[SDL_SCANCODE_RCTRL]) {

	}
	if(keystate[SDL_SCANCODE_LSHIFT]) {

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

	for( int y=0; y<SCREEN_HEIGHT; ++y )
		for( int x=0; x<SCREEN_WIDTH; ++x )
			depthBuffer[y][x] = 0;

	for( int i=0; i<triangles.size(); ++i )
	{
		currentColor = triangles[i].color;
		currentReflectance = triangles[i].color;
		currentNormal = triangles[i].normal;
		vector<Vertex> vertices(3);

		vertices[0] = Vertex(triangles[i].v0, triangles[i].normal, currentColor);
		vertices[1] = Vertex(triangles[i].v1, triangles[i].normal, currentColor);
		vertices[2] = Vertex(triangles[i].v2, triangles[i].normal, currentColor);

		//DrawPolygonEdges(vertices);
		DrawPolygon2(vertices);
		//DrawPolygon(vertices);
	}

	sdlAux->render();
}

/*
 * Interpolate from a to b and store result in the result vector
 */
void Interpolate2(Pixel a, Pixel b, vector<Pixel>& result) {

	int N = result.size();

	Pixel tmp = b - a;
	vec3 step = vec3(tmp.x, tmp.y, tmp.zinv) / float(max(N-1,1));

	//vec3 step2 = tmp.illumination / float(max(N-1,1));
	vec3 stepPos = tmp.pos3d / float(max(N-1,1));
	//vec3 current2 = a.illumination;
	//cout << "step2 = " << step.x << " " << step.y << endl;
	vec3 current(a.x, a.y, a.zinv);
	vec3 currentPos = a.pos3d;
	//cout << "current2 = " << current.x << " " << current.y << " " << current.z << endl;
	for( int i=0; i<N; ++i )
	{
		result[i].x = current.x;
		result[i].y = current.y;
		result[i].zinv = current.z;
		result[i].pos3d = currentPos;
		//result[i].illumination = current2;

		current += step;
		currentPos += stepPos;
		//current2 += step2;
	}

}


void ComputePolygonRows2(const vector<Pixel>& vertexPixels, vector<Pixel>& leftPixels, vector<Pixel>& rightPixels) {
	// 1. Find max and min y-value of the polygon
// and compute the number of rows it occupies.
	float min = +numeric_limits<int>::max(), max = 0, currentMin, currentMax;
	for(int i = 0; i < vertexPixels.size(); ++i) {
		currentMin = vertexPixels[i].y;
		currentMax = vertexPixels[i].y;
		if(currentMax > max) {
			max = currentMax;
		}
		if(currentMin < min) {
			min = currentMin;
		}
	}
	int ROWS = max-min+1;
	//cout << "Rows: " << ROWS << endl << "Min: " << min << endl << "Max: " << max << endl;

// 2. Resize leftPixels and rightPixels
// so that they have an element for each row.
	leftPixels.resize(ROWS);
	rightPixels.resize(ROWS);

// 3. Initialize the x-coordinates in leftPixels
// to some really large value and the x-coordinates
// in rightPixels to some really small value.
	for( int i=0; i<ROWS; ++i )
	{
		leftPixels[i].x = +numeric_limits<int>::max();
		rightPixels[i].x = -numeric_limits<int>::max();
		leftPixels[i].y = min + i;
		rightPixels[i].y = min + i;
	}

// 4. Loop through all edges of the polygon and use
// linear interpolation to find the x-coordinate for
// each row it occupies. Update the corresponding
// values in rightPixels and leftPixels.

	// Loop through every vertex
	for (int k = 0; k < vertexPixels.size(); ++k) {
		int j = (k + 1) % vertexPixels.size(); // The next vertex

		int delta = glm::abs(vertexPixels[k].y - vertexPixels[j].y)+1;

		vector<Pixel> line(delta);
		Interpolate2(vertexPixels[k], vertexPixels[j], line);

		// Loop through every line (edge)
		for(int l = 0; l < line.size(); ++l) {
			// Loop through every pixel and update x values
			int index = line[l].y-min;

			if(leftPixels[index].x > line[l].x) {
				leftPixels[index].x = line[l].x;
				leftPixels[index].zinv = line[l].zinv;
				leftPixels[index].pos3d = line[l].pos3d;
			}

			if(rightPixels[index].x < line[l].x) {
				rightPixels[index].x = line[l].x;
				rightPixels[index].zinv = line[l].zinv;
				rightPixels[index].pos3d = line[l].pos3d;
				//rightPixels[index].illumination = line[l].illumination;

			}

		}
	}

}
void DrawRows2(const vector<Pixel>& leftPixels, const vector<Pixel>& rightPixels) {
	// Write pixels
	for(int i = 0; i < leftPixels.size(); ++i) {
		vector<Pixel> line(getPixelSize2(leftPixels[i], rightPixels[i]));
		Interpolate2(leftPixels[i], rightPixels[i], line);

		for(int j = 0; j < line.size(); ++j) {
			PixelShader(line[j]);
		}
	}
}
void VertexShader2( const Vertex& v, Pixel& p ) {

	vec3 P = (v.position - cameraPos) * R; // Transform camera to be at origin
	//float depth = glm::distance(P, cameraPos);
	Pixel tmp((int) f*P.x/P.z + SCREEN_WIDTH/2, (int) f*P.y/P.z + SCREEN_HEIGHT/2, 1.f/P.z, v.position/P.z);
	p = tmp;
}

void DrawPolygon2( const vector<Vertex>& vertices )
{
	int V = vertices.size();
	vector<Pixel> vertexPixels( V );
	for( int i=0; i<V; ++i )
		VertexShader2( vertices[i], vertexPixels[i] );
	vector<Pixel> leftPixels;
	vector<Pixel> rightPixels;
	ComputePolygonRows2( vertexPixels, leftPixels, rightPixels );
	DrawRows2( leftPixels, rightPixels );
}

/*
 * Get the size of a vector before interpolation
 */
int getPixelSize2(Pixel a, Pixel b) {
	Pixel delta = a - b;
	delta = delta.abs();
	int pixels = glm::max(delta.x, delta.y) + 1;
	return pixels;
}

void PixelShader( const Pixel& p )
{

	int x = p.x;
	int y = p.y;
	if(x < SCREEN_WIDTH && y < SCREEN_HEIGHT && x >= 0 && y >= 0) {
		if (p.zinv > depthBuffer[y][x]) {
			depthBuffer[y][x] = p.zinv;

			vec3 pos = p.pos3d/p.zinv;
			vec3 illumination = ReflectedLight(pos);
			sdlAux->putPixel(x, y, illumination);
		}
	}
}

/*
 * Returns the reflected illumination for a specific intersection.
 */
vec3 ReflectedLight(const vec3& v) {


	float distanceBetweenPoints = glm::distance(v, lightPos);
	float A = 4 * M_PI * pow(distanceBetweenPoints, 2);

	float fraction = std::max(glm::dot(currentNormal, glm::normalize(lightPos - v)), (float) 0);

	return currentReflectance * (((lightPower * fraction) / A) + indirectLightPowerPerArea);

}