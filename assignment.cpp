#include <cmath>
#include <GL/freeglut.h>
#include "loadTGA.h"

int cam_hgt = 6;
float zoom = 1;
float look_x = 0;
float look_z = 0;
float eye_x = 0;
float eye_z = 35;
float angle = 0;
float kane_x = 4.5;
float ball_x = 0;
float ball_y = 0;
float bumra_arm = 0;
float cricketball_rotat = 0;
int cricket_event = 0;
float ball_z = 0;
int ball_arm = 45;
int volley_event = 0;
float volleyball_x = 9.75;
float volleyball_y = 5.25;
float volleyball_z = 3.5;
int serve_arm = 0;
int basket_arm = 45;
int basket_event = 0;
float basket_y = 5.125;
float basket_x = -5.75;
float t = 0;
GLuint txId[3];   //Texture ids

//--Draws a grid of lines on the floor plane -------------------------------
void drawFloor()
{
	glColor3f(0., 0.5,  0.);			//Floor colour

	for(int i = -50; i <= 50; i ++)
	{
		glBegin(GL_LINES);			//A set of grid lines on the xz-plane
			glVertex3f(-50, -0.75, i);
			glVertex3f(50, -0.75, i);
			glVertex3f(i, -0.75, -50);
			glVertex3f(i, -0.75, 50);
		glEnd();
	}
}

