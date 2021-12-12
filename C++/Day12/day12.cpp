#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>
#include <set>


std::vector<std::string> split(std::string s)
{
    std::string delimiter = "-";
    std::vector<std::string> res ;

    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        res.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    res.push_back(s);

    return res;


};

std::set<std::string> getCands(std::set<std::string> adjacency_set,std::set<std::string> visited)
{
    for(auto item : visited)
    {
        adjacency_set.erase(item);
    }
    return adjacency_set;

}

void search( std::map<std::string,std::set<std::string>> &adjacency_map,std::set<std::string> &part_one_paths,std::set<std::string> &part_two_paths,std::string current,std::set<std::string> visited,std::string path , int left)
{
    path+=current;

    if(current == "end")
    {
        if (left == 1) part_one_paths.insert(path);
        part_two_paths.insert(path);

        return;

    }

    if(current[0] == tolower(current[0]) && left > 0)
    {
        for (int j = 0; j < 2; ++j) {
            if( j == 1)
            {
                visited.insert(current);
            }
            std::set<std::string> next_posssible = getCands(adjacency_map[current],visited);
            for(std::string candidate : next_posssible)
            {
                search(adjacency_map,part_one_paths,part_two_paths,candidate,visited,path,j);
            }


        }
        return;
    }
    if(current[0] == tolower(current[0])) visited.insert(current);

    std::set<std::string> next_posssible = getCands(adjacency_map[current],visited);
    for(std::string candidate : next_posssible)
    {
        search(adjacency_map,part_one_paths,part_two_paths,candidate,visited,path,left);
    }



}
void addAdjacency(std::map<std::string,std::set<std::string>>& adjacency_map ,std::vector<std::string> caves)
{
    int j = 1;
    for (int i = 0; i < 2; ++i)
    {

        if (adjacency_map.find(caves[i]) == adjacency_map.end()) {
            std::set<std::string> children;
            children.insert(caves[j]);
            adjacency_map[caves[i]] = children;
        } else {
            adjacency_map[caves[i]].insert(caves[j]);
        }
        j--;
    }


}

int main() {
    std::ifstream input("input.txt");

    if(input.fail()) std::cout << "Failed to open file";
    else {

        std::map<std::string,std::set<std::string>> adjacency_map;
        while(input.peek() != EOF)
        {

            std::string line;
            input >> line;
            addAdjacency(adjacency_map,split(line));


        }
        std::set<std::string> part_one_paths;
        std::set<std::string> part_two_paths;

        search(adjacency_map,part_one_paths,part_two_paths,"start",{"start"},"",1);

        std::cout << "Part 1 : " << part_one_paths.size()<< std::endl;
        std::cout << "Part 2 : " << part_two_paths.size() << std::endl;

    }

    return 0;
}
