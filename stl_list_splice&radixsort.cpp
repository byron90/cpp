#include<iostream>
#include<list>
#include<algorithm>
using namespace std ;

#define NUM 30
typedef struct {
	char cKey1 ;
	char cKey2 ;
}NODE, *PNODE ;

void print( const NODE &nod )
{
	cout<<nod.cKey1<<" "<<nod.cKey2<<endl ;
}

int main()
{
	list<NODE> lstOri ;
	list<NODE>::iterator ite ;
	NODE nTemp ;
	int i, j ;
	//generate data
	for( j=1; j<=NUM/5; j++ )
		for( i=1; i<=5; i++ )
		{
			nTemp.cKey1 = 'a' + NUM/5 - j ;
			nTemp.cKey2 = 'a' + i - 1 ;
			lstOri.push_back( nTemp ) ;
		}
	//before sort
	for_each( lstOri.begin(), lstOri.end(), print ) ;

	cout<<endl ;

	int iArrange = NUM/5 > 5 ? NUM/5 : 5 ;
	list<NODE> *plstTemp = new list<NODE>[iArrange] ;
	for( i=0; i<iArrange; i++ )
		plstTemp[i].push_back(nTemp) ;

	list<NODE>::iterator iteObject ;
	int iArraNum ;
	//with key2
	while( lstOri.size()!=0 )
	{
		ite = lstOri.begin() ;
		iArraNum = ite->cKey2 - 'a' ;
		iteObject = plstTemp[iArraNum].end() ;
		iteObject-- ;
		plstTemp[iArraNum].splice( iteObject, lstOri, ite ) ;
	}
	for( i=iArrange-1; i>=0; i-- )
		lstOri.splice( lstOri.begin(), plstTemp[i], plstTemp[i].begin(), --(plstTemp[i].end()) ) ;

	for_each( lstOri.begin(), lstOri.end(), print ) ;
	cout<<endl ;
	//with key1
	while( lstOri.size()!=0 )
	{
		ite = lstOri.begin() ;
		iArraNum = ite->cKey1 - 'a' ;
		iteObject = plstTemp[iArraNum].end() ;
		iteObject-- ;
		plstTemp[iArraNum].splice( iteObject, lstOri, ite ) ;
	}
	for( i=iArrange-1; i>=0; i-- )
		lstOri.splice( lstOri.begin(), plstTemp[i], plstTemp[i].begin(), --(plstTemp[i].end()) ) ;

	for_each( lstOri.begin(), lstOri.end(), print ) ;

	system( "pause" ) ;
	return 0 ;
}

