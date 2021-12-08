#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>

std::vector<int> getFreq(std::vector<std::string> numbers , int pos)
{
     std::vector<int> freq;
     freq.push_back(0); // 0 frequency index
     freq.push_back(0); // 1 frequency index
    for (int i = 0; i <numbers.size() ; ++i)
    {
        freq[numbers[i][pos]-'0']++;
    }
    return freq;
}
std::vector<std::string> remove(std::vector<std::string> numbers , int val, int pos)
{
    std::vector<std::string> new_nums;
    for (int i = 0; i <numbers.size() ; ++i)
    {
        if((numbers[i][pos]-'0') == val) new_nums.push_back(numbers[i]);
    }
    return new_nums;
}


int part1(std::vector<std::string> numbers)
{
    int freq[] = {0,0};
    std::string gamma_rate = "" ;
    std::string epsilon_rate = "";

    for (int i = 0; i < 12 ; ++i)
    {
        // Calculates the column freq
        for (int j = 0; j < numbers.size() ; ++j)
        {
            freq[(numbers[j][i]-'0')] ++;

        }

        if(freq[0] > freq[1])
        {
            gamma_rate+='0';
            epsilon_rate+='1';

        } else
        {
            gamma_rate+='1';
            epsilon_rate+='0';

        }
        freq[0]  = 0;
        freq[1] = 0;

    }

    std::bitset<12> gamma_bites(gamma_rate);
    std::bitset<12> epsilon_bites(epsilon_rate);

    long long gamma = gamma_bites.to_ulong();
    long long epsilon = epsilon_bites.to_ulong();

    return gamma * epsilon;

}


long long part2(std::vector<std::string> oxygen_numbers)
{
    std::vector<std::string> co2_numbers = oxygen_numbers;
    
    for (int i = 0; i < 12; ++i)
    {
        if(oxygen_numbers.size() > 1)
        {
            std::vector<int> oxygen_freq = getFreq(oxygen_numbers, i);
            int more_freq = oxygen_freq[0] > oxygen_freq[1] ? 0 : 1;
            oxygen_numbers = remove(oxygen_numbers, more_freq, i);
        }
        if(co2_numbers.size() > 1)
        {
            std::vector<int> co2_freq = getFreq(co2_numbers, i);
            int less_freq = co2_freq[0] > co2_freq[1] ? 1 : 0;
            co2_numbers = remove(co2_numbers, less_freq, i);
        }
    }
    
    //only one element should be left in each vectors
    std::bitset<12> oxygen_bites(oxygen_numbers.back());
    std::bitset<12> co2_bites(co2_numbers.back());
        
    long long oxygen = oxygen_bites.to_ulong();
    long long co2 = co2_bites.to_ulong();
        
    return oxygen*co2;

    }


int main()
{
    std::vector<std::string> c;
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {


        while(input.peek() != EOF)
        {
            std::string inp;
            input >> inp;
            c.push_back(inp);
        }

        std::cout << "Part 1: " << part1(c) << std::endl;
        std::cout << "Part 2: " << part2(c) << std::endl;
    }

    return 0;
}
