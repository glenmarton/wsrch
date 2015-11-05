#include "CppUTest/TestHarness.h"
#include "wsrch2BuildTime.h"

TEST_GROUP(wsrch2BuildTime)
{
  wsrch2BuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new wsrch2BuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(wsrch2BuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

