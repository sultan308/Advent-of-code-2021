#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<int> splitBy(std::string st , char sep)
{
    std::vector<int> splited ;
    std::stringstream ss(st);

    for (int num; ss >> num;) {

        splited.push_back(num);
        if (ss.peek() == sep)
            ss.ignore();
    }
    return splited;

}
/*
 * Finds a cell with a given value and returns it position
 * If it doesn't exist returns {-1,-1}
 */
std::pair<int,int> findCell(int num,std::vector<std::vector<int>>  board)
{
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
        {
            if(board[i][j] == num) return {i,j};
        }

    }
    return {-1,-1};
}
/*
 * Searches for a row where all cell values are = -1
 * if found returns true otherwise returns false
 */
bool checkRows(std::vector<std::vector<int>>  board)
{
    bool won;
    for(std::vector<int> row : board)
    {
        won = true;
        for(int cell : row)
        {
            if(cell != -1)
            {
                won = false;
                break;
            }
        }
        if(won) return won;
    }
    return won;
}
/*
 * Searches for a Columns where all cell values are = -1
 * if found returns true otherwise returns false
 */
bool checkCols(std::vector<std::vector<int>>  board)
{
    bool won;
    for (int i = 0; i < 5; ++i) {
        won = true;
        for (int j = 0; j < 5 ; ++j)
        {
            if(board[j][i] != -1)
            {
                won = false;
                break;
            }

        }
        if(won) return won;
    }
    return won;
}
/*
 * Searches for a Columns or row where all cell values are = -1
 * if found returns true otherwise returns false
 */
bool won(std::vector<std::vector<int>>  board)
{
    return checkRows(board) || checkCols(board);
}
/*
 * Calcultes the sum of cell values where cells doesn't = -1
 * returns sum
 */
int unMarkedSum(std::vector<std::vector<int>>  board)
{
    int sum = 0;
    for(std::vector<int> row : board)
    {

        for(int cell : row)
        {
            if(cell !=-1) sum+=cell;
        }

    }
    return sum;
}

int part1(std::vector<int> deck,std::vector<std::vector<std::vector<int>>> boards)
{
    for(int card : deck)
    {
        for (int i = 0; i < boards.size(); ++i) {

            std::pair<int,int> pos = findCell(card,boards[i]);
            if(pos.first != -1)
            {
                //if a cell exists with the card value the cell values is changed to -1 indicating that is has been crossed
                boards[i][pos.first][pos.second] = -1;

                if (won(boards[i])) {
                    //once a wining column or row is found the unmarked cells total * the number of the cards drawn is returned
                    return unMarkedSum(boards[i]) * card;
                }
            }

        }
    }
    return -1;

}
//


int part2(std::vector<int> deck,std::vector<std::vector<std::vector<int>>> boards)
{
    //holds the boards status -1 if the board won 0 other wise
    int boards_status[100] = {0};


    int boardsWon = 0;

    for(int card : deck)
    {
        for (int i = 0; i < boards.size(); ++i) {

            //only if the board hasn't won yet
            if(boards_status[i] != -1)
            {

                std::pair<int, int> pos = findCell(card, boards[i]);

                if (pos.first != -1) {
                    //if a cell exists with the card value the cell values is changed to -1 indicating that is has been crossed

                    boards[i][pos.first][pos.second] = -1;
                    
                    if (won(boards[i])) {

                        boardsWon++;
                        boards_status[i] = -1;

                        //once all boards has wining column or row the unmarked cells total * the number of the cards drawn is returned
                        if(boardsWon == boards.size()) return unMarkedSum(boards[i]) * card;
                    }
                }
            }
        }
    }
    return -1;

}


int main()
{
    std::string draw;
    std::vector<std::vector<std::vector<int>>> boards;
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {
        input >> draw;
        std::vector<int> deck = splitBy(draw,',');

        while(input.peek() != EOF)
        {
            std::vector<std::vector<int>>  board;
            for (int i = 0; i < 5; ++i)
            {
                std::vector<int> row;
                for (int j = 0; j < 5; ++j)
                {
                    int cell;
                    input >> cell;
                   row.push_back(cell) ;
                }
                board.push_back(row);
            }
            boards.push_back(board);

        }

       std::cout << "Part 1: " << part1(deck,boards) << std::endl;
       std::cout << "Part 2: " << part2(deck,boards) << std::endl;
    }

    return 0;
}
