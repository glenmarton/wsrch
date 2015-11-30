extern "C"
{
#include "direction.h"
#include "wstable.h"
#include "Seq.h"
#include "try.h"
#include "verbose.h"
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
    }

    void teardown()
    {
		wstable_destroy( &puzzle );
		try_destroy();
    }

	void wstablefill( wstable_t puzzle )
	{
		static const char* line1 = "northsoutheastwest";
		static const char* line2 = "southeastwestnorth";
		static const char* line3 = "eastwestnorthsouth";
		static const char* line4 = "westnorthsoutheast";

		wstable_addLine( puzzle, line1 );
		wstable_addLine( puzzle, line2 );
		wstable_addLine( puzzle, line3 );
		wstable_addLine( puzzle, line4 );
	}
};

TEST(Try, ThisDirection)
{
	const char* north = "north";
	point_t start = point_new( 0, 0 );

	CHECK_TRUE( try_this_direction( north, start, EAST ));

	point_destroy( &start );
	try_free_answers();
}

TEST(Try, ThisDirectionFails)
{
	const char* search = "bungo";
	point_t start = point_new( 0, 0 );

	CHECK_FALSE( try_this_direction( search, start, EAST ));

	point_destroy( &start );
	try_free_answers();
}
