/**
	--- AoC 2017 ---
	--- Day 2: Corruption Checksum ---
	http://adventofcode.com/2017/day/2
-------------------------------------------------------------------------------------------------------------
Part 1:
The spreadsheet consists of rows of apparently-random numbers. To make sure the recovery process is on the right track, 
they need you to calculate the spreadsheet's checksum. For each row, determine the difference between the largest value 
and the smallest value; the checksum is the sum of all of these differences.

For example, given the following spreadsheet:

	5 1 9 5
	7 5 3
	2 4 6 8

    The first row's largest and smallest values are 9 and 1, and their difference is 8.
    The second row's largest and smallest values are 7 and 3, and their difference is 4.
    The third row's difference is 6.

In this example, the spreadsheet's checksum would be 8 + 4 + 6 = 18.

-------------------------------------------------------------------------------------------------------------
Part 2:
It sounds like the goal is to find the only two numbers in each row where one evenly divides the other - 
that is, where the result of the division operation is a whole number. 
They would like you to find those numbers on each line, divide them, and add up each line's result.

For example, given the following spreadsheet:

	5 9 2 8
	9 4 7 3
	3 8 6 5

    In the first row, the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
    In the second row, the two numbers are 9 and 3; the result is 3.
    In the third row, the result is 2.

In this example, the sum of the results would be 4 + 3 + 2 = 9.

*/
#pragma once
#include <iostream>
#include <fstream> 
#include <vector> 

void day2()
{
	std::vector<int> input;

	// Read the input from file.
	{	std::ifstream ifs("input_day2.txt");
		int num;
		while(ifs >> num) input.push_back(num);	}

	// Get the length of each row and column.
	const unsigned SZ = std::sqrt((float)input.size());

// == Part 1 ==================================================================================
{
	int totalSum = 0;

	for(unsigned y=0; y<SZ; ++y)
	{
		int max = input[y * SZ];
		int min = max;

		for(unsigned x=0; x<SZ; ++x)
		{
			const int NUM = input[y * SZ + x];
			if(NUM > max) max = NUM;
			if(NUM < min) min = NUM;
		}

		totalSum += (max-min);
	}

	std::cout << "Part 1 sum: " << totalSum << std::endl;  // Correct result: 36174
}

// == Part 2 ==================================================================================
{
	int totalSum = 0;

	for(unsigned y=0; y<SZ; ++y)
	{
		for(unsigned x=0; x<SZ; ++x)
		{
			int numerator = input[y * SZ + x];

			for(unsigned ix=0; ix<SZ; ++ix)
			{
				int denominator = input[y * SZ + ix];
				if(numerator > denominator && numerator % denominator == 0) totalSum += (numerator / denominator);
			}
		}
	}

	std::cout << "Part 2 sum: " << totalSum << std::endl; // Correct result: 244
}
}