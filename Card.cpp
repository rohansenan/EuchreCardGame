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

static int suit_value(const string &suit, const string &trump)
{
    int value = -1;
    for (int i = 0; i < NUM_SUITS; i++)
    {
        if (suit == SUIT_NAMES_BY_WEIGHT[i])
        {
            value = i;
        }
    }
    if (suit == trump)
    {
        value = NUM_SUITS;
    }
    assert(value != -1);
    return value;
}

static int card_value(const Card &c, const string &trump)
{
    int value = -1;
    int MAX_VALUE = (NUM_RANKS * NUM_SUITS) + 1;
    if (c.is_right_bower(trump))
    {
        value = MAX_VALUE;
    }
    else if (c.is_left_bower(trump))
    {
        value = MAX_VALUE - 1;
    }
    else 
    {
        if (c.get_suit() == trump)
        {
            value = (suit_value(c.get_suit(), trump) - 1) * 
            NUM_RANKS + rank_value(c.get_rank());
        }
        else
        {
            value = suit_value(c.get_suit(), trump) * 
            NUM_RANKS + rank_value(c.get_rank());
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

string Suit_next(const string &suit)
{
    string suit_next;
    if (suit == Card::SUIT_CLUBS)
    {
        suit_next = Card::SUIT_SPADES;
    }
    else if (suit == Card::SUIT_SPADES)
    {
        suit_next = Card::SUIT_CLUBS;
    }
    else if (suit == Card::SUIT_HEARTS)
    {
        suit_next = Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_DIAMONDS)
    {
        suit_next = Card::SUIT_HEARTS;
    }
    return suit_next;
}

ostream & operator<<(ostream &os, const Card &card)
{
    os << card.get_rank() << " of " << card.get_suit() << endl;
    return os;
}

bool Card_less(const Card &a, const Card &b, const string &trump)
{
    int a_value = card_value(a, trump);
    int b_value = card_value(b, trump);
    // cout << a_value << " " << b_value << endl;
    if (a_value < b_value)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, const string &trump)
{
    
}