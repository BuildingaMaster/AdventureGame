#ifndef GTESTING
#define GTESTING
#endif

#include "gtest/gtest.h"

#include <streambuf>
#include <ctime>
#include <random>

#include "../AdventureGame/Item.h"
#include "../AdventureGame/ContextParser.h"
#include "../AdventureGame/PlayerActions.h"

#include "../AdventureGame/CommonGameObjects.h"

namespace
{
    TEST(LocationMGRTest,validDirection)
    {
        locationManager::stringToDirection("north");
        //EXPECT_EQ(locationManager::stringToDirection("north"),cardinalDirection::North);
    }

    TEST(TimePassTest, cycle)
    {
        int start = locationManager::getCurrentTime();
        Location* temp = locationManager::getCurrentLocation();
        for (int i = 0; i <= 11; i++)
        {
            locationManager::updateCurrentLocation(temp->checkAdjacent(North));
            locationManager::updateCurrentLocation(temp->checkAdjacent(South));
        }
        int end = locationManager::getCurrentTime();
        EXPECT_TRUE(start == end);
    }

    TEST(TimePassTest, IsCycle24hours)
    {
        int start = locationManager::getCurrentTime();
        int steps = 0;
        Location* temp = locationManager::getCurrentLocation();
        do
        {
            if (steps % 2 == 0)
            {
                locationManager::updateCurrentLocation(temp->checkAdjacent(North));
            }
            if (steps % 2 == 1)
            {
                locationManager::updateCurrentLocation(temp->checkAdjacent(South));
            }
            steps++;
        } while (locationManager::getCurrentTime() != start);
        EXPECT_TRUE(steps == 24);
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
    TEST_F(HitTest, NPCHitBack)
    {
        NPCManager::init();
        while (!CP->interpretCommand("hit wolf"))
        {
            CP->interpretCommand("north");
        }
        EXPECT_EQ(playeract.checkPlayerHealth(), 2);
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
        locationManager::updateCurrentLocation(locationManager::locationMap[3]);
        

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
        locationManager::updateCurrentLocation(locationManager::locationMap[3]);
        // Pick up mushroom 
        EXPECT_TRUE(CP->interpretCommand("pick apple"));

        // Yes/No needs an input, so fake it
        PrintDisplay::GT_setString("yes\n");
    
        // Eat the apple
        testing::internal::CaptureStdout();
        EXPECT_TRUE(CP->interpretCommand("eat apple"));
        string output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output,"\nYou already have max health, are you sure you want to eat the apple?\n\nYes or no?\n> yes\n\nYou eat the apple!\n\nYou healed by 1 HP!\n");
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

    class InstantKillTest : public testing::Test {
        protected:
        Inventory *userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        InstantKillTest() {
            userInventory = new Inventory(&playeract);
            CommonGameObjects::PAManager = &playeract;
            CP = new ContextParser(userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~InstantKillTest() override {
            delete CP;
            delete userInventory;
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        void SetUp() override {
            playeract.healthMGR.restoreMaxHP();
            locationManager::updateCurrentLocation(locationManager::locationMap[3]);
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        void TearDown() override {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }
    };

    TEST_F(InstantKillTest, PlayerDiesInTrap)
    {
        // Player moves to kill room
        EXPECT_TRUE(CP->interpretCommand("east"));
        EXPECT_LE(playeract.healthMGR.checkHP(),0);
    }

    TEST_F(InstantKillTest, NoTrap)
    {
        // Player moves to non-kill room
        EXPECT_TRUE(CP->interpretCommand("west"));
        EXPECT_GT(playeract.healthMGR.checkHP(),0);
    }

        class GameOverTest : public testing::Test {
    protected:
        Inventory *userInventory;
        PlayerActions playeract;
        ContextParser *CP;

        // You can remove any or all of the following functions if their bodies would
        // be empty.

        GameOverTest() {
            userInventory = new Inventory(&playeract);
            CommonGameObjects::INManager = userInventory;
            CommonGameObjects::PAManager = &playeract;
            CP = new ContextParser(userInventory, &playeract);
            // You can do set-up work for each test here.
        }

        ~GameOverTest() override {
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

    TEST_F(GameOverTest, GameOver)
    {
        // Move to apple room
        locationManager::updateCurrentLocation(locationManager::locationMap[3]);
        // Pick an apple

        EXPECT_TRUE(CP->interpretCommand("pick apple"));
        
        // Player Dead
        playeract.healthMGR.removeHP(999);

        // Yes to play again
        PrintDisplay::GT_setString("yes\n");
        playeract.playAgain();


        // Nothing should be in the inventory
        EXPECT_EQ(userInventory->currentInventory.size(), 0);
        // We should be at the starting room
        EXPECT_EQ(locationManager::currentLocation->roomID, 1);
    }


} // namespace
    int main(int argc, char** argv)
    {
        srand(time(0));
        if (locationManager::init() == false)
        {
            cout << "Could not run tests." << endl;
            locationManager::deinit();
            return 1;
        }
        //startingRoom->setDescription("You are in a vibrant, yet desolate forest. \nThere seems to be no wildlife in sight, although a nearby apple tree seems to be within reach. \nTo the west is a shallow pond, \na deserted hut to the east, and more wilderness \nsouth and north of your location.");
        //startingRoom->printLocation();
        testing::InitGoogleTest(&argc, argv);
        int res =  RUN_ALL_TESTS();
        locationManager::deinit();
        return res;
    }

