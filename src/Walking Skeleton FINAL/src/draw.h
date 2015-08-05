/************************************************************************
 * draw.h
 *
 *  
 *
 *  Created:	2005/11/03
 *  Author: $Author: $ - Malf 
 *  Version $Id: $
 ************************************************************************/

#ifndef _DRAW_H_
#define _DRAW_H_


/************************************************************************
* Exported Type Declarations                       
************************************************************************/
typedef struct
{
	float pelvisAngle;
	float hipLeftAngle;
	float hipRightAngle;
	float kneeLeftAngle;
	float kneeRightAngle;
	float ankleLeftAngle;
	float ankleRightAngle;
	float sizeContraction;
	float scapulaAngle;
    float elbowLeftAngle;
    float elbowRightAngle;
    float shoulderLeftAngle;
    float shoulderRightAngle;
}
Skeleton;

 
/************************************************************************
 * Exported Function Declarations                                                                     
 ************************************************************************/
void drawSkeleton( int mode, Skeleton *skeleton );
void showhelp ();
void mFPS  ();
void changeMode();
int getMode();
void setMode(int mode);

#endif
