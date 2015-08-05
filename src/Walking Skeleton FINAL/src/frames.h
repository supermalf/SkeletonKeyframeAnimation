 /************************************************************************
  * frames.h
  *
  *  
  *
  *  Created:	2005/11/03
  *  Author: $Author: $ - Malf 
  *  Version $Id: $
  ************************************************************************/

#ifndef _FRAMES_H_
#define _FRAMES_H_
 
#define TOTAL_FRAMES 24

#include <stdlib.h>
#include <stdio.h>
#include "draw.h"


/************************************************************************
* Exported Function Declarations                                                                     
************************************************************************/
void setNextFrame(Skeleton *frame, int * frameNumber);
void debugFrame(Skeleton skeleton, int frameNumber);


#endif

