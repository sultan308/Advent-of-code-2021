#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

void updateElementFreq(std::map<char,long long> &char_freq, char element, long long freq)

{
    if (char_freq.find(element) == char_freq.end()) {

        char_freq[element] = freq;
    }
    else {
        char_freq[element]+= freq;
    }


}
void updatePairFreq(std::map<std::string,long long> &pair_freq,std::string pair,long long freq)

{
    if (pair_freq.find(pair) == pair_freq.end()) {

        pair_freq[pair] = freq;
    }
    else {
        pair_freq[pair] += freq;
    }


}
void solve(std::map<std::string,char> &polymer_template , std::map<std::string,long long> pair_freq, std::map<char,long long>& elements_freq, long long steps_left)
{
    steps_left--;
    std::map<std::string,long long> new_pair_freq;
    for(auto s : pair_freq)
    {
        char adj_element = polymer_template[s.first];

        std::string pair = "";

        pair += s.first[0];
        pair += adj_element;
        updatePairFreq(new_pair_freq,pair,s.second);

        pair = "";
        pair += adj_element;
        pair += s.first[1];
        updatePairFreq(new_pair_freq,pair,s.second);

        updateElementFreq(elements_freq, adj_element, s.second);
    }

    if(steps_left == 0) return;
    solve(polymer_template, new_pair_freq, elements_freq, steps_left);

}

std::map<std::string,long long> getPairFreq(std::string polymer)
{
    std::map<std::string,long long> pair_freq;

    for(int i = 0 ; i < polymer.size() - 1; ++i)
    {
        std::string key = "";
        key += polymer[i];
        key += polymer[i + 1];
        updatePairFreq(pair_freq,key,1);
    }

    return pair_freq;
}

std::pair<long long , long long> findMinMax(std::map<char,long long>& element_freq)
{
    std::pair<long long , long long> min_max;
    min_max.first = LLONG_MAX;
    min_max.second = 0;
    for(std::pair<char, long long> element : element_freq)
    {
        if(element.second < min_max.first) min_max.first = element.second;
        if(element.second > min_max.second) min_max.second = element.second;
    }
    return min_max;
}

long long part1(std::map<std::string,char> polymer_template, std::string polymer, std::map<char,long long> element_freq)
{
    std::map<std::string,long long> pair_freq = getPairFreq(polymer);

    solve(polymer_template, pair_freq, element_freq, 10);

    std::pair<long long , long long> min_max = findMinMax(element_freq);

    return (min_max.second - min_max.first);
}

long long part2(std::map<std::string,char> polymer_template, std::string polymer, std::map<char,long long> element_freq)
{
    std::map<std::string,long long> pair_freq = getPairFreq(polymer);

    solve(polymer_template, pair_freq, element_freq, 40);

    std::pair<long long , long long> min_max = findMinMax(element_freq);

    return (min_max.second - min_max.first);
}

int main()
{

    std::map<std::string,char> polymer_template;
    std::map<char,long long> element_freq;
    std::string polymer;


    std::string inp;
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {

        input >> polymer;
        for(char element : polymer)
        {
            updateElementFreq(element_freq, element, 1);
        }
        while(input.peek() != EOF)
        {
            input >> inp;
            std::pair<std::string,char> pair_element;
            pair_element.first = inp;

            input >>inp >> inp;

            pair_element.second = inp[0];
            polymer_template.insert(pair_element);


        }

    }
    std::cout << "Part 1 : " << part1(polymer_template, polymer, element_freq) << std::endl;
    std::cout << "Part 2 : " << part2(polymer_template, polymer, element_freq) << std::endl;

    return 0;
}
