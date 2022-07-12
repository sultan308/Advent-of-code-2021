#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
#include <limits.h>
#include <queue>

typedef std::pair<int, std::pair<int,int>> P;

std::map<std::pair<int,int>,int> findShortestPaths(std::map<std::pair<int,int>,std::map<std::pair<int,int>,int>> & adjacency_matrix, std::pair<int,int> src)
{
    std::map<std::pair<int,int>,int> dist;

   

    for(auto p : adjacency_matrix)
    {
        dist[p.first] = INT_MAX;
     


    }
    std::priority_queue< P, std::vector<P>, std::greater<P> > pq;
    dist[src] = 0;
    pq.push(make_pair(dist[src],src));



    while(pq.size() != 0)
    {
        std::pair<int,int> key = pq.top().second;
        
        pq.pop();

        for(std::pair<std::pair<int,int>,int> adj : adjacency_matrix[key])
        {
            int new_dist = dist[key] + adj.second;

            if(new_dist < dist[adj.first])
            {
                dist[adj.first] = new_dist;
                pq.push(make_pair(new_dist, adj.first));
            }
        }
    }
    return dist;
}

std::set<std::pair<int,int>> getAdj(std::pair<int,int> row_col,int max_row,int max_col)
{
    std::set<std::pair<int,int>> adj_set;
    for (int row_offset = -1; row_offset < 2; ++row_offset)
    {
        for (int col_offset = -1; col_offset < 2; ++col_offset)
        {
            if ((col_offset == 0 || row_offset == 0) && (!(col_offset == 0 && row_offset == 0)))
            {
                std::pair<int,int> adj_row_col = {row_col.first + row_offset, row_col.second + col_offset};

                if(((adj_row_col.first > -1) && ((adj_row_col.second > -1))) &&
                ((adj_row_col.first < max_row) && ((adj_row_col.second < max_col))))
                {
                    adj_set.insert(adj_row_col);
                }
            }
        }
    }
    return adj_set;
}
std::map<std::pair<int,int>,std::map<std::pair<int,int>,int>> creatAdjMatrix(std::vector<std::vector<int>> & risk_grid)
{
    std::map<std::pair<int,int>,std::map<std::pair<int,int>,int>> adjacency_matrix;

    for (int row = 0; row < risk_grid.size(); ++row) {
        for (int col = 0; col < risk_grid[0].size() ; ++col)
        {
            std::pair<int,int> row_col = {row,col};
            adjacency_matrix.insert({row_col, {}});

            for(std::pair<int,int> adj_row_col : getAdj(row_col,risk_grid.size(),risk_grid[0].size()) )
            {
                adjacency_matrix[row_col][adj_row_col] = risk_grid[adj_row_col.first][adj_row_col.second];
            }
        }
    }
    return adjacency_matrix;
}
int partOne(std::vector<std::vector<int>> &risk_grid)
{
    std::map<std::pair<int,int>,std::map<std::pair<int,int>,int>> adjacency_matrix = creatAdjMatrix(risk_grid);

    int last_index = risk_grid.size()-1;

    return findShortestPaths(adjacency_matrix, {0, 0})[{last_index, last_index}];

}
int partTwo(std::vector<std::vector<int>> &risk_grid)
{
    int orginal_size  = risk_grid.size();

    for (int i = 1; i <= 4; ++i)
    {
        for (int row = 0 ; row < orginal_size; ++row)
        {
            std::vector<int> new_row = risk_grid[row];

            for (int col = 0; col < new_row.size() ; ++col)
            {
                new_row[col]+=i;
                if(new_row[col] > 9) new_row[col]-=9;
            }

            risk_grid.push_back(new_row);

        }

    }
    orginal_size = risk_grid[0].size();
    for (int row = 0 ; row < risk_grid.size(); ++row)
    {
        for (int i = 1; i <= 4; ++i)
        {
            for (int col = 0; col < orginal_size; ++col)
            {
                int new_col = risk_grid[row][col] + i;
                if(new_col > 9) new_col -= 9 ;
                risk_grid[row].push_back(new_col);

            }
        }

    }

    std::map<std::pair<int,int>,std::map<std::pair<int,int>,int>> adjacency_matrix = creatAdjMatrix(risk_grid);

    int last_index = risk_grid.size()-1;

    return findShortestPaths(adjacency_matrix, {0, 0})[{last_index, last_index}];
}
int main()
{

    std::vector<std::vector<int>> risk_grid;

    std::string inp;
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {


        while(input.peek() != EOF)
        {
            input >> inp;
            std::vector<int> row;
            for (int i = 0; i < inp.size(); ++i)
            {
                row.push_back((inp[i]-'0'));
            }
            risk_grid.push_back(row);

        }

    }

    std::cout << "Part 1 : " << partOne(risk_grid) << std::endl;
    std::cout << "Part 2 : " << partTwo(risk_grid) << std::endl;



    return 0;
}
