/************************************************************************
 * draw.c
 *
 *  
 *
 *  Created:	2005/11/03
 *  Author: $Author: $ - Malf 
 *  Version $Id: $
 ************************************************************************/

#include <stdio.h>
#include "draw.h"
#include "glut.h"


/* Variaveis do Calculo de FrameRate */
static int   fpsTotal;
static int   fpsFrame;
static int   fpsTempo;
static int   fpsTempoBase = 0;
static float FPS   = 0.0;
static char  fpsString[30];

static int keyFrameMode = 0;

/************************************************************************
 *   drawAxis                                                                   
 ************************************************************************/
static void drawAxis(float size)
{
	glLineWidth(1);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0,    0.0, 0.0);
        glVertex3f(size, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0,  0.0, 0.0);
        glVertex3f(0.0, size, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, size);
    glEnd();
}


/************************************************************************
 *  mSolidTriangle                                                                    
 ************************************************************************/
void mSolidTriangle( GLdouble size )
{
	int i, j;
	float cside = size/2.0;

	float mVertex[5][4][3]= 
	{
		{{-1.0, -1.0, -1.0},{ 1.0, -1.0, -1.0},{ 1.0,  1.0, -1.0},{-1.0,  1.0, -1.0}}, //Costas
		{{ 1.0,  1.0, -1.0},{ 1.0,  -1.0,  1.0},{ 1.0, -1.0,  1.0},{ 1.0, -1.0, -1.0}}, //Direito
		{{-1.0,  1.0, -1.0},{-1.0,  1.0,  -1.0},{-1.0, -1.0,  1.0},{-1.0, -1.0, -1.0}}, //Esquerdo
		{{-1.0, -1.0,  1.0},{ 1.0, -1.0,  1.0},{ 1.0, -1.0, -1.0},{-1.0, -1.0, -1.0}}, //Chão
		{{-1.0,  1.0, -1.0},{-1.0,  -1.0,  1.0},{ 1.0,  -1.0,  1.0},{ 1.0,  1.0, -1.0}}  //Teto
	};

	float mNormal[5][3]= 
	{
		{ 0.0,  0.0, -1.0}, //Costas
		{ 1.0,  0.0,  0.0}, //Direito
		{-1.0,  0.0,  0.0}, //Esquerdo
		{ 0.0, -1.0,  0.0}, //Chão
		{ 0.0,  1.0,  0.0}  //Teto
	};

	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);

	for ( i = 0; i < 5; ++i ) 
	{
		glNormal3f(cside*mNormal[i][0], cside*mNormal[i][1], cside*mNormal[i][2]);

		for ( j = 0; j < 4; ++j ) 
			glVertex3f(cside*mVertex[i][j][0],  cside*mVertex[i][j][1], cside*mVertex[i][j][2]);
	} 
	glEnd( );
}

/************************************************************************
 *                                                                      
 ************************************************************************/
