#ifndef __DIRECTION_H__
#define __DIRECTION_H__
typedef enum directions { NONE,
	NORTH, NORTH_EAST, EAST, SOUTH_EAST,
	SOUTH, SOUTH_WEST, WEST, NORTH_WEST
} direction_t;

/* Global count: 1 */
const char* direction_tostring( direction_t d );

#endif /* __DIRECTION_H__ */
