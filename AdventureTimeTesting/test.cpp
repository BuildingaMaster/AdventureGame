#ifndef GTESTING
#define GTESTING
#endif

#include "gtest/gtest.h"

#include <streambuf>


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
        locationManager::stringToDirection("north");
        //EXPECT_EQ(locationManager::stringToDirection("north"),cardinalDirection::North);
    } 

    class HitTest : public testing::Test {
        protected:
        Inventory *userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        HitTest() {
            userInventory = new Inventory(&playeract);
            CommonGameObjects::PAManager = &playeract;
            CP = new ContextParser(userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~HitTest() override {
            delete CP;
            delete userInventory;
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
        string command;
        command = "hit self";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand(command));
        string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nFor some reason, you hit yourself.\nYou can withstand 2 more hits.\n");
        EXPECT_EQ(playeract.checkPlayerHealth(),2);
    }

    class CPTest : public testing::Test {
        protected:
        Inventory *userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        CPTest() {
            userInventory = new Inventory(&playeract);
            CommonGameObjects::PAManager = &playeract;
            CP = new ContextParser(userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~CPTest() override {
            delete CP;
            delete userInventory;
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
        playeract.healPlayer(-1);
        // Move to apple room
        CP->interpretCommand("north");
        CP->interpretCommand("north");
        

        // Can't eat apple, not picked up
        string command;
        command = "consume apple";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP->interpretCommand(command));
        string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou don't have any apples.\n");

        // Can pick up apple
        command = "pick apples";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou took 5 apples!\n");

        // Can't pick up apple, already done
        command = "pick apples";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nThere are no apples for you to pick!\n");

        // Eat apple
        command = "eat apple";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou eat the apple!\n\nYou healed by 1 HP!\n");

        // Drop apples
        command = "drop apples";
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou drop 4 apples!\n");

        // Can't eat apple, already ate
        command = "eat apple";
        testing::internal::CaptureStdout();
        EXPECT_FALSE(CP->interpretCommand(command));
        output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\nYou don't have any apples.\n");
    }

    class EatTest : public testing::Test {
        protected:
        Inventory *userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        EatTest() {
            userInventory = new Inventory(&playeract);
            CommonGameObjects::PAManager = &playeract;
            CP = new ContextParser(userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~EatTest() override {
            delete CP;
            delete userInventory;
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

    TEST_F(EatTest, OvereatTest)
    {
        // Pick up mushroom 
        EXPECT_TRUE(CP->interpretCommand("pick apple"));
        // Yes/No needs cin, so fake it
        streambuf *cinbuf = std::cin.rdbuf();
        std::stringstream ss;
        ss << "yes\n";
        cin.rdbuf(ss.rdbuf());
        // Eat the apple
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand("eat apple"));
        string output = testing::internal::GetCapturedStdout();
        // Reset cin
        cin.rdbuf(cinbuf);
        EXPECT_EQ(output,"\nYou already have max health, are you sure you want to eat the apple?\n\nYes or no?\n> \nYou eat the apple!\n\nYou healed by 1 HP!\n");
        EXPECT_EQ(playeract.checkPlayerHealth(), playeract.checkMaxPlayerHealth());

    }

    class IsOnCloud9Test : public testing::Test {
        protected:
        Inventory *userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        IsOnCloud9Test() {
            userInventory = new Inventory(&playeract);
            CommonGameObjects::PAManager = &playeract;
            CP = new ContextParser(userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~IsOnCloud9Test() override {
            delete CP;
            delete userInventory;
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

    TEST_F(IsOnCloud9Test, notHigh)
    {
        // Not high
        PrintDisplay::custom_cout << "This is a test.\nHello World!\n";
        testing::internal::CaptureStdout();
        PrintDisplay::flush();
        string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "This is a test.\nHello World!\n");
    }
    
    TEST_F(IsOnCloud9Test, newLineTest)
    {
        // High
        playeract.stepsUntilNotHigh = 3;
        playeract.playerIsHigh = true;

        // New lines not affected test
        PrintDisplay::custom_cout << "\n\nP\n\n";
        testing::internal::CaptureStdout();
        PrintDisplay::flush();
        string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, "\n\nP\n\n");
    }
    
    TEST_F(IsOnCloud9Test, pureRandom)
    {
        // High
        playeract.stepsUntilNotHigh = 3;
        playeract.playerIsHigh = true;

        // Pure random test
        PrintDisplay::custom_cout << "This text should be really scrambled.\n It shouldn't be too hard to read though.\n";
        testing::internal::CaptureStdout();
        PrintDisplay::flush();
        string output = testing::internal::GetCapturedStdout();
        cout << output;
        EXPECT_NE(output, "This text should be really scrambled.\n It shouldn't be too hard to read though.\n");
    }

} // namespace
    int main(int argc, char** argv)
    {

        //startingRoom->setDescription("You are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight, although a nearby apple tree seems to be within reach. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.");
        //startingRoom->printLocation();
        testing::InitGoogleTest(&argc, argv);
        int res =  RUN_ALL_TESTS();
        locationManager::deinit();
        return res;
    }

