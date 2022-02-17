// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}



// Add more test cases here
TEST(test_card_get_suit)
{
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit("Clubs"));
    ASSERT_EQUAL(Card::SUIT_SPADES, c2.get_suit("Clubs"));
}

TEST(test_is_face)
{
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    //Card c2(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_TRUE(c.is_face());
    // ASSERT_EQUAL(c2.is_face(), true);
    // ASSERT_EQUAL(c2.is_right_bower("Clubs"), false);
    // ASSERT_EQUAL(c2.is_left_bower("Clubs"), false);
    // ASSERT_EQUAL(c2.is_trump("Clubs"), true);
}

TEST(test_is_right)
{
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_right_bower("Clubs"));
}

TEST(test_is_left)
{
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_left_bower("Clubs"));
}

TEST(test_is_trump)
{
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c.is_trump("Clubs"));
}

TEST(test_bool_operators_less_and_less_and_equal)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator<(c, c2));
    ASSERT_TRUE(operator<(c3, c2));
    //ASSERT_TRUE(operator<=(c, c2));
}

TEST(test_bool_operators_greater_and_greater_and_equal)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_TRUE(operator>(c, c2));
    ASSERT_TRUE(operator>(c, c3));
    //ASSERT_TRUE(operator>=(c, c2)); 
}

TEST(test_bool_operator_equal_and_not_equal)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    Card c4(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_FALSE(operator==(c, c3));
    ASSERT_FALSE(operator==(c, c2));
    ASSERT_TRUE(operator==(c, c4)); 
    ASSERT_TRUE(operator!=(c, c3));
    ASSERT_TRUE(operator!=(c, c2));
}

TEST(test_suit_next)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Suit_next(c.get_suit()), Card::SUIT_SPADES);
}

TEST(test_operator_output)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    ostringstream output;
    operator<<(output, c);
    ostringstream correct_output;
    correct_output << "Ace of Clubs";
    ASSERT_EQUAL(output.str(), correct_output.str());
}

TEST(test_bool_card_less)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c4(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c5(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c6(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_SPADES;
    ASSERT_TRUE(Card_less(c, c2, trump));
    ASSERT_TRUE(Card_less(c2, c4, trump));
    ASSERT_TRUE(Card_less(c2, c5, trump));
    ASSERT_TRUE(Card_less(c6, c3, trump));
    ASSERT_TRUE(Card_less(c3, c, trump));
    ASSERT_TRUE(Card_less(c3, c5, trump));
    ASSERT_TRUE(Card_less(c5, c4, trump));
}

TEST(test_bool_card_less_including_led_suit)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card c4(Card::RANK_JACK, Card::SUIT_SPADES);
    Card c5(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c6(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_SPADES;
    ASSERT_TRUE(Card_less(c3, c, c2, trump));
    ASSERT_TRUE(Card_less(c, c3, c6, trump));
    ASSERT_TRUE(Card_less(c5, c4, c, trump));
    ASSERT_TRUE(Card_less(c, c6, c3, trump));   
}

TEST_MAIN()
