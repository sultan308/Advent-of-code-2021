#include <iostream>
#include <fstream>
#include <vector>


int getEnhancedIndex(std::vector<std::string>& image, int row,int col)
{
    std::string binary = "";
    for (int i = -1; i < 2 ; ++i)
    {
        for (int j =-1; j < 2 ; ++j)
        {
               binary += image[row+i][col+j];
        }
    }
    for (int i = 0; i < binary.size(); ++i)
    {
        binary[i] = binary[i] == '.' ? '0': '1';
    }

    return std::stoi(binary,0,2);
}
int getReapeatIndex(char pixel)
{
    pixel = pixel == '.' ? '0' : '1';
    std::string binary = "";
    for (int i = 0; i < 9; ++i) {
        binary += pixel;
    }
    return std::stoi(binary,0,2);
}
std::vector<std::string> enhance_image(std::vector<std::string> image , std::string& enhancement_algorithm )
{
    std::vector<std::string> enhanced_image =  image;
    for (int row = 0; row < (image.size()); ++row)
    {
        for (int col = 0; col < (image[0].size()); ++col)
        {
            int newValueIndex;
            if(col < 1 || row  < 1 || row == (image.size()-1) || col == (image[0].size()-1))
            {
                newValueIndex = getReapeatIndex(image[row][col]);

            } else
            {
                newValueIndex = getEnhancedIndex(image,row,col);

            }
            enhanced_image[row][col] = enhancement_algorithm[newValueIndex];

        }
    }
    return enhanced_image;
}
std::vector<std::string> expand(std::vector<std::string> image,char pixel)
{
    std::string dark_row = "";
    for (int i = 0; i < (image[0].size()+2); ++i)
    {
        dark_row += pixel;
    }

    std::vector<std::string> expanded_image;
    expanded_image.push_back(dark_row);


    for(std::string row : image)
    {
        row = pixel + row + pixel;
        expanded_image.push_back(row);
    }

    expanded_image.push_back(dark_row);


    return expanded_image;

}
int solve(std::vector<std::string> image,std::string& enhancement_algorithm , int number_of_enhancements )
{
    image = expand(image,'.');
    image = expand(image,'.');
    image = enhance_image(image,enhancement_algorithm);

    for (int i = 1; i < number_of_enhancements; ++i) {
        image = expand(image,image[0][0]);
        image = enhance_image(image,enhancement_algorithm);

    }
    int counter = 0;
    for(std::string row : image)
    {
        for(char pixel : row)
        {
            if(pixel == '#') counter++;
        }
    }
    return counter;

}

int main() {
    std::string enhancement_algorithm  ;
    std::vector<std::string> image;
    
    std::ifstream input("input.txt");


    if(input.fail()) std::cout << "Failed to open file";
    else {
        input >> enhancement_algorithm;
        while (input.peek() != EOF) {
            std::string pixel_line;
            input >> pixel_line;
            image.push_back(pixel_line);
        }
    }


    std::cout << "Part One: "<< solve(image,enhancement_algorithm,2)<< std::endl;
    std::cout << "Part Two: "<< solve(image,enhancement_algorithm,50)<< std::endl;
    return 0;
}
