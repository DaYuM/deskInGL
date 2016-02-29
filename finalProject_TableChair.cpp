
/* 4/26/13                       */
/* William Tinnes                 */
/* Project 3  */

// math, windows and std libraries if needed
#include <math.h>
#include <Windows.h>
#include <stdlib.h>

// setup GLUT for Apple or other Operating Systems (substitute FreeGlut if you want)
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
GLfloat rotate = 10.0;
GLint rotatey, rotatez,  rotatex = 0.0;
GLfloat yx = 1.0;
GLfloat tranx,tranz,trany = 0.0;
// GLdouble eyex=.5*cos(rotate);
//GLdouble eyey=.5*sin(rotate);
// GLdouble eyez=10;
//GLfloat a,b,c,h,j,l,m,n,q,r = 0.0;
//GLfloat f,g,i,k,o,p = 1.0;
//GLfloat d,e = .40;
 GLdouble eyex= 0;
GLdouble eyey= 0;
 GLdouble eyez= -5;
 GLdouble lastx, lastz, pivotx, pivotz, currentx, currentz;
 GLdouble pushChairIn = -16;
#define DEGREES_TO_RADIANS 3.1415/180.0
 GLfloat sideways;
GLfloat backwards;
	GLfloat tipChairOver;
 bool chairIsFalling, drawerIsBeingOpen, pushChairInOut, compartmentOpening1, compartmentOpening2;
 GLfloat pullOut;
 GLfloat compartmentOpen1, compartmentOpen2;


 //Normal arrays to calculate the normal for each side
GLfloat normal0[3];
GLfloat normal1[3];
GLfloat normal2[3];
GLfloat normal3[3];
GLfloat normal4[3];
GLfloat normal5[3];
GLfloat normal6[3];
GLfloat normal7[3];
// Camera variables
//GLfloat eyex, eyey, eyez;
//GLfloat upx, upy, upz;

// Global ambient variables
GLfloat globalAmbientOn[]={.3, 0.3, 0.3, 1.0};		// Global lighting
GLfloat globalAmbientOff[]={0.0, 0.0, 0.0, 1.0};		// Global lighting
bool ambientOn;

// Spotlight Variables
//
//GLfloat light0_ambient[]={1.0, 1.0, 1.0, 1.0};
//GLfloat light0_diffuse[]={.5, .5, .5, 1.0};
//GLfloat light0_specular[]={.2, .2, .2, .2};
////GLfloat dirVectorLight0[]={0.0, 0.0, 0.0};
//GLfloat light0_position[]={0.0, 3.0, 0.0, -1};
bool spotLightOn;

GLfloat light0_ambient[]={.1, .1, .1, 1.0};
GLfloat light0_diffuse[]={.5, .5, .5, 1.0};
GLfloat light0_specular[]={.1, .1, .1, 1.0};
GLfloat dirVectorLight3[]={0.0, 0.0, 0.0};
GLfloat light0_position[]={10.0, 10.0, 10.0, 1.0};

// Materials
//Chrome
GLfloat matChrome_specular[]={.774597, .458561, .200621, 1.0};
GLfloat matChrome_diffuse[]={.4, .4, .4, 1.0};
GLfloat matChrome_ambient[]={.25, .25, .25, 1.0};
GLfloat matChrome_shininess={76.8};

//Jade
GLfloat matJade_specular[]={.316228, .316228, .316228, .95};
GLfloat matJade_diffuse[]={.54, .89, .63, .95};
GLfloat matJade_ambient[]={.135, .2225, .1575, .95};
GLfloat matJade_shininess={12.8};

//Brass
GLfloat matBrass_specular[]={.992157, .941176, .807843, 1.0};
GLfloat matBrass_diffuse[]={.780392, .568627, .113725, 1.0};
GLfloat matBrass_ambient[]={.329412, .223529, .027451, 1.0};
GLfloat matBrass_shininess={27.8974};

