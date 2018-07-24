/**
	--- AoC 2017 ---
	--- Day 8: I Heard You Like Registers ---
	http://adventofcode.com/2017/day/8
-------------------------------------------------------------------------------------------------------------
Part 1:
You receive a signal directly from the CPU. Because of your recent assistance with jump instructions, 
it would like you to compute the result of a series of unusual register instructions.

Each instruction consists of several parts: the register to modify, whether to increase or decrease that register's value, 
the amount by which to increase or decrease it, and a condition. If the condition fails, 
skip the instruction without modifying the register. The registers all start at 0. 

The instructions look like this:
	b inc 5 if a > 1
	a inc 1 if b < 5
	c dec -10 if a >= 1
	c inc -20 if c == 10

These instructions would be processed as follows:
    Because a starts at 0, it is not greater than 1, and so b is not modified.
    a is increased by 1 (to 1) because b is less than 5 (it is 0).
    c is decreased by -10 (to 10) because a is now greater than or equal to 1 (it is 1).
    c is increased by -20 (to -10) because c is equal to 10.

After this process, the largest value in any register is 1.

You might also encounter <= (less than or equal to) or != (not equal to). 
However, the CPU doesn't have the bandwidth to tell you what all the registers are named, and leaves that to you to determine.

What is the largest value in any register after completing the instructions in your puzzle input?
-------------------------------------------------------------------------------------------------------------
Part 2:

*/
#pragma once
#include <map>
#include <utility>
#include <algorithm>

#include "Helper.hpp"

void day8()
{
	// Read input.
	auto input = read_lines_from_file("input_day8.txt");

	// Instructions are listed as: [reg],[dec],[value],[if],[reg],[!=],[value]
	std::vector<std::array<std::string, 8>> listOfInstructions;
	for each(auto& line in input)
	{
		std::istringstream is(line);
		unsigned i=0;
		std::array<std::string, 8> ins;
		while(is >> ins[i++]){}
		listOfInstructions.push_back(ins);
		//print_array<std::string, 7>(" ", ins);
	}

// == Part 1 & 2 ===============================================================================
	std::map<std::string, int> regs;
	int highest_value_ever = 0; // Part 2
	for each(auto& ins in listOfInstructions)
	{
		// 1 Check the operation.
		bool test = false;
		{
			const int& a = regs[ins[4]];
			const std::string& operand = ins[5];
			const int& b = std::atoi(ins[6].c_str());
			
			if(operand == "==") test = (a == b);
			else if(operand == "!=") test = (a != b);
			else if(operand == "<=") test = (a <= b);
			else if(operand == ">=") test = (a >= b);
			else if(operand == "<") test = (a < b);
			else if(operand == ">") test = (a > b);
			else std::cerr << "Unknown operand!" << std::endl;
		}

		// 2 If the operations result is false skip this instruction.
		if(!test) continue;

		// 3 Execute instructions.
		if(ins[1] == "inc") regs[ins[0]] += std::atoi(ins[2].c_str()); // Increment.
		if(ins[1] == "dec") regs[ins[0]] -= std::atoi(ins[2].c_str()); // Decrement.

		// Find highest value every for part 2.
		if(regs[ins[0]] > highest_value_ever) highest_value_ever = regs[ins[0]];
	}

	// Find the maximum value of all registers.
	int max = 0;
	for each(auto& reg in regs) if(reg.second > max) max = reg.second;
	std::cout << "Maximum value in any register: " << max << std::endl;
	std::cout << "Highest value ever held by any register: " << highest_value_ever << std::endl;
}