void drawSkeleton( int mode, Skeleton *skeleton )
{
	glTranslatef( 0.0f, skeleton->sizeContraction, 0.0f );

	//servical column
	if ((mode&2)==2)drawAxis(4);
	glPushMatrix(); 
		glTranslatef( 0.0f, 10.0f, 0.0f );
		glPushMatrix(); 
			if ((mode&2)==2)drawAxis(4);
			glScalef( 1,20, 1 );	
			glColor3f( 0.5f, 0.5f, 1.0f ); 
			glutSolidCube( 1.0 );
		glPopMatrix();		
		//Scapula
		glTranslatef( 0.0f, 10.0f, 0.0f );

		if ((mode&2)==2)drawAxis(4);
		glColor3f( 0.5f, 0.5f, 0.5f ); 
		glutSolidSphere( 1.0f, 20, 20 );	
		
		//Clavicle
		glPushMatrix(); 
		if ((mode&2)==2)drawAxis(4);		
		//glTranslatef( -8.0f, -5.0f, 2.0f );
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glRotatef(skeleton->scapulaAngle, 1.0f, 0.0f, 0.0f);		
		glPushMatrix(); 
		glScalef( 1,18, 1 );	
		glColor3f( 0.5f, 0.5f, 1.0f ); 
		glutSolidCube( 1.0 );
		glPopMatrix();
           

         glPushMatrix();    
        glRotatef(skeleton->shoulderLeftAngle, 0.0f, 1.0f, 0.0f);
        //L shoulder
        glPushMatrix(); 
        if ((mode&2)==2)drawAxis(4);
        glTranslatef( 0.0f, 9.0f, 0.0f );
        glColor3f( 0.5f, 0.5f, 0.5f ); 
        glutSolidSphere( 1.0f, 20, 20 );
        //L arm1
        glPushMatrix(); 
        if ((mode&2)==2)drawAxis(4);
        glTranslatef( -7.0f, 0.0f, 0.0f );
        glRotatef(90, 0.0f, 0.0f, 1.0f);
        glScalef( 1,14.0, 1 );	
        glColor3f( 0.5f, 0.5f, 1.0f ); 
        glutSolidCube( 1.0 );
        glPopMatrix();
        //L cotovelo  

        glPushMatrix();    
        if ((mode&2)==2)drawAxis(4);            
        glTranslatef( -14.0f, 0.0f, 0.0f );
        glColor3f( 0.5f, 0.5f, 0.5f );       
        glutSolidSphere( 1.0f, 20, 20 );   
        glRotatef(skeleton->elbowLeftAngle, 0.0f, 1.0f, 0.0f);  

        //L arm2
        glPushMatrix();             
        if ((mode&2)==2)drawAxis(4);
        glTranslatef( -8.0f, 0.0f, 0.0f );
        glRotatef(90, 0.0f, 0.0f, 1.0f);
        glScalef( 1,16, 1 );	
        glColor3f( 0.5f, 0.5f, 1.0f ); 
        glutSolidCube( 1.0 );
        glPopMatrix();
        //L 'hand
        glPushMatrix(); 
        if ((mode&2)==2)drawAxis(4);
        glTranslatef( -14.0f, 0.0f, 0.0f );
        glColor3f( 0.5f, 0.5f, 0.5f ); 
        glutSolidCube(2);
        glTranslatef( -2.0f, 0.0f, 0.0f );
        glutSolidCube(3);
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();

         glRotatef(skeleton->shoulderRightAngle, 0.0f, 1.0f, 0.0f);
		//R shoulder
		glPushMatrix(); 
		if ((mode&2)==2)drawAxis(4);
		glTranslatef( 0.0f, -9.0f, 0.0f );
		glColor3f( 0.5f, 0.5f, 0.5f ); 
		glutSolidSphere( 1.0f, 20, 20 );
			//R arm1
			glPushMatrix(); 
            if ((mode&2)==2)drawAxis(4);
			glTranslatef( -7.0f, 0.0f, 0.0f );
			glRotatef(90, 0.0f, 0.0f, 1.0f);
			glScalef( 1,14.0, 1 );	
			glColor3f( 0.5f, 0.5f, 1.0f ); 
			glutSolidCube( 1.0 );
			glPopMatrix();
				//R cotovelo  
            
				glPushMatrix();    
                if ((mode&2)==2)drawAxis(4);            
				glTranslatef( -14.0f, 0.0f, 0.0f );
				glColor3f( 0.5f, 0.5f, 0.5f );       
				glutSolidSphere( 1.0f, 20, 20 );   
                glRotatef(skeleton->elbowRightAngle, 0.0f, 1.0f, 0.0f);  

                //R arm2
                glPushMatrix();             
                if ((mode&2)==2)drawAxis(4);
                glTranslatef( -8.0f, 0.0f, 0.0f );
                glRotatef(90, 0.0f, 0.0f, 1.0f);
                glScalef( 1,16, 1 );	
                glColor3f( 0.5f, 0.5f, 1.0f ); 
                glutSolidCube( 1.0 );
                glPopMatrix();
                //R 'hand
                glPushMatrix(); 
                if ((mode&2)==2)drawAxis(4);
                glTranslatef( -14.0f, 0.0f, 0.0f );
                glColor3f( 0.5f, 0.5f, 0.5f ); 
                glutSolidCube(2);
                glTranslatef( -2.0f, 0.0f, 0.0f );
                glutSolidCube(3);
                glPopMatrix();
				glPopMatrix();
		glPopMatrix();
		glPopMatrix();		


	//neck
		glTranslatef( 0.0f, 4.5f, 0.0f );
		glPushMatrix(); 
	if ((mode&2)==2)drawAxis(4);
		glScalef( 1,8, 1 );	
		glColor3f( 0.5f, 0.5f, 1.0f ); 
		glutSolidCube( 1.0 );
		glPopMatrix();		
//Head
		glTranslatef( 0.0f, 4.0f, 0.0f );
		if ((mode&2)==2)drawAxis(8);
		glColor3f( 0.5f, 0.5f, 0.5f ); 
		glutSolidSphere( 4.0f, 20, 20 );	
	glPopMatrix();

	glRotatef(skeleton->pelvisAngle, 0.0f, 1.0f, 0.0f);

	//#Pelvis
	if ((mode&2)==2)drawAxis(8);	
	//if ((mode&1)==1) drawJoint( );
	glColor3f( 0.5f, 0.5f, 0.5f ); 
	glutSolidSphere( 2.5f, 20, 20 );


	//all HIP
    //glRotatef(arm->bottomArmAngle, 0.0f, 0.0f, 1.0f);
  	glTranslatef( 0.0f,- 5.0f, 0.0f );

//#Hip_L bone
	glPushMatrix();    	
		glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef( -3.0f,0.0f, 0.0f ); 
		if ((mode&2)==2)drawAxis(4);
		glPushMatrix();  
			glScalef( 1,10, 1 );	
			glColor3f( 0.5f, 0.5f, 1.0f ); 
			glutSolidCube( 1.0 );
		glPopMatrix();
	//#Hip_L joint
		glTranslatef( 0.0f,-5.0f, 0.0f );
		glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(skeleton->hipLeftAngle, 1.0f, 0.0f, 0.0f);
		if ((mode&2)==2)drawAxis(4);
		glColor3f( 0.5f, 0.5f, 0.5f ); 
		glutSolidSphere( 1.5f, 20, 20 );	
	//Femur L
		glTranslatef(0,- 16.5/2 , 0.0f );
		glPushMatrix();    	
			if ((mode&2)==2)drawAxis(4);
			glPushMatrix();  
				glScalef( 1,15, 1 );	
				glColor3f( 0.5f, 0.5f, 1.0f ); 
				glRotatef(-5, 0.0f, 0.0f, 1.0f);
				glutSolidCube( 1.0 );
			glPopMatrix();
		//#Knee L
			glTranslatef( 0.0f,-7.5f, 0.0f );
			if ((mode&2)==2)drawAxis(4);
			glColor3f( 0.5f, 0.5f, 0.5f ); 
			glutSolidSphere( 1.0f, 20, 20 );

			//Fibula L
			glRotatef(skeleton->kneeLeftAngle, 1.0f, 0.0f, 0.0f);
			glPushMatrix();    	
				glTranslatef( 0.0f, -7.5f, 0.0f ); 
				if ((mode&2)==2)drawAxis(4);
				glPushMatrix();  
					glScalef( 1,15, 1 );	
					glColor3f( 0.5f, 0.5f, 1.0f ); 
					glutSolidCube( 1.0 );
				glPopMatrix();
				//#Ankle L
				glTranslatef( 0.0f,-7.5f, 0.0f );
				if ((mode&2)==2)drawAxis(4);
				glRotatef(skeleton->ankleLeftAngle, 1.0f, 0.0f, 0.0f);
				glColor3f( 0.5f, 0.5f, 0.5f ); 
				glutSolidSphere( 1.0f, 20, 20 );
				glTranslatef( 0.0f,-1.5f, 0.0f );
				glutSolidCube( 3.0 );
				glTranslatef( 0.0f,0.0f, 2.0f );
				mSolidTriangle(3);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

//#Hip_R bone
	glPushMatrix();   
		glRotatef(15, 0.0f, 0.0f, 1.0f);	
		glTranslatef( 3.0f,0.0f, 0.0f );
		if ((mode&2)==2)drawAxis(4);
		glPushMatrix();  
			glScalef( 1,10, 1 );	
			glColor3f( 0.5f, 0.5f, 1.0f );
			glutSolidCube( 1.0 );
		glPopMatrix();
//#Hip_R Joint
		glTranslatef( 0.0f,-5.0f, 0.0f );	
		glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(skeleton->hipRightAngle, 1.0f, 0.0f, 0.0f);
		if ((mode&2)==2)drawAxis(4);
		glColor3f( 0.5f, 0.5f, 0.5f ); 
		glutSolidSphere( 1.5f, 20, 20 );
//Femur R
		glTranslatef(0,- 16.5/2 , 0.0f );
		glPushMatrix();    	
			if ((mode&2)==2)drawAxis(4);
			glPushMatrix();  
				glScalef( 1,15, 1 );	
				glColor3f( 0.5f, 0.5f, 1.0f ); 
				glRotatef(-5, 0.0f, 0.0f, 1.0f);
				glutSolidCube( 1.0 );
			glPopMatrix();
//#Knee R
			glTranslatef( 0.0f,-7.5f, 0.0f );
			if ((mode&2)==2)drawAxis(4);
			glColor3f( 0.5f, 0.5f, 0.5f ); 
			glutSolidSphere( 1.0f, 20, 20 );
//Fibula R
		glRotatef(skeleton->kneeRightAngle, 1.0f, 0.0f, 0.0f);
			glPushMatrix();    	
				glTranslatef( 0.0f, -7.5f, 0.0f ); 
				if ((mode&2)==2)drawAxis(4);
				glPushMatrix();  
					glScalef( 1,15, 1 );	
					glColor3f( 0.5f, 0.5f, 1.0f ); 
					glutSolidCube( 1.0 );
				glPopMatrix();
//#Ankle R
				glTranslatef( 0.0f,-7.5f, 0.0f );
				if ((mode&2)==2)drawAxis(4);
				glRotatef(skeleton->ankleRightAngle, 1.0f, 0.0f, 0.0f);
				glColor3f( 0.5f, 0.5f, 0.5f ); 
				glutSolidSphere( 1.0f, 20, 20 );
				glTranslatef( 0.0f,-1.5f, 0.0f );
				glutSolidCube( 3.0 );
				glTranslatef( 0.0f,0.0f, 2.0f );
				mSolidTriangle(3);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

/************************************************************************
* Funcao putstring:  Display message on screen.                                         
************************************************************************/
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

    glColor3f(0.0f,0.4f,0.8f);
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

/************************************************************************
 *  changeMode                                                                    
 ************************************************************************/
void changeMode()
{
     keyFrameMode ^= 1; 
}

/************************************************************************
*  getMode                                                                    
************************************************************************/
int getMode()
{
    return keyFrameMode; 
}

/************************************************************************
*   setMode                                                                   
************************************************************************/
void setMode(int mode)
{
    if (mode >= 1)
        keyFrameMode = 1;

    else if (mode <= 0)
        keyFrameMode = 0;

}

/************************************************************************
 * Funcao showhelp:  Display help message.    
 ************************************************************************/
void showhelp ()
{
    if(keyFrameMode)
        putstring("Modo: [ ALL FRAMES ]",-0.95,-0.35);
    else
        putstring("Modo: [ KEYFRAMES ]",-0.95,-0.35);
    putstring("ENTER: Fullscreen",-0.95,-0.43);
    putstring("m: Trocar modo (Keyframe / All )",-0.95,-0.51);
    putstring("e: Exibir eixos cartesianos",-0.95,-0.59);
    putstring("+: Aumenta velocidade do movimento",-0.95,-0.67);
    putstring("-: Diminui velocidade do movimento",-0.95,-0.75);
    putstring("ESC: sair",-0.95,-0.83);
}


/************************************************************************
*  Funcao mFPS:  Funcao que calcula o Framerate de parede e imprime na 
*    tela principal da aplicação                                                                                   
 ************************************************************************/
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

