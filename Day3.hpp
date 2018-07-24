/**
	--- AoC 2017 ---
	--- Day 3: Spiral Memory ---
	http://adventofcode.com/2017/day/3
-------------------------------------------------------------------------------------------------------------
Part 1:
You come across an experimental new kind of memory stored on an infinite two-dimensional grid.

Each square on the grid is allocated in a spiral pattern starting at a location marked 1 and then counting up while spiraling outward. 

For example, the first few squares are allocated like this:

	17  16  15  14  13
	18   5   4   3  12
	19   6   1   2  11
	20   7   8   9  10
	21  22  23---> ...

While this is very space-efficient (no squares are skipped), requested data must be carried back to square 1 
(the location of the only access port for this memory system) by programs that can only move up, down, left, or right. 
They always take the shortest path: the Manhattan Distance between the location of the data and square 1.

For example:

    Data from square 1 is carried 0 steps, since it's at the access port.
    Data from square 12 is carried 3 steps, such as: down, left, left.
    Data from square 23 is carried only 2 steps: up twice.
    Data from square 1024 must be carried 31 steps.


-------------------------------------------------------------------------------------------------------------
Part 2:
As a stress test on the system, the programs here clear the grid and then store the value 1 in square 1. 
Then, in the same allocation order as shown above, they store the sum of the values in all adjacent squares, including diagonals.

So, the first few squares' values are chosen as follows:

    Square 1 starts with the value 1.
    Square 2 has only one adjacent filled square (with value 1), so it also stores 1.
    Square 3 has both of the above squares as neighbors and stores the sum of their values, 2.
    Square 4 has all three of the aforementioned squares as neighbors and stores the sum of their values, 4.
    Square 5 only has the first and fourth squares as neighbors, so it gets the value 5.

Once a square is written, its value does not change. Therefore, the first few squares would receive the following values:

	147  142  133  122   59
	304    5    4    2   57
	330   10    1    1   54
	351   11   23   25   26
	362  747  806--->   ...

What is the first value written that is larger than your puzzle input?

*/
#pragma once
#include <iostream>
#include <string>
#include <cmath>

enum Direction{ Right, Up, Left, Down };

void day3()
{
	const unsigned INPUT = 325489, SIDE_LENGTH = 572;


// == Part 1 ==================================================================================	
{
	unsigned** mem_data = new unsigned*[SIDE_LENGTH];
	for (unsigned i = 0; i < SIDE_LENGTH; i++) mem_data[i] = new unsigned[SIDE_LENGTH];
	for(unsigned y=0; y<SIDE_LENGTH; ++y)
		for(unsigned x=0; x<SIDE_LENGTH; ++x)
			mem_data[y][x] = 0;


	unsigned pos_x = SIDE_LENGTH / 2, pos_y = SIDE_LENGTH / 2, path_length = 1, path_counter = 0, dest_x = 0, dest_y = 0;
	bool inc_path_length = false;	
	Direction dir = Right;			

	for(unsigned i=1; i<(SIDE_LENGTH*SIDE_LENGTH); ++i)
	{
		mem_data[pos_y][pos_x] = i;

		if(i  == INPUT)
		{
			dest_x = pos_x;
			dest_y = pos_y;
		}

		switch(dir)
		{
		case Up: --pos_y; break;
		case Down: ++pos_y; break;
		case Left: --pos_x; break;
		case Right: ++pos_x; break;
		default: break;
		}
	
		if(++path_counter >= path_length)
		{
			path_counter = 0;

			if(dir==Right) dir = Up;
			else if(dir==Up) dir = Left;
			else if(dir==Left) dir = Down;
			else dir = Right;

			if(inc_path_length)
			{
				++path_length;
				inc_path_length = false;
			}else inc_path_length = true;
		} 
	}

	unsigned val = SIDE_LENGTH / 2;
	int diffx = std::abs((long)(val - dest_x));
	int diffy = std::abs((long)(val - dest_y));
	std::cout << "Part 1 sum: " << diffy << "+" << diffx << "=" << diffy+diffx << std::endl;
}

// == Part 2 ==================================================================================
{
	unsigned** mem_data = new unsigned*[SIDE_LENGTH];
	for (unsigned i = 0; i < SIDE_LENGTH; i++) mem_data[i] = new unsigned[SIDE_LENGTH];
	for(unsigned y=0; y<SIDE_LENGTH; ++y)
		for(unsigned x=0; x<SIDE_LENGTH; ++x)
			mem_data[y][x] = 0;


	unsigned pos_x = SIDE_LENGTH / 2, pos_y = SIDE_LENGTH / 2, path_length = 1, path_counter = 0, dest_x = 0, dest_y = 0;
	
	bool inc_path_length = false;	
	Direction dir = Right;			

	for(unsigned i=1; i<(SIDE_LENGTH*SIDE_LENGTH); ++i)
	{
		int neighbour_sum = 0;
		
		if(pos_x > 0)
		{
			neighbour_sum += mem_data[pos_y][pos_x - 1];								// Left neighbour.
			if(pos_y > 0) neighbour_sum += mem_data[pos_y - 1][pos_x - 1];				// Top-Left neighbour.
			if(pos_y < SIDE_LENGTH-1) neighbour_sum += mem_data[pos_y + 1][pos_x - 1];	// Bottom-Left neighbour.
		}
		if(pos_x < SIDE_LENGTH-1) 
		{
			neighbour_sum += mem_data[pos_y][pos_x + 1];								// Right neighbour.
			if(pos_y > 0) neighbour_sum += mem_data[pos_y - 1][pos_x + 1];				// Top-Right neighbour.
			if(pos_y < SIDE_LENGTH-1) neighbour_sum += mem_data[pos_y + 1][pos_x + 1];	// Bottom-Right neighbour.
		}
		if(pos_y > 0) neighbour_sum += mem_data[pos_y - 1][pos_x];						// Top neighbour.
		if(pos_y < SIDE_LENGTH-1) neighbour_sum += mem_data[pos_y + 1][pos_x];			// Bottom neighbour.


		mem_data[pos_y][pos_x] = neighbour_sum;
		if(i==1) mem_data[pos_y][pos_x] = 1;

		if(neighbour_sum > INPUT)
		{
			std::cout << "Part 2 the 1st value > 'INPUT'(" << INPUT << ") is " << neighbour_sum << std::endl;
			break;
		}

		switch(dir)
		{
		case Up: --pos_y; break;
		case Down: ++pos_y; break;
		case Left: --pos_x; break;
		case Right: ++pos_x; break;
		default: break;
		}
	
		if(++path_counter >= path_length)
		{
			path_counter = 0;

			if(dir==Right) dir = Up;
			else if(dir==Up) dir = Left;
			else if(dir==Left) dir = Down;
			else dir = Right;

			if(inc_path_length)
			{
				++path_length;
				inc_path_length = false;
			}else inc_path_length = true;
		} 
	}
}
}