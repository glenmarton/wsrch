#include "direction.h"

const char* direction_tostring( direction_t d )
{
	static const char table[9][13] = { "no direction",
		"north", "north east", "east", "south east",
		"south", "south west", "west", "north west"};

	if (d < NONE || d > NORTH_WEST) {
		d = NONE;
	}

	return table[ d ];
}