void loadTexture()				
{
	glGenTextures(2, txId); 	// Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("wood.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("hexagon.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("turf.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

void henrySolidCube(int tile_no) {
	glBegin(GL_POLYGON);
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(  0.5, -0.5, 0.5 );
		glVertex3f(  0.5,  0.5, 0.5 );
		glVertex3f( -0.5,  0.5, 0.5 );
		glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(   0.0,  1.0,  0.0 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glTexCoord2f(0, tile_no); glVertex3f(  0.5,  0.5,  0.5 );
		glTexCoord2f(0, 0); glVertex3f(  0.5,  0.5, -0.5 );
		glTexCoord2f(tile_no, 0); glVertex3f( -0.5,  0.5, -0.5 );
		glTexCoord2f(tile_no, tile_no); glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	 
}

void shoot(void) {
	float start_point_x = basket_x;
	float start_point_y = 5.575;
	float end_point_y = 7.25;
	float end_point_x = -8.5;
	float control_point_x = -7;
	float control_point_y = 10.5;
	if (basket_arm < 135 && basket_event == 0) {
		basket_arm += 5;
		basket_y += 0.05;
	}
	if (basket_arm == 135 && basket_event == 0) {
		basket_event = 1;
	}
	if (t < 1 && basket_event == 1) {
		t+= 0.1;
		basket_x = ((1-t) * (1-t))*start_point_x + 2*(1-t)*t*control_point_x + (t*t)*end_point_x;
		basket_y = ((1-t) * (1-t))*start_point_y + 2*(1-t)*t*control_point_y + (t*t)*end_point_y;
	}
	if (t >= 1) {
		basket_event = 2;
		t = 0;
	}
	if (basket_event == 2) {
		start_point_x = -8.5;
		start_point_y = 7.25;
		end_point_x = -5.75;
		end_point_y = 5.125;
		control_point_x = -7;
		control_point_y = 8.5;
		if (t < 1) {
			basket_x = ((1-t) * (1-t))*start_point_x + 2*(1-t)*t*control_point_x + (t*t)*end_point_x;
			basket_y = ((1-t) * (1-t))*start_point_y + 2*(1-t)*t*control_point_y + (t*t)*end_point_y;
			t+= 0.1;
		}
		if (basket_arm != 45) {
			basket_arm -= 9;
		}
		if (t >= 1) {
			basket_event = 3;
		}
	}
	if (basket_event == 3) {
		basket_event = 0;
		basket_y = 5.125;
		basket_x = -5.75;
		basket_event = 0;
		t = 0;
	}
}

void serve(void) {
	if (ball_arm <= 110 && volley_event == 0) {
		ball_arm += 5;
		volleyball_y += 0.08;
	}
	if (volleyball_y >= 6.29 && volley_event == 0) {
		volley_event = 1;
	}
	if (volley_event == 1) {
		volleyball_x -= 0.045;
		volleyball_y += 0.03;
		volleyball_z -= 0.1;
		serve_arm -= 20;
	}
	if (serve_arm <= -180 && volley_event == 1) {
		volley_event = 2;
	}
	if (volley_event == 2) {
		volleyball_x += 0.3;
		ball_arm -= 5;
		serve_arm -= 20;
	}
	if (volleyball_x >= 12 && volley_event == 2) {
		volley_event = 3;
	}
	if (volley_event == 3) {
		if (ball_arm != 45) {
			ball_arm -= 5;
		}
		if (serve_arm != 0) {
			serve_arm -= 20;
		}
		if (serve_arm <=  -360) {
			serve_arm =  0;
		}
		volleyball_x -= 0.2625;
		volleyball_y -= 0.16;
		volleyball_z += 0.1;
	}
	if (volleyball_x <= 9.75 && volley_event == 3) {
		volley_event = 0;
		serve_arm = 0;
		ball_arm = 45;
		volleyball_x = 9.75;
		volleyball_y = 5.25;
		volleyball_z = 3.5;
	}
		
}
void bowling(void) {
	if (bumra_arm < 180) {
		bumra_arm+=20;
		cricketball_rotat+= 20;
	}
	if (bumra_arm == 180 && cricket_event == 0) {
		ball_y = 0;
		cricket_event = 1;
	}
	if (bumra_arm >= 180 && cricket_event == 1) {
		if (bumra_arm < 360) {
			bumra_arm += 20;
		}
		ball_x -= 0.5;
		ball_y += 0.4;
	}
	if (ball_y >= 2.1 && cricket_event == 1) {
		cricket_event = 2;
	}
	if (cricket_event == 2) {
		if (bumra_arm < 360) {
			bumra_arm += 20;
		}
		ball_x -= 0.5;
		ball_y -= 0.1875;
		ball_z += 0.15;
	}
	if (ball_x < -4.5) {
		cricket_event = 3;
	}
	if (cricket_event == 3) {
		ball_x += 0.5;
		ball_y += 0.04;
		ball_z -= 0.05;
	}
	if (ball_x == 0 && cricket_event == 3) {
		bumra_arm = 0;
		cricketball_rotat = 0;
		cricket_event = 0;
		ball_x = 0;
		ball_y = 0;
		ball_z = 0;
	}
}

void myTimer(int value)
{
	shoot();
	serve();
	bowling();
	glutPostRedisplay();
	glutTimerFunc(50, myTimer, 0);
}

void hoop(void) {
	//Basketball Hoop on Table 1
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-9.75, 4.3, -4);
		glScalef(1, 0.1, 1);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(-9.75, 5.5, -4);
		glScalef(0.5, 3, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-9.5, 7.5, -4);
		glScalef(0.1, 1.5, 3);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-9, 6.9, -4);
		glRotatef(-90, 1, 0, 0);
		glScalef(0.2, 0.3, 0.2);
		glutSolidTorus(0.1, 3, 5, 100);
	glPopMatrix();
}

