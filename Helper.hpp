#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>

const std::vector<const std::string> read_lines_from_file(const std::string path)
{
	std::vector<const std::string> input;
	std::ifstream ifs(path);
	std::string str;
	if(!ifs.is_open())
	{ 
		std::cerr << "Error! Could not find file!" << std::endl; 
		return input; 
	}
	while(!ifs.eof())
	{
		char c = ifs.get();
		if(c != '\n' && c != EOF) str += c;
		else
		{
			input.push_back(str);
			str = "";
		}
	}
	input.pop_back();
	return input;
}

template<typename T, std::size_t SZ>
void print_array(const std::string title, const std::array<T, SZ>& arr)
{
	std::cout << title << "=> ";
	for(unsigned i=0; i<SZ; ++i)
		std::cout << "[" << arr[i] << "] ";
	std::cout << std::endl;
}

template<typename T>
void print_vector(const std::string title, const std::vector<T>& vec)
{
	std::cout << title << std::endl;
	for each(const T& elem in vec)
		std::cout << "[" << elem << "]" << std::endl;
}