#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>


std::pair<int,int> split(std::string s)
{
    std::string splitter = ",";
    std::pair<int,int> coordinates ;

    int split_pos = s.find(splitter);


    coordinates.first = stoi(s.substr(0, split_pos));

    s.erase(0, split_pos + 1);

    coordinates.second = stoi(s);

    return coordinates;


};

std::set<std::pair<int,int>> foldX(int x ,std::set<std::pair<int,int>> &manual,std::pair<int,int>&size)
{
    std::set<std::pair<int,int>>new_manual;
    size.first-=(x+1);
    ;
    for(std::pair<int,int> cor : manual)
    {

        if(cor.first > x)
        {
            int new_x = size.first-(cor.first-(x+1));
            new_manual.insert({new_x, cor.second});;
        } else
        {
            new_manual.insert(cor);
        }
    }
    return new_manual;
}

std::set<std::pair<int,int>> foldY(int y ,std::set<std::pair<int,int>>& manual,std::pair<int,int>&size)
{
    std::set<std::pair<int,int>> new_manual;
    size.second-=(y+1);

    for(std::pair<int,int> cor : manual)
    {
        if(cor.second > y)
        {
            int new_y = size.second-(cor.second-(y+1));
            new_manual.insert({cor.first, new_y});;
        } else
        {
            new_manual.insert(cor);
        }
    }
    return new_manual;
}
void renderOutput(std::set<std::pair<int,int>> manual,std::pair<int,int>size)
{
    std::vector<std::vector<std::string>> output;
    for (int i = 0; i <= size.second ; ++i) {
        std::vector<std::string> row;
        for (int j = 0; j <= size.first ; ++j) {
            row.push_back("  ");
        }
        output.push_back(row);
    }
    for(auto cor : manual)
    {
        output[cor.second][cor.first] = "xx";
    }
    for (int i = 0; i < output.size(); ++i) {
        for (int j = 0; j < output[i].size(); ++j)
        {
            std::cout << output[i][j];
        }
        std::cout << std::endl;
    }
}

int part1(std::set<std::pair<int,int>> manual ,std::vector<std::pair<char,int>> folds,std::pair<int,int> size)
{
    manual = foldX(folds[0].second,manual,size);
    return manual.size();
}
void part2(std::set<std::pair<int,int>> manual ,std::vector<std::pair<char,int>> folds,std::pair<int,int> size)
{
    for(std::pair<char,int> fold : folds)
    {
        if(fold.first == 'x')
        {
            manual = foldX(fold.second,manual,size);
        } else if(fold.first == 'y')
        {
            manual = foldY(fold.second,manual,size);
        }
    }

    std::cout << "Part 2 :" << std::endl;
    renderOutput(manual,size);


}

int main() {

    std::ifstream input("input.txt");

    std::pair<int,int> size = {0,0};
    std::vector<std::pair<char,int>> folds;
    std::set<std::pair<int,int>> manual;

    if(input.fail()) std::cout << "Failed to open file";
    else {

        std::map<std::string,std::set<std::string>> adjacency_map;
        while(input.peek() != EOF)
        {
            std::string line;
            input >> line;
            if(line[0] >= '0' && line[0] <= '9')
            {
                std::pair<int,int> cor =  split(line);
                manual.insert(cor);

                //keeps track of the largest x and y
                size.first = size.first < cor.first ? cor.first : size.first;
                size.second = size.second < cor.second ? cor.second : size.second;

            } else if(line[0] == 'x' || line[0] == 'y' )
            {
                std::pair<char,int> fold;
                fold.first = line[0];
                line.erase(0, 2);
                fold.second = stoi(line);
                folds.push_back(fold);
            }

        }



        std::cout << "Part 1 : " << part1(manual,folds,size)<< std::endl;

        part2(manual,folds,size);

    }

    return 0;
}
