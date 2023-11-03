#ifndef GTESTING
#define GTESTING
#endif

#include "gtest/gtest.h"

#include "../AdventureGame/Item.h"
#include "../AdventureGame/ContextParser.h"
#include "../AdventureGame/PlayerActions.h"

namespace
{
    TEST(LocationMGRTest,init)
    {
        EXPECT_TRUE(locationManager::init());
    }

    TEST(LocationMGRTest,validDirection)
    {
        EXPECT_EQ(locationManager::stringToDirection("north"),cardinalDirection::North);
    } 

    class CPTest : public testing::Test {
        protected:
        Inventory userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        CPTest() {
            CP = new ContextParser(&userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~CPTest() override {
            delete CP;
            // You can do clean-up work that doesn't throw exceptions here.
        }

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
    };

    TEST_F(CPTest, NoCommands)
    {
        string command;
        command = "";
        EXPECT_FALSE(CP->interpretCommand(command));
    }

    TEST_F(CPTest, TooShort)
    {
        string command;
        command = "lol";
        EXPECT_FALSE(CP->interpretCommand(command));
    }

    TEST_F(CPTest, WrongShortCommand)
    {
        string command;
        command = "sume apple";
        EXPECT_FALSE(CP->interpretCommand(command));
    }

    TEST_F(CPTest, OutOfOrderTest)
    {
        // Move to apple room
        CP->interpretCommand("north");
        CP->interpretCommand("north");
        

        // Can't eat apple, not picked up
        string command;
        command = "consume apple";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP->interpretCommand(command));
        string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou don't have a(n) apple.\n");

        // Can pick up apple
        command = "pick apple";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou pick an apple from the tree.\n");

        // Can't pick up apple, already done
        command = "pick apple";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nThere is no apple for you to pick!\n");

        // Eat apple
        command = "eat apple";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou eat the apple!\n");

        // Can't eat apple, already ate
        command = "eat apple";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou don't have a(n) apple.\n");
    }

    class HitTest : public testing::Test {
        protected:
        Inventory userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        HitTest() {
            CP = new ContextParser(&userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~HitTest() override {
            delete CP;
            // You can do clean-up work that doesn't throw exceptions here.
        }

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
    };
    TEST_F(HitTest, HitYourself)
    {

    }

}
    int main(int argc, char** argv)
    {

        //startingRoom->setDescription("You are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight, although a nearby apple tree seems to be within reach. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.");
        //startingRoom->printLocation();
        testing::InitGoogleTest(&argc, argv);
        int res =  RUN_ALL_TESTS();
        locationManager::deinit();
        return res;
    }

