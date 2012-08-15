#include <iostream.h>
#include <stdlib.h>
#include <time.h>

#define NUM 25

void sort( int j, int *piArray, int n )  ;

int main()
{
	int *piArray = new int[NUM+1] ;
	srand( time(NULL) ) ;
	for( int i=1; i<=NUM; i++ )
	{
		piArray[i] = rand() % 100 ;
		cout<<piArray[i]<<" " ;
	}
	cout<<endl ;

	//构建堆
	i = NUM / 2 ;	
	for( ; i>0; i-- )  sort( i, piArray, NUM ) ;

	//对剩余的NUM-1个数进行堆排序
	int n = NUM ;
	for( i=1; i<=NUM-1; i++ )
	{
		//大值放在末尾
		int iTemp = piArray[n] ;
		piArray[n] = piArray[1] ; 
		piArray[1] = iTemp ;
		n-- ;
		sort( 1, piArray, n ) ;
	}

	for( i=1; i<=NUM; i++ )
		cout<<piArray[i]<<" " ;
	cout<<endl ;
	return 0 ;
}

//一次筛选
void sort( int j, int *piArray, int n ) 
{
	while( 2*j<=n )
	{
		int iPos = 2 * j ;
		if( iPos+1<=n && piArray[iPos+1]>piArray[2*j] )	iPos += 1 ;
		if( piArray[iPos]<piArray[j] )	break ;
		int iTemp = piArray[j] ;
		piArray[j] = piArray[iPos] ;
		piArray[iPos] = iTemp ;
		j = iPos ;
	}
}