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
      wstable_init( "./tests/input.txt" );
    }

    void teardown()
    {
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