void special(int key, int x, int y)
{
	if (eye_z >= -15 && eye_z <= 20 && eye_x > -15 && eye_x < 15 && cam_hgt < 16) {
		cam_hgt = 6;
	}
	if(key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
	else if(key == GLUT_KEY_RIGHT) angle += 0.1;
	else if(key == GLUT_KEY_DOWN)
	{  //Move backward
		eye_x -= 0.1*sin(angle);
		eye_z += 0.1*cos(angle);
	}
	else if(key == GLUT_KEY_UP)
	{ //Move forward
		eye_x += 0.1*sin(angle);
		eye_z -= 0.1*cos(angle);
	}
	else if (key == GLUT_KEY_F2)
	{
		if (!(eye_z >= -15 && eye_z <= 20 && eye_x > -15 && eye_x < 15 && cam_hgt < 16)) {
			if (cam_hgt < 20) {
				cam_hgt ++;
			}
		}
	}
	else if (key == GLUT_KEY_F1) 
	{
		if (!(eye_z >= -15 && eye_z <= 20 && eye_x > -15 && eye_x < 15 && cam_hgt < 16)) {
			if (cam_hgt >= 6) {
				cam_hgt -- ;
			}
		}
	}

	look_x = eye_x + 100*sin(angle);
	look_z = eye_z - 100*cos(angle);
	glutPostRedisplay();
}

void doorway(void)
{
	glPushMatrix();
		glColor3f(0.8, 0.7, 0.3); //Left Side of Doorway
		glTranslatef(-7.5, 4.5, 10);
		glScalef(11, 10, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.8, 0.7, 0.3); //Right side of Doorway
		glTranslatef(7.5, 4.5, 10);
		glScalef(11, 10, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.8, 0.7, 0.3); //Above Doorway
		glTranslatef(0.0, 8.25, 10);
		glScalef(4, 2.5, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.7, 0.7, 0.7);
		glTranslatef(0.0, 0, 10.75);
		glScalef(4, 1, 1.5);
		glutSolidCube(1.0); //Step into building
	glPopMatrix();
}
void wall(void)
{
	glPushMatrix();
		glTranslatef(-12.75, 4.5, 0); //Left Wall
		glScalef(0.5, 10, 20);
		glColor3f(0.8, 0.7, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(12.75, 4.5, 0); //Right Wall
		glScalef(0.5, 10, 20);
		glColor3f(0.8, 0.7, 0.3);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 4.5, -10);
		glScalef(26, 10, 0.5);
		glColor3f(0.8, 0.7, 0.3);
		glutSolidCube(1.0); //Back Wall
	glPopMatrix();
}

void stumps(void) {
	//Draws stumps
	glPushMatrix();
		glTranslatef(5.25, 4.25, -4);
		glScalef(0.25, 0.05, 1);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5.25, 4.625, -4);
		glScalef(0.125, 0.75, 0.125);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5.25, 4.625, -3.75);
		glScalef(0.125, 0.75, 0.125);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5.25, 4.625, -4.25);
		glScalef(0.125, 0.75, 0.125);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(5.25, 5, -4);
		glScalef(0.0625, 0.05, 1);
		glutSolidCube(1.0);
	glPopMatrix();
}

void tables(void) {
	//Table for volleyball exhibit
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, txId[0]);
		glTranslatef(9, 4, 3);
		glScalef(3, 0.5, 3);
		henrySolidCube(2);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(9, 2, 3);
		glScalef(1, 4, 1);
		glutSolidCube(1.0);
	glPopMatrix();
	
	//Table for second exhibit
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, txId[2]);
		glTranslatef(4, 4, -4);
		glScalef(3, 0.5, 3);
		henrySolidCube(1);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(4, 2, -4);
		glScalef(1, 4, 1);
		glutSolidCube(1.0);
	glPopMatrix();
	
	//Table for third exhibit
	glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(-9, 4, -4);
		glScalef(3, 0.5, 3);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(-9, 2, -4);
		glScalef(1, 4, 1);
		glutSolidCube(1.0);
	glPopMatrix();
	
	//Table for cricketer
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, txId[2]);
		glTranslatef(1, 4, -4);
		glScalef(3, 0.5, 3);
		henrySolidCube(1);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(1, 2, -4);
		glScalef(1, 4, 1);
		glutSolidCube(1.0);
	glPopMatrix();
	
	//Table for baller
	glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(-6, 4, -4);
		glScalef(3, 0.5, 3);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.4, 0.4, 0.4);
		glTranslatef(-6, 2, -4);
		glScalef(1, 4, 1);
		glutSolidCube(1.0);
	glPopMatrix();
}

