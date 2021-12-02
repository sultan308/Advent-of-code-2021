#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


int part1(std::vector<std::pair<std::string,int>> instructions)
{
    int height, depth;
    height = 0;
    depth = 0;
    for( std::pair<std::string,int> inst : instructions)
    {
        if(inst.first == "down")
        {
            depth+=inst.second;
        }
        else if(inst.first == "up")
        {
            depth-=inst.second;
        }
        else if(inst.first == "forward")
        {
            height+=inst.second;
        }
    }
    return height * depth;
}

int part2(std::vector<std::pair<std::string,int>> instructions)
{
    int height, depth ,aim;
    height = 0;
    depth = 0;
    aim = 0;
    for( std::pair<std::string,int> instruction : instructions)
    {
        if(instruction.first == "down")
        {
            aim += instruction.second;
        }
        else if(instruction.first == "up")
        {
            aim -= instruction.second;
        }
        else if(instruction.first == "forward")
        {
            height += instruction.second;
            depth += instruction.second * aim;
        }
    }
    return height * depth;

}
int main()
{
    std::vector<std::pair<std::string,int>> instructions;
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {


        while(input.peek() != EOF)
        {
            std::pair<std::string,int> instruction;
            input >> instruction.first >> instruction.second;
            instructions.push_back(instruction);


        }

        std::cout << "Part 1: " << part1(instructions) << std::endl;
        std::cout << "Part 2: " << part2(instructions) << std::endl;
    }

    return 0;
}