//Gold
GLfloat matGold_specular[]={.628281, .555802, .366065, 1.0};
GLfloat matGold_diffuse[]={.75164, .60648, .22648, 1.0};
GLfloat matGold_ambient[]={.24725, .1995, .0745, 1.0};
GLfloat matGold_shininess={51.2};

//Ruby
GLfloat matRuby_specular[]={.727811, .626959, .626959, .55};
GLfloat matRuby_diffuse[]={.61424, .04136, .04136, .55};
GLfloat matRuby_ambient[]={.1745, .01175, .01175, .55};
GLfloat matRuby_shininess={128.0};





 void CrossProduct(GLfloat point1[3], GLfloat point2[3], GLfloat point3[3], GLfloat normal[3])
{
	GLfloat vector1[3], vector2[3];
	/* Calculate 2 vectors */
	vector1[0] = point1[0] - point2[0];
	vector1[1] = point1[1] - point2[1];
	vector1[2] = point1[2] - point2[2];

	vector2[0] = point2[0] - point3[0];
	vector2[1] = point2[1] - point3[1];
	vector2[2] = point2[1] - point3[2];

	/* Calculate the normal */
	normal[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	normal[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	normal[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

/* Vector length required to normalize vector */
GLdouble VectorLength(GLfloat vector[3])
{
	return sqrt((vector[0] * vector[0]) +
		(vector[1] * vector[1]) +
		(vector[2] * vector[2]));
}

/* Normalize the vector to length 1 ... required by opengl */
void Normalize(GLfloat normalVector[3])
{
	GLdouble length = VectorLength(normalVector);

	for (int i =0; i <3; i++)
		normalVector[i] /= length;
}

 void room()
 {
	
	 //glPolygonMode(GL_FRONT, GL_LINE);
	 //glPolygonMode(GL_BACK, GL_FILL);
 GLfloat x1[] = {-10, -10, -10};				// left back top
	GLfloat x2[] = {-10, -10, 10};				// left front top
	GLfloat x3[] = {10, -10, 10};				// right front top
	GLfloat x4[] = {10, -10, -10};				// right back top
	GLfloat x5[] = {-10, -10.5, -10};			// left back bottom
	GLfloat x6[] = {-10, -10.5, 10};				// left front bottom
	GLfloat x7[] = {10, -10.5, 10};				// right front bottom
	GLfloat x8[] = {10, -10.5, -10};				// right back bottom
	
	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
	glMaterialfv(GL_BACK, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_BACK, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_BACK, GL_SHININESS, matRuby_shininess);
	glNormal3f(0,1,0);
	////(0,0,0);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//
	glMaterialfv(GL_BACK, GL_SPECULAR, matBrass_specular);
	glMaterialfv(GL_BACK, GL_AMBIENT, matBrass_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, matBrass_diffuse);
	glMaterialf(GL_BACK, GL_SHININESS, matBrass_shininess);
	//Bottom
	glNormal3f(0,-1,0);
	////(1,1,1);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matJade_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matJade_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matJade_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matJade_shininess);
	//Back
	glNormal3f(0,0,-1);
	////(1,0,0);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
	////(0,1,0);
	glNormal3f(0,0,1);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
	////(0,0,1);
	glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
	////(1,1,0);
	glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void floor()
 {
	GLfloat x1[] = {-10, 10, -10};				// left back top
	GLfloat x2[] = {-10, 10, 10};				// left front top
	GLfloat x3[] = {10, 10, 10};				// right front top
	GLfloat x4[] = {10, 10, -10};				// right back top
	GLfloat x5[] = {-10, -13.5, -10};			// left back bottom
	GLfloat x6[] = {-10, -13.5, 10};				// left front bottom
	GLfloat x7[] = {10, -13.5, 10};				// right front bottom
	GLfloat x8[] = {10, -13.5, -10};				// right back bottom

	//Bottom
	glMaterialfv(GL_FRONT, GL_SPECULAR, matGold_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matGold_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGold_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matGold_shininess);
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	
	glEnd();
 }

 void table()
 {

	 glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {-5, .5, -15};				// left back top
	GLfloat x2[] = {-5, .5, 1};				// left front top
	GLfloat x3[] = {25, .5, 1};				// right front top
	GLfloat x4[] = {25, .5, -15};				// right back top
	GLfloat x5[] = {-5, -.5, -15};			// left back bottom
	GLfloat x6[] = {-5, -.5, 1};				// left front bottom
	GLfloat x7[] = {25, -.5, 1};				// right front bottom
	GLfloat x8[] = {25, -.5, -15};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matGold_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matGold_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGold_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matGold_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void drawerbase()
 {

	 glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {0, .75, -15};				// left back top
	GLfloat x2[] = {0, .75, 1};				// left front top
	GLfloat x3[] = {20, .75, 1};				// right front top
	GLfloat x4[] = {20, .75, -15};				// right back top
	GLfloat x5[] = {0, .5, -15};			// left back bottom
	GLfloat x6[] = {0, .5, 1};				// left front bottom
	GLfloat x7[] = {20, .5, 1};				// right front bottom
	GLfloat x8[] = {20, .5, -15};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matRuby_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void drawersides()
 {

	 glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {0, 2.25, -15};				// left back top
	GLfloat x2[] = {0, 2.25, 1};				// left front top
	GLfloat x3[] = {.25, 2.25, 1};				// right front top
	GLfloat x4[] = {.25, 2.25, -15};				// right back top
	GLfloat x5[] = {0, .75, -15};			// left back bottom
	GLfloat x6[] = {0, .75, 1};				// left front bottom
	GLfloat x7[] = {.25, .75, 1};				// right front bottom
	GLfloat x8[] = {.25, .75, -15};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matRuby_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void compartments()
 {

  glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {-5, 2.25, -12};				// left back top
	GLfloat x2[] = {-5, 2.25, -2};				// left front top
	GLfloat x3[] = {-4.75, 2.25, -2};				// right front top
	GLfloat x4[] = {-4.75, 2.25, -12};				// right back top
	GLfloat x5[] = {-5, .5, -12};			// left back bottom
	GLfloat x6[] = {-5, .5, -2};				// left front bottom
	GLfloat x7[] = {-4.75, .5, -2};				// right front bottom
	GLfloat x8[] = {-4.75, .5, -12};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matRuby_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void compartmentSides()
 {

  glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {-4.75, 2.25, -1.75};				// left back top
	GLfloat x2[] = {-4.75, 2.25, -2};				// left front top
	GLfloat x3[] = {-.25, 2.25, -2};				// right front top
	GLfloat x4[] = {-.25, 2.25, -1.75};				// right back top
	GLfloat x5[] = {-4.75, .5, -1.75};			// left back bottom
	GLfloat x6[] = {-4.75, .5, -2};				// left front bottom
	GLfloat x7[] = {-.25, .5, -2};				// right front bottom
	GLfloat x8[] = {-.25, .5, -1.75};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matRuby_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }
 void compartmentBase()
 {

  glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {-5, .75, -12};				// left back top
	GLfloat x2[] = {-5, .75, -2};				// left front top
	GLfloat x3[] = {0, .75, -2};				// right front top
	GLfloat x4[] = {0, .75, -12};				// right back top
	GLfloat x5[] = {-5, .5, -12};			// left back bottom
	GLfloat x6[] = {-5, .5, -2};				// left front bottom
	GLfloat x7[] = {0, .5, -2};				// right front bottom
	GLfloat x8[] = {0, .5, -12};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matRuby_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void compartmentHandle()
 {
	glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {-5.25, 1, -9};				// left back top
	GLfloat x2[] = {-5.25, 1, -6};				// left front top
	GLfloat x3[] = {-5, 1, -6};				// right front top
	GLfloat x4[] = {-5, 1, -9};				// right back top
	GLfloat x5[] = {-5.25, .75, -9};			// left back bottom
	GLfloat x6[] = {-5.25, .75, -6};				// left front bottom
	GLfloat x7[] = {-5, .75, -6};				// right front bottom
	GLfloat x8[] = {-5, .75, -9};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matJade_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matJade_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matJade_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matJade_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }
 void drawerfb()
 {

	 glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {0, 2.25, .75};				// left back top
	GLfloat x2[] = {0, 2.25, 1};				// left front top
	GLfloat x3[] = {20, 2.25, 1};				// right front top
	GLfloat x4[] = {20, 2.25, .75};				// right back top
	GLfloat x5[] = {0, .75, .75};			// left back bottom
	GLfloat x6[] = {0, .75, 1};				// left front bottom
	GLfloat x7[] = {20, .75, 1};				// right front bottom
	GLfloat x8[] = {20, .75, .75};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matRuby_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void drawerHandle()
 {
	glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
	
	GLfloat x1[] = {7.5, 1, .75};				// left back top
	GLfloat x2[] = {7.5, 1, 1};				// left front top
	GLfloat x3[] = {12.5, 1, 1};				// right front top
	GLfloat x4[] = {12.5, 1, .75};				// right back top
	GLfloat x5[] = {7.5, .75, .75};			// left back bottom
	GLfloat x6[] = {7.5, .75, 1};				// left front bottom
	GLfloat x7[] = {12.5, .75, 1};				// right front bottom
	GLfloat x8[] = {12.5, .75, .75};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matJade_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matJade_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matJade_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matJade_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }


 void leg()
 {
	 glEnable(GL_NORMALIZE);

	 glPolygonMode(GL_FRONT, GL_FILL);		// front is solid fill
		
	GLfloat x1[] = {-5, -.5, -1};				// left back top
	GLfloat x2[] = {-5, -.5, 1};				// left front top
	GLfloat x3[] = {-2.5, -.5, 1};				// right front top
	GLfloat x4[] = {-2.5, -.5, -1};				// right back top
	GLfloat x5[] = {-5, -13.5, -1};			// left back bottom
	GLfloat x6[] = {-5, -13.5, 1};				// left front bottom
	GLfloat x7[] = {-2.5, -13.5, 1};				// right front bottom
	GLfloat x8[] = {-2.5, -13.5, -1};				// right back bottom
	
	


	glMaterialfv(GL_FRONT, GL_SPECULAR, matRuby_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matRuby_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matRuby_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matRuby_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);
	glEnd();
 }

 void paper()
 {
	 GLfloat x1[] = {0, .25, 0};				// left back top
	GLfloat x2[] = {0, .25, 2.5};				// left front top
	GLfloat x3[] = {4, .25, 2.5};				// right front top
	GLfloat x4[] = {4, .25, 0};				// right back top
	GLfloat x5[] = {0, 0, 0};			// left back bottom
	GLfloat x6[] = {0, 0, 2.5};				// left front bottom
	GLfloat x7[] = {4, 0, 2.5};				// right front bottom
	GLfloat x8[] = {4, 0, 0};				// right back bottom
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matChrome_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matChrome_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matChrome_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matChrome_shininess);
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void screen()
 {
	 GLfloat x1[] = {0, 4, -.25};				// left back top
	GLfloat x2[] = {0, 4, 0};				// left front top
	GLfloat x3[] = {6, 4, 0};				// right front top
	GLfloat x4[] = {6, 4, -.25};				// right back top
	GLfloat x5[] = {0, 0, -.25};			// left back bottom
	GLfloat x6[] = {0, 0, 0};				// left front bottom
	GLfloat x7[] = {6, 0, 0};				// right front bottom
	GLfloat x8[] = {6, 0, -.25};				// right back bottom
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matChrome_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matChrome_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matChrome_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matChrome_shininess);
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void screenBotTop()
 {
	 GLfloat x1[] = {0, .25, -.5};				// left back top
	GLfloat x2[] = {0, .25, -.25};				// left front top
	GLfloat x3[] = {6, .25, -.25};				// right front top
	GLfloat x4[] = {6, .25, -.5};				// right back top
	GLfloat x5[] = {0, 0, -.5};			// left back bottom
	GLfloat x6[] = {0, 0, -.25};				// left front bottom
	GLfloat x7[] = {6, 0, -.25};				// right front bottom
	GLfloat x8[] = {6, 0, -.5};				// right back bottom
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matChrome_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matChrome_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matChrome_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matChrome_shininess);
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

  void screenLeftRight()
 {
	 GLfloat x1[] = {0, 3.75, -.5};				// left back top
	GLfloat x2[] = {0, 3.75, -.25};				// left front top
	GLfloat x3[] = {.25, 3.75, -.25};				// right front top
	GLfloat x4[] = {.25, .25, -.5};				// right back top
	GLfloat x5[] = {0, .25, -.5};			// left back bottom
	GLfloat x6[] = {0, .25, -.25};				// left front bottom
	GLfloat x7[] = {.25, .25, -.25};				// right front bottom
	GLfloat x8[] = {.25, .25, -.5};				// right back bottom
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matChrome_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matChrome_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matChrome_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matChrome_shininess);
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }

 void stand()
 {
	  GLfloat x1[] = {3, 6, 0};				// left back top
	GLfloat x2[] = {3, 6, .5};				// left front top
	GLfloat x3[] = {4, 6, .5};				// right front top
	GLfloat x4[] = {4, 6, 0};				// right back top
	GLfloat x5[] = {3, 0, 0};			// left back bottom
	GLfloat x6[] = {3, 0, .5};				// left front bottom
	GLfloat x7[] = {4, 0, .5};				// right front bottom
	GLfloat x8[] = {4, 0, 0};				// right back bottom
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matChrome_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matChrome_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matChrome_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matChrome_shininess);
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();

 }

 void computer()
 {
	 GLfloat x1[] = {3, 6, -4};				// left back top
	GLfloat x2[] = {3, 6, .5};				// left front top
	GLfloat x3[] = {5, 6, .5};				// right front top
	GLfloat x4[] = {5, 6, -4};				// right back top
	GLfloat x5[] = {3, 0, -4};			// left back bottom
	GLfloat x6[] = {3, 0, .5};				// left front bottom
	GLfloat x7[] = {5, 0, .5};				// right front bottom
	GLfloat x8[] = {5, 0, -4};				// right back bottom
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, matChrome_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matChrome_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matChrome_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matChrome_shininess);
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();

 }

 void keyboard()
 {
 }

 void mouse()
 {
 }


 void PC()
 {
	 GLfloat x1[] = {-5, 4.5, -2};				// left back top
	GLfloat x2[] = {-5, 4.5, 1};				// left front top
	GLfloat x3[] = {0, 4.5, 1};				// right front top
	GLfloat x4[] = {0, 4.5, -2};				// right back top
	GLfloat x5[] = {-5, -.5, -2};			// left back bottom
	GLfloat x6[] = {-5, -.5, 1};				// left front bottom
	GLfloat x7[] = {0, -.5, 1};				// right front bottom
	GLfloat x8[] = {0, -.5, -2};				// right back bottom
	
	

	glMaterialfv(GL_FRONT, GL_SPECULAR, matGold_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matGold_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGold_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matGold_shininess);


	/* Draw the faces vertices are counterclockwise when looked at */
	glBegin(GL_QUADS);
	//Top
		glNormal3f(0,1,0);
	////(1,.5,1);
	glVertex3fv(x1);
	glVertex3fv(x2);
	glVertex3fv(x3);
	glVertex3fv(x4);

	//Bottom
		glNormal3f(0,-1,0);
	glVertex3fv(x5);
	glVertex3fv(x8);
	glVertex3fv(x7);
	glVertex3fv(x6);	

	//Back
		glNormal3f(0,0,-1);
	glVertex3fv(x1);
	glVertex3fv(x4);
	glVertex3fv(x8);
	glVertex3fv(x5);

	//Front
		glNormal3f(0,0,-1.0);
	glVertex3fv(x2);
	glVertex3fv(x6);
	glVertex3fv(x7);
	glVertex3fv(x3);

	//Left
		glNormal3f(-1,0,0);
	glVertex3fv(x2);
	glVertex3fv(x1);
	glVertex3fv(x5);
	glVertex3fv(x6);

	//Right
		glNormal3f(1,0,0);
	glVertex3fv(x4);
	glVertex3fv(x3);
	glVertex3fv(x7);
	glVertex3fv(x8);

	glEnd();
 }
 
void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING); /* turn lights on */

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	if (spotLightOn)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
	glLoadIdentity();

	gluLookAt(currentx, eyey, currentz, 0, 0, 0, 0, 1, 0);
	

	// create table
	glPushMatrix();
		glScalef(yx,yx,yx);
		glTranslatef(-tranx,-trany,-tranz);
		glRotatef( rotatex, 1.0, 0.0, 0.0 );
		glRotatef( -rotatey, 0.0, 1.0, 0.0 );
		glRotatef( rotatez, 0.0, 0.0, 1.0 );
		glPushMatrix();
			glPushMatrix();
				glScalef(1,.75,1);
				leg();
			glPopMatrix();
			glPushMatrix();
				glScalef(1,.5,1);
				PC();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0,-14);
				glPushMatrix();
					glScalef(1,.75,1);
					leg();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(27.5,0,0);
				glPushMatrix();
					glScalef(1,.75,1);
					leg();
				glPopMatrix();
					glPushMatrix();
						glTranslatef(0,0,14);
						glPushMatrix();
							glScalef(1,.75,1);
							leg();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

				glPushMatrix();
					glTranslatef(0,0,-13);
					glPushMatrix();
							glScalef(1,.5,1);
							PC();
							glPopMatrix();
					glPushMatrix();
						glTranslatef(25,0,0);
						glPushMatrix();
							glScalef(1,.5,1);
							PC();
							glPopMatrix();
						glPushMatrix();
							glTranslatef(0,0,13);
							glPushMatrix();
							glScalef(1,.5,1);
							PC();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0,2.6,0);
					glPushMatrix();
							glScalef(1,.75,1);
							table();
					glPopMatrix();
				glPopMatrix();
		glPopMatrix();
		table();




		// create the computer
			glPushMatrix();
			glTranslatef(5,3.1,-5);
			glRotatef(90,0,1,0);
			paper();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(8.5,4,-4);
				screen();
				screenBotTop();
				screenLeftRight();
				glPushMatrix();
					glTranslatef(0,3.75,0);
					screenBotTop();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(5.75,0,0);
					screenLeftRight();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-.5,-2,0);
					stand();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(4,-2,-4);
					computer();
				glPopMatrix();
			glPopMatrix();
			
			glPushMatrix();
	

	//create chair
	glTranslatef(10,-2.5,pushChairIn);
	glRotatef(tipChairOver,backwards,0, sideways);
	glScalef(.25,.50,.50);
			leg();
			glPushMatrix();
				glTranslatef(0,0,-14);
				leg();
				glPushMatrix();
					glTranslatef(27.5,0,0);
					leg();
					glPushMatrix();
						glTranslatef(0,0,14);
						leg();
						glPushMatrix();
							glScalef(1,1.5,1);
							glTranslatef(0,13.5,-14);
							leg();
							glPushMatrix();
								glTranslatef(-27.5,0,0);
								leg();
								glPushMatrix();
									glTranslatef(6.875,0,0);
									leg();
									glPushMatrix();
										glTranslatef(6.875,0,0);
										leg();
										glPushMatrix();
											glTranslatef(6.875,0,0);
											leg();
											glPushMatrix();
												glTranslatef(-6.875,-.25,1.0);
												glTranslatef(-6.875,0,0);
												glTranslatef(-6.875,0,0);
												glScalef(1,.75,.18);
												table();
											glPopMatrix();
										glPopMatrix();
									glPopMatrix();
								glPopMatrix();
							glPopMatrix();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			table();
		glPopMatrix();

		//create drawer

	glPushMatrix();
	glTranslatef(0,0,pullOut);
		drawerbase();
		drawersides();	
		drawerfb();
		glPushMatrix();
			glTranslatef(20,0,0);
			drawersides();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-15.75);
			drawerfb();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,.4,-16);
			drawerHandle();
		glPopMatrix();
	glPopMatrix();

	//create side drawers

	glPushMatrix();
		glTranslatef(0,0,0);
		glPushMatrix();
			glTranslatef(compartmentOpen1,0,0);
			compartments();
			compartmentBase();
			glPushMatrix();
					glTranslatef(0,0,-.25);
					compartmentSides();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,.25,0);
				compartmentHandle();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(4.75,0,0);
				compartments();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0,-10.);
				compartmentSides();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-4,.66,-6);
				glRotatef(90,0,1,0);
				paper();

			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			
			glTranslatef(29.75,0,0);
			glPushMatrix();
			
			glTranslatef(compartmentOpen2,0,0);
				compartments();
			glPushMatrix();
				glTranslatef(-4.75,0,0);
				compartments();
				compartmentBase();
				glPushMatrix();
					glTranslatef(0,0,-.25);
					compartmentSides();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-4.75,0,-10.);
				compartmentSides();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(.5,.25,0);
				compartmentHandle();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-7.5,.66,-6);
				glRotatef(90,0,1,0);
				paper();
			glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
	


	glPopMatrix();



	
		if (spotLightOn)
	{
		glPushMatrix();
			glPushAttrib(GL_LIGHTING_BIT);
				glDisable(GL_LIGHTING); /* enable lighting */
				glMaterialfv(GL_FRONT, GL_SPECULAR, matJade_specular);
				glMaterialfv(GL_FRONT, GL_AMBIENT, matJade_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, matJade_diffuse);
				glMaterialf(GL_FRONT, GL_SHININESS, matJade_shininess);
				glTranslatef(10.0, 10, 10.0);
				glutWireSphere(.1, 10.0, 10.0);
				glEnable(GL_LIGHTING); /* enable lighting */
			glPopAttrib();
		glPopMatrix();
	}

	glutSwapBuffers();
}


