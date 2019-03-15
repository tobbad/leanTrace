/*
 * test_ltrace.cpp
 *
 *  Created on: 24.02.2019
 *      Author: badi
 */

#include "gtest/gtest.h"
// DUT
#include "ltrace.h"

namespace {

class LTInitTest : public :: testing::Test {
protected:
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
       // Code here will be called immediately after the constructor (right
       // before each test).
    }

    void TearDown() override {
       // Code here will be called immediately after each test (right
       // before the destructor).
    }
}; // class

uint16_t myWrite(uint8_t *buf, uint16_t cnt){ return cnt;}

TEST_F(LTInitTest, CheckInitNull)
{
    ltrace_msg_e res = lt_init(NULL);

    ASSERT_EQ(res, LT_ERROR);
}

TEST_F(LTInitTest, CheckInitStructWithWriteNull)
{
    lt_init_t llif = {0};
    ltrace_msg_e res = lt_init(&llif);

    ASSERT_EQ(res, LT_ERROR);
}

TEST_F(LTInitTest, CheckInitStructWithWriteOk)
{
    lt_init_t llif = {0};
    llif.write = myWrite;
    ltrace_msg_e res = lt_init(&llif);

    ASSERT_EQ(res, LT_OK);
}


class LTTest : public :: testing::Test {
protected:
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    lt_init_t llif = {0};

    void SetUp() override {
        llif.write = myWrite;
        ltrace_msg_e res = lt_init(&llif);
       // Code here will be called immediately after the constructor (right
       // before each test).
    }

    void TearDown() override {
       // Code here will be called immediately after each test (right
       // before the destructor).
    }
}; // class


TEST_F(LTTest, CheckHashForKnown)
{
    uint32_t exp = 0xf1c6fd7f;
    ASSERT_EQ(HASH("funny_bone"), exp);
}

TEST_F(LTTest, CheckHashCollision)
{
    char inStr[]="fu";
    printf("strlen(%s)=%d\n", inStr, strlen(inStr));
    for (uint8_t i=0;i<strlen(inStr);i++)
    {
        printf("str[%d]= %c\n",i, inStr[i]);
    }
    uint32_t exp =
       ((uint32_t)
        (
            (
                (
                    (
                        (
                            0*65599u
                            +(uint8_t)0
                        )*65599u
                        +(uint8_t)0
                    )*65599u
                    +(uint8_t)'f'
                )*65599u
                +(uint8_t)'u'
            )
         )
       );

    ASSERT_EQ(((uint32_t)(H4("fu",0,0))), exp);
}

} // namespace

