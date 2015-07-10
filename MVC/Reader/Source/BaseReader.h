/******************************************************************************/
/*
\file	BaseReader.h
\author Chong Jun Xiang
\brief
Handle all reading & loading of files using this class
Idea inspired by Kah Wei
Original code by Kah Wei but modified to fit personal usage

Handles all txt file that are written in the same format

Format:
Made up of branches {} which contains Attributes [attribute name] <attribute value>
A branch can child branches

*Note*
All attribute name will be in CAPS for consistency purposes

E.g.
{
	[NAME] Parent Branch
	[ATTRIBUTE] Parent variable value

	{
		[NAME] Child Branch
		[ATTRIBUTE] Child variable value
	}
}
*/
/******************************************************************************/
#ifndef BASE_READER_H
#define BASE_READER_H

#include "BranchReader.h"

// A class created to handle any txt files that are written in the same format
class BaseReader
{
private:
	static const char BRANCH_START = '{';
	static const char BRANCH_END = '}';
	static const char ATTRIBUTE_START = '[';
	static const char ATTRIBUTE_END = ']';
	static const char COMMENT = '#';

public:
	static Branch FileToRead(const string fileName);

	static vector<string> ReadFile(const string fileName);
	static Branch ProcessFile(vector<string> branch);
	
	static string Trim(const string str);
	
};

#endif