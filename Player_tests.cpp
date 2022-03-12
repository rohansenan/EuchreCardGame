// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(make_trump)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");

    const Card c6("Nine", "Clubs");
    const Card c7("Jack", "Hearts");
    const Card c8("Jack", "Diamonds");

    string order_up_suit;

    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);

    ASSERT_TRUE(jayson->make_trump(c6, false, 1, order_up_suit));
    ASSERT_FALSE(jayson->make_trump(c7, false, 1, order_up_suit));
    ASSERT_FALSE(jayson->make_trump(c7, false, 2, order_up_suit));
    ASSERT_TRUE(jayson->make_trump(c8, true, 2, order_up_suit));
    ASSERT_FALSE(jayson->make_trump(c8, true, 1, order_up_suit));
    ASSERT_TRUE(jayson->make_trump(c8, false, 2, order_up_suit));

    delete jayson;
}

// TEST(make_trump_2)
// {
//     Player * jayson = Player_factory("Jayson", "Simple");

//     const Card c("Jack", "Spades");
//     const Card c2("Nine", "Clubs");
//     const Card c3("Nine", "Diamonds");
//     const Card c4("Jack", "Hearts");
//     const Card c5("Nine", "Hearts");
//     const Card c6("Ten", "Diamonds");

//     string order_up_suit;

//     jayson->add_card(c);
//     jayson->add_card(c2);
//     jayson->add_card(c3);
//     jayson->add_card(c4);
//     jayson->add_card(c5);

//     ASSERT_TRUE(jayson->make_trump(c6, false, 2, order_up_suit));

//     delete jayson;
// }

TEST(add_and_discard)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Nine", "Clubs");

    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);

    jayson->add_and_discard(c6);

    vector<Card> played;
    played.push_back(jayson->lead_card("Clubs"));
    ASSERT_TRUE(played.size() < 6);

    for (size_t i = 0; i < played.size(); i++)
    {
        ASSERT_NOT_EQUAL(played.at(i), c3);
    }

    delete jayson;
}

TEST(lead_card)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    Player * rohan = Player_factory("Rohan", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    
    const Card c6("Ten", "Hearts");
    const Card c7("Jack", "Hearts");
    const Card c8("King", "Hearts");

    string order_up_suit;

    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);

    rohan->add_card(c3);
    rohan->add_card(c4);
    rohan->add_card(c6);
    rohan->add_card(c7);
    rohan->add_card(c8);

    ASSERT_EQUAL(jayson->lead_card("Clubs"), c4);
    ASSERT_EQUAL(jayson->lead_card("Hearts"), c);
    ASSERT_EQUAL(jayson->lead_card("Spades"), c5);
    ASSERT_EQUAL(jayson->lead_card("Clubs"), c3);
    ASSERT_EQUAL(jayson->lead_card("Spades"), c2);

    ASSERT_EQUAL(rohan->lead_card("Spades"), c8);
    ASSERT_EQUAL(rohan->lead_card("Diamonds"), c4);
    rohan->add_card(c4);
    ASSERT_EQUAL(rohan->lead_card("Hearts"), c7);


    delete jayson;
    delete rohan;
}

TEST(lead_card_test_2)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    Player * rohan = Player_factory("Rohan", "Simple");
    const Card c("Jack", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    
    const Card c6("Ten", "Hearts");
    const Card c7("Jack", "Hearts");
    const Card c8("King", "Hearts");

    string order_up_suit;

    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);

    rohan->add_card(c3);
    rohan->add_card(c4);
    rohan->add_card(c6);
    rohan->add_card(c7);
    rohan->add_card(c8); 

    ASSERT_EQUAL(jayson->lead_card("Spades"), c4);
    ASSERT_EQUAL(rohan->lead_card("Clubs"), c8);

    delete jayson;
    delete rohan;
}

TEST(play_card_1)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Ten", "Clubs");
    jayson->add_card(c);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->play_card(c3, "Clubs"), c2);
    delete jayson;    
}

TEST(play_card_2)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Nine", "Clubs");
    const Card c2("Jack", "Clubs");
    const Card c3("Ten", "Clubs");
    jayson->add_card(c);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->play_card(c3, "Spades"), c);
    delete jayson;
}

TEST(play_card_3)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Nine", "Diamonds");
    const Card c2("Ace", "Clubs");
    jayson->add_card(c);
    ASSERT_EQUAL(jayson->play_card(c2, "Spades"), c);
    delete jayson;
}

TEST(play_card_4)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Spades");
    jayson->add_card(c);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->play_card(c3, "Spades"), c2);
    delete jayson;
}

TEST(play_card_5)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Spades");
    jayson->add_card(c);
    jayson->add_card(c3);
    ASSERT_EQUAL(jayson->play_card(c2, "Clubs"), c);
    delete jayson;
}

//Submit to autograder without this one and see if you still get 14/17
TEST(play_card)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    Player * rohan = Player_factory("Rohan", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    
    const Card c6("Ten", "Hearts");
    const Card c7("Jack", "Hearts");
    const Card c8("King", "Hearts");

    const Card c9("Nine", "Spades");
    const Card c10("Nine", "Diamonds");
    const Card c11("Ace", "Hearts");

    string trump;

    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);

    rohan->add_card(c3);
    rohan->add_card(c4);
    rohan->add_card(c6);
    rohan->add_card(c7);
    rohan->add_card(c8);

    ASSERT_EQUAL(jayson->play_card(c9, "Spades"), c2);
    ASSERT_EQUAL(jayson->play_card(c10, "Spades"), c5);
    ASSERT_EQUAL(jayson->play_card(c6, "Spades"), c4);

    ASSERT_EQUAL(rohan->play_card(c11, "Spades"), c8);
    ASSERT_EQUAL(rohan->play_card(c11, "Hearts"), c7);
    ASSERT_EQUAL(rohan->play_card(c9, "Clubs"), c3);

    delete jayson;
    delete rohan;
}

TEST_MAIN()
