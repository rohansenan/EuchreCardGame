#include <iostream>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
//#include <assert.h>

using namespace std;

class Simple : public Player 
{
 public:
    const string &get_name() const override
    {
        return name;
    }
    void add_card(const Card &c) override
    {
        //assert(hand.size() <= 5);
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override
    {
        string upcardSuit = upcard.get_suit();
        string nextSuit = Suit_next(upcardSuit);
        int upcardSuitCount = 0;
        int nextSuitCount = 0;
        for (int i = 0; i < 5; i++)
        {
            if (hand.at(i).is_trump(upcardSuit) && hand.at(i).is_face())
            {
                upcardSuitCount++;
            }
            else if(hand.at(i).is_trump(nextSuit) && hand.at(i).is_face())
            {
                nextSuitCount++;
            }
        }
        if (round == 1)
        {
            if (upcardSuitCount >= 2)
            {
                order_up_suit = upcardSuit;
            }
        }
        else if (round == 2)
        {
            if (nextSuitCount >= 1)
            {
                order_up_suit = nextSuit;
            }
            else if (is_dealer)
            {
                order_up_suit = nextSuit;
            }
        }
    }
    void add_and_discard(const Card &upcard) override
    {
        hand.push_back(upcard);
        int i = 0; 
        for (int j = 1; j <= 5; j++)
        {
            if (Card_less(hand.at(i), hand.at(j), upcard.get_suit()))
            {
                continue;
            }
            else
            {
                i = j;
            }
        }
        hand.erase(hand.begin() + i);
    }
    Card lead_card(const std::string &trump) override
    {
        bool allTrump;
        for (int i = 0; i < 5; i++)
        {
            if (!hand.at(i).is_trump(trump))
            {
                allTrump = false;
            }
        }
        if (allTrump)
        {
            
        }
    }
    Card play_card(const Card &led_card, const std::string &trump) override
    {

    }
 private: 
    string name;
    string strategy;
    vector<Card> hand;
};

class Human : public Player 
{
 public:
    const string &get_name() const override
    {

    }
    void add_card(const Card &c) override
    {

    }
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override
    {

    }
    void add_and_discard(const Card &upcard) override
    {

    }
    Card lead_card(const std::string &trump) override
    {

    }
    Card play_card(const Card &led_card, const std::string &trump) override
    {

    }
 private: 
    string name;
    string strategy;
    vector<Card> hand;
};

Player * Player_factory(const std::string &name, const std::string &strategy)
{

}

ostream & operator<<(std::ostream &os, const Player &p)
{

}
