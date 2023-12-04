#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>

#include "main.h"

bool PRINT_DEBUG = false;
bool TASK1 = false;
int TASK = 2;

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

    
    // read file line by line
    std::string line;
    int sum = 0;
    // create int circular buffer with length 5
    if (TASK == 1) {
        while (std::getline(file, line))
        {
            sum += process_line(line);
        }
    } else {
        bool init = false;
        RingBuff* buffer;
        while (std::getline(file, line))
        {
            if (!init)
            {
                int len_buf = get_from_line(line);
                std::cout << "Length of buffer " << len_buf << std::endl;
                // initialize the buffer 
                buffer = new RingBuff(len_buf+1);
                init = true;
            }
            // process line
            sum += process_line2(line, buffer);
        }
    }
    std::cout << sum << std::endl;
    
}

int get_from_line(std::string line){
    // get winning numbers part

    std::string winn_numbers = line.substr(line.find(":")+1, line.find("|"));
    int temp;
    int sum = 0;
    std::stringstream ss(winn_numbers);
    while (ss >> temp)
    {
        sum += 1;
    }
    return sum;
}

int process_line(std::string line)
{
    // remove part before :
    std::string delimiter = ":";
    std::string token = line.substr(line.find(delimiter) + 1, line.length());

    delimiter = "|";
    std::string token1 = token.substr(0, token.find(delimiter));
    std::string token2 = token.substr(token.find(delimiter) + 1, token.length());

    // save numbers in token1 separated with space, in a set
    std::set<int> numbers1;
    std::stringstream ss1(token1);
    int temp;
    while (ss1 >> temp)
    {
        numbers1.insert(temp);
    }

    // save numbers in token2 separated with space
    std::set<int> numbers2;
    std::stringstream ss2(token2);
    while (ss2 >> temp)
    {
        numbers2.insert(temp);
    }

    // find length of interseciton
    std::set<int> inters;
    std::set_intersection(numbers1.begin(), numbers1.end(), numbers2.begin(), numbers2.end(), std::inserter(inters, inters.begin()));
    // get length of intersection
    int num_magic = pow(2, inters.size()-1);
    return num_magic;
}

int process_line2(std::string line, RingBuff* buffer){
    // remove part before :
    std::string delimiter = ":";
    std::string token = line.substr(line.find(delimiter) + 1, line.length());

    delimiter = "|";
    std::string token1 = token.substr(0, token.find(delimiter));
    std::string token2 = token.substr(token.find(delimiter) + 1, token.length());

    // save numbers in token1 separated with space, in a set
    std::set<int> numbers1;
    std::stringstream ss1(token1);
    int temp;
    while (ss1 >> temp)
    {
        numbers1.insert(temp);
    }

    // save numbers in token2 separated with space
    std::set<int> numbers2;
    std::stringstream ss2(token2);
    while (ss2 >> temp)
    {
        numbers2.insert(temp);
    }

    // find length of interseciton
    std::set<int> inters;
    std::set_intersection(numbers1.begin(), numbers1.end(), numbers2.begin(), numbers2.end(), std::inserter(inters, inters.begin()));
    
    // get length of intersection
    int num_magic = inters.size();
    // std::cout << "Num magic: " << num_magic << std::endl;
    // increase the next num_magic elements by 1
    int curr_tickets = buffer->get_head();
    // std::cout << "Current tickets: " << curr_tickets << std::endl;
    buffer->increase_next_n(num_magic, curr_tickets);

    // pop the first element
    int first_element = buffer->pop_element();

    return first_element;
}
