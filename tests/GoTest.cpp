#include <iostream>
using namespace std;

extern "C"
{
#include "direction.h"
#include "go.h"
#include "gotest.h"
#include "solution.h"
#include "wstable.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Go)
{
	pointStruct point;
	point_t p;

    void setup()
	{
		int latitude = 2, longitude = 3;
		point.row = latitude;
		point.col = longitude;
		p = &point;

		go_init( 4, 5 );
	}
    void teardown()
    {
       /* do nothing */
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

// North tests:
TEST(Go, North)
{
	CHECK_TRUE( go_north( p ));
	LONGS_EQUAL( 1, p->row );
}
TEST(Go, NorthBeyondTable)
{
	CHECK_TRUE( go_north( p ));
	CHECK_TRUE( go_north( p ));
	CHECK_FALSE( go_north( p ));
	LONGS_EQUAL( 0, p->row );
}

TEST(Go, NorthStartNorthOfTable)
{
	point.row = -1;
	CHECK_FALSE( go_north( p ));
	LONGS_EQUAL( 0, p->row );
}

TEST(Go, NorthStartSouthOfTable)
{
	point.row = 4;
	CHECK_FALSE( go_north( p ));
	LONGS_EQUAL( 3, p->row );
}

TEST(Go, NorthColBeyondTable)
{
	point.col = -1;
	CHECK_FALSE( go_north( p ));
	LONGS_EQUAL( 0, p->col );

	point.col = 5;
	CHECK_FALSE( go_north( p ));
	LONGS_EQUAL( 4, p->col );
}

// South tests:
TEST(Go, South)
{
	CHECK_TRUE( go_south( p ));
	LONGS_EQUAL( 3, p->row );
}

TEST(Go, SouthBeyondTable)
{
	//cerr << __FILE__ << __LINE__ << " - beyond south: (" << p->row << ", " << p->col << ")\n";
	CHECK_TRUE( go_south( p ));
	CHECK_FALSE( go_south( p ));
	LONGS_EQUAL( 3, p->row );
}

TEST(Go, SouthStartSouthOfTable)
{
	point.row = 4;
	CHECK_FALSE( go_south( p ));
	LONGS_EQUAL( 3, p->row );
}

TEST(Go, SouthStartNorthOfTable)
{
	point.row = -1;
	CHECK_FALSE( go_south( p ));
	LONGS_EQUAL( 0, p->row );
}

TEST(Go, SouthColBeyondTable)
{
	point.col = -1;
	CHECK_FALSE( go_south( p ));
	LONGS_EQUAL( 0, p->col );

	point.col = 5;
	CHECK_FALSE( go_south( p ));
	LONGS_EQUAL( 4, p->col );
}

// East tests:
TEST(Go, East)
{
	CHECK_TRUE( go_east( p ));
	LONGS_EQUAL( 4, p->col );
}

TEST(Go, EastBeyondTable)
{
	CHECK_TRUE(  go_east( p ));
	CHECK_TRUE(  go_east( p ));
	CHECK_FALSE( go_east( p ));
	LONGS_EQUAL( 4, p->col );
}

TEST(Go, EastStartEastOfTable)
{
	p->col = 5;
	CHECK_FALSE( go_east( p ));
	LONGS_EQUAL( 4, p->col );
}

TEST(Go, EastStartWestOfTable)
{
	p->col = -1;
	CHECK_FALSE( go_east( p ));
	LONGS_EQUAL( 0, p->col );
}

TEST(Go, EastRowBeyondTable)
{
	point.row = -1;
	CHECK_FALSE( go_east( p ));
	LONGS_EQUAL( 0, p->row );

	point.row = 4;
	CHECK_FALSE( go_east( p ));
	LONGS_EQUAL( 3, p->row );
}

// West tests:
TEST(Go, West)
{
	CHECK_TRUE( go_west( p ));
	LONGS_EQUAL( 2, p->col );
}

TEST(Go, WestBeyondTable)
{
	p->col = 1;
	CHECK_TRUE(  go_west( p ));
	CHECK_FALSE( go_west( p ));
	LONGS_EQUAL( 0, p->col );
}

TEST(Go, WestStartWestOfTable)
{
	p->col = -1;
	CHECK_FALSE( go_west( p ));
	LONGS_EQUAL( 0, p->col );
}

TEST(Go, WestStartWayWestOfTable)
{
	p->col = -15;
	CHECK_FALSE( go_west( p ));
	LONGS_EQUAL( 0, p->col );
}

TEST(Go, WestStartEastOfTable)
{
	p->col = 5;
	CHECK_FALSE( go_west( p ));
	LONGS_EQUAL( 4, p->col );
}

TEST(Go, WestRowBeyondTable)
{
	point.row = -1;
	CHECK_FALSE( go_west( p ));
	LONGS_EQUAL( 0, p->row );

	point.row = 4;
	CHECK_FALSE( go_west( p ));
	LONGS_EQUAL( 3, p->row );
}

TEST(Go, GetFunctionPtr)
{
	POINTERS_EQUAL( go_north, go_getFunctionPtr( NORTH ) );
	POINTERS_EQUAL( go_south, go_getFunctionPtr( SOUTH ) );
	POINTERS_EQUAL( go_east, go_getFunctionPtr( EAST ) );
	POINTERS_EQUAL( go_west, go_getFunctionPtr( WEST ) );
	POINTERS_EQUAL( go_northeast, go_getFunctionPtr( NORTH_EAST ) );
	POINTERS_EQUAL( go_southeast, go_getFunctionPtr( SOUTH_EAST ) );
	POINTERS_EQUAL( go_northwest, go_getFunctionPtr( NORTH_WEST ) );
	POINTERS_EQUAL( go_southwest, go_getFunctionPtr( SOUTH_WEST ) );
	POINTERS_EQUAL( NULL,  go_getFunctionPtr( NONE ) );
	POINTERS_EQUAL( NULL,  go_getFunctionPtr( (direction_t)9 ) );
}

IGNORE_TEST(Go, FindWordNorth)
{
#ifdef NOT_YET	//gmj20151112
	const char *input = "north";

	wstable_init( "./somefilename.txt" );

	Seq_T answer = Seq_new( 5 );

	CHECK_TRUE( go_findWord( input, answer ));
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
#endif /* NOT_YET */
}

TEST(Go, FindWordSouth)
{
#ifdef NOT_YET	//gmj20151112
	const char* input = "south";
	size_t n = 0;

	wstable_read();

	Seq_T answer = Seq_new( 8 );

	CHECK_TRUE( go_findWord( input, answer ));
	LONGS_EQUAL( 6, Seq_length( answer ));

	check_solution( 0, 1, SOUTH, Seq_get( answer, n++ ));
	check_solution( 0, 2, SOUTH_EAST, Seq_get( answer, n++ ));
	check_solution( 2, 11, EAST, Seq_get( answer, n++ ));
	check_solution( 5, 14, NORTH, Seq_get( answer, n++ ));
	check_solution( 6, 13, SOUTH, Seq_get( answer, n++ ));
	check_solution( 9, 10, SOUTH_WEST, Seq_get( answer, n++ ));

	free_answers( answer );
	Seq_free( &answer );
#endif /* NOT_YET */
}
