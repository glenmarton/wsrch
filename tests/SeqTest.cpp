#include <iostream>
using namespace std;
extern "C"
{
#include "Seq.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Seq)
{
	Seq_T seq;
    void setup()
    {
		seq = Seq_new(5);
    }

    void teardown()
    {
		Seq_free(&seq);
    }
};

TEST(Seq, CreateSeq_withOneEntry)
{
	Seq_T b = Seq_seq((void*)"one");
	size_t len;

	CHECK(NULL != b);

	len = Seq_length(b);
	CHECK (1 == len);

	Seq_free (&b);
}

TEST(Seq, CreateSeq_withMultipleEntries)
{
	Seq_T b = Seq_seq((void*)"one", (void*)"two", NULL );
	size_t len;

	CHECK(NULL != b);

	len = Seq_length(b);
	CHECK (2 == len);

	Seq_free (&b);
}

TEST(Seq, Free)
{
	Seq_T s = Seq_new(6);
	Seq_free (&s);

	CHECK (NULL == s);
}

TEST(Seq, Length)
{
	Seq_addhi(seq, (void*)1);
	Seq_addhi(seq, (void*)2);
	Seq_addhi(seq, (void*)3);

	size_t len = Seq_length(seq);

	CHECK (3 == len);
}

TEST(Seq, Get)
{
	Seq_addhi(seq, (void*)1);

	long actual = (long) Seq_get(seq, 0);

	CHECK (1 == actual);
}

TEST(Seq, Put)
{
	long expect = 1;
	long actual;

	Seq_addhi(seq, (void*)expect);
	actual = (long)Seq_put(seq, 0, (void*)17);

	CHECK(expect == actual);
	CHECK(17 == (long)Seq_get(seq, 0));
}

TEST(Seq, RemHi)
{
	Seq_addhi(seq, (void*)15);
	Seq_addhi(seq, (void*)16);
	Seq_addhi(seq, (void*)17);

	CHECK(17 == (long)Seq_remhi(seq));
	CHECK(2 == (long)Seq_length(seq));
}

TEST(Seq, RemLo)
{
	Seq_addhi(seq, (void*)15);
	Seq_addhi(seq, (void*)16);
	Seq_addhi(seq, (void*)17);

	CHECK(15 == (long)Seq_remlo(seq));
	CHECK(2 == (long)Seq_length(seq));
}

TEST(Seq, AddHi)
{
	void* vp = (void*)16;
	Seq_addhi(seq, (void*)15);
	CHECK (vp == Seq_addhi(seq, vp));

	vp = Seq_get(seq, 1);

	CHECK (16 == (long)vp);
	CHECK(2 == (long)Seq_length(seq));
}

TEST(Seq, AddLo)
{
	void* vp = (void*)16;
	Seq_addlo(seq, (void*)15);
	CHECK (vp == Seq_addlo(seq, vp));

	vp = Seq_get(seq, 1);

	CHECK (15 == (long)vp);
	CHECK(2 == (long)Seq_length(seq));
}
//cerr << __FILE__ << ":" << __LINE__ << " - len = " << len << endl;
