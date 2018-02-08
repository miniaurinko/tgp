#include "GL/freeglut.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "vecmath.h"
using namespace std;
// Tekijä: Ville Kuokkanen
// Arvio: 3/5
// Ominaisuudet: perusvaatimusten lisäksi objektin pyöritys ja värien sulava vaihtuminen
// Vaikenta tehtävässä oli ymmärtää millä tavalla .obj tiedostosta rivit kannattaisi tallentaa
// ja millä tavalla ne saa piirrettyä oikein




// This is the list of points (3D vectors)
vector<vector<float>> vecv;

// This is the list of normals (also 3D vectors)
vector<vector<float>> vecn;

// This is the list of faces (indices into vecv and vecn)
vector<vector<unsigned> > vecf;
vector<Vector3f> vertexIndices;
vector<Vector3f> normalIndices;

// You will need more global variables to implement color and position changes
int counter = 0;
int tilanne = 0;
bool start = false;
bool väri_aloita = false;
int kulma = 0;
int intervalli = 16;
float väri_index = 0;
GLfloat väri[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat horizontal = 1.0f;
GLfloat vertical = 1.0f;

void värifunktio(int t)
{
	if (väri_aloita)
	{
		if (väri[1] > 1.0)
		{
			tilanne = 1;
		}
		if (väri[0] < 0.0)
		{
			tilanne = 2;
		}
		if (väri[2] > 1.0)
		{
			tilanne = 3;
		}
		if (väri[1] < 0.0)
		{
			tilanne = 4;
		}
		if (väri[0] > 1.0)
		{
			tilanne = 5;
		}
		if (väri[2] < 0.0)
		{
			tilanne = 0;
			väri[0] = 1.0;
			väri[1] = 0.0;
			väri[2] = 0.0;
			väri[3] = 1.0;
		}

		if (tilanne == 0)
		{
			väri[1] += 0.1;
		}
		if (tilanne == 1)
		{
			väri[0] -= 0.1;
		}
		if (tilanne == 2)
		{
			väri[2] += 0.1;
		}
		if (tilanne == 3)
		{
			väri[1] -= 0.1;
		}
		if (tilanne == 4)
		{
			väri[0] += 0.1;
		}
		if (tilanne == 5)
		{
			väri[2] -= 0.1;
		}

	}
	glutPostRedisplay();
	glutTimerFunc(75, värifunktio, 0);
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
        // add code to change color here
		//counter++;
		//cout << "Unhandled key press " << key << "." << endl; 
		if (väri_aloita) väri_aloita = false;
		else väri_aloita = true;
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

	for (unsigned int i = 0; i < vecf.size(); i++)
	{
		
		unsigned a = vecf[i][0];
		unsigned c = vecf[i][1];
		unsigned d = vecf[i][2];
		unsigned f = vecf[i][3];
		unsigned g = vecf[i][4];
		unsigned ii = vecf[i][5];

		glNormal3d(vecn[c - 1][0], vecn[c - 1][1], vecn[c - 1][2]);
		glVertex3d(vecv[a - 1][0], vecv[a - 1][1], vecv[a - 1][2]);
		glNormal3d(vecn[f - 1][0], vecn[f - 1][1], vecn[f - 1][2]);
		glVertex3d(vecv[d - 1][0], vecv[d - 1][1], vecv[d - 1][2]);
		glNormal3d(vecn[ii - 1][0], vecn[ii - 1][1], vecn[ii - 1][2]);
		glVertex3d(vecv[g - 1][0], vecv[g - 1][1], vecv[g - 1][2]);

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
GLfloat diffColors[4][4] = { {1.0, 0.5, 0.9},
							 {0.9, 0.5, 0.5, 1.0},
							 {0.5, 0.9, 0.3, 1.0},
							 {0.3, 0.8, 0.9, 1.0} };

// Here we use the first color entry as the diffuse color
glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, väri);

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



void loadInput()
{
	FILE * file = fopen("./garg.obj", "r");
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
			vector<float> vert;
			float vertx;
			float verty;
			float vertz;
			fscanf(file, "%f %f %f\n", &vertx, &verty, &vertz);
			vert.push_back(vertx);
			vert.push_back(verty);
			vert.push_back(vertz);
			vecv.push_back(vert);
		}
		else if (strcmp(lukija, "vn") == 0)
		{
			vector<float> normaali;
			float normx;
			float normy;
			float normz;
			fscanf(file, "%f %f %f\n", &normx, &normy, &normz);
			normaali.push_back(normx);
			normaali.push_back(normy);
			normaali.push_back(normz);
			//cout << normx; cout << " "; cout << normy; cout << " "; cout << normz; cout << "\n";
			vecn.push_back(normaali);
		}
	
		else if (strcmp(lukija, "f") == 0) 
		{
			std::string vertex1, vertex2, vertex3;
			unsigned vertexIndex[3], uvIndex[3], normalIndex[3];
			vector<unsigned> vektorit;
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("Ei saada auki\n");
				return;
			}
			vektorit.push_back(vertexIndex[0]);
			vektorit.push_back(normalIndex[0]);
			
			vektorit.push_back(vertexIndex[1]);
			vektorit.push_back(normalIndex[1]);
			
			vektorit.push_back(vertexIndex[2]);
			vektorit.push_back(normalIndex[2]);
			
			vecf.push_back(vektorit);
		}
	}
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    loadInput();

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
	glutTimerFunc(75, värifunktio, 0);
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	// This line is never reached.
}
