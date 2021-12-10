#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>


bool isOpeningBracket(char bracket)
{
    return bracket == '<' || bracket == '[' || bracket == '{' || bracket == '(';
}
char getClosingBracket(char opening_bracket)
{
    std::map<char,char> brackets= {{ '<','>',},{'{','}'},{'[',']'},{'(',')'}};
    return brackets[opening_bracket];
}

long long part1(std::vector<std::string> lines)
{

    std::map<char,int> bracket_values= {{')',3},{']',57},{'}',1197},{'>', 25137}};
    int score = 0;

    for(std::string line : lines)
    {
        std::vector<char> next_stack;

        for(char bracket : line)
        {
            if(isOpeningBracket(bracket))
            {
                next_stack.push_back(getClosingBracket(bracket));
            }
            else
            {
               if(bracket != next_stack.back())
               {
                   score += bracket_values[bracket];
                   break;
               }

               next_stack.pop_back();
            }
        }

    }



    return score;
}
//


long long part2(std::vector<std::string> lines)

{
    std::map<char,int> bracket_values= {{')',1},{']',2},{'}',3},{'>', 4}};
    std::vector<long long > scores;


    for(std::string line : lines)
    {
        std::vector<char> next_stack;
        bool valid_line = true;
        long long line_score = 0;

        for( char bracket : line)
            {

                if(isOpeningBracket(bracket))
                {
                    next_stack.push_back(getClosingBracket(bracket));
                }
                else
                {
                    if(bracket != next_stack.back())
                    {
                        valid_line = false;
                        break;
                    }

                    next_stack.pop_back();
                }

            }

            if(valid_line && next_stack.size() != 0)
            {
                while(next_stack.size() > 0)
                {
                    line_score = line_score*5;
                    line_score += bracket_values[next_stack.back()];
                    next_stack.pop_back();

                }
                scores.push_back(line_score);
            }

        }
        std::sort(scores.begin(),scores.end());


        return scores[(scores.size())/2];
}


int main()
{
    std::string line;
    std::vector<std::string> lines;
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {

        while(input.peek() != EOF)
        {
            input >> line;
            lines.push_back(line);

        }

        std::cout << "Part 1: " << part1(lines) << std::endl;
        std::cout << "Part 2: " << part2(lines) << std::endl;
    }

    return 0;
}
