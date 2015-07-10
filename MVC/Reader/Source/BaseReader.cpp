/******************************************************************************/
/*
\file	BaseReader.cpp
\author Chong Jun Xiang
\brief
Handle all reading & loading of files using this class.
Idea inspired by Tng Kah Wei.
Original code by Tng Kah Wei but modified to fit personal usage

Handles all txt file that are written in the same format

Format:
Made up of branches {} which contains Attributes [attribute name] <attribute value>
A branch can child branches

*Note*
All attribute name will be in CAPS for consistency purposes

E.g.
{
[ATTRIBUTE] Parent Branch
[ATTRIBUTE] Variable value

{
[ATTRIBUTE] Child Branch
}
}
*/
/******************************************************************************/
#include "BaseReader.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;

// Read and process the file
Branch BaseReader::FileToRead(const string fileName)
{
	vector<string> fileToProcess = ReadFile(fileName);

	return ProcessFile(fileToProcess);
}

// Read the file and store each line into a vector
vector<string> BaseReader::ReadFile(const string fileName)
{
	vector<string> result;
	ifstream file;

	file.open(fileName);

	if (file.is_open())
	{
		while (!file.eof())
		{
			string line;
			getline(file, line);
			line = Trim(line);

			// Ignore empty line and comments
			if (line.length() > 0 && line[0] != COMMENT)
			{
				result.push_back(line);
			}
		}
	}

	return result;
}

// Process the file based on the format
Branch BaseReader::ProcessFile(vector<string> branch)
{
	Branch result;
	Attribute tempAttrib;

	bool isChildBranch = false;
	bool validFile = true;

	// Get the parent branch
	for (size_t i = 0; i < branch.size(); ++i)
	{
		// Check the first char of each line
		if (branch[i][0] == BRANCH_START)
		{
			// Handle child branches
			if (isChildBranch)
			{
				// Gather everything within the child branch
				vector<string> childBranch;

				// Find the child branch's end
				short branchLevel = 0;
				// Find the number of attributes that belong to the child branch
				for (size_t j = i; j < branch.size(); ++j)
				{
					// a new child found
					if (branch[j][0] == BRANCH_START)
					{
						++branchLevel;
					}

					else if (branch[j][0] == BRANCH_END)
					{
						--branchLevel;
					}

					// Store everything that belongs to the child
					if (branchLevel < 1)
					{
						for (size_t startLine = i; startLine < j; ++startLine)
						{
							childBranch.push_back(branch[startLine]);
						}

						break;
					}
				}

				// Skip to the next BRANCH_START
				i += childBranch.size();

				// Pass this block in recursively and add to the top level branch /*very smart processing*/
				result.childBranches.push_back(ProcessFile(childBranch));
			}

			// First open branch
			else 
			{
				isChildBranch = true;
			}
		}

		// New attribute
		else if (branch[i][0] == ATTRIBUTE_START)
		{
			// Store attribute name
			string attribName = "";
			// Starts from 1 because of BRANCH_START
			size_t j = 1;
			while (branch[i][j] != ATTRIBUTE_END)
			{
				attribName += branch[i][j];
				++j;

				// Attribute does not have a close
				// Error handling
				if (j >= branch[i].length())
				{
					validFile = false;
					break;
				}
			}

			// Skip the ATTRIBUTE_END
			++j;

			// Store the attribute value
			string attribValue = "";
			while (j < branch[i].length())
			{
				attribValue += branch[i][j];
				++j;
			}

			// Special case attribute for "NAME"
			if (attribName == "NAME")
			{
				result.branchName = attribValue;
			}
			// Add attribute with value into branch
			else
			{
				tempAttrib.Set(attribName, attribValue);

				result.attributes.push_back(tempAttrib);

				// Reset temp storage
				tempAttrib.Set();
			}
		}
	}

	return result;
}

// Remove spaces and tab from the string
string BaseReader::Trim(string str)
{
	string result = "";

	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			result += str[i];
		}
	}

	return result;
}