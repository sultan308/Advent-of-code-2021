#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class Octopus
{
public:

    int value;
    
    std::vector<Octopus*> adjacent ;
    
    bool flashed = false;
    


    Octopus(int val)
    {
        value = val;

    }
    // if the value is bigger than 9
    // flashes the octopus and increments all adjacent octopuses recursively
    // returns total number of Octopuses that has flashed.
    int flash()
    {
        int flash_counter = 0;
        if(this->value > 9)
        {
            this->flashed = true;
            this->value = 0;
            flash_counter++;

            for (int i = 0 ; i < adjacent.size() ; i++) {
                flash_counter+= adjacent[i]->increment();
            }
        }
        return flash_counter;
    }
    //if the octopus hasn't flashed yet
    //increments value by one and checks if it has flashed
    //Returns the total number of flashes caused by this incrementation
    int increment()
    {
        int flashes = 0;
        if(!flashed)
        {
            this->value++;
            flashes = this->flash();

        }
        return flashes;

    }


    // find all neighboring octopuses and add the to the adjacent vector.
    void updateAdjacent(std::vector<std::vector<Octopus >>& octopus_grid , int octopus_row, int octopus_column) {
        for (int row_offset = -1; row_offset < 2; ++row_offset) {
            for (int column_offset = -1; column_offset < 2; ++column_offset) {

                if (!(row_offset == 0 && column_offset == 0)) {
                    int row = octopus_row + row_offset;
                    int column = octopus_column + column_offset;

                    if (row > -1 && column > -1 && row < octopus_grid.size() && column < octopus_grid[row].size()) {

                        this->adjacent.push_back(&octopus_grid[row][column]);

                    }
                }

            }
        }
    }

};

void simulateTillSimultaneousFlash(std::vector<std::vector<Octopus>>& oct_grid)
{
    int total_flashes = 0;
    int step = 1;
    bool found = false;
    while(found == false)
    {
        int this_step_flashes = 0;
        
        for (int row = 0; row < oct_grid.size(); ++row)
        {
            for (int col = 0; col < oct_grid[row].size(); ++col) {

                this_step_flashes+= oct_grid[row][col].increment();

            }
        }

        //Rests all octopuses flashed status
        for (int row = 0; row < oct_grid.size(); ++row) {
            for (int col = 0; col < oct_grid[row].size(); ++col) {

                oct_grid[row][col].flashed = false;
            }
        }

        if(this_step_flashes == (oct_grid.size()*oct_grid.back().size()))
        {
                std::cout << "Part Two : " << step <<std::endl;
                found = true;
        }
        total_flashes+=this_step_flashes;

        if(step == 100) std::cout << "Part One : " << total_flashes <<std::endl;

        step++;
    }

}
int main()
{
    std::vector<std::vector<Octopus >> oct_grid;
    std::string line;
    std::ifstream input("input.txt");
    if(input.fail()) std::cout << "Failed to open file";
    else {


        while(input.peek() != EOF)
        {
            std::string line;
            input >> line;
            std::vector<Octopus > oct_row;
            for(char digit : line)
            {
                oct_row.push_back(Octopus(digit - '0'));
            }

            oct_grid.push_back(oct_row);
        }

        // updates all the octopuses adjacent vectors
        for (int i = 0; i < oct_grid.size(); ++i) {
            for (int j = 0; j < oct_grid[i].size(); ++j)
            {
                oct_grid[i][j].updateAdjacent(oct_grid,i,j);
            }

        }

        simulateTillSimultaneousFlash(oct_grid);
    }

    return 0;
}
