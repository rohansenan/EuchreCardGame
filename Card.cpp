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
    return value;
}

static int suit_value(const string &suit)
{
    int value = -1;
    for (int i = 0; i < NUM_SUITS; i++)
    {
        if (suit == SUIT_NAMES_BY_WEIGHT[i])
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
    else if (Card::is_left_bower(trump))
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
    else if (lhs_value == rhs_value)
    {
        int lhs_suit_value = suit_value(lhs.get_suit());
        int rhs_suit_value = suit_value(rhs.get_suit());
        if (lhs_suit_value < rhs_suit_value)
        {
            return true;
        }
        else
        {
            return false;
        }
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
    else if (lhs_value == rhs_value)
    {
        int lhs_suit_value = suit_value(lhs.get_suit());
        int rhs_suit_value = suit_value(rhs.get_suit());
        if (lhs_suit_value > rhs_suit_value)
        {
            return true;
        }
        else
        {
            return false;
        }
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
    if (lhs.get_rank() == rhs.get_rank())
    {
        if (lhs.get_suit() == rhs.get_suit())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator!=(const Card &lhs, const Card &rhs)
{
    if (lhs==rhs)
    {
        return false;
    }
    else
    {
        return true;
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
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const string &trump)
{
    if (a.is_right_bower(trump))
    {
        return false;
    }
    else if (b.is_right_bower(trump))
    {
        return true;
    }
    else if (a.is_left_bower(trump))
    {
        return false;
    }
    else if (b.is_left_bower(trump))
    {
        return true;
    }
    else if (a.get_suit(trump) == trump && b.get_suit(trump) != trump)
    {
        return false;
    }
    else if (a.get_suit(trump) != trump && b.get_suit(trump) == trump)
    {
        return true;
    }
    else
    {
        if (rank_value(a.get_rank()) == rank_value(b.get_rank()))
        {
            string a_suit = a.get_suit();
            string b_suit = b.get_suit();
            int a_suit_value = suit_value(a_suit);
            int b_suit_value = suit_value(b_suit);
            return a_suit_value < b_suit_value;
        }
        else
        {
            return a < b;
        }
    }
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, const string &trump)
{
    string led_suit = led_card.get_suit(trump);
    if (led_suit == trump)
    {
        return Card_less(a, b, trump);
    }
    else if (a.get_suit(trump) != led_suit && b.get_suit(trump) != led_suit)
    {
        return Card_less(a, b, trump);
    }
    else if (a.get_suit(trump) != trump && b.get_suit(trump) != trump)
    {
        if (a.get_suit(trump) == led_suit && b.get_suit(trump) != led_suit)
        {
            return false;
        }
        else if (a.get_suit(trump) != led_suit && b.get_suit(trump) == led_suit)
        {
            return true;
        }
        else 
        {
            return a < b;
        }
    }
    else if (a.get_suit(trump) == trump && b.get_suit(trump) != trump)
    {
        return false;
    }
    else if (a.get_suit(trump) != trump && b.get_suit(trump) == trump)
    {
        return true;
    }
    return -1;
}