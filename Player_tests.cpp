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
TEST(add_card_and_lead_card)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    Card c("Ace", "Clubs");
    jayson->add_card(c);
    ASSERT_EQUAL(jayson->lead_card("Clubs"), c);
}

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
    ASSERT_TRUE(jayson->make_trump(c7, false, 2, order_up_suit));
    ASSERT_TRUE(jayson->make_trump(c8, true, 2, order_up_suit));
    ASSERT_FALSE(jayson->make_trump(c8, true, 1, order_up_suit));
    ASSERT_FALSE(jayson->make_trump(c8, false, 2, order_up_suit));
}

TEST(add_and_discard)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Nine", "Clubs");

    string order_up_suit;

    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);

    jayson->add_and_discard(c6);

    vector<Card> played;

    played.push_back(jayson->lead_card("Clubs"));
    ASSERT_TRUE(played.size() < 6);

    for (int i = 0; i < played.size(); i++)
    {
        ASSERT_NOT_EQUAL(played.at(i), c3);
    }
}

TEST_MAIN()
