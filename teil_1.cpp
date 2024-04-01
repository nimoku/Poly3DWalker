// GD-Praktikum:   teil_1_kamera.cpp  (Teil 2: Szenegraph und Animationen)

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL

#include "Wuerfel.h"



//Global Variables for the Animation (Rotation) 40 max
GLfloat MOVEMENT_SPEED = 1.5;
GLfloat MOVEMENT_SPEED_ARM = 0.8;

GLfloat RIGHT_UPPER_ARM = 20;
GLfloat RIGHT_UNDER_ARM = 40;
GLfloat LEFT_UPPER_ARM = -20;
GLfloat LEFT_UNDER_ARM = 0;
GLfloat RIGHT_LEG = -40;
GLfloat LEFT_LEG = 40;


bool RIGHT_LEG_FOWARD = true;
bool LEFT_LEG_FOWARD = false;
bool LEFT_UPPER_ARM_FOWARD = true;
bool LEFT_UNDER_ARM_FOWARD = true;
bool RIGHT_UPPER_ARM_FOWARD = false;
bool RIGHT_UNDER_ARM_FOWARD = false;





void Init()
{
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen	
	glClearColor(0.6, 0.1, 0, 1);
	glEnable(GL_DEPTH_TEST);
}


void RenderScene() //Zeichenfunktion
{
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Kameraposition, Blickwinkel und Up-Vector
	gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.); // extrinsische Kameraparameter


	// Kopf
	glPushMatrix();
	glTranslatef(0.0, 0.5, 0);
	Wuerfel(0.1, 0.1, 0.1);
	glPopMatrix();


	// Koerper
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0);
	Wuerfel(0.4, 0.5, 0.2);
	glPopMatrix();


	// Arm (links)
	glPushMatrix();
	// Rotation of whole arm (upper + lower)
	glTranslatef(0.25, 0.425, 0);
	glRotatef(LEFT_UPPER_ARM, 1, 0, 0);
	glTranslatef(-0.25, -0.425, 0);
	
		// Unterarm
		glPushMatrix();
			glTranslatef(0.25, 0.225, 0);
			glRotatef(LEFT_UNDER_ARM, 1, 0, 0);
			glTranslatef(-0.25, -0.225, 0);


			glTranslatef(0.25, 0.225, 0);
			//glRotatef(LEFT_UNDER_ARM, 1, 0, 0);
			Wuerfel(0.08, 0.23, 0.1);
		glPopMatrix();

	// Oberarm
	glTranslatef(0.25, 0.425, 0);
	Wuerfel(0.08, 0.1, 0.1);
	glPopMatrix();


	// Arm (rechts)
	glPushMatrix();
	// Rotation of whole arm (upper + lower)
	glTranslatef(0.25, 0.425, 0);
	glRotatef(RIGHT_UPPER_ARM, 1, 0, 0);
	glTranslatef(-0.25, -0.425, 0);

		// Unterarm
		glPushMatrix();
			glTranslatef(-0.25, 0.225, 0);
			glRotatef(RIGHT_UNDER_ARM, 1, 0, 0);
			glTranslatef(0.25, -0.225, 0);

			glTranslatef(-0.25, 0.225, 0);
			Wuerfel(0.08, 0.23, 0.1);
		glPopMatrix();

	// Oberarm
	glTranslatef(-0.25, 0.425, 0);
	Wuerfel(0.08, 0.1, 0.1);
	glPopMatrix();



	// Bein (links)
	glPushMatrix();
	// Rotation des Beines um die Hüfle
	glTranslatef(0, -0.1, 0);
	glRotatef(LEFT_LEG, 1, 0, 0);
	glTranslatef(0, 0.1, 0);

	glTranslatef(0.15, -0.2, 0);
	Wuerfel(0.08, 0.23, 0.1);
	glPopMatrix();


	// Bein (rechts)
	glPushMatrix();
	// Rotation des Beines um die Hüfle
	glTranslatef(0, -0.1, 0);
	glRotatef(RIGHT_LEG, 1, 0, 0);
	glTranslatef(0, 0.1, 0);

	//glRotatef(-40, 1, 0, 0);
	glTranslatef(-0.15, -0.2, 0);
	Wuerfel(0.08, 0.23, 0.1);
	glPopMatrix();


	glutSwapBuffers();
}