void volleyball(void)
{
	//Volleyball Man
	glPushMatrix(); //Head
		glTranslatef(9, 5.8, 3);
		glColor3f(1, 1, 1);
		glScalef(0.25, 0.25, 0.25);
		glutSolidCube(1.4);
	glPopMatrix();
	
	glColor3f(1., 0., 0.); //Torso
	glPushMatrix();
		glTranslatef(9, 5.3, 3);
		glScalef(0.4, 0.8, 0.6);
		glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0., 0., 1.);			//Right leg
	glPushMatrix();
		glTranslatef(9, 4.6, 2.8);
		glScalef(0.25, 0.6, 0.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left leg
	glPushMatrix();
		glTranslatef(9, 4.6, 3.2);
		glScalef(0.25, 0.6, 0.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right arm
	glPushMatrix();
		glTranslatef(9, 5.625, 3.425);
		glRotatef(ball_arm, 0, 0, 1);
		glTranslatef(-9, -5.625, -3.425);
		glTranslatef(9, 5.125, 3.425);
		glScalef(0.25, 1, -.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left arm
	glPushMatrix();
		glTranslatef(9, 5.625, 2.575);
		glRotatef(serve_arm, 0, 0, 1);
		glTranslatef(-9, -5.625, -2.575);
		glTranslatef(9, 5.125, 2.575);
		glScalef(0.25, 1, 0.25);
		glutSolidCube(1);
	glPopMatrix();
	//Volleyball
	glPushMatrix();
		glColor3f(1, 0.5, 0.2);
		glTranslatef(volleyball_x, volleyball_y, volleyball_z);
		glutSolidSphere(0.25, 100, 100);
	glPopMatrix();
}
	
void baller(void)
{
	//Basketball Man
	glPushMatrix(); //Head
		glTranslatef(-5, 5.8, -4);
		glColor3f(1, 1, 1);
		glScalef(0.25, 0.25, 0.25);
		glutSolidCube(1.4);
	glPopMatrix();
	
	glColor3f(1., 0., 0.); //Torso
	glPushMatrix();
		glTranslatef(-5, 5.3, -4);
		glScalef(0.4, 0.8, 0.6);
		glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0., 0., 1.);	//Right leg
	glPushMatrix();
		glTranslatef(-5, 4.6, -3.8);
		glScalef(0.25, 0.6, 0.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);	//Left leg
	glPushMatrix();
		glTranslatef(-5, 4.6, -4.2);
		glScalef(0.25, 0.6, 0.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);	//Left arm
	glPushMatrix();
		glTranslatef(-5, 5.625, -3.575);
		glRotatef(-basket_arm, 0, 0, 1);
		glTranslatef(5, -5.625, 3.575);
		glTranslatef(-5, 5.125, -3.575);
		glScalef(0.25, 1, -.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);	//Right arm
	glPushMatrix();
		glTranslatef(-5, 5.625, -4.425);
		glRotatef(-basket_arm, 0, 0, 1);
		glTranslatef(5, -5.625, 4.425);
		glTranslatef(-5, 5.125, -4.425);
		glScalef(0.25, 1, 0.25);
		glutSolidCube(1);
	glPopMatrix();
	//Basketball
	glPushMatrix();
		glColor3f(1, 0.5, 0.2);
		glTranslatef(basket_x, basket_y, -4);
		glutSolidSphere(0.375, 100, 100);
	glPopMatrix();

}

void cricketers(void) 
{
	//Bowler
	glPushMatrix(); //Head
		glColor3f(0.8, 0.2, 0.1);
		glTranslatef(0, 5.8, -4);
		glColor3f(1, 1, 1);
		glScalef(0.25, 0.25, 0.25);
		glutSolidCube(1.4);
	glPopMatrix();
	
	glColor3f(1., 0., 0.); //Torso
	glPushMatrix();
		glTranslatef(0, 5.3, -4);
		glScalef(0.4, 0.8, 0.6);
		glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0., 0., 1.);			//Right leg
	glPushMatrix();
		glTranslatef(0, 4.6, -3.8);
		glScalef(0.25, 0.6, 0.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left leg
	glPushMatrix();
		glTranslatef(0.0, 4.6, -4.2);
		glScalef(0.25, 0.6, 0.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right arm
	glPushMatrix();
		glTranslatef(0, 5.625, -3.575);
		glRotatef(-bumra_arm, 0, 0, 1);
		glTranslatef(0, -5.625, 3.575);
		glTranslatef(0, 5.125, -3.575);
		glScalef(0.25, 1, -.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left arm
	glPushMatrix();
		glTranslatef(0, 5.125, -4.425);
		glScalef(0.25, 1, 0.25);
		glutSolidCube(1);
	glPopMatrix();
	//Sandpapered Ball
	glPushMatrix();
		glColor3f(1, 0.1, 0.2);
		glTranslatef(0, 5.625, -3.575);
		if (cricketball_rotat <= 180) {
			glRotatef(-cricketball_rotat, 0, 0, 1);
		}
		glTranslatef(ball_x, ball_y, -ball_z);
		glTranslatef(0, -5.625, 3.575);
		glTranslatef(0, 4.5625, -3.575);
		glutSolidSphere(0.125, 100, 100);
	glPopMatrix();
	
	//Captain Fantastic King Kane Williamson
	glTranslatef(kane_x, 5.4, -3.3);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-kane_x, -5.4, 4);
	glPushMatrix(); //Head
		glTranslatef(kane_x, 5.8, -4);
		glScalef(0.25, 0.25, 0.25);
		glColor3f(1, 1, 1);
		glutSolidCube(1.4);
	glPopMatrix();
	
	glColor3f(1., 0., 0.); //Torso
	glPushMatrix();
		glTranslatef(kane_x, 5.3, -4);
		glScalef(0.4, 0.8, 0.6);
		glutSolidCube(1);
	glPopMatrix();
	
	glColor3f(0., 0., 1.);			//Right leg
	glPushMatrix();
		glTranslatef(kane_x, 4.6, -3.8);
		glScalef(0.25, 0.6, 0.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left leg
	glPushMatrix();
	  glTranslatef(kane_x, 4.6, -4.2);
	  glScalef(0.25, 0.6, 0.25);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right arm
	glPushMatrix();
		glTranslatef(kane_x, 5.625, -3.575);
		glRotatef(45, 0, 1, 1);
		glTranslatef(-kane_x, -5.625, 3.575);
		glTranslatef(kane_x, 5.125, -3.575);
		glScalef(0.25, 1, -.25);
		glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);	//Left arm
	glPushMatrix();
		glTranslatef(kane_x, 5.625, -4.425);
		glRotatef(45, 0, -1, 1);
		glTranslatef(-kane_x, -5.625, 4.425);
		glTranslatef(kane_x, 5.125, -4.425);
		glScalef(0.25, 1, 0.25);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); //Bat Handle
		glColor3f(0, 1, 0);
		glTranslatef(kane_x+0.75, 4.75, -3.75);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-45, 1, 0, 0);
		glutSolidCylinder(0.1, 0.2, 100, 100);
	glPopMatrix();
	glPushMatrix(); //Bat
		glColor3f(1, 1, 0);
		glTranslatef(kane_x+0.75, 4.75, -3.75);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-45, 1, 0, 0);
		glTranslatef(0, 0, -0.125);
		glScalef(0.0675, 0.25, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
}

