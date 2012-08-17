//#include<iostream>
//#include<list>
//#include<algorithm>
//using namespace std ;

//typedef struct {
//	char c ;
//	int i ;
//}NODE, *PNODE ;

//void PrtLst( NODE &nod ) ;

//bool operator==( const NODE &nod1, const NODE &nod2 ) 
//{
//	return nod1.c==nod2.c && nod1.i==nod2.i ;
//}

//int main()
//{
//	list<NODE> lst ;
//	list<NODE>::iterator ite ;
//	int i ;
//	PNODE pTemp ;
//	for( i=1; i<=10; i++ )
//	{
//		 pTemp = new NODE ;
//		 pTemp->c = 'a' + i -1 ;
//		 pTemp->i = i ;
//		 //lst.emplace_back( move(*pTemp) ) ;
//		 lst.push_back( *pTemp ) ;
//	}
//	for_each( lst.begin(), lst.end(), PrtLst ) ;
//	NODE nod ;
//	nod.c = 'c' ;		nod.i = 3 ;
//	lst.remove( nod ) ;
//	for_each( lst.begin(), lst.end(), PrtLst ) ;
//	system( "pause" ) ;
//	return 0 ;
//}

//void PrtLst( NODE &nod )
//{
//	cout<<nod.c<<" "<<nod.i<<endl ;
//}
