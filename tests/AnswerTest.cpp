extern "C"
{
#include "answer.h"
#include "verbose.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Answer)
{
	Seq_T answer;

    void setup()
    {
		//verbose_set( CONSTRUCTOR_DESTRUCTOR );
		answer = answer_create();

    }

    void teardown()
    {
       answer_destroy( &answer );
    }
};

TEST(Answer, Create)
{
	CHECK_FALSE( NULL == answer );
	LONGS_EQUAL( 0, answer_count( answer ));
}

TEST(Answer, Destroy)
{
	answer_destroy( &answer );

	CHECK_TRUE( NULL == answer );

	answer = answer_create();
}

TEST(Answer, Add)
{
	solution_t expect = solution_create();

	answer_add( answer, expect );

	solution_t actual = answer_get( answer, 0 );
	POINTERS_EQUAL( expect, actual );
	LONGS_EQUAL( 1, answer_count( answer ));

	actual = answer_remove( answer );
	POINTERS_EQUAL( expect, actual );
	LONGS_EQUAL( 0, answer_count( answer ));

	solution_destroy( &expect );
}

