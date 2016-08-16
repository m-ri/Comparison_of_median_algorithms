


#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
//#define MAX 64000001

using namespace std;

extern long vect[];

extern long vectAus[];
long offLevel[100];
//long padding[]={LONG_MAX,LONG_MIN,LONG_MAX,LONG_MIN,LONG_MAX};

void prepareOffLevel(int dim){
offLevel[0]=0;
int off=0;
int i;
for(i=1,dim/=4;dim>0;i++,dim/=4){
	off+=(dim+4);
	offLevel[i]=off;
}
offLevel[i]=off+4;

}

//http://stackoverflow.com/questions/480960/code-to-calculate-median-of-five-in-c-sharp/6984153#6984153
//with no branch,I don't have misprediction branch
inline long getMedians3(long a,long b,long c){
	return max(min(a,b),min(c,max(a,b))); 
}
inline long getMedians5(long a,long b,long c,long d,long e){
	long f=max(min(a,b),min(c,d)); // discards lowest from first 4
  long g=min(max(a,b),max(c,d)); // discards biggest from first 4
  return getMedians3(e,f,g);
}
inline long getMedians4(long a,long b,long c,long d){//Is it correct?!?
	return min(max(a,b),max(b,c));
}
long getMedians(long /*__restrict__*/ from[],int dim,long /*__restrict__*/ to[],int level){

int i,j;
if(dim==1)return from[0];
int newDim=dim/5;
for(i=0;i<newDim;i++){
	to[i]=getMedians5(from[i*5],from[i*5+1],from[i*5+2],from[i*5+3],from[i*5+4]);
}

int rest=dim-((newDim)*5);
if(rest>0){
	if(rest==1)to[newDim]=from[newDim*5];
	else if(rest==2)to[newDim]=from[newDim*5+RAND()%2];//min(from[newDim*5],from[newDim*5+1]);/*It's not wrong..without it,I'll have problem when no element(in a set of 2) are < pivot,because the recursion will never stop*/
	else if(rest==3)to[newDim]=getMedians3(from[newDim*5],from[newDim*5+1],from[newDim*5+2]);
	else to[newDim]=getMedians4(from[newDim*5],from[newDim*5+1],from[newDim*5+2],from[newDim*5+3]);
	newDim++;
	/*for(j=0;j<rest;j++)
		from[newDim*5]=padding[j];*/

}
level++;
return getMedians(to,newDim,vectAus+offLevel[level],level);
}



long median_medians(long dim,long pos){
/*static char prepared=0;
if(!prepared){prepareOffLevel(MAX);prepared=1;for(int j=0;j<30;j++)printf("%d\n",offLevel[j]);}*/
long pivot=getMedians(vect,dim,vectAus,0);;
//if(dim==2)printf("%ld %ld %ld %ld %ld\n",vect[0],vect[1],pivot,dim,pos);
//if(dim==1)return vect[0];

//printf("%d %d %d\n",pivot,dim,pos);

long contLess=0;
for(long i=0;i<dim;i++){//careful to branch prediction
	//contLess+=(vect[i]<pivot);
	//contLess+=(vect[i]-pivot)>>63;problemi
	if(vect[i]<pivot)contLess++;
}
if(contLess== (pos))return pivot;
else if(contLess >pos){
	long so=0,de=0;
	for(so=0;so<dim;so++){
		vect[de]=vect[so];
		de+=(vect[so]<pivot);
		//if(vect[so]<pivot)vect[de++]=vect[so];
	}
	return median_medians(de,pos);

}else{
	long so=0,de=0;
	for(so=0;so<dim;so++){
		vect[de]=vect[so];
		de+=(vect[so]>=pivot);
	//if(vect[so]>=pivot)vect[de++]=vect[so];
	}
	return median_medians(de,pos-contLess);


}


}
/*DEAD CODE
1) use 3 comparisons to arrange elements in array such that a[1]<a[2] , a[4]<a[5] and a[1]<a[4]
a) compare a[1] and a[2] and swap if necessary
b) compare a[4] and a[5] and swap if necessary 
c) compare a[1] and a[4].if a[4] is smaller than a[1] , then swap a[1] wid a[4] and a[2] wid a[5]
2)if a[3]>a[2].if a[2]<a[4] median value = min(a[3],a[4]) else median value=min(a[2],a[5]) 
3)if a[3]<a[2].if a[3]>a[4] median value = min(a[3],a[5]) else median value=min(a[2],a[4]) */

/*long getMedian5_modif(long[] arr){//find median between five el..it modify order!!
	
if(arr[0]>arr[1])swap(arr[0],arr[1]);
if(arr[3]>arr[4])swap(arr[4],arr[5]);
if(arr[0]>arr[3]){swap(arr[0],arr[3]);swap(arr[1],arr[4]);}
if(arr[2]>arr[1])
	if(arr[2]>arr[3])return min(arr[2],arr[4]);
	else return min(a[1],a[4]);
if(a[2]<a[1])
	if(arr[2]>arr[3])return min(arr[2],arr[4]);
	else return min(arr[1],arr[3]);
printf("problema getMedian5_modif!!\n");
return -1;
}*/
