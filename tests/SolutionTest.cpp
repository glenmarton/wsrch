extern "C"
{
#include "direction.h"
#include "point.h"
#include "solution.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Solution)
{
	solution_t solution;

    void setup()
    {
      solution = solution_create();
    }

    void teardown()
    {
       solution_destroy( &solution );
    }
};

TEST(Solution, Create)
{
	CHECK_TRUE( solution != NULL );
}

TEST(Solution, Destroy)
{
	solution_t s = solution_create();
	solution_destroy( &s );

	CHECK_TRUE( s == NULL );
}

TEST(Solution, Word)
{
	char* expect = (char*)"bungo";

	solution_setWord( solution, expect );

	char* actual = solution_getWord( solution );

	STRCMP_EQUAL( expect, actual );
}

TEST(Solution, Point)
{
	point_t expect = point_new( 4, 5 );

	solution_setPoint( solution, expect );

	point_t actual = solution_getPoint( solution );

	LONGS_EQUAL( expect->row, actual->row );
	LONGS_EQUAL( expect->col, actual->col );

	point_destroy( &expect );
}

TEST(Solution, Direction)
{
	direction_t expect = NORTH_WEST;

	solution_setDirection( solution, expect );
	direction_t actual = solution_getDirection( solution );

	LONGS_EQUAL( NORTH_WEST, actual );
}

TEST(Solution, Init)
{
	char* expectW = (char*)"north";
	direction_t expectD = NORTH;
	point_t expectP = point_new( 4, 5 );

	solution_destroy( &solution );

	solution = solution_init( expectW, expectP, expectD );

	STRCMP_EQUAL( expectW, solution_getWord( solution ));
	LONGS_EQUAL( expectD, solution_getDirection( solution ));


	point_t actualP = solution_getPoint( solution );

	LONGS_EQUAL( expectP->row, actualP->row );
	LONGS_EQUAL( expectP->col, actualP->col );

	point_destroy( &expectP );
}
