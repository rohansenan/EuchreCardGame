// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// Add more tests here
TEST(test_pack_ctor)
{
    stringstream input;
    input << "Nine of Spades\n Ten of Spades\n Jack of Spades\n Queen of Spades\n King of Spades\n Ace of Spades\n"; 
    Pack pack(input);
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
    ASSERT_EQUAL(Card::RANK_TEN, second.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, second.get_suit());
}

TEST(test_reset)
{
    Pack pack;
    pack.deal_one();
    pack.deal_one();
    pack.deal_one();
    pack.reset();
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// TEST(test_shuffle)
// {
//     Pack pack;
//     Card firstOriginal = pack.deal_one();
//     Card secondOriginal = pack.deal_one();
//     pack.reset();
//     pack.shuffle();
//     pack.deal_one();
//     Card secondNew = pack.deal_one();
//     pack.deal_one();
//     Card fourthNew = pack.deal_one();
//     ASSERT_EQUAL(firstOriginal, secondNew);
//     ASSERT_EQUAL(secondOriginal, fourthNew);
// }

TEST(test_empty)
{
    Pack pack;
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
    for (int i = 0; i < 23; i++)
    {
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}

TEST_MAIN()
