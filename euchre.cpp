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
    vector<Player*> players;
    int tricks_won = 0;
    int team_score = 0;
    bool is_attack = false;

public:
    void add_player_to_team(Player *player)
    {
        players.push_back(player);
    }
    void set_attack()
    {
        is_attack = true;
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
    vector<Player*> players;
    Card upCard;
    Pack pack;
    Team team1;
    Team team2;

public:
    void add_player(Player *player)
    {
        players.push_back(player);
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
    void add_to_team(int teamNumber, Player *player)
    {
        if (teamNumber == 1)
        {
            team1.add_player_to_team(player);
        }
        else if (teamNumber == 2)
        {
            team2.add_player_to_team(player);
        }
    }
    void shuffleDeck()
    {
        pack.shuffle();
    }
    void dealCards()
    {
        for (int j = 0; j < 5; j++)
        {
            for (size_t i = 0; i < players.size(); i++)
            {
                players[i]->add_card(pack.deal_one());
            }
        }
    }
    void set_upCard(Card card)
    {
        upCard = card;
    }
};


