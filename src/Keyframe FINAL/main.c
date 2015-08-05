/**
KNOWN BUGS: - Nao inicializar uma operação de quaternio com {0,0,0,0} - Corrigir algebra.c
**/


#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include "algebra.h"

/* Valor do PI */
#define PI 3.1415926535897932384

/* Initial screen dimension */
#define W 600
#define H 400

/* Global camera controls */
#define DL 1.0f     /* linear increment */
#define DA 1.0f     /* angular increment */
#define DZ 1.0f     /* zoom increment */

/* Floor geometry (at y=0 plane) */
#define DFLOOR 10.0f


/* Display mode */
static int help = 1;  /* help message on/off */

/* Global camera parameters */
static float fovy = 50.0f;
static float matrix[16] = { 1.0f,0.0f,0.0f,0.0f,
											0.0f,1.0f,0.0f,0.0f,
											0.0f,0.0f,1.0f,0.0f,
											0.0f,0.0f,0.0f,1.0f
										   };


/* Variaveis do Calculo de FrameRate */
static int   fpsTotal;
static int   fpsFrame;
static int   fpsTempo;
static int   fpsTempoBase = 0;
static float FPS   = 0.0;
static char  fpsString[30];


//Teste feio de translacao
/**
FRAME 1
T(-5.5f, 0.5f , 0.0f)

FRAME 2
T(5.5f, 0.5f , 0.0f)

**/
//Variaveis das Translacoes
static float tx = -5.5f;
static float ty =  0.5f;
static float tz =  0.0f;

static float tx_frame1 = -5.5f;
static float ty_frame1 =  0.5f;
static float tz_frame1 =  0.0f;

static float tx_frame2 =  5.5f;
static float ty_frame2 =  3.5f;
static float tz_frame2 =  0.0f;

//KeyFrames
static int frameActualT		  = 1;
static int subFrameActualT  = 0;
static int frameDivisionT		  = 100; //Numero de subframes entre 2 frames


//Teste feio de rotacao
/**
FRAME 1
R(0 ,0,0,0)

FRAME 2
R(270,  0,0,1)

**/
//Variaveis das Rotacoes
static float rAngle =  0.0f;
static float rx =  0.0f;
static float ry =  0.0f;
static float rz =  1.0f;

static float rAngleFrame1 = 0.0f;
static Vector rFrame1 = { 0, 0 , 1};
//static float rx_frame1 = 0;
//static float ry_frame1 = 0;
//static float rz_frame1 = 1;

static float rAngleFrame2 = -180.0f;
static Vector rFrame2 = { 0, 0 , 1};
//static float rx_frame2 =  0;
//static float ry_frame2 =  0;
//static float rz_frame2 =  1;

//KeyFrames
static int frameActualR		  = 1;
static int subFrameActualR  = 0;
static int frameDivisionR		  = 100; //Numero de subframes entre 2 frames



/******************************/
/* Funcoes Criadas            */
/******************************/
void mFPS           (void);



/************************************************************************/
/* Funcao drawscene:  Scene composed by a set of spheres and cubes on a
/*                   planar floor.                                         
/*
/************************************************************************/


static void drawscene ()
{

 /* position light */
 float lpos[4] = {0.0f,10.0f,10.0f,1.0f};
 glLightfv(GL_LIGHT0,GL_POSITION,lpos);

 /* draw floor */
 glColor3f(0.8f,0.5f,0.0f);
 glNormal3f(0.0f,1.0f,0.0f);
 glBegin(GL_QUADS);
  glVertex3f(-DFLOOR,0.0f,-DFLOOR);
  glVertex3f(-DFLOOR,0.0f, DFLOOR);
  glVertex3f( DFLOOR,0.0f, DFLOOR);
  glVertex3f( DFLOOR,0.0f,-DFLOOR);
 glEnd();

 /* draw box */
  glColor3f(0.0f,0.0f,1.0f);
    glPushMatrix();
		//glRotatef(rAngle,rx,ry,rz);
       glRotatef(rAngle,0.0f ,0.0f ,1.0f);
        //printf("A:%lf - RX:%lf - RY: %lf - RZ:%lf\n", rAngle, rx, ry,rz);
		//Tranformacoes para a forma do objeto
		glTranslatef(0,1.5 , 0);
		glScalef(1,3.0 , 1);
		glutSolidCube(1.0f);
    glPopMatrix();

	 /* draw Sphere */
	glColor3f(1.0f,0.0f,0.0f);
    glPushMatrix();
		glTranslatef(tx, ty , tz);
		glutSolidSphere(0.5,32,32);	
	glPopMatrix();
}



