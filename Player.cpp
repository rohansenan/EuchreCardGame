//Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "Player.h"
#include "Card.h"

//#include <assert.h>

using namespace std;

void sort(vector<Card> &hand)
{
    Card placeholder;
    for(size_t i=1;i<hand.size();i++)
    {
        if(hand[i]<hand[i-1])
        {
            placeholder=hand[i-1];
            hand[i-1]=hand[i];
            hand[i]=placeholder;
            i=0;
        }
    }
}

class Simple : public Player 
{
 public:
    Simple(const string &name)
    : name(name) {}

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
        for (size_t i = 0; i < 5; i++)
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
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (round == 2)
        {
            if (nextSuitCount >= 1)
            {
                order_up_suit = nextSuit;
                return true;
            }
            else if (is_dealer)
            {
                order_up_suit = nextSuit;
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
    void add_and_discard(const Card &upcard) override
    {
        hand.push_back(upcard);
        int i = 0; 
        for (size_t j = 1; j <= 5; j++)
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
        sort(hand);
        bool allTrump = true;
        for (size_t i = 0; i < 5; i++)
        {
            if (!hand.at(i).is_trump(trump))
            {
                allTrump = false;
            }
        }
        if(hand.size()==1)
        {
            return hand[0];
        }
        if (allTrump)
        {
            Card card = hand[0];
            for (size_t i = 1; i <= 5; i++)
            {
                if(Card_less(card,hand[i], trump))
                {
                    card=hand[i];
                }
            }
            return card;
        }
        else
        {
            Card card = hand[0];
            for (size_t i = 1; i <= hand.size(); i++)
            {
                while(hand[i].get_suit(trump)==trump)
                {
                    i+=1;
                    if(i>hand.size())
                    {
                        return card;
                    }
                }
                if(card<hand[i])
                {
                    card=hand[i];
                }
            }
            return card;
        }
    }
    Card play_card(const Card &led_card, const std::string &trump) override
    {
        sort(hand);
        if(hand.size()==1)
        {
            return hand[0];
        }
        bool boolean =false;
        for(size_t i = 0; i< hand.size(); i++)
        {
            if(hand[i].get_suit(trump)==led_card.get_suit(trump))
            {
                boolean = true;
            }
        }
        if(boolean)
        {
            Card card = hand[0];
            for (size_t i = 1; i < hand.size(); i++)
            {
                while(hand[i].get_suit(trump)!=led_card.get_suit(trump))
                {
                    i+=1;
                    if(i>=hand.size())
                    {
                        return card;
                    }
                }
                if(Card_less(card,hand[i],trump))
                {
                    card=hand[i];
                }
            }
            return card;
        }
        else
        {
            
            Card card = hand[0];
            for (size_t i = 1; i < hand.size(); i++)
            {
                while(hand[i].get_suit(trump)==trump)
                {
                    i+=1;
                    if(i>=hand.size())
                    {
                        return card;
                    }
                }
                if(!Card_less(card,hand[i], trump))
                {
                    card=hand[i];
                }
            }
            return card;
        }
       
    }
 private: 
    string name;
    string strategy;
    vector<Card> hand;
};

class Human : public Player 
{
 public:
    Human(const string &name)
    : name(name) {}
    const string &get_name() const override
    {
        return name;
    }
   void add_card(const Card &c) override
    {
        hand.push_back(c);
    }
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const override
    {
        vector <Card> handCopy = hand;
        sort(handCopy);
        string decision;
        for (size_t i = 0; i < handCopy.size(); i++)
        {
            cout << handCopy[i] << endl;
        }
        cout << "Do you want to pass or order up?" << endl;
        cin >> decision;
        if (!(decision == "pass"))
        {
            order_up_suit = decision;
            return true;
        }
        else
        {
            return false;
        }
    }
    void add_and_discard(const Card &upcard) override
    {
        sort(hand);
        size_t idx;
        for (size_t i = 0; i < hand.size(); i++)
        {
            cout << hand[i] << endl;
        }
        cout << upcard << endl;
        cout << "Choose card to discard" << endl;
        cin >> idx;
        if (idx < hand.size())
        {        
            hand.erase(hand.begin() + idx);
            hand.push_back(upcard);
        }
    }
    Card lead_card(const string &trump) override
    {
        Card card;
        return card;
    }
    Card play_card(const Card &led_card, const string &trump) override
    {
        sort(hand);
        for (size_t i = 0; i < hand.size(); i++)
        {
            cout << hand[i] << endl;
        }
        cout << "Select a card" << endl;
        size_t idx;
        cin >> idx;
        if (idx<= hand.size())
        {
            return hand[idx];
        }
        else
        {
            cout<<"dumbass"<<endl;
            return hand[idx];
        }
    }

 private: 
    string name;
    string strategy;
    vector<Card> hand;
};

Player * Player_factory(const std::string &name, const std::string &strategy)
{
    if (strategy == "Simple")
    {
        return new Simple(name);
    }
    else if (strategy == "Human")
    {
        return new Human(name);
    }
    else
    {
        return 0;
    }
}

ostream & operator<<(std::ostream &os, const Player &p)
{
    string name = p.get_name();
    os << name;
    return os;
}
