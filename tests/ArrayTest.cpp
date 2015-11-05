extern "C"
{
#include "Array.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Array)
{
	Array_T ary;
    void setup()
    {
		ary = Array_new(5, 4);
    }

    void teardown()
    {
		Array_free(&ary);
    }
};

TEST(Array, Create)
{
	size_t length = 5;
	size_t size = 4;
	CHECK (ary != NULL);
	CHECK (length == Array_length(ary));
	CHECK (size == Array_size(ary));
}

TEST(Array, Free)
{
	Array_T a = Array_new(3, 2);
	Array_free (&a);
	CHECK (NULL == a);
}

TEST(Array, GetNothing)
{
	char *expected = NULL;
	char *actual = (char*)Array_get(ary, 0);

	CHECK (expected != actual);
}

TEST(Array, Put)
{
	char expect[] = "one";
	char *actual;

	Array_put(ary, 0, (void*)expect);
	actual = (char*)Array_get(ary, 0);

	STRCMP_EQUAL (expect, actual);
}

TEST(Array, PutInt)
{
	unsigned int expect[] = {7, 25};

	Array_T a1 = Array_new(sizeof( expect )/sizeof( unsigned int ),
			sizeof( unsigned int ));
	Array_put( a1, 0, &expect[0]);
	Array_put( a1, 1, &expect[1]);

	CHECK_TRUE( expect[0] == *(unsigned short*)Array_get( a1, 0 ));
	CHECK_TRUE( expect[1] == *(unsigned short*)Array_get( a1, 1 ));

	Array_free( &a1 );
}

TEST(Array, Length)
{
	size_t num_of_elements_array_can_hold = 5;
	size_t len = Array_length(ary);

	CHECK (num_of_elements_array_can_hold == len);
}

TEST(Array, Size)
{
	size_t how_many_bytes_in_one_element = 4;
	size_t size = Array_size(ary);

	CHECK (how_many_bytes_in_one_element == size);
}

TEST(Array, Resize)
{
	size_t expect = 10;
	size_t actual;

	Array_resize(ary, expect);
	actual = Array_length(ary);

	CHECK (expect == actual);
}

TEST(Array, Copy)
{
	char expect[] = "one";
	char *actual = NULL;
	Array_T b = NULL;

	Array_put(ary, 0, (void*)expect);
	b = Array_copy(ary, 2);
	actual = (char*)Array_get(b, 0);

	STRCMP_EQUAL (expect, actual);

	Array_free(&b);
}
