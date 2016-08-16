#include<stdlib.h>

#define RAND() xorshf96()

#ifndef _myRandom
#define _myRandom

static unsigned long x=123456789, y=362436069, z=521288629;

inline unsigned long xorshf96(void) {          //period 2^96-1
unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}
int g_seed;
inline int fastrand() { 
  g_seed = (214013*g_seed+2531011); 
  return (g_seed>>16)&0x7FFF; 
} 

static unsigned long myS=796821;
unsigned long fakeR(void){

myS=(myS<<8)^myS;
return myS;
}

#endif
