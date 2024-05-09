/*
 * NavPwrTester.cpp
 *
 *  Created on: July 19, 2017
 *      Author: Gorang Gandhi
 */

#include <gtest/gtest.h>
#include <Fw/Test/UnitTest.hpp>
#include <Tester.hpp>

TEST(TestNominal, CycleTest) {
    RobotArm::Tester tester;
    tester.testCycle();
}

TEST(TestNominal, Angles) {
    RobotArm::Tester tester;
    tester.testAngles();
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
