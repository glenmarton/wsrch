extern "C"
{
#include <stdio.h>
#include "direction.h"
#include "wstable.h"
#include "Seq.h"
#include "run.h"
#include "solution.h"
#include "verbose.h"
#include "wordsearch.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Run)
{
	wstable_t puzzle;
    void setup()
    {
		//verbose_set( TRY );
		const char *fname = "./tests/input.txt";

		puzzle = wordsearch_create( fname );
    }

    void teardown()
    {
		wstable_destroy( &puzzle );
    }
	bool check_solution( int row, int col, int direction, void* vp )
	{
		solution_t s = (solution_t)vp;
		point_t p = solution_getPoint( s );

		return (( row == p->row ) &&
				( col == p->col ) &&
				( direction == solution_getDirection( s )));
	}
	void free_answers( Seq_T seq )
	{
		size_t stop = Seq_length( seq );
		size_t i = 0;

		while (i < stop) {
			solution_t s = (solution_t)Seq_remhi( seq );
			solution_destroy( &s );
			i++;
		}
	}


};

TEST(Run, FindWordNorth)
{
	const char *input = "north";

	Seq_T answer = run_findWord( puzzle, input );

	CHECK_FALSE( NULL == answer );
	LONGS_EQUAL( 10, Seq_length( answer ));

	CHECK_TRUE( check_solution( 3, 12, NORTH, Seq_get( answer, 0 )));
	CHECK_TRUE( check_solution( 4, 0,  EAST, Seq_get( answer, 1 )));
	CHECK_TRUE( check_solution( 4, 0, NORTH, Seq_get( answer, 2 )));
	CHECK_TRUE( check_solution( 8, 11, NORTH_WEST, Seq_get( answer, 3 )));
	CHECK_TRUE( check_solution( 9, 12, NORTH, Seq_get( answer, 4 )));
	CHECK_TRUE( check_solution( 14, 0, SOUTH, Seq_get( answer, 5 )));
	CHECK_TRUE( check_solution( 17, 3, NORTH_EAST, Seq_get( answer, 6 )));
	CHECK_TRUE( check_solution( 17, 12, NORTH, Seq_get( answer, 7 )));
	CHECK_TRUE( check_solution( 18, 1, EAST, Seq_get( answer, 8 )));
	CHECK_TRUE( check_solution( 18, 10, WEST, Seq_get( answer, 9 )));

	free_answers( answer );
	Seq_free( &answer );
}

TEST(Run, FindWordSouth)
{
	const char* input = "south";
	size_t n = 0;

	Seq_T answer = run_findWord( puzzle, input );
	CHECK_TRUE( answer != NULL );
	LONGS_EQUAL( 6, Seq_length( answer ));

	CHECK_TRUE( check_solution( 0, 1, SOUTH, Seq_get( answer, n++ )));
	CHECK_TRUE( check_solution( 0, 2, SOUTH_EAST, Seq_get( answer, n++ )));
	CHECK_TRUE( check_solution( 2, 11, EAST, Seq_get( answer, n++ )));
	CHECK_TRUE( check_solution( 5, 14, NORTH, Seq_get( answer, n++ )));
	CHECK_TRUE( check_solution( 6, 13, SOUTH, Seq_get( answer, n++ )));
	CHECK_TRUE( check_solution( 9, 10, SOUTH_WEST, Seq_get( answer, n++ )));

	free_answers( answer );
	Seq_free( &answer );
}
