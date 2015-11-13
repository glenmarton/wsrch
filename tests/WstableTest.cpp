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
	wstable_t puzzle;

    void setup()
    {
		//verbose_set( CONSTRUCTOR_DESTRUCTOR | GET_SET );
		puzzle = wstable_create();
		fill_wstable( puzzle );
    }

    void teardown()
    {
		wstable_destroy( &puzzle );
    }

	void fill_wstable( wstable_t puzzle )
	{
		const char* line1 = "northsoutheastwest";
		const char* line2 = "southeastwestnorth";
		const char* line3 = "eastwestnorthsouth";

		wstable_addLine( puzzle, line1 );
		wstable_addLine( puzzle, line2 );
		wstable_addLine( puzzle, line3 );
	}

};

TEST(Wstable, Create)
{
	CHECK( puzzle != NULL );
}

TEST(Wstable, At)
{
	size_t col = 1;
	size_t row = 2;
	char expect = 'u';

	char actual = wstable_at( puzzle, row, col );

	BYTES_EQUAL( expect, actual );
}

TEST(Wstable, Line)
{
	size_t row = 5;
	const char* expect = "norththhasdcaeom\n";

	char* actual = wstable_getLine( puzzle, row );

	STRCMP_EQUAL( expect, actual );
}

TEST(Wstable, AtPoint)
{
	point_t p = point_new( 2, 3 );
	int expect = 'd';

	int actual = wstable_atPoint( puzzle, p );

	LONGS_EQUAL( expect, actual );
	point_destroy( &p );
}

