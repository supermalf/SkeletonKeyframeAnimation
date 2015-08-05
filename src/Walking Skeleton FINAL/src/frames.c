 /************************************************************************
  * frames.c
  *
  *  
  *
  *  Created:	2005/11/03
  *  Author: $Author: $ - Malf 
  *  Version $Id: $
  ************************************************************************/
 
#include <stdlib.h>
#include <stdio.h>
#include "frames.h"
#include "draw.h"


static Skeleton  frames[TOTAL_FRAMES]  = 
{   
// pelvis - hipL - hipR - kneeL - kneeR - ankleL - ankleR - size - scapula - elbowL- elbowR - shoulderL - shoulderR
    { 65.0f,   0.0f, -13.0f,   0.0f, 42.0f,    0.0f,  20.0f,  0.0f, 65.0f, 13.0f, 13.0f,  4.0f, -1.0f }, 
    { 65.0f,   4.0f, -16.0f,   0.0f, 43.0f,    0.0f,    8.0f,  0.0f, 65.0f, 13.0f, 13.0f,   8.0f,   -5.0f },
    { 65.0f,   6.0f, -18.0f,   0.0f, 34.0f,    0.0f,  12.0f,  0.0f, 65.0f, 11.0f, 12.0f, 12.0f,   -8.0f },
    { 65.0f,   8.0f, -18.0f,   0.0f, 21.0f,    0.0f,  10.0f, -0.2f, 65.0f, 10.0f, 11.0f, 15.0f, -11.0f },
    { 65.0f, 10.0f, -16.0f,   0.0f,   8.0f,    0.0f,   -3.0f, -0.4f, 65.0f,   8.0f,   9.0f, 18.0f, -13.0f },
    { 65.0f, 12.0f, -16.0f,   0.0f,   2.0f,    5.0f, -19.0f, -0.6f, 65.0f,   7.0f,   8.0f, 19.0f, -14.0f },
    { 65.0f, 14.0f, -18.0f,   0.0f,   2.0f,    4.0f, -14.0f, -0.8f, 65.0f,   8.0f,   7.0f, 20.0f,  -15.0f },
    { 67.0f, 16.0f, -17.0f,   0.0f,   2.0f,  20.0f,   -7.0f, -1.0f, 67.0f,   9.0f,   6.0f, 16.0f, -15.0f },
    { 69.0f, 16.0f, -14.0f,   5.0f,   2.0f,  28.0f,   -1.0f, -0.8f, 69.0f, 10.0f,   6.0f, 13.0f, -15.0f },
    { 69.0f, 14.0f,   -8.0f, 15.0f,   2.0f,  27.0f,    5.0f, -0.6f, 69.0f, 13.0f,   4.0f, 11.0f, -13.0f },
    { 69.0f,    8.0f,  -4.0f, 23.0f,   2.0f,  27.0f,    8.0f, -0.4f, 69.0f, 13.0f,   6.0f,    6.0f, -11.0f },
    { 71.0f,    0.0f,  -2.0f, 37.0f,   0.0f,  23.0f,  10.0f, -0.2f, 71.0f, 13.0f, 12.0f,   2.0f,  -6.0f },
    { 73.0f,   -4.0f,   0.0f, 41.0f,   0.0f,  23.0f,  10.0f,  0.0f, 73.0f, 13.0f, 14.0f,  -1.0f,  -3.0f },
    { 74.0f, -11.0f,   4.0f, 51.0f,   0.0f,  23.0f,  10.0f,  0.0f, 74.0f, 10.0f, 19.0f,  -1.0f,  -2.0f },
    { 75.0f, -17.0f, 10.0f, 54.0f,   0.0f,    9.0f,  10.0f,  0.0f, 75.0f,   7.0f, 20.0f,   -3.0f,   0.0f },
    { 75.0f, -19.0f, 12.0f, 35.0f,   0.0f,    2.0f,  10.0f, -0.2f, 75.0f,   9.0f, 17.0f,   -8.0f,   7.0f },
    { 75.0f, -19.0f, 15.0f, 22.0f,   0.0f,    2.0f,  17.0f, -0.4f, 75.0f, 11.0f, 19.0f, -15.0f, 11.0f },
    { 75.0f, -19.0f, 17.0f, 10.0f,   0.0f,   -5.0f,  25.0f, -0.6f, 75.0f, 12.0f, 15.0f, -19.0f, 18.0f },
    { 75.0f, -19.0f, 19.0f,   0.0f,   0.0f, -17.0f,  28.0f, -1.0f, 75.0f, 13.0f, 17.0f, -20.0f, 18.0f },
    { 75.0f, -17.0f, 17.0f,   6.0f,   8.0f,     0.0f,  34.0f, -0.6f, 75.0f, 14.0f, 16.0f, -18.0f, 14.0f },
    { 75.0f, -12.0f, 15.0f,   6.0f, 14.0f,     6.0f,  34.0f, -0.4f, 75.0f, 14.0f, 17.0f, -12.0f, 12.0f },
    { 73.0f, -10.0f, 11.0f,   6.0f, 18.0f,     6.0f,  34.0f, -0.2f, 73.0f, 14.0f, 16.0f,   -6.0f, 10.0f },
    { 71.0f,   -6.0f,    2.0f,   6.0f, 24.0f,    6.0f,  34.0f,   0.0f, 71.0f, 14.0f, 15.0f,   -4.0f,  6.0f },
    { 69.0f,   -4.0f,   -3.0f,   3.0f, 28.0f,     6.0f,  34.0f,   0.0f, 69.0f, 14.0f, 14.0f,    0.0f,  2.0f } 
};