/************************************************************************/                                   
/*
/************************************************************************/


static void interpolTranslation ( void )
{ 
	float distanceFrame1, distanceFrame2;

	//Pegando a distancia do subframe atual para o frame anterior e o proximo
	//A contribuicao para a interpolacao e' o inverso
	distanceFrame2 = (( 100.0f * subFrameActualT ) / frameDivisionT) /100.0f;
	distanceFrame1 = fabs(distanceFrame2 - 1.0f);

	//Novas posicoes do objeto
	tx = (tx_frame1 * distanceFrame1) + (tx_frame2 * distanceFrame2);
	ty = (ty_frame1 * distanceFrame1) + (ty_frame2 * distanceFrame2);
	tz = (tz_frame1 * distanceFrame1) + (tz_frame2 * distanceFrame2);

	//Adicionado SubFrame de interpolação
	subFrameActualT++;

	//Verificar passagem de frame
	if ( subFrameActualT == frameDivisionT)
	{
		subFrameActualT = 0;
		frameActualT++;

		printf("end!");
	}
}



/************************************************************************/                                    
/*
/************************************************************************/

static void interpolRotation ( void )
{
	float distanceFrame1;
	Quat q1, q2, resultQuaternion;

	Vector resultAxis;
	float resultAngle;

	//Criando o quatérnio 1 baseado no Frame1
	q1 = algQuat(0,0,0,0); 
	q1 = algQuatFromRot(rAngleFrame1, rFrame1 );

	//Criando o quatérnio 2 baseado no Frame2
	q2 = algQuat(0,0,0,0); 
	q2 = algQuatFromRot(rAngleFrame2, rFrame2 );

	//Pegando a distancia do Frame1
	distanceFrame1 = (( 100.0f * subFrameActualR ) / frameDivisionR) /100.0f;

	//Fazendo interpolação dos Quatérnios
	resultQuaternion =  algQuatSLERP(q1, q2, distanceFrame1);

	resultAngle = algQuatRotAngle(resultQuaternion);
	resultAxis   = algQuatRotAxis(resultQuaternion);

	rAngle = resultAngle;
	rx		   = resultAxis.x;
	ry		   = resultAxis.y;
	rz		   = resultAxis.z;

	//Adicionado SubFrame de interpolação
	subFrameActualR++;

	//Verificar passagem de frame
	if ( subFrameActualR == frameDivisionR)
	{
		subFrameActualR = 0;
		frameActualR++;

		printf("end!");
	}

}


/************************************************************************/
/* Funcao putstring:  Display message on screen.                                         
/*
/************************************************************************/

static void putstring (char* s, float x, float y)
{
   int i;
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   glColor3f(1.0f,1.0f,1.0f);
   glRasterPos3d(x,y,0.8);
   
   for (i=0; s[i]; i++)
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}


/************************************************************************/
/* Funcao showhelp:  Display help message.                                        
/*
/************************************************************************/

static void showhelp ()
{
   putstring("** Teste de interpolacao de Keyframes **",-0.95,-0.59);
   putstring("1: Interpolar esfera (Translate)",-0.95,-0.67);
   putstring("2: interpolar paralelepipedo (Rotation)",-0.95,-0.75);
   putstring("ESC: sair",-0.95,-0.83);
}


/************************************************************************/
/* Funcao reshape:  Reshape callback.                                        
/*
/************************************************************************/

static void reshape (int w, int h)
{
   float white[4] = {1.0f,1.0f,1.0f,1.0f};
   glViewport(0,0,w,h);
   glClearColor(0,0,0,1); 
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50.0);
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
}


