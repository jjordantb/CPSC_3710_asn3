#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

const int ROT_STEP = 1;

int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

float cubeZ = 0;
float lookX = 0, lookY = 0, lookZ = cubeZ;
float cameraX = 0, cameraY = 0, cameraZ = 5;

int rotationAngle = 0;

static void drawString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void CallBackRenderScene(void)
{
  char buf[80];

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ, 0, 1, 0);

  glTranslatef(0, 0, cubeZ);
  glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
  glTranslatef(0, 0, 0);

  glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(0.0, 0.9, 0.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(0.9, 0.0, 0.0, 1.0);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(0.0, 0.0, 0.9, 1.0);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(0.9, 0.9, 0.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor4f(0.9, 0.0 ,0.9, 1.0);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f,  -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor4f(0.0, 0.9, 0.9, 1.0);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f,  -1.0f);
    glVertex3f(1.0f,  -1.0f,  1.0f);
    glVertex3f(-1.0f,  -1.0f, 1.0f);

  glEnd();

  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  glOrtho(0,Window_Width,0,Window_Height,-1.0,1.0);
  glColor4f(0.6,1.0,0.6,1.00);

  drawString(125, Window_Height - 20, GLUT_BITMAP_HELVETICA_12, "Use 'z' to move the cube 'forward");
  char cameraBuf[256];
  snprintf(cameraBuf, sizeof cameraBuf, "%s%f%s%f%s%f%s", "Camera: [", cameraX, ", ", cameraY, ", ", cameraZ, "]");
  char lookBuff[256];
  snprintf(lookBuff, sizeof lookBuff, "%s%f%s%f%s%f%s", "At: [", lookX, ", ", lookY, ", ", lookZ, "]");
  char cubeLoc[256];
  snprintf(cubeLoc, sizeof cubeLoc, "%s%f%s%f%s%f%s", "Cube: [", 0.0, ", ", 0.0, ", ", cubeZ, "]");
  drawString(15, Window_Height - 100, GLUT_BITMAP_HELVETICA_12, cameraBuf);
  drawString(15, Window_Height - 115, GLUT_BITMAP_HELVETICA_12, lookBuff);
  drawString(15, Window_Height - 130, GLUT_BITMAP_HELVETICA_12, cubeLoc);

  glPopMatrix();
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

  glutSwapBuffers();

  rotationAngle = (rotationAngle + ROT_STEP) % 360;
}

void CallBackMouseEvent(int button, int state, int x, int y)
{
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    cameraX = 5;
    cameraY = 5;
    cameraZ = 5 + cubeZ;
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    cameraX = 0;
    cameraY = 0;
    cameraZ = 5 + cubeZ;
  }
}

void CallBackKeyPressed(unsigned char key, int x, int y)
{
   if (key == 122) {
     printf("z pressed \n");
     cubeZ += 0.5;
     cameraZ += 0.5;
     lookZ += 0.5;
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
