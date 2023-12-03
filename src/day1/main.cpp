#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "trie.cpp"

int main()
{
    // filename
    std::string filename = "input.txt";
    
    // Open the file 
    std::ifstream file(filename);

    // trie with number from one to nine
    Trie trie;
    trie.insert("one");
    trie.insert("two");
    trie.insert("three");
    trie.insert("four");
    trie.insert("five");
    trie.insert("six");
    trie.insert("seven");
    trie.insert("eight");
    trie.insert("nine");

    // number map
    std::map<std::string, int> number_map;
    number_map["one"] = 1;
    number_map["two"] = 2;
    number_map["three"] = 3;
    number_map["four"] = 4;
    number_map["five"] = 5;
    number_map["six"] = 6;
    number_map["seven"] = 7;
    number_map["eight"] = 8;
    number_map["nine"] = 9;

    // Check if the file is opened
    if (!file.is_open())
    {
        std::cout << "Error: File not opened" << std::endl;
        return 1;
    }

    int sum = 0;
    // array of two int
    int numbers[2];
    // Read the file line by line
    std::string line;
    // iterate lines in the file
    

    while (std::getline(file, line))
    {
        auto start = true;

        // iterate efficiently over the string
        for (auto it = line.begin(); it != line.end(); ++it)
        {
            // check if the character is a digit
            if (std::isdigit(*it))
            {
                if (start)
                {
                    // convert the character to an integer
                    int digit = *it - '0';
                    numbers[0] = digit;
                    numbers[1] = digit;
                    start = false;
                }
                else
                {   
                    int digit = *it - '0';
                    numbers[1] = digit;
                }
            }

            // else use the trie to check if character is the start of a letter
            else
            {
                // check if the trie contains the word
                int n = 1;
                while (trie.startsWith(line.substr(it - line.begin(), n)))
                {   
                    // std::cout << line.substr(it - line.begin(), n) << std::endl;
                    n += 1;
                    if (it + n > line.end())
                    {
                        break;
                    }
                }
                // if the word is in the trie
                if (trie.search(line.substr(it - line.begin(), n - 1))){
                    if (start){
                        numbers[0] = number_map[line.substr(it - line.begin(), n - 1)];
                        numbers[1] = number_map[line.substr(it - line.begin(), n - 1)];
                        start = false;
                    }
                    else
                    {
                        numbers[1] = number_map[line.substr(it - line.begin(), n - 1)];
                    }
                }
            }
        }
        // std::cout << numbers[0] << " " << numbers[1] << std::endl;
        sum += numbers[0]*10 + numbers[1];
        
    }

    std::cout << "Sum: " << sum << std::endl;

    // Close the file
    file.close();

    return 0;
}

