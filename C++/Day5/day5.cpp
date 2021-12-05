#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

int mapPartOne[1000][1000] = {0};
int mapPartTwo[1000][1000] = {0};

std::vector<int> splitBy(std::string st , char sep)
{
    std::vector<int> splited ;
    std::stringstream ss(st);

    for (int num; ss >> num;) {

        splited.push_back( num);
        if (ss.peek() == sep)
            ss.ignore();

    }
    return splited;

}

void plotLine(std::pair<int,int> startPoint, std::pair<int,int>endPoint)
{

        int xDiff = endPoint.first - startPoint.first  ;
        int yDiff = endPoint.second - startPoint.second ;

        bool isHorizontal = (xDiff == 0 || yDiff == 0);

        int xIncrement = xDiff == 0 ? 0 : (xDiff / abs(xDiff));
        int yIncrement = yDiff == 0 ? 0 :  (yDiff/ abs(yDiff));

        startPoint.first-=xIncrement;
        startPoint.second-=yIncrement;

        while((startPoint.first != endPoint.first ) || (startPoint.second != endPoint.second))
        {
            startPoint.first+=xIncrement;
            startPoint.second+=yIncrement;

            //adds vertical and horizontal lines only to the 2d array for part one
            if(isHorizontal) mapPartOne[startPoint.first][startPoint.second]++;

            //adds all lines only to the 2d array for part two
            mapPartTwo[startPoint.first][startPoint.second]++;

        }




}
int part1()
{
    int total = 0;
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j <1000 ; ++j)
        {
            if(mapPartOne[i][j] > 1) total++;

        }

    }
    return total;
}


int part2()
{
    int total = 0;
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j <1000 ; ++j)
        {
            if(mapPartTwo[i][j] > 1) total++;

        }

    }
    return total;
}


int main()
{
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {


        while(input.peek() != EOF)
        {
            std::pair<int,int> startPoint,endPoint;
            std::vector<int> res;
            std::string buffer;
            input >> buffer;
            res = splitBy(buffer,',');

            startPoint.first = res[0];
            startPoint.second = res[1];

            input >> buffer >> buffer;

            res = splitBy(buffer,',');

            endPoint.first = res[0];
            endPoint.second = res[1];

            plotLine(startPoint, endPoint);



        }

        std::cout << "Part 1: " << part1() << std::endl;
        std::cout << "Part 2: " << part2() << std::endl;
    }

    return 0;
}
