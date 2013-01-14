#include <cstdio>
#include <ctime>
#include <cstdlib>
void shu( int wD[][ 13 ] );
void dl( const int wD[][ 13 ], const char *wFace[],
		  const char *wS[], int D5[5][2] );

int main()
{
	const char *su[ 4 ] = { "Hs", "Ds", "Cs", "Ss" };

	const char *fa[ 13 ] = 
	{ "A", "D", "T", "Fo", 
	"Fi", "Si", "Se", "E",
	"N", "Tn", "J", "Q", "K" };

	int d[ 4 ][ 13 ] = { 0 };
	int D[5][2];	
	srand( time( 0 ) ); 

	shu( d );
	dl( d, fa, su, D);
	

	//getchar();
	//getchar();

	return 0; 

} 

/* shu  in d */
void shu( int wD[][ 13 ] )
{
	int rw;    /* rw number */
	int cl; /* cl number */
	int cd;   /* counter */

	for ( cd = 1; cd <= 52; cd++ ) {

		do {
			rw = rand() % 4;
			cl = rand() % 13;
		} while( wD[ rw ][ cl ] != 0 ); /* end do...while */

		wD[ rw ][ cl ] = cd;
	} /* end for */

} /* end function shu */


/* dl  in d */
void dl( const int wD[][ 13 ], const char *wFace[],
		  const char *wS[], int D5[5][2] )
{
	int cd;   /* cd counter */
	int rw;    /* rw counter */
	int cl; /* cl counter */	

	for ( cd = 1; cd <= 5; cd++ ) {
		for ( rw = 0; rw <= 3; rw++ ) {
			for ( cl = 0; cl <= 12; cl++ ) {
				if ( wD[ rw ][ cl ] == cd ) {
					printf( "%5s of %-8s\r\n", wFace[ cl ], wS[ rw ]); 
					D5[cd-1][0]= cl;
					D5[cd-1][1]= rw ;
				} /* end if */
			} /* end for */
		} /* end for */
	} /* end for */
}/* end function dl */
