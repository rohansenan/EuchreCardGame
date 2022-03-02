#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
#include "Pack.h"
#include "Player.h"

using namespace std;

class Team
{
private:
    int tricks_won;
    int team_score;
    bool is_attack;
    vector<Player*> players;

public:
    Team (Player *p1, Player *p2, bool is_attack)
    : tricks_won(0), team_score(0), is_attack(is_attack)
    {
        players.push_back(p1);
        players.push_back(p2);
    }
    void set_attack()
    {
        is_attack = true;
    }
    void set_defense()
    {
        is_attack = false;
    }
    void add_tricks_won()
    {
        tricks_won++;
    }
    void add_score(int tricks_won)
    {
        if (is_attack)
        {
            if (tricks_won == 3 || tricks_won == 4)
            {
                team_score++;
            }
            else if (tricks_won == 5)
            {
                team_score += 2;
            }
        }
        else
        {
            if (tricks_won >= 3)
            {
                team_score += 2;
            }
        }
    }
    bool is_player_here(Player *player)
    {
        for (size_t i = 0; i < players.size(); i++)
        {
            if (players[i] == player)
            {
                return true;
            }
        }
        return false;
    }
    void clear_trick_count()
    {
        tricks_won = 0;
    }
};

class Game 
{
private:
    Team team1;
    Team team2;
    Pack pack;
    int dealerIndex;
    vector<Player*> players;
    Card upCard;

public:
    Game (Player *p1, Player *p2, Player *p3, Player *p4)
    : team1(p1, p3, false), team2(p2, p4, false), pack(), dealerIndex(0) 
    {
        players.push_back(p1);
        players.push_back(p2);
        players.push_back(p3);
        players.push_back(p4);
    }
    Game (Player *p1, Player *p2, Player *p3, Player *p4, istream& pack_input)
    : team1(p1, p3, false), team2(p2, p4, false), pack(pack_input), dealerIndex(0) 
    {
        players.push_back(p1);
        players.push_back(p2);
        players.push_back(p3);
        players.push_back(p4);
    }
    void add_tricks_won(Player *player)
    {
        if (team1.is_player_here(player))
        {
            team1.add_tricks_won();
        }
        else if (team2.is_player_here(player))
        {
            team2.add_tricks_won();
        }
    }
    void reset_tricks()
    {
        team1.clear_trick_count();
        team2.clear_trick_count();
    }
    void shuffleDeck()
    {
        pack.shuffle();
    }
    void nextDealer()
    {
        dealerIndex++;
        if (dealerIndex >= players.size())
        {
            dealerIndex = dealerIndex % players.size();
        }
    }
    int getDealerIndex()
    {
        return dealerIndex;
    }
    void dealCards()
    {
        int j = 0;
        for (size_t i = dealerIndex + 1; j < 2; i + 2)
        {
            size_t k = i;
            if (k >= players.size())
            {
                k = k % players.size();
            }
            players[k]->add_card(pack.deal_one());
            players[k]->add_card(pack.deal_one());
            players[k]->add_card(pack.deal_one());
            size_t n = i + 1;
            if (n >= players.size())
            {
                n = n % players.size();
            }
            players[n]->add_card(pack.deal_one());
            players[n]->add_card(pack.deal_one());
            j++;
        }
        j = 0;
        for (size_t i = dealerIndex + 1; j < 2; i + 2)
        {
            size_t k = i;
            if (k >= players.size())
            {
                k = k % players.size();
            }
            players[k]->add_card(pack.deal_one());
            players[k]->add_card(pack.deal_one());
            size_t n = i + 1;
            if (n >= players.size())
            {
                n = n % players.size();
            }
            players[n]->add_card(pack.deal_one());
            players[n]->add_card(pack.deal_one());
            players[n]->add_card(pack.deal_one());
        }
        nextDealer();
        upCard = pack.deal_one();
    }
    void set_upCard(Card card)
    {
        upCard = card;
    }
};

int main (int argc, char *argv[])
{

}
