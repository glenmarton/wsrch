#include <iostream>
using namespace std;

extern "C"
{
#include "direction.h"
#include "point.h"
#include "go.h"
#include "Seq.h"
#include "solution.h"
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