/************************************************************************
 *  setNextFrame                                                                    
 ************************************************************************/
void setNextFrame(Skeleton *skeleton, int *frameNumber)
{
    (*frameNumber) ++;   
    
    if(*frameNumber >= TOTAL_FRAMES)
        *frameNumber = 0;

    skeleton->sizeContraction       = frames[*frameNumber].sizeContraction;
    skeleton->pelvisAngle               = frames[*frameNumber].pelvisAngle;
    skeleton->hipLeftAngle              = frames[*frameNumber].hipLeftAngle;
    skeleton->hipRightAngle           = frames[*frameNumber].hipRightAngle;
    skeleton->kneeLeftAngle          = frames[*frameNumber].kneeLeftAngle;
    skeleton->kneeRightAngle        = frames[*frameNumber].kneeRightAngle;
    skeleton->ankleLeftAngle         = frames[*frameNumber].ankleLeftAngle;
    skeleton->ankleRightAngle       = frames[*frameNumber].ankleRightAngle;
    skeleton->sizeContraction       = frames[*frameNumber].sizeContraction;
    skeleton->scapulaAngle           = frames[*frameNumber].scapulaAngle;
    skeleton->elbowLeftAngle        = frames[*frameNumber].elbowLeftAngle;
    skeleton->elbowRightAngle      = frames[*frameNumber].elbowRightAngle;
    skeleton->shoulderLeftAngle    = frames[*frameNumber].shoulderLeftAngle;
    skeleton->shoulderRightAngle  = frames[*frameNumber].shoulderRightAngle;
}

/************************************************************************
 *  debugFrame                                                                    
 ************************************************************************/
 void debugFrame(Skeleton skeleton, int frameNumber)
 {
     //printf("FRAME #%d\n", frameNumber);
     printf(" -Pelvis: %lf\n",skeleton.pelvisAngle);
     printf(" -Hip L: %lf\n",skeleton.hipLeftAngle);
     printf(" -Hip R: %lf\n",skeleton.hipRightAngle);
     printf(" -Knee L: %lf\n",skeleton.kneeLeftAngle);
     printf(" -Knee R: %lf\n",skeleton.kneeRightAngle);
     printf(" -Ankle L: %lf\n",skeleton.ankleLeftAngle);
     printf(" -Ankle R: %lf\n",skeleton.ankleRightAngle);
     printf(" -Size: %lf\n",skeleton.sizeContraction);     
     printf(" -Elbow L: %lf\n",skeleton.elbowLeftAngle);
     printf(" -Elbow R: %lf\n",skeleton.elbowRightAngle);
     printf(" -Shoulder L: %lf\n",skeleton.shoulderLeftAngle);
     printf(" -Shoulder R: %lf\n",skeleton.shoulderRightAngle);
     printf("============================\n");
 }

