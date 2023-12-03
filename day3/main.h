#ifndef MYHEADER_H
#define MYHEADER_H

#include <vector>
#include <string>

void print_matrix(std::vector<std::string> matrix);
std::vector<std::string> pad_matrix(std::vector<std::string> matrix);
bool check_validity(std::vector<std::string> matrix, int num_start, int num_end, int num_row);
void check_gears(std::vector<std::string> matrix, int num_start, int num_end, int num_row, std::vector<std::vector<int>>* gears_ratio, std::vector<std::vector<int>>* gears_count);
void count_gears(std::vector<std::vector<int>> gears_ratio, std::vector<std::vector<int>> gears_count);

#endif
