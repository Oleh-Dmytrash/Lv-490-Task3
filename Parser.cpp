#include "Parser.h"

Parser::Parser(string strr, string paths) :str(strr), path(paths), r_num_of_lines("\n"), r_num_of_coments("(/\\*(.|\n)*?\\*/)\|(//[^\n\r]*)"), r_num_of_white_lines("^\s*$")
{
	if (isCFile())
	{
		num_of_lines = countFileSize();
		num_of_coments = countCommentLines();
		num_of_white_lines = countWhiteLines();
	}
};
int Parser::countLinesRegex(regex x)
{
	sregex_iterator iter(str.begin(), str.end(), x);
	sregex_iterator end;
	int res = 0;
	while (iter != end)
	{
		std::smatch match = *iter;
		std::string match_str = match.str();
		res = res + count(match_str.begin(), match_str.end(), '\n') + 1;
		++iter;
	}
	return res;
}
int Parser::countCommentLines()
{
	return countLinesRegex(r_num_of_coments);
}
int Parser::countWhiteLines()
{
	return countLinesRegex(r_num_of_white_lines)+1;
}
int Parser::countFileSize()
{
	return count(str.begin(), str.end(), '\n')+1;
}
string Parser::info() 
{
	
	string res = "";
	res = res + "number of lines: " + to_string(num_of_lines);
	res = res + "\nnumber of blank lines: " + to_string(num_of_white_lines);
	res = res + "\nnumber of lines with coments: " + to_string(num_of_coments);
	return res;
}
bool Parser::isCFile() 
{
	regex r_is_h_file(".*\.h");
	regex r_is_hpp_file(".*\.hpp");
	regex r_is_c_file(".*\.c");
	regex r_is_cpp_file(".*\.cpp");
	bool res = regex_match(path.begin(), path.end(), r_is_h_file);
	res = res || regex_match(path.begin(), path.end(), r_is_hpp_file);
	res = res || regex_match(path.begin(), path.end(), r_is_c_file);
	res = res || regex_match(path.begin(), path.end(), r_is_cpp_file);
	return res;
}