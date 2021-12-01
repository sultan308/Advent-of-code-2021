#include <iostream>
#include <fstream>
#include <vector>


/*
 * iterates over the input
 * keeps the previous value
 * if the current index value is more than the previous index value it adds one to the counter
 * returns counter
*/
int part1(std::vector<int> sonar)
{
    int cur , prev ,counter;

    counter = 0;
    prev = sonar[0];

    for (int i = 1; i < sonar.size() ; i++)
    {
        cur = sonar[i];
        if(cur > prev) counter++;
        prev = cur;
    }
    return counter;
}
//

/*
 * iterates over the input while the current index has two next elements
 * for each index adds the value and the next two index ie (index+1 & index+2) values up
 * keeps the previous value
 * if the current index total is more than the previous total it adds one to the counter
 * returns counter
*/
int part2(std::vector<int> sonar)
{
    int cur , prev ,counter;

    counter = 0;
    prev = sonar[0] + sonar[1] + sonar[2];

    for (int i = 1; i < sonar.size()-2 ; i++)
    {
        cur = sonar[i] + sonar[i+1] + sonar[i+2];
        if(cur > prev) counter++;
        prev = cur;
    }
    return counter;
}
int main()
{

    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {
        std::vector<int> sonar;
        int next;
        while(input.peek() != EOF)
        {
            input >> next;
            sonar.push_back(next);
        }

        std::cout << "Part 1: " << part1(sonar) << std::endl;
        std::cout << "Part 2: " << part2(sonar) << std::endl;
    }

    return 0;
}
