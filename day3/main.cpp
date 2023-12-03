#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include "main.h"

bool PRINT_DEBUG = false;
bool TASK1 = false;

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

    // load input file in a 2-d matrix
    // initialize matrix
    std::vector<std::string> matrix;
    // read file line by line
    std::string line;
    int sum = 0;
    while (std::getline(file, line))
    {
        // load every character in a vector
        std::string row;
        for (auto c : line)
        {
            row.push_back(c);
        }
        // add row to matrix
        matrix.push_back(row);
    }
    matrix = pad_matrix(matrix);
    if (PRINT_DEBUG)
    {
        print_matrix(matrix);
    }

    std::vector<std::vector<int>> gears_ratio;
    std::vector<std::vector<int>> gears_count;
    if (TASK1){
        std::cout << "Task 1" << std::endl;
    } else {
        std::cout << "Task 2" << std::endl;
        // create two matrices of same size as input matrix but all ones and all zeros 
        for (auto i = 0; i < matrix.size(); i++)
        {
            std::vector<int> row_ratio;
            std::vector<int> row_count;
            for (auto j = 0; j < matrix[i].size(); j++)
            {
                row_ratio.push_back(1);
                row_count.push_back(0);
            }
            gears_ratio.push_back(row_ratio);
            gears_count.push_back(row_count);
        }
    }

    sum = 0;
    for (auto i = 1; i < matrix.size() - 1; i++)
    {
        int num_start = 0;
        int num_end = 0;
        bool in_num = false;
        for (auto j = 1; j < matrix[i].size(); j++)
        {   
            // if current symbol is a digit
            if (isdigit(matrix[i][j]))
            {
                if (in_num){ // if we are in a number
                    num_end = j;
                } else { // if we are not in a number
                    in_num = true;
                    num_start = j;
                }
            } else {
                if (in_num){ // if we found the end of a number, then it's time to process it
                    num_end = j;
                    if (TASK1){
                        if (check_validity(matrix, num_start, num_end, i)){
                            if (PRINT_DEBUG){
                                std::cout << "valid" << std::endl;
                            }
                            sum += std::stoi(matrix[i].substr(num_start, num_end - num_start));
                        } else {
                            if (PRINT_DEBUG){
                                std::cout << "invalid" << std::endl;
                            }
                        }
                    } else {
                        check_gears(matrix, num_start, num_end, i, &gears_ratio, &gears_count);
                    }
                    in_num = false;
                } // if we are not in a number, do nothing
            }
        }
    }
    if (TASK1){
        std::cout << "Sum: " << sum << std::endl;
    } else {
        count_gears(gears_ratio, gears_count);
    }
}

