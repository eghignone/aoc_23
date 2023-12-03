#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

int main()
{
    std::string filename = "input.txt";

    // read file 
    std::ifstream file(filename);
    // check if file is opened
    if (!file.is_open())
    {
        // std::cout << "Error: File not opened" << std::endl;
        return 1;
    }

    std::map<std::string, int> number_map;
    number_map["red"] = 12;
    number_map["green"] = 13;
    number_map["blue"] = 14;

    // read file line by line
    std::string line;
    int sum = 0;
    while (std::getline(file, line))
    {
        // parse the string dividng first by colon then by semicolon
        auto colon = line.find(':');
        // get the string before colon
        auto before_colon = line.substr(0, colon);
        // get the string after colon
        auto after_colon = line.substr(colon + 1);
        // parse number after "Game "
        int game_no = std::stoi(before_colon.substr(5));

        // std::cout << "Game no.: " << game_no << std::endl;

        std::istringstream iss(after_colon);
        std::string game;
        bool bad = false;
        std::map<std::string, int> max_balls_map;
        max_balls_map["red"] = 0;
        max_balls_map["green"] = 0;
        max_balls_map["blue"] = 0;
        while (std::getline(iss, game, ';') and !bad)
        {
            // std::cout  << "game: ";
            // std::cout << game << std::endl;

            std::istringstream iss2(game);
            std::string number;
            while (std::getline(iss2, number, ',') and !bad)
            {   
                // remove leading space
                number.erase(0, number.find_first_not_of(' '));
                // parse number before space
                auto space = number.find(' ');
                // get the string after the space
                auto number_final = std::stoi(number.substr(0, space));

                std::string color = number.substr(space + 1);
                // remove any other space from color 
                // color.erase(std::remove(color.begin(), color.end(), ' '), color.end());
                
                // std::cout << "number: " << number_final << " color: >" << color << "<" << std::endl;
                max_balls_map[color] = std::max(max_balls_map[color], number_final);
            }
        }
        sum += max_balls_map["red"] * max_balls_map["green"] * max_balls_map["blue"];
        // std::cout << std::endl;
    }

    std::cout << "Sum: " << sum << std::endl;
}