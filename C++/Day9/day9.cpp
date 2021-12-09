#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>



class Point
{
public:

    int value;
    // holds all adjacent points
    std::vector<Point * > adjacent ;

    // used for the dfs search when finding basins.
    bool visited = false;

    Point(int val)
    {
        value = val;

    }
    //Checks if the point is a low point ie all adjacent points has larger values.
    bool isLowPoint()
    {
        for(Point* adj_point : adjacent )
        {
            if(adj_point->value <= this-> value) return false;
        }
        return true;
    }
};
//DFS to find basin size stops when it reaches 9 or a lower value
int findBasinSize(Point* point)
{
    int size = 1;
    //Marks the point as visited to avoid counting the same point twice;
    point->visited = true;
    for(Point* adj_point : point->adjacent)
    {
        if(!adj_point->visited && adj_point->value < 9 && adj_point->value > point->value )
        {
            size+=findBasinSize(adj_point);
        }
    }
    
    return size;
}

int part1(std::vector<std::vector<Point>> height_map)
{
    int total = 0;
    for (int i = 0; i < height_map.size(); ++i) {
        for (int j = 0; j < height_map[i].size(); ++j)
        {
            if(height_map[i][j].isLowPoint()) total+= (height_map[i][j].value+1) ;
        }
    }
    return total;
}
int part2(std::vector<std::vector<Point>> height_vec)
{
    std::vector<int> sizes ;
    for(std::vector<Point> row : height_vec)
    {
        for(Point p: row)
        {
            if(p.isLowPoint())sizes.push_back(findBasinSize(&p));
        }
    }
    std::sort(sizes.begin(),sizes.end());
    return (sizes[sizes.size()-3]*sizes[sizes.size()-2]*sizes[sizes.size()-1]);


}

int main()
{
    std::string inp;
    std::vector<std::vector<Point>> height_vec;


    std::ifstream input("input.txt");

    if(input.fail()) std::cout << "Failed to open file";
    else {

        while (input.peek() != EOF)
        {
            input >> inp;
            std::vector<Point> height_row;
            for (char digit : inp) {

                height_row.push_back(Point(digit - '0'));
            }
            height_vec.push_back(height_row);
        }

        // Off set to check the top, bottom, left and right positions
        std::vector<std::pair<int,int>> off_sets = {{0,1},{0,-1},{1,0},{-1,0}};


        for (int i = 0; i < height_vec.size(); ++i) {
            for (int j = 0; j < height_vec[i].size(); ++j)
            {
                // check each offset
                for(std::pair<int,int> off_set : off_sets)
                {
                    std::pair<int,int> adjasent_index = {i+off_set.first,j+off_set.second};

                    //checks if the point is with in boundaries
                    if( (adjasent_index.first > -1 && adjasent_index.second > -1) &&
                      (adjasent_index.first < height_vec.size() && adjasent_index.second < height_vec[i].size()))
                    {
                        //Add the point reference to the adjacent points vector in the current point
                        height_vec[i][j].adjacent.push_back(&height_vec[adjasent_index.first][adjasent_index.second]);


                    }
                }


            }
        }


        std::cout << "Part 1: " << part1(height_vec) << std::endl;
        std::cout << "Part 2: " << part2(height_vec) << std::endl;

    }

    return 0;
}
