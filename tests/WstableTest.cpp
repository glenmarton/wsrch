#include <iostream>
using namespace std;

extern "C"
{
#include <stdio.h>
#include "direction.h"
#include "point.h"
#include "Seq.h"
#include "solution.h"
#include "testtable.h"
#include "verbose.h"
#include "wstable.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Wstable)
{
	const char* table[4];
	wstable_t puzzle;

    void setup()
    {
		//verbose_set( CONSTRUCTOR_DESTRUCTOR | GET_SET );
		puzzle = wstable_createEmpty();
		fill_wstable( puzzle );
    }

    void teardown()
    {
		wstable_destroy( &puzzle );
    }

	void fill_wstable( wstable_t puzzle )
	{
		static const char* line1 = "northsoutheastwest";
		static const char* line2 = "southeastwestnorth";
		static const char* line3 = "eastwestnorthsouth";
		static const char* line4 = "westnorthsoutheast";

		wstable_addLine( puzzle, line1 );
		wstable_addLine( puzzle, line2 );
		wstable_addLine( puzzle, line3 );
		wstable_addLine( puzzle, line4 );

		testtable_init();
		testtable_addline(line1 );
		testtable_addline(line2 );
		testtable_addline(line3 );
		testtable_addline(line4 );
	}

};

TEST(Wstable, CreateEmpty)
{
	CHECK( puzzle != NULL );
}

TEST(Wstable, Create)
{
	size_t height = 4;
	size_t width = 18;
	wstable_t actual = wstable_create( height, width, testtable_getline );
	const char* expect = "northsoutheastwest";

	CHECK_TRUE( height == wstable_getHeight( actual ));
	CHECK_TRUE( width == wstable_getWidth( actual ));
	STRCMP_EQUAL( expect, wstable_getLine( actual, 0 ));

	wstable_destroy( &actual );
}

TEST(Wstable, Duplicate)
{
	size_t height = 4;
	size_t width = 18;
	wstable_t actual = wstable_duplicate( puzzle );
	const char* expect = "northsoutheastwest";

	LONGS_EQUAL( height, wstable_getHeight( actual ));
	LONGS_EQUAL( width,  wstable_getWidth(  actual ));
	STRCMP_EQUAL( expect, wstable_getLine( actual, 0 ));

	wstable_destroy( &actual );
}

TEST(Wstable, Height)
{
	size_t expect = 4;
	size_t actual = wstable_getHeight( puzzle );

	LONGS_EQUAL( expect, actual );
}

TEST(Wstable, Width)
{
	size_t expect = 18;
	size_t actual = wstable_getWidth( puzzle );

	LONGS_EQUAL( expect, actual );
}

TEST(Wstable, At)
{
	size_t col = 1;
	size_t row = 2;
	char expect = 'a';

	char actual = wstable_at( puzzle, row, col );

	BYTES_EQUAL( expect, actual );
}

TEST(Wstable, Line)
{
	size_t row = 3;
	const char* expect = "westnorthsoutheast";

	char* actual = wstable_getLine( puzzle, row );

	STRCMP_EQUAL( expect, actual );
}

TEST(Wstable, AtPoint)
{
	point_t p = point_new( 2, 4 );
	int expect = 'w';

	int actual = wstable_atPoint( puzzle, p );

	LONGS_EQUAL( expect, actual );
	point_destroy( &p );
}

