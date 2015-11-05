#include "direction.h"

const char* direction_tostring( direction_t d )
{
	const char* cp = NULL;

	if (d == NORTH) {
		static const char north[] = "north";
		cp = north;
	} else if (d == NORTH_EAST) {
		static const char direction[] = "north east";
		cp = direction;
	} else if (d == EAST) {
		static const char direction[] = "east";
		cp = direction;
	} else if (d == SOUTH_EAST) {
		static const char direction[] = "south east";
		cp = direction;
	} else if (d == SOUTH) {
		static const char direction[] = "south";
		cp = direction;
	} else if (d == SOUTH_WEST) {
		static const char direction[] = "south west";
		cp = direction;
	} else if (d == WEST) {
		static const char direction[] = "west";
		cp = direction;
	} else if (d == NORTH_WEST) {
		static const char direction[] = "north west";
		cp = direction;
	} else {
		static const char direction[] = "no such direction";
		cp = direction;
	}

	return cp;
}
