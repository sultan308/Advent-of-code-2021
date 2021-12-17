#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>


std::vector<int> splitBy(std::string st)
{
    std::vector<int> splited ;
    std::stringstream ss(st);

    for (int num; ss >> num;) {

        splited.push_back(num);
        if (ss.peek() == '.')
            ss.ignore();
        if (ss.peek() == '.')
            ss.ignore();
    }
    return splited;

}
bool isValid(int x,int y,std::pair<int,int> x_bounds,std::pair<int,int> y_bounds)
{
    std::pair<int,int> current = {x,y};

    bool found = false;

    while(!found)
    {
        if(current.second < y_bounds.first) break;
        if((current.first >= x_bounds.first && current.first <= x_bounds.second) && ( current.second >= y_bounds.first && current.second <= y_bounds.second) )
        {
            found = true;
        } else
        {
            int x_inc = 0;
            if(x > 0) x_inc = -1;
            if(0 > x) x_inc = 1;
            x+= x_inc;
            y--;

            current.first+=x;
            current.second+=y;

        }
    }

    return found;
}
std::vector<int> getXValues(int x_upper_bound)
{
    std::vector<int> x_values;

    for(int x = 1; x <= x_upper_bound ; x++)
    {
        x_values.push_back(x);
    }

    return x_values;
}
std::vector<int> getYValues(int y_lower_bound)
{
    std::vector<int> y_values;

    for (int y = y_lower_bound; y < (y_lower_bound*-1)  ; ++y)
    {
        y_values.push_back(y);
    }

    return y_values;
}
//For this to work y's lower bound must be less than 0;

int part1(int y_lower_bound)
{

    return (y_lower_bound*(y_lower_bound+1))/2;
}
int part2(std::pair<int,int> x_bounds,std::pair<int,int> y_bounds)
{
    std::vector<int> x_values = getXValues(x_bounds.second);
    std::vector<int> y_values = getYValues(y_bounds.first);

    int counter = 0;

    for(int x : x_values)
    {
        for(int y : y_values)
        {
            if(isValid(x,y,x_bounds,y_bounds)) counter++;
        }
    }
    return counter;
}

int main()
{
    std::string inp;
    std::pair<int,int> x_bounds;
    std::pair<int,int> y_bounds;
    std::ifstream input("input.txt");

    if(input.fail()) std::cout << "Failed to open file";
    else {

        std::string delimiter = "..";

        
        input >> inp >> inp >> inp;

        inp.erase(0,2);

        int pos = inp.find(delimiter);
        x_bounds.first = std::stoi(inp.substr(0, pos));


        inp.erase(0,pos+delimiter.size());
        x_bounds.second = std::stoi(inp.substr(0, inp.find(',')));

        input >> inp;

        inp.erase(0,2);
        pos = inp.find(delimiter);
        y_bounds.first = std::stoi(inp.substr(0, pos));
        inp.erase(0,pos+delimiter.size());
        y_bounds.second = std::stoi(inp);






        std::cout << "Part 1: " << part1(y_bounds.first) << std::endl;
        std::cout << "Part 2: " << part2(x_bounds,y_bounds) << std::endl;

    }

    return 0;
}
