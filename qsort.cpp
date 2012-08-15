#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//一次快速排序
int partition( int * array, int low, int high )
{
	array[0] = array[low] ;
	while( low<high )
	{
		while( high>low && array[high]>=array[0] ) high-- ;
		if( high>low ) array[low] = array[high] ;
		while( high>low && array[low]<array[0] ) low++ ;
		if( high>low ) array[high] = array[low] ;
	}
	array[low] = array[0] ;  //////////////////////////////////////////////////////////////////////////
	return low ;
}

//完整的快速排序
void qsort( int *array, int low, int high )
{
	int mid = partition( array, low, high ) ;
	if( mid-1>0 && low<mid-1 )
		qsort( array, low, mid-1 ) ;
	if( mid+1<high ) 
		qsort( array, mid+1, high ) ;
}

int main()
{
	int ia[11] ;
	ia[0] = 0 ;
	srand( (unsigned)time(NULL) ) ;
	for( int i=1; i<11; i++ )
	{
		ia[i] = rand() ;
		cout<<ia[i]<<" " ;
	}
	cout<<endl ;
	qsort( ia, 1, 10 ) ;
	for( i=1; i<11; i++ )
		cout<<ia[i]<<" " ;
	cout<<endl ;
	
	return 0 ;
}