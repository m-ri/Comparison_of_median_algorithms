//NOT now used,I've tried multiple dinamic allocation

#include <vector>
#include <algorithm>
#include "myRandom.cpp"

using namespace std;

long quick_select_my(vector<long> vect,long pos){
long pivot=vect[RAND()%vect.size()];

//if(dim==1)return vect[0];

//printf("%d %d %d\n",pivot,dim,pos);

long contLess=0;
for(long i=0;i<vect.size();i++){//careful to branch prediction
	contLess+=(vect[i]<pivot);
	//contLess+=(vect[i]-pivot)>>63;problemi
	//if(vect[i]<pivot)contLess++;
}
vector<long> newVect;
if(contLess== (pos))return pivot;
else if(contLess >pos){
	long so=0,de=0;
	for(so=0;so<vect.size();so++)
		if(vect[so]<pivot)newVect.push_back(vect[so]);
	return quick_select_my(newVect,pos);

}else{
	long so=0,de=0;
	for(so=0;so<vect.size();so++)
		if(vect[so]>=pivot)newVect.push_back(vect[so]);
	return quick_select_my(newVect,pos-contLess);


}


}
