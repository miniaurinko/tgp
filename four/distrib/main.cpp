#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

float clampedDepth(float depthInput, float depthMin, float depthMax);

#include "bitmap_image.hpp"
int main(int argc, char* argv[])
{
	char* input;
	char* output;
	int sizevaaka;
	int sizepysty;
	// Fill in your implementation here.

	// This loop loops over each of the input arguments.
	// argNum is initialized to 1 because the first
	// "argument" provided to the program is actually the
	// name of the executable (in our case, "a4").
	for (int argNum = 1; argNum < argc; ++argNum)
	{
		std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
	}

	input = argv[2];
	output = argv[7];
	sizevaaka = stoi(argv[4]);
	sizepysty = stoi(argv[5]);

	SceneParser scene = SceneParser(input);
	Image img = Image(sizevaaka, sizepysty);
	group = scene->parseGroup();

	for (int i = 0; i < sizevaaka; i++) {
		for (int j = 0; j < sizepysty; j++){
			Vector2f xy = Vector2f(i / sizevaaka, j / sizepysty);
			Ray r = scene.getCamera()->generateRay(xy);
			Hit h = Hit(FLT_MAX, NULL, Vector3f(0.f, 0.f, 0.f));

			//img.SetPixel(j, i, Vector3f(0.5, 0.5, 0.5));
			
		}
    }
	img.SaveBMP(output);

  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.



 
  ///TODO: below demonstrates how to use the provided Image class
  ///Should be removed when you start
  Vector3f pixelColor (1.0f,0,0);
  //width and height
  Image image( 10 , 15 );
  image.SetPixel( 5,5, pixelColor );
  image.SaveImage("demo.bmp");
  return 0;
}

