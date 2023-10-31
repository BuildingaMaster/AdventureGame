#include "gtest/gtest.h"

#include "../AdventureGame/Item.h"
#include "../AdventureGame/ContextParser.h"
#include "../AdventureGame/PlayerActions.h"

#include "gtest/gtest.h"



namespace
{
    Inventory userInventory;
    Location *startingRoom = new Location();
    PlayerActions playeract;
    ContextParser CP(&userInventory, &playeract);

    TEST(ItemTest, Init)
    {
        Item t(consumable, inWorld);
        t.setItemName("Joe mama");
        EXPECT_EQ("Joe mama", t.getItemName());
    }

    TEST(ContextTest, NoCommands)
    {
        string command;
        command = "";
        EXPECT_FALSE(CP.interpretCommand(startingRoom,command));
    }

    TEST(ContextTest, TooShort)
    {
        string command;
        command = "lol";
        EXPECT_FALSE(CP.interpretCommand(startingRoom,command));
    }

    TEST(ContextTest, WrongShortCommand)
    {
        string command;
        command = "sume apple";
        EXPECT_FALSE(CP.interpretCommand(startingRoom,command));
    }

    TEST(ContextTest, OutOfOrderTest)
    {
        string command;
        command = "consume apple";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP.interpretCommand(startingRoom,command));
        string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou don't have an apple.\n");


        command = "pick apple";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP.interpretCommand(startingRoom,command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou pick an apple from the tree.\n");

        command = "pick apple";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP.interpretCommand(startingRoom,command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nThere is no apple for you to pick!\n");

        command = "eat apple";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP.interpretCommand(startingRoom,command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou eat the apple!\n");
    }

    int main(int argc, char** argv)
    {

        startingRoom->setDescription("You are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight, although a nearby apple tree seems to be within reach. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.");
        startingRoom->printLocation();
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

}