void print_matrix(std::vector<std::string> matrix)
{
    for (auto row : matrix)
    {
        for (auto c : row)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

std::vector<std::string> pad_matrix(std::vector<std::string> matrix)
{
    // add a row of periods to the matrix's top and bottom
    std::string row;
    for (auto i = 0; i < matrix[0].size(); i++)
    {
        row.push_back('.');
    }
    matrix.insert(matrix.begin(), row);
    matrix.push_back(row);

    // add a period before and after every row in the matrix
    for (auto i = 0; i < matrix.size(); i++)
    {
        matrix[i].insert(matrix[i].begin(), '.');
        matrix[i].push_back('.');
    }
    return matrix;
}

bool check_validity(std::vector<std::string> matrix, int num_start, int num_end, int num_row)
{
    // check if the number is valid
    // check if the number is surrounded by a symbol (not a period)
    if (PRINT_DEBUG){
        std::cout << "In row and column: " << num_row << " " << num_start << std::endl;
        std::cout << "Checking number >" << matrix[num_row].substr(num_start, num_end - num_start) << "<" << std::endl;
    }
    
    // row before and after
    for (auto i = num_start - 1; i <= num_end; i++)
    {   
        if (PRINT_DEBUG){
            std::cout << "check: >" << matrix[num_row - 1][i] << std::endl;
            std::cout << "check: >" << matrix[num_row + 1][i] << std::endl;
        }
        if (!(isdigit(matrix[num_row - 1][i])))
        {   
            if (matrix[num_row - 1][i] != '.')
            {
                return true;
            }
        }
        if (!(isdigit(matrix[num_row + 1][i])))
        {   
            if (matrix[num_row + 1][i] != '.')
            {
                return true;
            }
        }
    }
    // elements before and after
    if (PRINT_DEBUG){
        std::cout << "check: >" << matrix[num_row][num_start - 1] << std::endl;
        std::cout << "check: >" << matrix[num_row][num_end + 1] << std::endl;
    }
    if (!(isdigit(matrix[num_row][num_start - 1])))
    {   
        if (matrix[num_row][num_start - 1] != '.')
        {
            return true;
        }
    }
    if (!(isdigit(matrix[num_row][num_end])))
    {   
        if (matrix[num_row][num_end] != '.')
        {
            return true;
        }
    }
    return false;
}

void check_gears(std::vector<std::string> matrix, int num_start, int num_end, int num_row, std::vector<std::vector<int>>* gears_ratio, std::vector<std::vector<int>>* gears_count)
{
    // check if the number is valid
    // check if the number is surrounded by a symbol (not a period)
    if (PRINT_DEBUG){
        std::cout << "In row and column: " << num_row << " " << num_start << std::endl;
        std::cout << "Checking number >" << matrix[num_row].substr(num_start, num_end - num_start) << "<" << std::endl;
    }
    int num = std::stoi(matrix[num_row].substr(num_start, num_end - num_start));
    
    // row before and after
    for (auto i = num_start - 1; i <= num_end; i++)
    {   
        if (PRINT_DEBUG){
            std::cout << "check: >" << matrix[num_row - 1][i] << std::endl;
            std::cout << "check: >" << matrix[num_row + 1][i] << std::endl;
        }
        if (matrix[num_row - 1][i] == '*')
        {   
            // modify pointed element
            (*gears_ratio)[num_row - 1][i] *= num;
            (*gears_count)[num_row - 1][i] += 1;
        }
        if (matrix[num_row + 1][i] == '*')
        {   
            (*gears_ratio)[num_row + 1][i] *= num;
            (*gears_count)[num_row + 1][i] += 1;
        }
    }
    // elements before and after
    if (PRINT_DEBUG){
        std::cout << "check: >" << matrix[num_row][num_start - 1] << std::endl;
        std::cout << "check: >" << matrix[num_row][num_end + 1] << std::endl;
    }
    if (matrix[num_row][num_start - 1] == '*')
    {   
        (*gears_ratio)[num_row][num_start - 1] *= num;
        (*gears_count)[num_row][num_start - 1] += 1;
    }
    if (matrix[num_row][num_end] == '*')
    {   
        (*gears_ratio)[num_row][num_end] *= num;
        (*gears_count)[num_row][num_end] += 1;
    }
}

void count_gears(std::vector<std::vector<int>> gears_ratio, std::vector<std::vector<int>> gears_count)
{   
    if (PRINT_DEBUG){
        std::cout << "Gears ratio" << std::endl;
        for (auto row : gears_ratio)
        {
            for (auto c : row)
            {
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Gears count" << std::endl;
        for (auto row : gears_count)
        {
            for (auto c : row)
            {
                std::cout << c << " ";
            }
            std::cout << std::endl;
        }
    }
    int sum = 0;
    for (auto i = 1; i < gears_ratio.size() - 1; i++)
    {
        for (auto j = 1; j < gears_ratio[i].size() - 1; j++)
        {
            if (gears_count[i][j] == 2){
                sum += gears_ratio[i][j];
            }
        }
    }
    std::cout << "Sum: " << sum << std::endl;
}