void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);


	glShadeModel(GL_SMOOTH);
	//(   1.0,  0.0,  0.0 );
	//glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT, GL_LINE);
	//glFrontFace(GL_CW);
		pivotx = 0;
	pivotz = 0;
	currentx = 0;
		currentz = 35;
		tipChairOver = 0;
		sideways = 0;
		backwards = 0;
		chairIsFalling = false;
		drawerIsBeingOpen = false;
		pushChairInOut = false;
		spotLightOn = false;
		pullOut = 0;
		compartmentOpen1,compartmentOpen2 = 0;
		compartmentOpening1,compartmentOpening2 = false;
		glEnable(GL_LIGHTING);
		//glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 40.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
}

void timer1(int input)
{
	if (chairIsFalling)
	{
		tipChairOver -= 5;
		if (tipChairOver <= -90)
			tipChairOver = -90;

		glutPostRedisplay();
	}

	if (!chairIsFalling)
	{
		tipChairOver += 5;
		if (tipChairOver > 0)
			tipChairOver = 0;

		glutPostRedisplay();
	}

	if (drawerIsBeingOpen)
	{
		pullOut -= .1;
		if (pullOut < -4)
			pullOut = -4;
			
	glutPostRedisplay();
	}

	if (!drawerIsBeingOpen)
	{
	pullOut += .1;
		if (pullOut > 0)
			pullOut = 0;
			
	glutPostRedisplay();
	}

	if (pushChairInOut)
	{
		pushChairIn += .1;
		if(pushChairIn > -10)
			pushChairIn = -10;
	glutPostRedisplay();
	}

	if (!pushChairInOut)
	{
		pushChairIn -= .1;
	if(pushChairIn < -16)
		pushChairIn = -16;
		glutPostRedisplay();
	}


	if (compartmentOpening1)

	{
		compartmentOpen1 -= .1;
		if (compartmentOpen1 < -2.5)
			compartmentOpen1 = -2.5;
			glutPostRedisplay();
	}

	if (!compartmentOpening1)
	{
		compartmentOpen1 += .1;
		if (compartmentOpen1 > 0)
			compartmentOpen1 = 0;
		glutPostRedisplay();
	}

		
	if (compartmentOpening2)
	{
		compartmentOpen2 += .1;
		if (compartmentOpen2 > 2.5)
			compartmentOpen2 = 2.5;
		glutPostRedisplay();
	}

		
	if (!compartmentOpening2)
	{
		compartmentOpen2 -= .1;
		if (compartmentOpen2 < 0)
			compartmentOpen2 = 0;
		glutPostRedisplay();
	}


		 glutTimerFunc(100,timer1,1);
}

