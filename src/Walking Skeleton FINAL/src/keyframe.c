/************************************************************************
 * keyframe.c
 *
 *  
 *
 *  Created:	2005/11/03
 *  Author: $Author: $ - Malf 
 *  Version $Id: $
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "keyframe.h"
#include "draw.h"
#include "algebra.h"



static Skeleton  keyFrames[KEY_FRAMES]  = 
{   
// pelvis - hipL - hipR - kneeL - kneeR - ankleL - ankleR - size - scapula - elbowL- elbowR - shoulderL - shoulderR
    { 65.0f,   0.0f, -13.0f,   0.0f, 42.0f,    0.0f,  20.0f,  0.0f, 65.0f, 13.0f, 13.0f,  4.0f, -1.0f }, 
   // { 65.0f,   4.0f, -16.0f,   0.0f, 43.0f,    0.0f,    8.0f,  0.0f, 65.0f, 13.0f, 13.0f,   8.0f,   -5.0f },
  //  { 65.0f,   6.0f, -18.0f,   0.0f, 34.0f,    0.0f,  12.0f,  0.0f, 65.0f, 11.0f, 12.0f, 12.0f,   -8.0f },
  { 65.0f,   8.0f, -18.0f,   0.0f, 21.0f,    0.0f,  10.0f, -0.2f, 65.0f, 10.0f, 11.0f, 15.0f, -11.0f },
    //{ 65.0f, 10.0f, -16.0f,   0.0f,   8.0f,    0.0f,   -3.0f, -0.4f, 65.0f,   8.0f,   9.0f, 18.0f, -13.0f },
 //   { 65.0f, 12.0f, -16.0f,   0.0f,   2.0f,    5.0f, -19.0f, -0.6f, 65.0f,   7.0f,   8.0f, 19.0f, -14.0f },
    { 65.0f, 14.0f, -18.0f,   0.0f,   2.0f,    4.0f, -14.0f, -0.8f, 65.0f,   8.0f,   7.0f, 20.0f,  -15.0f },
  //  { 67.0f, 16.0f, -17.0f,   0.0f,   2.0f,  20.0f,   -7.0f, -1.0f, 67.0f,   9.0f,   6.0f, 16.0f, -15.0f },
 //   { 69.0f, 16.0f, -14.0f,   5.0f,   2.0f,  28.0f,   -1.0f, -0.8f, 69.0f, 10.0f,   6.0f, 13.0f, -15.0f },
    { 69.0f, 14.0f,   -8.0f, 15.0f,   2.0f,  27.0f,    5.0f, -0.6f, 69.0f, 13.0f,   4.0f, 11.0f, -13.0f },
  //  { 69.0f,    8.0f,  -4.0f, 23.0f,   2.0f,  27.0f,    8.0f, -0.4f, 69.0f, 13.0f,   6.0f,    6.0f, -11.0f },
  //  { 71.0f,    0.0f,  -2.0f, 37.0f,   0.0f,  23.0f,  10.0f, -0.2f, 71.0f, 13.0f, 12.0f,   2.0f,  -6.0f },
    { 73.0f,   -4.0f,   0.0f, 41.0f,   0.0f,  23.0f,  10.0f,  0.0f, 73.0f, 13.0f, 14.0f,  -1.0f,  -3.0f },
  //  { 74.0f, -11.0f,   4.0f, 51.0f,   0.0f,  23.0f,  10.0f,  0.0f, 74.0f, 10.0f, 19.0f,  -1.0f,  -2.0f },
  //  { 75.0f, -17.0f, 10.0f, 54.0f,   0.0f,    9.0f,  10.0f,  0.0f, 75.0f,   7.0f, 20.0f,   -3.0f,   0.0f },
    { 75.0f, -19.0f, 12.0f, 35.0f,   0.0f,    2.0f,  10.0f, -0.2f, 75.0f,   9.0f, 17.0f,   -8.0f,   7.0f },
  //  { 75.0f, -19.0f, 15.0f, 22.0f,   0.0f,    2.0f,  17.0f, -0.4f, 75.0f, 11.0f, 19.0f, -15.0f, 11.0f },
  // { 75.0f, -19.0f, 17.0f, 10.0f,   0.0f,   -5.0f,  25.0f, -0.6f, 75.0f, 12.0f, 15.0f, -19.0f, 18.0f },
    { 75.0f, -19.0f, 19.0f,   0.0f,   0.0f, -17.0f,  28.0f, -1.0f, 75.0f, 13.0f, 17.0f, -20.0f, 18.0f },
  //  { 75.0f, -17.0f, 17.0f,   6.0f,   8.0f,     0.0f,  34.0f, -0.6f, 75.0f, 14.0f, 16.0f, -18.0f, 14.0f },
  //  { 75.0f, -12.0f, 15.0f,   6.0f, 14.0f,     6.0f,  34.0f, -0.4f, 75.0f, 14.0f, 17.0f, -12.0f, 12.0f },
   { 73.0f, -10.0f, 11.0f,   6.0f, 18.0f,     6.0f,  34.0f, -0.2f, 73.0f, 14.0f, 16.0f,   -6.0f, 10.0f },
    //{ 71.0f,   -6.0f,    2.0f,   6.0f, 24.0f,    6.0f,  34.0f,   0.0f, 71.0f, 14.0f, 15.0f,   -4.0f,  6.0f },
  //  { 69.0f,   -4.0f,   -3.0f,   3.0f, 28.0f,     6.0f,  34.0f,   0.0f, 69.0f, 14.0f, 14.0f,    0.0f,  2.0f } 
};

static Vector skeletonRotPos [12] = 
{
    {0.0f, 1.0f, 0.0f},     // pelvis
    {1.0f, 0.0f, 0.0f},     // hipL
    {1.0f, 0.0f, 0.0f},     // hipR 
    {1.0f, 0.0f, 0.0f},     // kneeL
    {1.0f, 0.0f, 0.0f},     // kneeR
    {1.0f, 0.0f, 0.0f},     // ankleL
    {1.0f, 0.0f, 0.0f},     // ankleR 
    {1.0f, 0.0f, 0.0f},     // scapula
    {0.0f, 1.0f, 0.0f},     // elbowL
    {0.0f, 1.0f, 0.0f},     // elbowR 
    {0.0f, 1.0f, 0.0f},     // shoulderL
    {0.0f, 1.0f, 0.0f}      // shoulderR
};


//KeyFrames
static int actualFrame = 0;
static int subFrameActual = 0;
static int frameDivision = KEY_FRAMES_DIVISION; //Numero de subframes entre 2 frames


/************************************************************************
*                                                                      
************************************************************************/
void setNextKeyframe(Skeleton *skeleton, int *frameNumber)
{
    int _actualFrame,  _nextFrame;
	Vector pos1, pos2;

        actualFrame = *frameNumber;    //debug

      _actualFrame = *frameNumber;
      _nextFrame = _actualFrame +1;

      if(_nextFrame >= KEY_FRAMES)
          _nextFrame = 0;

     //Calculating Frame...

    //Pelvis
    skeleton->pelvisAngle = interpolRotation(  keyFrames[_actualFrame].pelvisAngle, 
                                                                         keyFrames[_nextFrame].pelvisAngle, 
                                                                         skeletonRotPos[0] );
    //Left Hip
     skeleton->hipLeftAngle = interpolRotation(  keyFrames[_actualFrame].hipLeftAngle, 
                                                                            keyFrames[_nextFrame].hipLeftAngle, 
                                                                            skeletonRotPos[1] );
     //Right Hip
     skeleton->hipRightAngle = interpolRotation( keyFrames[_actualFrame].hipRightAngle, 
                                                                             keyFrames[_nextFrame].hipRightAngle, 
                                                                             skeletonRotPos[2] );
      //Left Knee
     skeleton->kneeLeftAngle = interpolRotation( keyFrames[_actualFrame].kneeLeftAngle, 
                                                                              keyFrames[_nextFrame].kneeLeftAngle, 
                                                                              skeletonRotPos[3] );
     //Right Knee
     skeleton->kneeRightAngle = interpolRotation( keyFrames[_actualFrame].kneeRightAngle, 
                                                                                 keyFrames[_nextFrame].kneeRightAngle, 
                                                                                 skeletonRotPos[4] );
     //Left Ankle
     skeleton->ankleLeftAngle = interpolRotation( keyFrames[_actualFrame].ankleLeftAngle, 
                                                                               keyFrames[_nextFrame].ankleLeftAngle, 
                                                                               skeletonRotPos[5] );
     //Right Ankle
     skeleton->ankleRightAngle = interpolRotation( keyFrames[_actualFrame].ankleRightAngle, 
                                                                                 keyFrames[_nextFrame].ankleRightAngle, 
                                                                                 skeletonRotPos[6] );
     //Scapula
     skeleton->scapulaAngle = interpolRotation( keyFrames[_actualFrame].scapulaAngle, 
                                                                             keyFrames[_nextFrame].scapulaAngle, 
                                                                             skeletonRotPos[7] );
     //Left Elbow
     skeleton->elbowLeftAngle = interpolRotation( keyFrames[_actualFrame].elbowLeftAngle, 
                                                                                keyFrames[_nextFrame].elbowLeftAngle, 
                                                                                skeletonRotPos[8] );
     //Right Elbow
     skeleton->elbowRightAngle = interpolRotation( keyFrames[_actualFrame].elbowRightAngle, 
                                                                                  keyFrames[_nextFrame].elbowRightAngle, 
                                                                                  skeletonRotPos[9] );
     //Left Shoulder
     skeleton->shoulderLeftAngle = interpolRotation( keyFrames[_actualFrame].shoulderLeftAngle, 
                                                                                    keyFrames[_nextFrame].shoulderLeftAngle, 
                                                                                    skeletonRotPos[10] );
     //Right Shoulder
     skeleton->shoulderRightAngle = interpolRotation( keyFrames[_actualFrame].shoulderRightAngle, 
                                                                                      keyFrames[_nextFrame].shoulderRightAngle, 
                                                                                      skeletonRotPos[11] );

     //Size
		pos1 = algVector( 0.0f, keyFrames[_actualFrame].sizeContraction, 0.0f, 1.0f );
		pos2 = algVector( 0.0f, keyFrames[_nextFrame].sizeContraction, 0.0f, 1.0f );
		skeleton->sizeContraction= interpolTranslation(pos1, pos2);

   
	//Adicionado SubFrame de interpolação
    subFrameActual++;

    //Verificar passagem de frame
    if ( subFrameActual == frameDivision)
    {
        subFrameActual = 0;
        //frameActualR++;

        (*frameNumber) ++;   

        if(*frameNumber >= KEY_FRAMES)
            *frameNumber = 0;

    }

     actualFrame = *frameNumber;    //debug
}

