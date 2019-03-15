#include "CppUTest/TestHarness.h"
#include "ring_buffer.h"

TEST_GROUP(RingBuffer)
{ RingBuffer * buf;

    void setup()
    {
        buf = new RingBuffer;
    }
    void teardown()
    {
        delete buf;
    }
};

TEST(RingBuffer, Init)
{
    CHECK(ring_buffer_empty(buf));
}
