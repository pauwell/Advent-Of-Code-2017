/**
	--- AoC 2017 ---
	--- Day 6: Memory Reallocation ---
	http://adventofcode.com/2017/day/6
-------------------------------------------------------------------------------------------------------------
Part 1:
A debugger program here is having an issue: it is trying to repair a memory reallocation routine, 
but it keeps getting stuck in an infinite loop. In this area, there are sixteen memory banks; 
each memory bank can hold any number of blocks. 
The goal of the reallocation routine is to balance the blocks between the memory banks.

The reallocation routine operates in cycles. In each cycle, it finds the memory bank with the most blocks 
(ties won by the lowest-numbered memory bank) and redistributes those blocks among the banks. 
To do this, it removes all of the blocks from the selected bank, then moves to the next (by index) 
memory bank and inserts one of the blocks. It continues doing this until it runs out of blocks; 
if it reaches the last memory bank, it wraps around to the first one.

The debugger would like to know how many redistributions can be done 
before a blocks-in-banks configuration is produced that has been seen before.

For example, imagine a scenario with only four memory banks:

    - The banks start with 0, 2, 7, and 0 blocks. The third bank has the most blocks, so it is chosen for redistribution.
    - Starting with the next bank (the fourth bank) and then continuing to the first bank, the second bank, and so on, 
	the 7 blocks are spread out over the memory banks. The fourth, first, and second banks get two blocks each, 
	and the third bank gets one back. The final result looks like this: 2 4 1 2.
    - Next, the second bank is chosen because it contains the most blocks (four). Because there are four memory banks, 
	each gets one block. The result is: 3 1 2 3.
    - Now, there is a tie between the first and fourth memory banks, both of which have three blocks. 
	The first bank wins the tie, and its three blocks are distributed evenly over the other three banks, leaving it with none: 0 2 3 4.
    - The fourth bank is chosen, and its four blocks are distributed such that each of the four banks receives one: 1 3 4 1.
    - The third bank is chosen, and the same thing happens: 2 4 1 2.

At this point, we've reached a state we've seen before: 2 4 1 2 was already seen. The infinite loop is detected after the fifth block redistribution cycle, and so the answer in this example is 5.

Given the initial block counts in your puzzle input, how many redistribution cycles must be completed before a configuration is produced that has been seen before?

-------------------------------------------------------------------------------------------------------------
Part 2:
Out of curiosity, the debugger would also like to know the size of the loop: starting from a state that has already been seen, 
how many block redistribution cycles must be performed before that same state is seen again?
In the example above, 2 4 1 2 is seen again after four cycles, and so the answer in that example would be 4.
How many cycles are in the infinite loop that arises from the configuration in your puzzle input?

*/
#pragma once
#include <iostream>
#include <algorithm>
#include <array>
#include <functional>

#include "Helper.hpp"

void day6()
{
	std::array<int, 16> repeatingMemBankFromPart1 = { 0, 0, 0, 0 };

// == Part 1 ==================================================================================
{
	/*
		FIX: Works(!) BUT needs forever and a day to run because I am not hashing the history.
	*/

	// Fetch data from input day 6
	std::array<int, 16> memBanks = {4, 10, 4, 1, 8, 4, 9, 14, 5, 1, 14, 15, 0, 15, 3, 5 }; // Real input
	std::vector<std::array<int, 16>> history;

	//std::array<int, 4> memBanks = { 0, 2, 7, 0 }; 
	//std::vector<std::array<int, 4>> history;

	for(unsigned cycles = 0;; ++cycles)
	{
		// Find the index of the highest current bankvalue.
		unsigned maxValIndex = 0;
		for(unsigned i=0; i<memBanks.size(); ++i) 
			if(memBanks[i] > memBanks[maxValIndex]) maxValIndex = i;

		// Check how many blocks should be distributed.
		int totalBlocksToMove = memBanks[maxValIndex];

		// Empty the current Bank.
		memBanks[maxValIndex] = 0;

		// Get the starting index for the distribution.
		unsigned tmpIndex = maxValIndex + 1;
		if(tmpIndex >= memBanks.size()) tmpIndex = 0;

		// Loop as long as there are blocks to distribute.
		while(totalBlocksToMove > 0)
		{
			++memBanks[tmpIndex]; // Add a block to the current bank ...
			--totalBlocksToMove; // ... and decrease the number of blocks that are to distribute.
			if((++tmpIndex) >= memBanks.size()) tmpIndex = 0; // Skip to the next bank (or first if it is the last).
		}

		// If a duplicate is found the cycles end.
		bool duplicateFound = false;
		for(unsigned i=0; i<history.size(); ++i)
		{
			bool isDifferent = false;
			for(unsigned j=0; j<memBanks.size(); ++j)
			{
				if(memBanks[j] != history[i][j])
				{
					isDifferent = true;
					break;
				}
			}
			if(!isDifferent)
			{
				print_array<int, 16>("History", history[i]);
				print_array<int, 16>("Current Membank", memBanks);

				std::cout << "Duplicate found! Lasted " << cycles + 1 << " cycles!" << std::endl;
				duplicateFound = true;
			}
		}
		if(duplicateFound)
		{
			std::copy(memBanks.begin(), memBanks.end(), repeatingMemBankFromPart1.begin());
			break;
		}

		// Add current memorybank to history. 
		history.push_back(memBanks);
	}
}
// == Part 2 ==================================================================================
{
	const std::array<int, 16> PART1_MEMBANK = repeatingMemBankFromPart1;
	std::array<int, 16> memBanks = repeatingMemBankFromPart1;

	for(unsigned cycles = 0;; ++cycles)
	{
		// Find the index of the highest current bankvalue.
		unsigned maxValIndex = 0;
		for(unsigned i=0; i<memBanks.size(); ++i) 
			if(memBanks[i] > memBanks[maxValIndex]) maxValIndex = i;

		// Check how many blocks should be distributed.
		int totalBlocksToMove = memBanks[maxValIndex];

		// Empty the current Bank.
		memBanks[maxValIndex] = 0;

		// Get the starting index for the distribution.
		unsigned tmpIndex = maxValIndex + 1;
		if(tmpIndex >= memBanks.size()) tmpIndex = 0;

		// Loop as long as there are blocks to distribute.
		while(totalBlocksToMove > 0)
		{
			++memBanks[tmpIndex]; // Add a block to the current bank ...
			--totalBlocksToMove; // ... and decrease the number of blocks that are to distribute.
			if((++tmpIndex) >= memBanks.size()) tmpIndex = 0; // Skip to the next bank (or first if it is the last).
		}

		bool isDifferent = false;
		for(unsigned j=0; j<memBanks.size(); ++j)
		{
			if(memBanks[j] != PART1_MEMBANK[j])
			{
				isDifferent = true;
				break;
			}
		}
		if(!isDifferent)
		{
			print_array<int, 16>("Duplicate from part1", PART1_MEMBANK);
			print_array<int, 16>("Current Membank", memBanks);

			std::cout << "Duplicate found! Lasted " << cycles + 1 << " cycles!" << std::endl;
			break;
		}
	}
}
}
