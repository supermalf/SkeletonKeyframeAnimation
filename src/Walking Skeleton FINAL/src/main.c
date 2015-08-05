/************************************************************************
 * main.c
 *
 *  
 *
 *  Created:	2005/11/03
 *  Author: $Author: $ - Malf 
 *  Version $Id: $
 ************************************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "glut.h"
#include "draw.h"
#include "frames.h"
#include "keyframe.h"

/************************************************************************
 *                                                                      
 ************************************************************************/
static int actualFrame = 0;  
static int actualKeyframe = 0;     
static int mode =1;
static float walkSpeed = 8.0f;
static Skeleton skeleton  = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
static int help = 1; 


/************************************************************************
 *                                                                      
 ************************************************************************/
static void setupRenderingContext(void);
static void reshapeWindow( int width, int height );
static void renderScene(void);
static void handleKeys( unsigned char key, int x, int y );
static void handleSpecialKeys( int key, int x, int y );
static void idle (void);


/************************************************************************
 *  main                                                                    
 ************************************************************************/
int main( int argc, char *argv[] )
{
    int windowWidth;
    int windowHeight;

    glutInit(&argc, argv);

    //windowWidth = glutGet( GLUT_SCREEN_WIDTH );
    //windowHeight = glutGet( GLUT_SCREEN_HEIGHT );
    
    windowHeight = 800;
    windowWidth = 600;
    
    glutInitWindowSize( windowWidth, windowHeight );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    glutCreateWindow("Projeto Orientado - Walking Skeleton by KeyFrames");

    glutReshapeFunc( reshapeWindow );
    glutDisplayFunc( renderScene );
    glutKeyboardFunc( handleKeys );
    glutSpecialFunc( handleSpecialKeys );
    glutIdleFunc(idle);
    
    setupRenderingContext();
    
    glutMainLoop();

    return 0;
}

/************************************************************************
 *  setupRenderingContext                                                                    
 ************************************************************************/
void setupRenderingContext(void)
{
    static float ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };  
    static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    static float specularLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    static float lightPosition[] = { -100.0f, 100.0f, -150.0f, 1.0f };
    static float specularReflectivity[] = { 0.6f, 0.6f, 0.6f, 1.0f };

    glEnable( GL_DEPTH_TEST ); 
    glEnable(GL_LIGHTING);  

    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientLight );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight );
    glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
    glEnable( GL_LIGHT0 );

    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

    glMaterialfv( GL_FRONT, GL_SPECULAR, specularReflectivity );
    glMateriali( GL_FRONT, GL_SHININESS, 64 );

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
}

/************************************************************************
 *  reshapeWindow                                                                    
 ************************************************************************/
void reshapeWindow( int width, int height )
{
    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 15.0f, ( (float)width / (float)height ), 1.0, 500.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(100,150,250,0.,0.,0.,0.,1.,0.);

}

/************************************************************************
 *  idle                                                                    
 ************************************************************************/
static void idle (void)
{
    renderScene();
}

/************************************************************************
 *  renderScene                                                                    
 ************************************************************************/
void renderScene(void)
{      
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );

    glPushMatrix();  
        drawSkeleton( mode, &skeleton );
    glPopMatrix();   

    if (help)
        showhelp(); 
    
    if (getMode())
    {     
        #ifdef _WIN32
        Sleep(walkSpeed*4);
        #endif
        setNextFrame(&skeleton, &actualFrame);
    }

    else
    {   
        #ifdef _WIN32
        Sleep( walkSpeed);
        #endif
        setNextKeyframe(&skeleton, &actualFrame);
    }
 
    
    /*
    #include <time.h>
    // Processo de sleep para nao consumir a maquina
    timespec * lag;
    lag =  new timespec();
    lag->tv_sec = 0;
    lag->tv_nsec = 30;
    nanosleep(lag, NULL);           
    */

    glutSwapBuffers();
}

/************************************************************************
 *  handleKeys                                                                    
 ************************************************************************/
void handleKeys( unsigned char key, int x, int y )
{
    static int isFullscreen = 0;

    switch( key )
    {
        case 'h': case 'H': 
            help ^= 1; 
            break;
        
        case '+':
            walkSpeed -=1;
            if (walkSpeed<0)
                walkSpeed = 0;
            break;
              
        case '-': 
            walkSpeed +=1;
            break;

        case 'e':case 'E':
            if ((mode&2)==2) 
                mode=(mode&1);
            else
                mode=mode|2;
            break;

        case 'm': 
        case 'M': 
            changeMode(); 
            break;
        
        case 13:   //ENTER
        if( isFullscreen )
        {
            glutReshapeWindow( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
            isFullscreen = 0;
        }
        else
        {
            glutFullScreen();
            isFullscreen = 1;
        }
        break;

    case 27:  //ESC
        exit( 0 );
        break;
    }

    //glutPostRedisplay(); 
}

/************************************************************************
 * handleSpecialKeys                                                                     
 ************************************************************************/
void handleSpecialKeys( int key, int x, int y )
{
    switch( key )
    {
       case GLUT_KEY_F1:
            debugFrame(skeleton, actualFrame);    
            break;

       case GLUT_KEY_F3:
           setNextFrame(&skeleton, &actualFrame);  
           setMode(1); 
           break;

       case GLUT_KEY_F4:
           setNextKeyframe(&skeleton, &actualKeyframe);   
           setMode(0); 
           break; 
    }

    //glutPostRedisplay();
}
