#include<stdio.h>
#include<stdlib.h>
#include <algorithm>
#include <vector>
#include "quick_select_my.cpp"
#include "myRandom.cpp"
#include "median_of_medians.cpp"
#include "rand_median.cpp"

#include <time.h>

 clock_t start, end;
 double cpu_time_used;

#define YES_COPY
 

#define MAX 64000005

using namespace std;

long vect[MAX],vectAus[MAX];//,vectCopy[MAX];
#ifdef YES_COPY
long vectCopy[MAX];
#endif

long quick_select(long dim,long pos){
long pivot=vect[RAND()%dim];

//if(dim==1)return vect[0];

//printf("%d %d %d\n",pivot,dim,pos);

long contLess=0;
for(long i=0;i<dim;i++){//careful to branch prediction
	contLess+=(vect[i]<pivot);
	//contLess+=(vect[i]-pivot)>>63;problemi
	//if(vect[i]<pivot)contLess++;
}
if(contLess== (pos))return pivot;
else if(contLess >pos){
	long so=0,de=0;
	for(so=0;so<dim;so++){
		vect[de]=vect[so];
		de+=(vect[so]<pivot);
		//if(vect[so]<pivot)vect[de++]=vect[so];
	}
	return quick_select(de,pos);

}else{
	long so=0,de=0;
	for(so=0;so<dim;so++){
		vect[de]=vect[so];
		de+=(vect[so]>=pivot);
	//if(vect[so]>=pivot)vect[de++]=vect[so];
	}
	return quick_select(de,pos-contLess);


}


}

long quick_select_swap(long* __restrict__ orig,long* __restrict__ aus,long dim,long pos){
long pivot=orig[RAND()%dim];

//if(dim==1)return vect[0];

//printf("%d %d %d\n",pivot,dim,pos);

long contLess=0;
for(long i=0;i<dim;i++){//careful to branch prediction
	contLess+=(orig[i]<pivot);
	//contLess+=(vect[i]-pivot)>>63;problemi
	//if(vect[i]<pivot)contLess++;
}
if(contLess== (pos))return pivot;
else if(contLess >pos){
	long so=0,de=0;
	for(so=0;so<dim;so++){
		aus[de]=orig[so];
		de+=(orig[so]<pivot);
		//if(vect[so]<pivot)vect[de++]=vect[so];
	}
	return quick_select_swap(aus,orig,de,pos);

}else{
	long so=0,de=0;
	for(so=0;so<dim;so++){
		aus[de]=orig[so];
		de+=(orig[so]>=pivot);
	//if(vect[so]>=pivot)vect[de++]=vect[so];
	}
	return quick_select_swap(aus,orig,de,pos-contLess);


}


}


int main(int argc,char* argv[]){

if(argc!=3 && argc!=4){printf("format error!!\nuse nameCommand [size] [type] {r,R}\n\ntype:\n1)quick select C\n2)quick select swap(don't use it)\n3)median of medians\n4)random median\n\n+10 if u want also the true median (e.g. 14)  \n\nr=repeat 20 times\nR=repet 1000 times\n");return 1;}

long dim=atoi(argv[1]);
long typeIn=atoi(argv[2]);

srand(2);
prepareOffLevel(MAX);//the vector could also be computed at compile time

start = clock();

int repeat=1;
if(argc>=4 && argv[3][0]=='r')repeat=20;
if(argc>=4 && argv[3][0]=='R')repeat=1000;

for(int rep=0;rep<repeat;rep++){

for(long i=0;i<dim;i++)vect[i]=RAND();
if(typeIn==11)for(long i=0;i<dim;i++)vectAus[i]=vect[i];//quick select is implemented in a destructive way
else if(typeIn>=10){
#ifdef YES_COPY
for(long i=0;i<dim;i++)vectCopy[i]=vect[i];
#else
printf("true median not enabled\n");
#endif

}
//vector<long> vectSTL(vect,vect+dim);

long type=(typeIn>=10)?(typeIn-10):typeIn;
switch(type){
	case 1:printf("%ld\n", quick_select(dim,(dim-1)/2));break;
	case 2:printf("%ld\n", quick_select_swap(vect,vectAus,dim,(dim-1)/2));break;
	//case 2:printf("l%d\n", quick_select_my(vectSTL,(dim-1)/2));break;
	//case 3:selectionByMedianOfMedians(vectSTL,(dim-1)/2);break;//printf("%d\n", selectionByMedianOfMedians(vectSTL,(dim-1)/2));break;
	case 3:printf("%ld\n",median_medians(dim,(dim-1)/2));break;
	case 4:while(0==rand_median(vect,dim)){};break;
}

if(typeIn>=10 && (typeIn!=11)){
#ifdef YES_COPY
	std::sort(vectCopy,vectCopy+dim);
	printf("The true median is %ld\n",vectCopy[(dim-1)/2]);
#endif
}else if(typeIn==11){
	std::sort(vectAus,vectAus+dim);
	printf("The true median is %ld\n",vectAus[(dim-1)/2]);

}

}//end for

end = clock();
 cpu_time_used = ((double) (end - start)) /(double) CLOCKS_PER_SEC;

printf("CPU time used %.6lf\n",cpu_time_used );

return 0;



}
