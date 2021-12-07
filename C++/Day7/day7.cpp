#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

std::map<int,int> getFrequencyMap(std::string input , char sep)
{
    std::map<int,int> freq_map;
    std::stringstream ss(input);

    for (int num; ss >> num;) {

        if(freq_map.count(num) == 1)
        {
            freq_map[num]++;
        } else
        {
            freq_map[num] = 1;
        }

        if (ss.peek() == sep)
            ss.ignore();
    }
    return freq_map;

}
int getDistanceFuelConsumption(int distance, bool increasing_sum )
{
    if(increasing_sum)
    {
        /* Calculates the distance where the fuel consumption increases by one for each step using the sum of arithmetic sequence 
           if distance =  5 then consumption would be 1+2+3+4+5 */
        return (distance*(distance+1))/2;
    } else return distance;
}
int getMinimumFuelConsumption(std::map<int,int> crabs_freq , bool increasing_sum )
{
    int minimum_fuel = -1;
    /* Each pair has has position mapped to the number of crab at this position
       example position 1 has 5 crabs would be {1,5}*/
    for(std::pair<int,int> still_crab : crabs_freq)
    {
        int total_fuel_used = 0;

        for(std::pair<int,int> moving_crab : crabs_freq)
        {
           int distance = abs(still_crab.first - moving_crab.first);

           total_fuel_used += (getDistanceFuelConsumption(distance, increasing_sum) * moving_crab.second);

        }

        if(minimum_fuel == -1 || minimum_fuel > total_fuel_used) minimum_fuel = total_fuel_used;
    }
    return minimum_fuel;
}

int part1(std::map<int,int> crabs_freq )
{
    return getMinimumFuelConsumption(crabs_freq, false);
}

int part2( std::map<int,int> crabs_freq )
{
    return getMinimumFuelConsumption(crabs_freq, true);
}

int main()
{
    std::string inp;

    std::ifstream input("input.txt");

    if(input.fail()) std::cout << "Failed to open file";
    else {
        input >> inp;

        std::map<int,int> crabs_freq = getFrequencyMap(inp,',');

        std::cout << "Part 1: " << part1(crabs_freq) << std::endl;
        std::cout << "Part 2: " << part2(crabs_freq) << std::endl;

    }

    return 0;
}
