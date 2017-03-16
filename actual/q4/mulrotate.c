#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

const float cubeSpeed = 0.25f;
const float pyramidSpeed = 1.0f;
const float sphereSpeed = 2.0f;

float atX = 0, atY = 0, atZ = -10;
float cameraX = 0, cameraY = 0, cameraZ = 0;

float angleCube = 0;
float anglePyramid = 0;
float angleSphere = 0;

bool isCubeRotating = true;
bool isPyramidRotating = true;
bool isSphereRotating = true;

static void drawString(float x, float y, void *font,const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void CallBackRenderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, atX, atY, atZ, 0, 1, 0);

  //Sphere
  glRotatef(angleSphere, 0.0f, 0.0f, 1.0f);
  glTranslatef(0, 2, -4);

  glColor3f(1, 1, 1);
  glutSolidSphere(0.5f, 50, 50);

  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, atX, atY, atZ, 0, 1, 0);
  glTranslatef(0, 0, -3);
  glRotatef(anglePyramid, 0.0f, 0.0f, 1.0f);
  glRotatef(90, 1.0f, 0.0f, 0.0f);

  //Pyramid
  glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f,  -0.5f);
    glVertex3f(0.5f,  -0.5f,  0.5f);
    glVertex3f(-0.5f,  -0.5f, 0.5f);
  glEnd();

  glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f,  -0.5f);
    glVertex3f(0, 0.5f, 0);

    glColor3f(1, 0, 1);
    glVertex3f(0.5f, -0.5f,  -0.5f);
    glVertex3f(0.5f,  -0.5f,  0.5f);
    glVertex3f(0, 0.5f, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0.5f,  -0.5f,  0.5f);
    glVertex3f(-0.5f,  -0.5f, 0.5f);
    glVertex3f(0, 0.5f, 0);

    glColor3f(1, 1, 0);
    glVertex3f(-0.5f,  -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0, 0.5f, 0);
  glEnd();

  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, atX, atY, atZ, 0, 1, 0);
  glTranslatef(0, 0, -5);
  glRotatef(angleCube, 0.0f, 0.0f, 1.0f);

  // CUBE
  glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glColor3f(0, 1, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);

    glColor3f(1, 1, 0);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f,  -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, 0.5f);

    glColor3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f,  -0.5f);
    glVertex3f(0.5f,  -0.5f,  0.5f);
    glVertex3f(-0.5f,  -0.5f, 0.5f);
  glEnd();

  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glPopMatrix();
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  glutSwapBuffers();

  angleCube = (isCubeRotating) ? (angleCube + cubeSpeed) : angleCube;

  anglePyramid = (isPyramidRotating) ? (anglePyramid + pyramidSpeed) : anglePyramid;

  angleSphere = (isSphereRotating) ? (angleSphere + sphereSpeed) : angleSphere;
}

void CallBackMouseEvent(int button, int state, int x, int y) {
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    cameraX = 5;
    cameraY = 5;
    cameraZ = 5;
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    cameraX = 0;
    cameraY = 0;
    cameraZ = 0;
  } else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    cameraX = -5;
    cameraY = 5;
    cameraZ = 5;
  } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    cameraX = 0;
    cameraY = 0;
    cameraZ = 0;
  }
}

void CallBackKeyPressed(unsigned char key, int x, int y) {
   if (key == 122) { // z
     isPyramidRotating = false;
     isCubeRotating = true;
     isSphereRotating = true;
   } else if (key == 97) { // a
     isPyramidRotating = true;
     isSphereRotating = true;
     isCubeRotating = false;
   } else if (key == 113) { // q
     isPyramidRotating = false;
     isSphereRotating = false;
     isCubeRotating = false;
   } else if (key == 32) { // space
     isPyramidRotating = true;
     isCubeRotating = true;
     isSphereRotating = true;
   }
}

void CallBackResizeScene(int Width, int Height)
{
   if (Height == 0)
      Height = 1;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

int init(int Width, int Height) {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  glClearDepth(1.0);
  glDepthFunc(GL_LESS);

  glDepthMask(GL_TRUE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_SMOOTH);
  CallBackResizeScene(Width,Height);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(Window_Width, Window_Height);
  Window_ID = glutCreateWindow("Florchinger Jordan");

  glutDisplayFunc(&CallBackRenderScene);
  glutIdleFunc(&CallBackRenderScene);
  glutReshapeFunc(&CallBackResizeScene);
  glutMouseFunc(&CallBackMouseEvent);
  glutKeyboardFunc(&CallBackKeyPressed);

  init(Window_Width, Window_Height);

  glutMainLoop();
  return 1;
}
