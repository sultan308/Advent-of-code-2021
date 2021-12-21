#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class player
{
    public:
    int score = 0;
    int pos;
    player(int starting)
    {
        this->pos = starting;
    }
    int move(int movment)
    {
        pos += movment;
        pos = pos%10;
        pos = pos == 0 ? 10 : pos;


    }

};
std::vector<int> incrementDice(std::vector<int>  dice)
{
    int base = dice.back();
    for (int i = 0; i < dice.size(); ++i) {
        dice[i] = base+1;
        dice[i] = dice[i] > 100 ? 1 : dice[i];
        base = dice[i];
    }
    return dice;
}


int part1(player p1,player p2)
{
    std::vector<int>  dice = {1,2,3};
    int turn = 0;
    int rolls =3;
    player p[2] = {p1,p2};
    bool game_ended = false;

    while(!game_ended)
    {
        p[turn].move(dice[0]+dice[1]+dice[2]);
        p[turn].score+=(p[turn].pos);

        if(p[turn].score >= 1000)
        {
            turn = turn == 1 ? 0 : 1;
            return (p[turn].score*rolls);
        }
        turn = turn == 1 ? 0 :1;
        dice = incrementDice(dice);
        rolls+=3;
    }

}

std::map<std::pair<std::vector<int>,std::vector<int>>, long long> splitMultiverse(std::map<std::pair<std::vector<int>,std::vector<int>>, long long> multiverses,std::vector<long long> &  wins ,int turn)
{
    std::map<std::pair<std::vector<int>,std::vector<int>>, long long > splitted_multiverses;

    for(std::pair<std::pair<std::vector<int>,std::vector<int>>, long long > verse : multiverses)
    {
        for (int dice1 = 1; dice1 < 4; ++dice1) {

            for (int dice2 = 1; dice2 < 4; ++dice2) {

                for (int dice3 = 1; dice3 < 4; ++dice3) {

                    int player_pos = verse.first.first[turn] + dice1 + dice2 +dice3;

                    int corrected_pos = (player_pos%10);
                    corrected_pos = corrected_pos == 0 ? 10 : corrected_pos;

                    int player_score = verse.first.second[turn] + corrected_pos;

                    if(player_score > 20)
                    {
                        wins[turn]+= verse.second;
                    } else
                    {
                        std::pair<std::pair<std::vector<int>,std::vector<int>>, long long > new_verse = verse;
                        new_verse.first.first[turn] = player_pos;
                        new_verse.first.second[turn] = player_score;

                        if(splitted_multiverses.find(new_verse.first) == splitted_multiverses.end())
                        {
                            splitted_multiverses[new_verse.first] = new_verse.second;
                        }
                        else
                        {
                            splitted_multiverses[new_verse.first] += new_verse.second;
                        }

                    }
                }
            }
        }
    }
    return splitted_multiverses;
}
std::vector<long long> part2(std::vector<player> players)
{
    std::vector<long long> wins = {0};

    //key {positions , scores} = value frequency
    std::map<std::pair<std::vector<int>,std::vector<int>>, long long> multiverses;
    multiverses[{{players[0].pos,players[1].pos},{players[0].score,players[0].score}}] = 1;

    int turn =0;
    while(!multiverses.empty())
    {
        multiverses = splitMultiverse(multiverses,wins,turn);
        turn = turn == 1 ? 0 : 1;

    }


    return wins;
}

int main() {
    //input numbers
    player player1 = player(4);
    player player2 = player(1) ;

    std::vector<long long> wins = part2({player1, player2});



    std::cout << "Part 1 : " << part1(player1,player2)<< std::endl;
    std::cout << "Part 2 : "<< std::endl;
    std::cout << "Winner score : "<< (wins[1] > wins[0] ? wins[1] : wins[0]) << std::endl;
    std::cout << "Loser score : "<< (wins[1] < wins[0] ? wins[1] : wins[0]) << std::endl;

    return 0;
}
