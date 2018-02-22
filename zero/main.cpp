#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "vecmath.h"
using namespace std;

// Tekijä: Ville Kuokkanen
// Arvio: 3/5
// Ominaisuudet: perusvaatimusten lisäksi objektin pyöritys ja värin sulava vaihtuminen
// Vaikenta tehtävässä oli ymmärtää millä tavalla .obj tiedostosta rivit kannattaisi tallentaa
// ja millä tavalla ne saa piirrettyä oikein
//
// luettava tiedosto annetaan komentoriviargumenttina




// This is the list of points (3D vectors)
//vector<vector<float>> vecv;
vector<Vector3f> vecv;

// This is the list of normals (also 3D vectors)
vector<Vector3f> vecn;

// This is the list of faces (indices into vecv and vecn)
vector<vector<unsigned> > vecf;

// You will need more global variables to implement color and position changes
int counter = 0;
int tilanne = 0;
bool start = false;
bool color_aloita = false;
int kulma = 0;
int intervalli = 16;
int color_index = 0;
GLfloat color[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat horizontal = 1.0f;
GLfloat vertical = 1.0f;
void colorfunktio(int t)
{
	if (color_aloita)
	{


		if (color[1] > 1.0)
		{
			tilanne = 1;
		}
		if (color[0] < 0.0)
		{
			tilanne = 2;
		}
		if (color[2] > 1.0)
		{
			tilanne = 3;
		}
		if (color[1] < 0.0)
		{
			tilanne = 4;
		}
		if (color[0] > 1.0)
		{
			tilanne = 5;
		}
		if (color[2] < 0.0)
		{
			tilanne = 0;
			color[0] = 1.0;
			color[1] = 0.0;
			color[2] = 0.0;
			color[3] = 1.0;
		}

		if (tilanne == 0)
		{
			color[1] += 0.1;
		}
		if (tilanne == 1)
		{
			color[0] -= 0.1;
		}
		if (tilanne == 2)
		{
			color[2] += 0.1;
		}
		if (tilanne == 3)
		{
			color[1] -= 0.1;
		}
		if (tilanne == 4)
		{
			color[0] += 0.1;
		}
		if (tilanne == 5)
		{
			color[2] -= 0.1;
		}
		
	}

	glutPostRedisplay();
	glutTimerFunc(75, colorfunktio, 0);
}

void aikafunktio(int t)
{
	if (start)
	{
		kulma += 2;
		kulma %= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(intervalli, aikafunktio, 0);
}
// These are convenience functions which allow us to call OpenGL 
// methods on Vec3d objects
inline void glVertex(const Vector3f &a) 
{ glVertex3fv(a); }

inline void glNormal(const Vector3f &a) 
{ glNormal3fv(a); }


// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
		if (color_aloita) color_aloita = false;
		else color_aloita = true;
		break;
        break;
	case 'r':
		if (start) start = false;
		else start = true;
		break;
    default:
        cout << "Unhandled key press " << key << "." << endl;        
    }

	// this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
        // add code to change light position
		// cout << "Unhandled key press: up arrow." << endl;
		vertical = vertical + 0.5f;
		break;
    case GLUT_KEY_DOWN:
        // add code to change light position
		// cout << "Unhandled key press: down arrow." << endl;
		vertical = vertical - 0.5f;
		break;
    case GLUT_KEY_LEFT:
        // add code to change light position
		//cout << "Unhandled key press: left arrow." << endl;
		horizontal = horizontal - 0.5f;
		break;
    case GLUT_KEY_RIGHT:
        // add code to change light position
		//cout << "Unhandled key press: right arrow." << endl;
		horizontal = horizontal + 0.5f;
		break;
    }

	// this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}

void loadObject()
{
	
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < vecf.size(); i++) {

		vector<unsigned> &v = vecf[i];

		
		glNormal3d(vecn[v[2] - 1][0], vecn[v[2] - 1][1], vecn[v[2] - 1][2]);
		glVertex3d(vecv[v[0] - 1][0], vecv[v[0] - 1][1], vecv[v[0] - 1][2]);
		glNormal3d(vecn[v[5] - 1][0], vecn[v[5] - 1][1], vecn[v[5] - 1][2]);
		glVertex3d(vecv[v[3] - 1][0], vecv[v[3] - 1][1], vecv[v[3] - 1][2]);
		glNormal3d(vecn[v[8] - 1][0], vecn[v[8] - 1][1], vecn[v[8] - 1][2]);
		glVertex3d(vecv[v[6] - 1][0], vecv[v[6] - 1][1], vecv[v[6] - 1][2]);
		
	}
	glEnd();

}

