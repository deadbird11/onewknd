#include "common.h"

#include "Ray.h"
#include "HittableList.h"
#include "prim/Sphere.h"
#include "Camera.h"
#include "Materials.h"

#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

void writeColor(ostream& out, color pixelColor, unsigned int samplesPerPixel) {

	float r = pixelColor.x;
	float g = pixelColor.y;
	float b = pixelColor.z;

	float scale = 1.0f / samplesPerPixel;
	// for gamma = 0.5f
	r = glm::sqrt(scale * r);
	g = glm::sqrt(scale * g);
	b = glm::sqrt(scale * b);

	out << static_cast<int>(255.999 * glm::clamp(r, 0.0f, 0.9999f)) << ' '
		<< static_cast<int>(255.999 * glm::clamp(g, 0.0f, 0.9999f)) << ' '
		<< static_cast<int>(255.999 * glm::clamp(b, 0.0f, 0.9999f)) << '\n';
}

color rayColor(const Ray& r, const IHittable& hittable, int depth) {
	
	if (depth <= 0) return color(0.0f);

	HitRecord rec;
	if (hittable.Hit(r, 0.001f, infinity, rec)) {
		Ray scattered;
		color attenuation;
		if (rec.p_Material->Scatter(r, rec, attenuation, scattered)) {
			return attenuation * rayColor(scattered, hittable, depth - 1);
		}
	}
	glm::vec3 unitDir = glm::normalize(r.Dir);
	float t = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

int main(int argc, char** argv) {

	auto start = high_resolution_clock::now();

	// Image Dimensions
	const int IMAGE_WIDTH = 400;
	const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
	const int SAMPLES_PER_PIXEL = 100;

	// World
	HittableList scene;
	
	auto groundMat = MakeRef<Lambertian>(color(0.8f, 0.8f, 0.0f));
	auto centerMat = MakeRef<Lambertian>(color(0.7f, 0.3f, 0.3f));
	auto leftMat   = MakeRef<Metal>(color(0.8f));
	auto rightMat  = MakeRef<Metal>(color(0.8f, 0.6f, 0.2f));

	scene.Add(MakeRef<Sphere>(point3( 0.0f, -100.5f, -1.0f),  100.0f, groundMat));
	scene.Add(MakeRef<Sphere>(point3( 0.0f,    0.0f, -1.0f),    0.5f, centerMat));
	scene.Add(MakeRef<Sphere>(point3(-1.0f,    0.0f, -1.0f),    0.5f, leftMat));
	scene.Add(MakeRef<Sphere>(point3( 1.0f,    0.0f, -1.0f),    0.5f, rightMat));

	// Camera
	Camera cam;

	// Rendering
	ofstream output("output.ppm");

	output << "P3" << endl << IMAGE_WIDTH << ' ' 
		 << IMAGE_HEIGHT << endl << 255 << endl;

	const int MAX_DEPTH = 50;

	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		cerr << "Scanlines remaining: " << j << ' ' << flush << endl;
		for (int i = 0; i < IMAGE_WIDTH; ++i) {
			color pixel(0.0f);
			for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
				float u = (i + Random::GetRandomInRange<float>(0.0f, 0.9999f)) / (IMAGE_WIDTH - 1);
				float v = (j + Random::GetRandomInRange<float>(0.0f, 0.9999f)) / (IMAGE_HEIGHT - 1);
				Ray r = cam.GetRay(u, v);
				pixel += rayColor(r, scene, MAX_DEPTH);
			}
			writeColor(output, pixel, SAMPLES_PER_PIXEL);
		}
	}

	cerr << endl <<  "Done." << endl;

	output.close();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);

	cerr << "Image took " << duration.count() << " seconds to generate." << endl;
}