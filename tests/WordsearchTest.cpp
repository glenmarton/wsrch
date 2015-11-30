#include <iostream>
using namespace std;

extern "C"
{
#include <stdio.h>
#include "Seq.h"
#include "solution.h"
#include "wstable.h"
#include "wordsearch.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Wordsearch)
{
	const char *infn;
	wstable_t puzzle;

    void setup()
    {
		static const char infname[] = "./tests/input.txt";
		infn = infname;

		puzzle = wordsearch_create( infn );
    }
    void teardown()
    {
		wstable_destroy( &puzzle );
    }
};

TEST(Wordsearch, Create)
{
	LONGS_EQUAL( 19, wstable_getHeight( puzzle ));

	LONGS_EQUAL( 16, wstable_getWidth(  puzzle ));

	const char* actual = wstable_getLine( puzzle, 0 );
	const char* expect = "hsstjasdfewotdpe";
	STRCMP_EQUAL( expect, actual );
}

TEST(Wordsearch, Load)
{

	LONGS_EQUAL( 19, wordsearch_getHeight());
	LONGS_EQUAL( 16, wordsearch_getWidth() );
	STRCMP_EQUAL( infn, wordsearch_getFilename() );

	const char* actual = wordsearch_getLine( 0 );
	const char* expect = "hsstjasdfewotdpe";
	STRCMP_EQUAL( expect, actual );
}

