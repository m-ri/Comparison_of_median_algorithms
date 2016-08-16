#include <algorithm>
#include <math.h>
#include "myRandom.cpp"

//#define MAX 64000001

//#define FAST_MEDIAN

extern long vectAus[];
//long samplVect[MAX],destVect[MAX];

//It return 1=success,0=fail
char rand_median(long vect[],long dim){

#ifdef FAST_MEDIAN
float powSampl=pow(dim,2.0/4.0);
long nSampl=powSampl;
float radDim=pow(dim,0.25);
#else
float powSampl=pow(dim,3.0/4.0);
long nSampl=powSampl;
float radDim=pow(dim,0.5);
#endif




//for(int i=0;i<dim;i++)printf("%ld\n",vect[i]);

for(int i=0;i<nSampl;i++)vectAus[i]=vect[RAND()%dim];

//for(int i=0;i<nSampl;i++)printf("us %ld\n",samplVect[i]);
std::sort(vectAus,vectAus+nSampl);

//for(int i=0;i<nSampl;i++)printf("s %ld\n",samplVect[i]);
long d=vectAus[(int)(powSampl/2-radDim)];
long u=vectAus[(int)(powSampl/2+radDim)];

long l_d=0,l_u=0,dim_C=0;

//I reuse the same auxiliary vector for C

for(int i=0;i<dim;i++){
	/*if(vect[i]<d)l_d++;
	if(vect[i]>u)l_u++;
	if((unsigned(vect[i]-d)<=unsigned(u-d)))destVect[dim_C++]=vect[i];*/
	if(vect[i]<d)l_d++;
	else if(vect[i]>u)l_u++;
	else	vectAus[dim_C++]=vect[i];
	/*l_d+=(vect[i]<d);
	l_u+=(vect[i]>u);
	vectAus[dim_C]=vect[i];
	dim_C+=!(((vect[i]<d))||((vect[i]>u)));*/
}
/*for(int i=0;i<dim;i++){
	if((unsigned(vect[i]-d)<=unsigned(u-d)))destVect[dim_C++]=vect[i];
}*/

if(l_d>=dim/2 || l_u>=dim/2){
	printf("problem in choose of d=%ld or u=%ld (l_d=%ld l_u=%ld\n",d,u,l_d,l_u);
	return 0;
}

std::sort(vectAus,vectAus+dim_C);
printf("the median is %ld\n",vectAus[dim/2-l_d-1]);

return 1;

}