void timer2(int input)
{
		 GLfloat neweyex, neweyez;
           neweyex = pivotx +
                             (currentx - pivotx) *
                             cos (DEGREES_TO_RADIANS * rotate) -
                             (currentz - pivotz) *
                             sin (DEGREES_TO_RADIANS * rotate);
 
           neweyez = pivotz +
                          (currentx - pivotx) *
                             sin (DEGREES_TO_RADIANS * rotate) +
                             (currentz - pivotz) *
                             cos (DEGREES_TO_RADIANS * rotate);
           currentz = neweyez;
           currentx = neweyex;
     glutPostRedisplay();
          
    
     glutTimerFunc(500,timer2,1);
}

void keyboardFunc(unsigned char key, int x, int y)
{
	switch(key)
	{

	case 'a':
	rotatey += 5;	
	glutPostRedisplay();
	break;
	case 'd':
	rotatey -= 5;
	glutPostRedisplay();
	break;
	case 'w':
	rotatex += 5;
	glutPostRedisplay();
	break;
	case 's':
	rotatex -= 5;
	glutPostRedisplay();
	break;
	case 'c':
	rotatez += 5;
	glutPostRedisplay();
	break;
	case 'e':
	rotatez -= 5;
	glutPostRedisplay();
	break;
	case 'q':
	yx += .1;
	glutPostRedisplay();
	break;
	case 'z':
	yx -= .1;
	glutPostRedisplay();
	break;
	case 'r':
	backwards = 1;
	chairIsFalling = false;
	
	glutPostRedisplay();
	break;
	case 'v':
	backwards = 1;

	chairIsFalling = true;
	glutPostRedisplay();
	break;
	case 'p':
	tranz -= .1;
	glutPostRedisplay();
	break;
	case 'o':
	tranz += .1;
	glutPostRedisplay();
	break;
	case'k':
	pushChairInOut = true;

	glutPostRedisplay();
	break;
	case 'i':
		pushChairInOut = false;

	glutPostRedisplay();

	break;
	case ';':
	drawerIsBeingOpen  = true;
	glutPostRedisplay();
	break;

	case '.':
	drawerIsBeingOpen = false;
	break;

	case 'g':
	compartmentOpening2 = true;
	//compartmentOpen2 = 90;
	glutPostRedisplay();
	break;
	case 't':
		spotLightOn = true;
		compartmentOpening1 = true;
	//compartmentOpen1 = 90;
	glutPostRedisplay();
	break;

	case ']':
		compartmentOpening1 = false;
		glutPostRedisplay();
	break;

	case '[':
		compartmentOpening2 = false;
		glutPostRedisplay();
	break;

	}
	
}

void specialKey(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
	{
		
		trany += .1;
		glutPostRedisplay();
		
	}
	if(key == GLUT_KEY_DOWN)
	{
		trany -= .1;
		glutPostRedisplay();
	}

	if(key == GLUT_KEY_RIGHT)
	{
		tranx += .1;
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_LEFT)
	{
		tranx -= .1;
		glutPostRedisplay();
	}
}
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, (GLfloat) w, (GLfloat) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (GLfloat) w/ (GLfloat) h, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D Scene");
	init();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialKey);
	//glutTimerFunc(100,timer,1);
	
	glutTimerFunc(100,timer1,1);
	//glutTimerFunc(500,timer2,1);
	glutMainLoop();
	return 0;



}