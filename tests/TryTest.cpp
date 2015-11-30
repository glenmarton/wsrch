extern "C"
{
#include "direction.h"
#include "wstable.h"
#include "Seq.h"
#include "try.h"
#include "trymock.h"
#include "verbose.h"
#include "wstablefill.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Try)
{
	wstable_t puzzle;
    void setup()
    {
		//verbose_set( TRY | GO );
		puzzle = wstable_createEmpty();
		wstablefill( puzzle );
		try_create( puzzle );
		UT_PTR_SET( try_this_directionFp, try_this_directionMock );
    }

    void teardown()
    {
		wstable_destroy( &puzzle );
		try_destroy();
    }
};

TEST(Try, ThisDirection)
{
	const char* north = "north";
	point_t start = point_new( 0, 0 );

	try_this_directionFp = try_this_directionImpl;

	CHECK_TRUE( try_this_direction( north, start, EAST ));

	point_destroy( &start );
	try_free_answers();
}

TEST(Try, ThisDirectionFails)
{
	const char* search = "bungo";
	point_t start = point_new( 0, 0 );

	try_this_directionFp = try_this_directionImpl;

	CHECK_FALSE( try_this_direction( search, start, EAST ));

	point_destroy( &start );
	try_free_answers();
}
