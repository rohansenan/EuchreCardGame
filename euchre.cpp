#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
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
    int get_tricks()
    {
        return tricks_won;
    }
    int get_score()
    {
        return team_score;
    }
    vector<Player*> get_players_in_team()
    {
        return players;
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
                cout << "march!" << endl;
            }
        }
        else
        {
            if (tricks_won >= 3)
            {
                team_score += 2;
                cout << "euchred!" << endl;
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
    Game (Player *p1, Player *p2, Player *p3, Player *p4, istream& pack_input)
    : team1(p1, p3, false), team2(p2, p4, false), pack(pack_input), dealerIndex(0) 
    {
        players.push_back(p1);
        players.push_back(p2);
        players.push_back(p3);
        players.push_back(p4);
    }
    int get_team1_score()
    {
        team1.get_score();
    }
    int get_team2_score()
    {
        team2.get_score();
    }
    int get_team1_tricks()
    {
        team1.get_tricks();
    }
    int get_team2_tricks()
    {
        team2.get_tricks();
    }
    Player * get_player(int player_index)
    {
        return players[player_index];
    }
    vector<Player*> get_team1_players()
    {
        return team1.get_players_in_team();
    }
    vector<Player*> get_team2_players()
    {
        return team2.get_players_in_team();
    }
    Card get_up_card()
    {
        return upCard;
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
        else
        {
            cout << "error player is not in any team" << endl;
        }
    }
    void add_score_to_teams()
    {
        team1.add_score(team1.get_tricks());
        team2.add_score(team2.get_tricks());
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
    int get_dealer_index()
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
        upCard = pack.deal_one();
    }
    void set_upCard(Card card)
    {
        upCard = card;
    }
    bool makingTrump(string trump, int round)
    {
        for (size_t i = 0; i < 4; i++)
        {
            bool is_dealer = false;
            if (i == dealerIndex)
            {
                is_dealer = true;
            }
            if (players[i]->make_trump(upCard, is_dealer, round, trump))
            {
                cout << players[i]->get_name() << " orders up " << trump << endl;
                players[dealerIndex]->add_and_discard(upCard);
                return true;
            }
            else
            {
                cout << players[i]->get_name() << " passes" << endl;
            }
        }
        return false;
    }
    void play_hand(string trump, int &leader_index)
    {
        size_t led_index = leader_index;
        if (led_index > players.size())
        {
            led_index = led_index % players.size();
        }
        Card led_card = players[led_index]->lead_card(trump);
        cout << led_card << " led by " << players[led_index]->get_name() << endl;
        int j = 0;
        Card winner = led_card;
        int winner_index = led_index;
        for (size_t i = led_index + 1; j < 3; i++)
        {
            if (i > players.size())
            {
                i = i % players.size();
            }
            Card played_card = players[i]->play_card(led_card, trump);
            cout << played_card << " played by " << players[i]->get_name() << endl;
            if (Card_less(winner, played_card, led_card, trump))
            {
                winner = played_card;
                winner_index = i;
            }
        }
        cout << players[winner_index]->get_name() << " takes the trick" << endl;
        add_tricks_won(players[winner_index]);
        leader_index = winner_index;
    }
};

int main (int argc, char *argv[])
{
    if (argc != 12 && atoi(argv[3]) < 1 || atoi(argv[3]) > 100 && argv[2] != "shuffle" 
    || argv[2] != "noshuffle" && argv[5] != "Simple" || argv[5] != "Human" 
    && argv[7] != "Simple" || argv[7] != "Human" && argv[9] != "Simple" 
    || argv[9] != "Human" && argv[11] != "Simple" || argv[11] != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }

    int max_points = atoi(argv[3]);

    string pack_filename = argv[1];
    ifstream fin(pack_filename);

    if (!fin.is_open())
    {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }

    for (int i = 0; i < 12; i++)
    {
        cout << argv[i] << " ";
    }
    cout << endl;

    Player *p1 = Player_factory(argv[4], argv[5]);
    Player *p2 = Player_factory(argv[6], argv[7]);
    Player *p3 = Player_factory(argv[8], argv[9]);
    Player *p4 = Player_factory(argv[10], argv[11]);

    stringstream pack_file;
    pack_file << pack_filename;

    Game game(p1, p2, p3, p4, pack_file);

    vector<Player*> team1_players = game.get_team1_players();
    vector<Player*> team2_players = game.get_team2_players();

    while (game.get_team1_score() < max_points && game.get_team2_score() < max_points)
    {
        int hand = 0;
        cout << "Hand " << hand << endl;
        int tricks = 0;
        cout << game.get_player(game.get_dealer_index())->get_name() << " deals" 
            << endl;
        game.dealCards();
        cout << game.get_up_card() << " turned up" << endl;
        string trump;
        
        bool trumpMade = game.makingTrump(trump, 1);

        if (!trumpMade)
        {
            game.makingTrump(trump, 2);
        }
        cout << endl;

        int leader_index = game.get_dealer_index() + 1;

        while (tricks < 5)
        {
            game.play_hand(trump, leader_index);
            cout << endl;
            tricks++;
        }

        if (game.get_team1_tricks() > game.get_team2_tricks())
        {
            cout << team1_players[0]->get_name() << " and " 
            << team1_players[1]->get_name() << " win the hand" << endl;
        }
        else
        {
            cout << team2_players[0]->get_name() << " and " 
            << team2_players[1]->get_name() << " win the hand" << endl;
        }
        game.add_score_to_teams();
        int team1_score = game.get_team1_score();
        int team2_score = game.get_team2_score();
        cout << team1_players[0]->get_name() << " and " << team1_players[1]->get_name()
        << " have " << team1_score << " points" << endl;
        cout << team2_players[0]->get_name() << " and " << team2_players[1]->get_name()
        << " have " << team2_score << " points" << endl;
        cout << endl;
        hand++;
    }
    if (game.get_team1_score() >= max_points)
    {
        cout << team1_players[0]->get_name() << " and " << team1_players[1]->get_name()
        << " win!" << endl;
    }
    else
    {
        cout << team2_players[0]->get_name() << " and " << team2_players[1]->get_name()
        << " win!" << endl;
    }
}
