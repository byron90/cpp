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

	//������
	i = NUM / 2 ;	
	for( ; i>0; i-- )  sort( i, piArray, NUM ) ;

	//��ʣ���NUM-1�������ж�����
	int n = NUM ;
	for( i=1; i<=NUM-1; i++ )
	{
		//��ֵ����ĩβ
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

//һ��ɸѡ
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