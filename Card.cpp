// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here
using namespace std;
// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
static string find_left_bower(const string &trump)
{
    string left_bower;
    if (trump == "Clubs")
    {
        left_bower = "Spades";
    }
    else if (trump == "Spades")
    {
        left_bower = "Clubs";
    }
    else if (trump == "Hearts")
    {
        left_bower = "Diamonds";
    }
    else
    {
        left_bower = "Hearts";
    }
    return left_bower;
}

static int rank_value(const string &rank)
{
    int value = -1;
    for (int i = 0; i < NUM_RANKS; i++)
    {
        if (rank == RANK_NAMES_BY_WEIGHT[i])
        {
            value = i;
        }
    }
    assert(value != -1);
    return value;
}

Card::Card()
: rank(RANK_TWO), suit(SUIT_SPADES) {}

Card::Card(const string &rank_in, const string &suit_in)
: rank(rank_in), suit(suit_in) {}

string Card::get_rank() const
{
    return rank;
}

string Card::get_suit() const
{
    return suit;
}

string Card::get_suit(const string &trump) const
{
    string left_bower = find_left_bower(trump);
    if (rank == RANK_JACK && suit == left_bower)
    {
        return trump;
    }
    else
    {
        return suit;
    }
}

bool Card::is_face() const
{
    if (rank == RANK_ACE || rank == RANK_KING || rank == RANK_QUEEN || rank == RANK_JACK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Card::is_right_bower(const string &trump) const
{
    if (rank == RANK_JACK && suit == trump)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Card::is_left_bower(const string &trump) const
{
    string left_bower = find_left_bower(trump);
    if (rank == RANK_JACK && suit == left_bower)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Card::is_trump(const string &trump) const
{
    if (suit == trump)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool operator<(const Card &lhs, const Card &rhs)
{
    int lhs_value = rank_value(lhs.get_rank());
    int rhs_value = rank_value(rhs.get_rank());
    if (lhs_value < rhs_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator<=(const Card &lhs, const Card &rhs)
{
    int lhs_value = rank_value(lhs.get_rank());
    int rhs_value = rank_value(rhs.get_rank());
    if (lhs_value <= rhs_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator>(const Card &lhs, const Card &rhs)
{
    int lhs_value = rank_value(lhs.get_rank());
    int rhs_value = rank_value(rhs.get_rank());
    if (lhs_value > rhs_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator>=(const Card &lhs, const Card &rhs)
{
    int lhs_value = rank_value(lhs.get_rank());
    int rhs_value = rank_value(rhs.get_rank());
    if (lhs_value >= rhs_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator==(const Card &lhs, const Card &rhs)
{
    int lhs_value = rank_value(lhs.get_rank());
    int rhs_value = rank_value(rhs.get_rank());
    if (lhs_value == rhs_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!=(const Card &lhs, const Card &rhs)
{
    int lhs_value = rank_value(lhs.get_rank());
    int rhs_value = rank_value(rhs.get_rank());
    if (lhs_value != rhs_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}