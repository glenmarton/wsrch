extern "C"
{
#include "testtable.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Testtable)
{
    void setup()
    {
		testtable_init();
    }

    void teardown()
    {
		testtable_init();
    }
};

TEST(Testtable, Create)
{
	const char* expect = "this is a line of text";
	const char* actual = NULL;

	testtable_addline( expect );

	LONGS_EQUAL( 1, testtable_getHeight() );
	LONGS_EQUAL( 22, testtable_getWidth() );

	actual = testtable_getline( 0 );
	STRCMP_EQUAL( expect, actual );
}

