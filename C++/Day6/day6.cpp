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

long long getPopulationSizeAfter( std::vector<int> population , int days )
{
   /*Every index represents a day 
    *Every value represents the number of offspring to be the added to population on the following day*/
    long long days_arr[256] = {0};

    long long population_size = population.size();
    
    //Adds the starting fish population to the days array
    for(int fish : population) days_arr[fish - 1]++;

    for (int i = 0; i < days; ++i)
    {
        if(days_arr[i] > 0 )
        {
            if(i+7 < days) days_arr[i + 7] += days_arr[i]; // Parent next offspring production
            if(i+9 < days) days_arr[i + 9] += days_arr[i];  // Child fish next offspring production
            if(i+1 < days) population_size += days_arr[i]; // children to be added on the population on the following day

        }
    }

    return population_size;

};

long long part1(std::vector<int> population)
{
    return getPopulationSizeAfter(population,80);
}
long long part2(std::vector<int> population)
{
    return getPopulationSizeAfter(population,256);
}

int main()
{
    std::string inp;

    std::ifstream input("input.txt");

    if(input.fail()) std::cout << "Failed to open file";
    else {
        input >> inp;

        std::vector<int> population = splitBy(inp,',');

        std::cout << "Part 1: " << part1(population) << std::endl;
        std::cout << "Part 2: " << part2(population) << std::endl;

    }

    return 0;
}