void Reshape(int width, int height)
{
	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt

	 // Matrix fuer Transformation: Frustum -> viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
	// Viewport definieren
	glViewport(0, 0, width, height);
	// Kamera definieren (intrinsische Kameraparameter)
	//glOrtho(-1., 1., -1., 1., 0., 10.); // orthogonale Kamera
	gluPerspective(45., 1, 0.1, 10.); // perspektivische Kamera
	// Matrix fuer Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}


void move() {
	// RIGHT LEG
	if (RIGHT_LEG_FOWARD) {
		RIGHT_LEG += MOVEMENT_SPEED;
		if (RIGHT_LEG >= 40) {
			RIGHT_LEG_FOWARD = false;
		}
	}
	if (!RIGHT_LEG_FOWARD) {
		RIGHT_LEG -= MOVEMENT_SPEED;
		if (RIGHT_LEG <= -40) {
			RIGHT_LEG_FOWARD = true;
		}
	}

	// LEFT LEG
	if (LEFT_LEG_FOWARD) {
		LEFT_LEG += MOVEMENT_SPEED;
		if (LEFT_LEG >= 40) {
			LEFT_LEG_FOWARD = false;
		}
	}
	if (!LEFT_LEG_FOWARD) {
		LEFT_LEG -= MOVEMENT_SPEED;
		if (LEFT_LEG <= -40) {
			LEFT_LEG_FOWARD = true;
		}
	}


	// LEFT UPPFER ARM
	if (LEFT_UPPER_ARM_FOWARD) {
		LEFT_UPPER_ARM += MOVEMENT_SPEED_ARM;
		if (LEFT_UPPER_ARM >= 20) {
			LEFT_UPPER_ARM_FOWARD = false;
		}
	}
	if (!LEFT_UPPER_ARM_FOWARD) {
		LEFT_UPPER_ARM -= MOVEMENT_SPEED_ARM;
		if (LEFT_UPPER_ARM <= -20) {
			LEFT_UPPER_ARM_FOWARD = true;
		}
	}

	// RIGHTEFT UPPFER ARM
	if (RIGHT_UPPER_ARM_FOWARD) {
		RIGHT_UPPER_ARM += MOVEMENT_SPEED_ARM;
		if (RIGHT_UPPER_ARM >= 20) {
			RIGHT_UPPER_ARM_FOWARD = false;
		}
	}
	if (!RIGHT_UPPER_ARM_FOWARD) {
		RIGHT_UPPER_ARM -= MOVEMENT_SPEED_ARM;
		if (RIGHT_UPPER_ARM <= -20) {
			RIGHT_UPPER_ARM_FOWARD = true;
		}
	}

	// LEFT UNDER ARM
	if (LEFT_UNDER_ARM_FOWARD) {
		LEFT_UNDER_ARM += MOVEMENT_SPEED_ARM;
		if (LEFT_UNDER_ARM >= 10) {
			LEFT_UNDER_ARM_FOWARD = false;
		}
	}
	if (!LEFT_UNDER_ARM_FOWARD) {
		LEFT_UNDER_ARM -= MOVEMENT_SPEED_ARM;
		if (LEFT_UNDER_ARM <= -40) {
			LEFT_UNDER_ARM_FOWARD = true;
		}
	}

	// RIGHT UNDER ARM
	if (RIGHT_UNDER_ARM_FOWARD) {
		RIGHT_UNDER_ARM += MOVEMENT_SPEED_ARM;
		if (RIGHT_UNDER_ARM >= 10) {
			RIGHT_UNDER_ARM_FOWARD = false;
		}
	}
	if (!RIGHT_UNDER_ARM_FOWARD) {
		RIGHT_UNDER_ARM -= MOVEMENT_SPEED_ARM;
		if (RIGHT_UNDER_ARM <= -40) {
			RIGHT_UNDER_ARM_FOWARD = true;
		}
	}

}


void Animate(int value)
{
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 
	std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen
	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);

	move();

}




int main(int argc, char** argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);         // Fenster-Konfiguration
	glutCreateWindow("Name_1; Name_2");   // Fenster-Erzeugung
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}