void display(void) 
{ 
	float lpos1[4] = {0., 10., 10., 1.0};  //museum's light pos
	float lpos2[4] = {0, 20, 10, 1.0}; //sunlight pos

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(eye_x, cam_hgt, eye_z,  look_x, 5, look_z,   0, 1, 0);	

	glLightfv(GL_LIGHT0,GL_POSITION, lpos1);
	glLightfv(GL_LIGHT0,GL_POSITION, lpos2);

	glDisable(GL_LIGHTING);			//Disable lighting when drawing floor.
    drawFloor();
	glEnable(GL_LIGHTING);
    glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, txId[1]);
		glScalef(25, 1, 20);
		henrySolidCube(4);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	wall();
	doorway();
	glPushMatrix();
		glColor3f(0.7, 0.7, 0.7);
		glTranslatef(0, 10, 0);
		glScalef(25, 1, 20);
		glutSolidCube(1.0);
	glPopMatrix();
	tables();
	glPushMatrix();
		glTranslatef(-0.1, 0, 0);
		hoop();
	glPopMatrix();
	stumps();
	volleyball();
	baller();
	cricketers();
	glFlush();
} 

void initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	loadTexture();
	glEnable(GL_LIGHTING);		
	glEnable(GL_LIGHT0);
 	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 1000.0);  
}

int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);  
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Museum");
	initialize();
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutTimerFunc(50, myTimer, 0);
	glutMainLoop();
	return 0; 
}


