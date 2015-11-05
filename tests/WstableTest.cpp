#include <iostream>
using namespace std;

extern "C"
{
#include "direction.h"
#include "point.h"
#include "Seq.h"
#include "solution.h"
#include "verbose.h"
#include "wstable.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Wstable)
{
    void setup()
    {
		//verbose_set( CONSTRUCTOR_DESTRUCTOR | GET_SET );
      wstable_create( "./tests/input.txt" );
    }

    void teardown()
    {
       wstable_destroy();
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

TEST(Wstable, Create)
{
	const char* expect = "./tests/input.txt";
	char* actual = wstable_getFilename();

	STRCMP_EQUAL( expect, actual );
}

TEST(Wstable, Read)
{
	size_t expect_height = 19;
	size_t expect_width = 17;

	wstable_read();

	LONGS_EQUAL( expect_height, wstable_getHeight() );
	LONGS_EQUAL( expect_width, wstable_getWidth() );
}

TEST(Wstable, At)
{
	size_t col = 1;
	size_t row = 2;
	char expect = 'u';

	wstable_read();

	char actual = wstable_at( row, col );

	BYTES_EQUAL( expect, actual );
}

TEST(Wstable, Line)
{
	size_t row = 5;
	const char* expect = "norththhasdcaeom\n";

	wstable_read();

	char* actual = wstable_getLine( row );

	STRCMP_EQUAL( expect, actual );
}

TEST(Wstable, AtPoint)
{
	point_t p = point_new( 2, 3 );
	int expect = 'd';

	wstable_read();

	int actual = wstable_atPoint( p );

	LONGS_EQUAL( expect, actual );
	point_destroy( &p );
}

TEST(Wstable, HasWordNorth)
{
	const char *input = "north";

	wstable_read();

	Seq_T answer = Seq_new( 5 );

	CHECK_TRUE( wstable_findWord( input, answer ));
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

TEST(Wstable, HasWordSouth)
{
	const char* input = "south";
	size_t n = 0;

	wstable_read();

	Seq_T answer = Seq_new( 8 );

	CHECK_TRUE( wstable_findWord( input, answer ));
	LONGS_EQUAL( 6, Seq_length( answer ));

	check_solution( 0, 1, SOUTH, Seq_get( answer, n++ ));
	check_solution( 0, 2, SOUTH_EAST, Seq_get( answer, n++ ));
	check_solution( 2, 11, EAST, Seq_get( answer, n++ ));
	check_solution( 5, 14, NORTH, Seq_get( answer, n++ ));
	check_solution( 6, 13, SOUTH, Seq_get( answer, n++ ));
	check_solution( 9, 10, SOUTH_WEST, Seq_get( answer, n++ ));

	free_answers( answer );
	Seq_free( &answer );
}