/************************************************************************/                                   
/*
/************************************************************************/
float interpolTranslation ( Vector firstPos, Vector secondPos )
{ 
    float distanceFrame1, distanceFrame2;
	Vector resultPos;

    //Pegando a distancia do subframe atual para o frame anterior e o proximo
    //A contribuicao para a interpolacao e' o inverso
    distanceFrame2 = (( 100.0f * subFrameActual ) / frameDivision) /100.0f;
    distanceFrame1 = (float) fabs(distanceFrame2 - 1.0f);

    //Novas posicoes do objeto
	//resultPos.x = (firstPos.x * distanceFrame1) + (secondPos.x * distanceFrame2);
	resultPos.y = (firstPos.y * distanceFrame1) + (secondPos.y * distanceFrame2);
    //resultPos.z = (firstPos.z * distanceFrame1) + (secondPos.z * distanceFrame2);
	//resultPos.w = 1;

	return (float)resultPos.y;
}

/************************************************************************/                                    
/*
/************************************************************************/
float interpolRotation ( float firstAngle, float secondAngle, Vector position)
{
    float distanceFrame1, resultAngle;
    Quat q1, q2, resultQuaternion;
     Vector resultAxis;

     
    //Desfazendo angulos negativos
    if(firstAngle < 0.0f)
        firstAngle = 360.0f + firstAngle;

    if(secondAngle < 0.0f)
        secondAngle = 360.0f + secondAngle;
      
    //Criando o quatérnio 1 baseado no Frame1
    q1 = algQuat(0,0,0,0); 
    q1 = algQuatFromRot(firstAngle, position );

    //Criando o quatérnio 2 baseado no Frame2
    q2 = algQuat(0,0,0,0); 
    q2 = algQuatFromRot(secondAngle, position );

    //Pegando a distancia do Frame1
    distanceFrame1 = (( 100.0f * subFrameActual ) / frameDivision) /100.0f;

    //Fazendo interpolação dos Quatérnios
    resultQuaternion =  algQuatSLERP(q1, q2, distanceFrame1);

    resultAngle = (float)algQuatRotAngle(resultQuaternion);
    resultAxis   = algQuatRotAxis(resultQuaternion);

    //Invertendo eixo
    if ( ((resultAxis.x < 0) && (position.x == 1))  || 
         ((resultAxis.y < 0) && (position.y == 1))  ||
         ((resultAxis.z < 0) && (position.z == 1)))
         return -resultAngle;

    return resultAngle;
}