// This function is responsible for displaying the object.
void drawScene(void)
{
int i;

// Clear the rendering window
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// Rotate the image
glMatrixMode(GL_MODELVIEW);  // Current matrix affects objects positions
glLoadIdentity();              // Initialize to the identity

// Position the camera at [0,0,5], looking at [0,0,0],
// with [0,1,0] as the up direction.
gluLookAt(3.0 * sin(kulma * 3.14 / 180), 0.0, 3.0 * cos(kulma * 3.14 / 180),
	0.0, 0.0, 0.0,
	0.0, 1.0, 0.0);

// Set material properties of object

// Here are some colors you might use - feel free to add more
GLfloat diffColors[4][4] = { {1.0, 0.5, 0.9, 1.0},
							 {0.9, 0.5, 0.5, 1.0},
							 {0.5, 0.9, 0.3, 1.0},
							 {0.3, 0.8, 0.9, 1.0} };

// Here we use the first color entry as the diffuse color
glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

// Define specular color and shininess
GLfloat specColor[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess[] = { 100.0 };

// Note that the specular color and shininess can stay constant
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

// Set light properties

// Light color (RGBA)
GLfloat Lt0diff[] = { 1.0,1.0,1.0,1.0 };
// Light position
GLfloat Lt0pos[] = { horizontal, vertical, 5.0f, 1.0f };

glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

// This GLUT method draws a teapot.  You should replace
// it with code which draws the object you loaded.
//glutSolidTeapot(1.0);
loadObject();

// Dump the image to the screen.
glutSwapBuffers();


}



// Initialize OpenGL's rendering modes
void initRendering()
{
	glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
	glEnable(GL_LIGHTING);     // Enable lighting calculations
	glEnable(GL_LIGHT0);       // Turn on light #0.
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
	// Always use the largest square viewport possible
	if (w > h) {
		glViewport((w - h) / 2, 0, h, h);
	}
	else {
		glViewport(0, (h - w) / 2, w, w);
	}

	// Set up a perspective view, with square aspect ratio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 50 degree fov, uniform aspect ratio, near = 1, far = 100
	gluPerspective(50.0, 1.0, 1.0, 100.0);
}



void loadInput(char* arg)
{

	FILE * file = fopen(arg, "r");
	if (file == NULL) {
		printf("Tiedostoa ei saa auki!\n");
		return;
	}
	while (1) {

		char lukija[256];
		int res = fscanf(file, "%s", lukija);
		if (res == EOF)
			break;

		if (strcmp(lukija, "v") == 0)
		{
			Vector3f v;
			float vertx;
			float verty;
			float vertz;
			fscanf(file, "%f %f %f\n", &vertx, &verty, &vertz);
	
			v[0] = vertx;
			v[1] = verty;
			v[2] = vertz;
			vecv.push_back(v);
		}
		else if (strcmp(lukija, "vn") == 0)
		{
			Vector3f v;
			float normx;
			float normy;
			float normz;
			fscanf(file, "%f %f %f\n", &normx, &normy, &normz);
			v[0] = normx;
			v[1] = normy;
			v[2] = normz;

			vecn.push_back(v);
		}
	
		else if (strcmp(lukija, "f") == 0) 
		{
			unsigned a, b, c, d, e, f, g, h, i;
			vector<unsigned> vec;
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &a, &b, &c, &d, &e, &f, &g, &h, &i);
			if (matches != 9) {
				printf("Ei saada auki\n");
				return;
			}
		
			vec.push_back(a);
			vec.push_back(b);
			vec.push_back(c);
			vec.push_back(d);
			vec.push_back(e);
			vec.push_back(f);
			vec.push_back(g);
			vec.push_back(h);
			vec.push_back(i);
			vecf.push_back(vec);
			
		}
	}
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    loadInput(argv[1]);

    glutInit(&argc,argv);

    // We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Assignment 0");

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

	glutTimerFunc(intervalli, aikafunktio, 0);
	glutTimerFunc(75, colorfunktio, 0);
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	// This line is never reached.
}
