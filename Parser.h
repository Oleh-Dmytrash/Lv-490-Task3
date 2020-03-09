#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <algorithm>
using namespace std;
class Parser 
{
public:
	Parser(string strr, string paths);
	int r;
	int num_lines = 0;
	int num_comment_lines = 0;
	int num_of_lines;
	int num_of_coments;
	int num_of_white_lines;
	bool isCFile();
	string info();
private:
	string str;
	string path;
	int countLinesRegex(regex x);
	regex r_num_of_lines;
	regex r_num_of_coments;
	regex r_num_of_white_lines;
	regex r_num_of_code;
	
	int countLinesFile();
	int countWhiteLines();
	int countCommentLines();
	int countCodeLines();
	int countFileSize();
};