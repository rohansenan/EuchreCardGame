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


// Add more test cases here

TEST_MAIN()
