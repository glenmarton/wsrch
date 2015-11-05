extern "C"
{
#include "direction.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Direction)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(Direction, North)
{
	const char* str = "north";

	STRCMP_EQUAL( str, direction_tostring( NORTH ));
}

TEST(Direction, South)
{
	const char* str = "south";

	STRCMP_EQUAL( str, direction_tostring( SOUTH ));
}

TEST(Direction, East)
{
	const char* str = "east";

	STRCMP_EQUAL( str, direction_tostring( EAST ));
}

TEST(Direction, West)
{
	const char* str = "west";

	STRCMP_EQUAL( str, direction_tostring( WEST ));
}

TEST(Direction, NorthEast)
{
	const char* str = "north east";

	STRCMP_EQUAL( str, direction_tostring( NORTH_EAST ));
}

TEST(Direction, NorthWest)
{
	const char* str = "north west";

	STRCMP_EQUAL( str, direction_tostring( NORTH_WEST ));
}

TEST(Direction, SouthEast)
{
	const char* str = "south east";

	STRCMP_EQUAL( str, direction_tostring( SOUTH_EAST ));
}

TEST(Direction, SouthWest)
{
	const char* str = "south west";

	STRCMP_EQUAL( str, direction_tostring( SOUTH_WEST ));
}

TEST(Direction, None)
{
	const char* str = "no direction";

	STRCMP_EQUAL( str, direction_tostring( NONE ));
}

