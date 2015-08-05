/************************************************************************
* keyframe.h
*
*  
*
*  Created:	2005/11/03
*  Author: $Author: $ - Malf 
*  Version $Id: $
************************************************************************/

#ifndef _KEYFRAME_H_
#define _KEYFRAME_H_

#define KEY_FRAMES 8
#define KEY_FRAMES_DIVISION 10

#include "draw.h"
#include "algebra.h"


/************************************************************************
* Exported Function Declarations                                                                     
************************************************************************/
void setNextKeyframe(Skeleton *skeleton, int *frameNumber);
float interpolRotation ( float firstAngle, float secondAngle, Vector position);
float interpolTranslation ( Vector firstPos, Vector secondPos );

#endif

