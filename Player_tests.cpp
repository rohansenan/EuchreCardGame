// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>
#include <fstream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(make_trump_basic_false_round_1)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Queen", "Diamonds");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);
    string order_up_suit;
    ASSERT_FALSE(jayson->make_trump(c6, false, 1, order_up_suit));
    delete jayson;
}

TEST(make_trump_basic_true_round_1)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("King", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Ten", "Hearts");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);
    string order_up_suit;
    ASSERT_TRUE(jayson->make_trump(c6, false, 1, order_up_suit));
    delete jayson;
}

TEST(make_trump_basic_false_round_2)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Ten", "Hearts");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);
    string order_up_suit;
    ASSERT_FALSE(jayson->make_trump(c6, false, 2, order_up_suit));
    delete jayson;
}

TEST(make_trump_basic_true_round_2)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Queen", "Diamonds");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);
    string order_up_suit;
    ASSERT_TRUE(jayson->make_trump(c6, false, 2, order_up_suit));
    delete jayson;
}

TEST(make_trump_is_dealer_round_1)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Queen", "Diamonds");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);
    string order_up_suit;
    ASSERT_FALSE(jayson->make_trump(c6, true, 1, order_up_suit));
    delete jayson;
}

TEST(make_trump_screw_the_dealer)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Queen", "Hearts");
    const Card c5("Ten", "Diamonds");
    const Card c6("Ten", "Hearts");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    jayson->add_card(c4);
    jayson->add_card(c5);
    string order_up_suit;
    ASSERT_TRUE(jayson->make_trump(c6, true, 2, order_up_suit));
    delete jayson;
}

TEST(make_trump_bower_test)
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
    ASSERT_TRUE(jayson->make_trump(c6, false, 1, order_up_suit));
    delete jayson;
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

TEST(add_and_discard_equal_rank_case)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Nine", "Clubs");
    const Card c2("Nine", "Spades");
    const Card c3("Nine", "Hearts");
    const Card c4("Nine", "Diamonds");
    const Card c5("Ace", "Clubs");
    const Card c6("Ten", "Clubs");
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
        ASSERT_NOT_EQUAL(played.at(i), c2);
    }
    delete jayson;
}

TEST(add_and_discard_upcard)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Jack", "Clubs");
    const Card c2("Jack", "Spades");
    const Card c3("Ace", "Clubs");
    const Card c4("King", "Clubs");
    const Card c5("Queen", "Clubs");
    const Card c6("Ten", "Clubs");
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
        ASSERT_NOT_EQUAL(played.at(i), c6);
    }
    delete jayson;
}

TEST(lead_card_1)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Queen", "Hearts");
    const Card c3("Jack", "Hearts");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    ASSERT_EQUAL(jayson->lead_card("Clubs"), c2);
    delete jayson;
}

TEST(lead_card_2)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Jack", "Hearts");
    const Card c2("Ten", "Hearts");
    const Card c3("Queen", "Hearts");
    jayson->add_card(c);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->lead_card("Diamonds"), c2);
    jayson->add_card(c2);
    jayson->add_card(c3);
    ASSERT_EQUAL(jayson->lead_card("Hearts"), c);
    ASSERT_EQUAL(jayson->lead_card("Clubs"), c3);
    ASSERT_EQUAL(jayson->lead_card("Spades"), c2);
    delete jayson;
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
    ASSERT_EQUAL(jayson->play_card(c3, "Spades"), c2);
    delete jayson;
}

TEST(play_card_3)
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

TEST(play_card_4)
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

TEST(play_card_5)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Ace", "Clubs");
    const Card c2("Ten", "Spades");
    const Card c3("Nine", "Spades");
    jayson->add_card(c);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->play_card(c3, "Spades"), c2);
    delete jayson;
}

TEST(play_card_6)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c("Nine", "Hearts");
    const Card c2("Queen", "Hearts");
    const Card c3("Jack", "Hearts");
    const Card c4("Ten", "Hearts");
    jayson->add_card(c);
    jayson->add_card(c2);
    jayson->add_card(c3);
    ASSERT_EQUAL(jayson->play_card(c4, "Spades"), c2);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->play_card(c4, "Hearts"), c3);
    delete jayson;
}

TEST(play_card_7)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    const Card c ("Queen", "Hearts");
    const Card c2 ("Jack", "Hearts");
    const Card c3 ("Nine", "Clubs");
    jayson->add_card(c);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->play_card(c3, "Spades"), c2);
    jayson->add_card(c2);
    ASSERT_EQUAL(jayson->play_card(c3, "Hearts"), c);
    jayson->add_card(c);
    ASSERT_EQUAL(jayson->play_card(c3, "Diamonds"), c);
    delete jayson;
}

TEST(operator_output)
{
    Player * jayson = Player_factory("Jayson", "Simple");
    ostringstream output;
    output << *jayson;
    ostringstream correctOutput;
    correctOutput << "Jayson";
    ASSERT_EQUAL(output.str(), correctOutput.str());
    delete jayson;
}

TEST_MAIN()
