#include "common.h"

#include "Ray.h"
#include "HittableList.h"
#include "prim/Sphere.h"
#include "Camera.h"
#include "util/Random.h"

#include <iostream>
#include <fstream>

using namespace std;

void writeColor(ostream& out, color pixelColor, unsigned int samplesPerPixel) {

	float r = pixelColor.x;
	float g = pixelColor.y;
	float b = pixelColor.z;

	float scale = 1.0f / samplesPerPixel;
	r *= scale;
	g *= scale;
	b *= scale;

	out << static_cast<int>(255.999 * glm::clamp(r, 0.0f, 0.9999f)) << ' '
		<< static_cast<int>(255.999 * glm::clamp(g, 0.0f, 0.9999f)) << ' '
		<< static_cast<int>(255.999 * glm::clamp(b, 0.0f, 0.9999f)) << '\n';
}

color rayColor(const Ray& r, const IHittable& hittable) {
	HitRecord rec;
	if (hittable.Hit(r, 0, infinity, rec)) {
		return 0.5f * (rec.normal + color(1, 1, 1));
	}
	glm::vec3 unitDir = glm::normalize(r.Dir);
	float t = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

int main(int argc, char** argv) {
	// Image Dimensions
	const int IMAGE_WIDTH = 400;
	const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
	const int SAMPLES_PER_PIXEL = 100;

	// World
	HittableList scene;
	scene.Add(MakeRef<Sphere>(point3(0, 0, -1), 0.5f));
	scene.Add(MakeRef<Sphere>(point3(0.0f, -100.5f, -1.0f), 100));

	// Camera
	Camera cam;

	// Rendering

	ofstream output("output.ppm");

	output << "P3" << endl << IMAGE_WIDTH << ' ' 
		 << IMAGE_HEIGHT << endl << 255 << endl;

	for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
		cerr << "Scanlines remaining: " << j << ' ' << flush << endl;
		for (int i = 0; i < IMAGE_WIDTH; ++i) {
			color pixel(0.0f);
			for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
				float u = (i + Random::GetRandomInRange<float>(0.0f, 0.9999f)) / (IMAGE_WIDTH - 1);
				float v = (j + Random::GetRandomInRange<float>(0.0f, 0.9999f)) / (IMAGE_HEIGHT - 1);
				Ray r = cam.GetRay(u, v);
				pixel += rayColor(r, scene);
			}
			writeColor(output, pixel, SAMPLES_PER_PIXEL);
		}
	}

	cerr << endl <<  "Done." << endl;

	output.close();
}