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
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit("Clubs"));
}

TEST(test_is_functions)
{
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(c.is_face(), true);
    ASSERT_EQUAL(c.is_right_bower("Clubs"), false);
    ASSERT_EQUAL(c.is_left_bower("Clubs"), true);
    ASSERT_EQUAL(c.is_trump("Clubs"), false);
}

TEST(test_bool_operators_less_and_less_and_equal)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator<(c, c2));
    ASSERT_TRUE(operator<(c3, c2));
    ASSERT_TRUE(operator<=(c, c2));
}

TEST(test_bool_operators_greater_and_greater_and_equal)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator>(c, c2));
    ASSERT_TRUE(operator>(c, c3));
    ASSERT_TRUE(operator>=(c, c2)); 
}

TEST(test_bool_operator_equal_and_not_equal)
{
    Card c(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c3(Card::RANK_TWO, Card::SUIT_HEARTS);
    ASSERT_FALSE(operator==(c, c3));
    ASSERT_TRUE(operator==(c, c2)); 
    ASSERT_TRUE(operator!=(c, c3));
    ASSERT_FALSE(operator!=(c, c2));
}

TEST_MAIN()
