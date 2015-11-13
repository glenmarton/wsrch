extern "C"
{
#include "wstable.h"
#include "wordsearch.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Wordsearch)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Wordsearch, Load)
{
	const char* input = "./tests/input.txt";
	CHECK_TRUE( wordsearch_load( input ));

	LONGS_EQUAL( 19, wordsearch_getHeight());
	LONGS_EQUAL( 16, wordsearch_getWidth() );
	STRCMP_EQUAL( input, wordsearch_getFilename() );

	/*
	wstable_t puzzle = wordsearch_get();
	CHECK_TRUE( puzzle != NULL );
	*/
}