/************************************************************************/
/* Funcao mFPS:  Funcao que calcula o Framerate de parede e imprime na 
/*             tela principal da aplicação                                             
/*
/************************************************************************/

void mFPS (void)
{

   fpsFrame++;
   fpsTempo = glutGet(GLUT_ELAPSED_TIME);

   if(fpsTempo - fpsTempoBase > 1000)
   {
      FPS          = fpsFrame*1000.0/(fpsTempo - fpsTempoBase);
	   fpsTempoBase = fpsTempo;
	   fpsFrame     = 0;

      sprintf(fpsString,"FPS: %4.2f", FPS);
   }

   putstring(fpsString, -0.95f,-0.50f);

   return;
}

/************************************************************************/
/* Funcao display:  Display callback.                                        
/*
/************************************************************************/

static void display (void)
{
   int vp[4]; glGetIntegerv(GL_VIEWPORT,vp);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(fovy,(float)vp[2]/vp[3],1.0,100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glMultMatrixf(matrix);
   gluLookAt(0,2,10,0,0,0,0,1,0);

   //draw scene
   drawscene();

   /* Calculo do FPS */
   mFPS();

 // display help message
 if (help)
  showhelp();

 glutSwapBuffers();
}


/************************************************************************/
/* Funcao idle:  Idle callback.                                        
/*
/************************************************************************/

static void idle (void)
{
 display();
}


/************************************************************************/
/* Funcao keyboard:  Keyboard callback.                                        
/*
/************************************************************************/

static void keyboard (unsigned char key, int x, int y)
{
   float dx = 0.0f;
   float dy = 0.0f;
   float dz = 0.0f;
   float rz = 0.0f;
   float lx = 0.0f;
   float ly = 0.0f;
   float lz = 0.0f;

   switch (key)
   {
      case 's': dz -= DL; break;
      case 'w': dz += DL; break;
      case 'd': dx -= DL; break;
      case 'a': dx += DL; break;
      case 'r': dy -= DL; break;
      case 'f': dy += DL; break;
      case 'e': rz -= DA; break;
      case 'q': rz += DA; break;
      case '+': fovy -= DZ; break;
      case '-': fovy += DZ; break;
      case 'h': case 'H': help ^= 1; break;
	  case '1':  interpolTranslation ( ); break;
	  case '2': interpolRotation (); break;
		  
      case 27: exit(0); break;
   }

   // accumulate transformation using OpenGL matrix operations
   glPushMatrix();
   glLoadIdentity();
   glTranslatef(dx,dy,dz);
   glRotatef(rz,0.0f,0.0f,1.0f);
   glMultMatrixf(matrix);
   glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
   glPopMatrix();
}


/************************************************************************/
/* Funcao special: Special Keyboard callback.                                        
/*
/************************************************************************/

static void special (int key, int x, int y)
{
   float rx = 0.0f;
   float ry = 0.0f;

   switch (key)
   {
      case GLUT_KEY_UP:    rx += DA; break;
      case GLUT_KEY_DOWN:  rx -= DA; break;
      case GLUT_KEY_RIGHT: ry += DA; break;
      case GLUT_KEY_LEFT:  ry -= DA; break;
      default: return;
   }

   // accumulate transformation using OpenGL matrix operations
   glPushMatrix();
   glLoadIdentity();
   glRotatef(rx,1.0f,0.0f,0.0f);
   glRotatef(ry,0.0f,1.0f,0.0f);
   glMultMatrixf(matrix);
   glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
   glPopMatrix();

   display();
}


/************************************************************************/
/*
/*                         [  MAIN  ]                                  
/*
/************************************************************************/

int main (int argc, char* argv[])
{
   // open GLUT 
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
   glutInitWindowSize(W,H); 

   // create window
   glutCreateWindow ("Projeto Orientado - Teste de Interpolação de KeyFrames");
   glutReshapeFunc(reshape); 
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutIdleFunc(idle);

   // interact... 
   glutMainLoop();
   return 0;
}