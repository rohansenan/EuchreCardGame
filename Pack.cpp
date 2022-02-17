#include <iostream>
#include <cassert>
#include <string>
#include "Pack.h"
#include "Card.h"

using namespace std;


Pack::Pack()
: cards {Card("Nine", "Spades"), Card("Ten", "Spades"), Card("Jack", "Spades"),
 Card("Queen", "Spades"), Card("King", "Spades"), Card("Ace", "Spades"), 
 Card("Nine", "Hearts"), Card("Ten", "Hearts"), Card("Jack", "Hearts"), 
 Card("Queen", "Hearts"), Card("King", "Hearts"), Card("Ace", "Hearts"), 
 Card("Nine", "Clubs"), Card("Ten", "Clubs"), Card("Jack", "Clubs"), 
 Card("Queen", "Clubs"), Card("King", "Clubs"), Card("Ace", "Clubs"),
 Card("Nine", "Diamonds"), Card("Ten", "Diamonds"), Card("Jack", "Diamonds"), 
 Card("King", "Diamonds"), Card("Queen", "Diamonds"), Card("Ace", "Diamonds"),},next(0)
 {}

Pack::Pack(istream &pack_input)
{
    string rank;
    string suit;
    string ignore;
    int line = 0;
    while(line < 24)
    {
        pack_input >> rank >> ignore >> suit;
        cards[line] = Card(rank, suit);
        line++;
    }
    next = 0;
}

Card Pack::deal_one()
{
    Card deal = cards[next];
    next += 1;
    return deal; 
}

void Pack::reset()
{
    next = 0;
}

void Pack::shuffle()
{
    int top = 11;
    int bot = 23;
    for (int i = 23; i >= 0; i--)
    {
        Card placeholder = cards[i];
        cards[i] = cards[top];
        i--;
        top--;
        cards[i] = cards[bot];
        bot--;
    }
}

bool Pack::empty() const
{
    if (next == 24)
    {
        return true;
    }
    else
    {
        return false;
    }
}


