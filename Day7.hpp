/**
	--- AoC 2017 ---
	--- Day 7: Recursive Circus ---
	http://adventofcode.com/2017/day/7
-------------------------------------------------------------------------------------------------------------
Part 1:
One program at the bottom supports the entire tower. It's holding a large disc, and on the disc are balanced several more sub-towers. 
At the bottom of these sub-towers, standing on the bottom disc, are other programs, each holding their own disc, and so on. 
At the very tops of these sub-sub-sub-...-towers, many programs stand simply keeping the disc below them balanced but with no disc of their own.

You offer to help, but first you need to understand the structure of these towers. 
You ask each program to yell out their name, their weight, and (if they're holding a disc) the names of the programs 
immediately above them balancing on that disc. You write this information down (your puzzle input). 
Unfortunately, in their panic, they don't do this in an orderly fashion; by the time you're done, you're not sure which program gave which information.

For example, if your list is the following:
	pbga (66)
	xhth (57)
	ebii (61)
	havc (66)
	ktlj (57)
	fwft (72) -> ktlj, cntj, xhth
	qoyq (66)
	padx (45) -> pbga, havc, qoyq
	tknk (41) -> ugml, padx, fwft
	jptl (61)
	ugml (68) -> gyxo, ebii, jptl
	gyxo (61)
	cntj (57)

...then you would be able to recreate the structure of the towers that looks like this:
					gyxo
				  /     
			 ugml - ebii
		   /      \     
		  |         jptl
		  |        
		  |         pbga
		 /        /
	tknk --- padx - havc
		 \        \
		  |         qoyq
		  |             
		  |         ktlj
		   \      /     
			 fwft - cntj
				  \     
					xhth

In this example, tknk is at the bottom of the tower (the bottom program), and is holding up ugml, padx, and fwft. 
Those programs are, in turn, holding up other programs; in this example, none of those programs are holding up any other programs, 
and are all the tops of their own towers. (The actual tower balancing in front of you is much larger.)

Before you're ready to help them, you need to make sure your information is correct. What is the name of the bottom program?

-------------------------------------------------------------------------------------------------------------
Part 2:

*/
#pragma once
#include <map>
#include <utility>
#include <algorithm>

#include "Helper.hpp"

struct Program
{
	const std::string name;
	const unsigned weight;
	std::vector<const std::string> abovePrograms;
	Program(const std::string name, const unsigned weight, std::vector<const std::string> abovePrograms)
		: name(name), weight(weight), abovePrograms(abovePrograms)
	{}
};
std::ostream& operator<<(std::ostream& os, const Program& p)
{
	os << p.name << " (" << p.weight << ") ";
	if(p.abovePrograms.size() == 0) return os;
	os << " -> ";
	for(unsigned i=0; i<p.abovePrograms.size(); ++i) 
	{
		os << p.abovePrograms[i];
		if(i != p.abovePrograms.size() - 1) os << ", ";
	}
	return os;
}

const int find_weight_by_name(const std::string name, const std::vector<Program> progList)
{
	for each(auto& e in progList) if(e.name == name) return e.weight;
	std::cerr << "Couldnt find weight for name " << name << "!" << std::endl;
	return -1;
}

void day7()
{
	// List of all programs, converted from input-file.
	std::vector<Program> programList;

	// Read the list of programs from file.
	std::vector<const std::string> input = read_lines_from_file("input_day7.txt");

	for each(std::string line in input)
	{
		std::istringstream is(line);
		std::string name;
		std::string weight;
		std::string neighbour;
		is >> name >> weight >> neighbour >> neighbour;
		
		std::vector<const std::string> aboveNeighbours;
		do aboveNeighbours.push_back(neighbour);
		while(is >> neighbour);

		// Cut '(', ')', ','
		weight = weight.substr(1, weight.length() - 2);
		for(unsigned i=0; i<aboveNeighbours.size(); ++i) 
			if(aboveNeighbours[i].find(',') != std::string::npos) 
				aboveNeighbours[i] = aboveNeighbours[i].substr(0, aboveNeighbours[i].length() - 1);

		programList.push_back(Program(name, std::atoi(weight.c_str()), aboveNeighbours ));
	}

	print_vector<Program>("Program", programList);

// == Part 1 ==================================================================================
{
	// Find root node
	for each(auto& elem in programList)
	{
		bool foundInChild = false;
		for each(auto& sub_elem in programList)
		{
			auto match = std::find(sub_elem.abovePrograms.begin(), sub_elem.abovePrograms.end(), elem.name);
			if(match != sub_elem.abovePrograms.end()) 
				foundInChild = true;
		}
		if(!foundInChild && elem.abovePrograms.size() != 0)
		{
			std::cout << "Root: " << elem.name << std::endl;
		}
	}
}
// == Part 2 ==================================================================================
{
	for each(auto& prog in programList)
	{
		// If no children detected continue the loop.
		if(prog.abovePrograms.size() == 0) continue;
		
		// Check if the above programs have children. 
		bool aboveProgramsHaveChildren = false;
		for(unsigned i=0; i<programList.size(); ++i)
			if(prog.abovePrograms[0] == programList[i].name && programList[i].abovePrograms.size() != 0)
				aboveProgramsHaveChildren = true;
		if(aboveProgramsHaveChildren) continue; // Maybe here call func again for recursion ? ;|

		// Loop through the above program-names.
		const int singleValue = find_weight_by_name(prog.abovePrograms[0], programList);
		int totalValue  = 0;
		for each(auto& sub_prog in prog.abovePrograms)
		{
			const int sub_weight = find_weight_by_name(sub_prog, programList);
			std::cout << "Weight for " << sub_prog << " is " << sub_weight << "!" << std::endl;
			if(sub_weight != singleValue) 
				std::cout << "Different weight detected!" << sub_prog << ", " << sub_weight << ", " << singleValue << std::endl;
			totalValue += sub_weight;
		}
	}
}
}