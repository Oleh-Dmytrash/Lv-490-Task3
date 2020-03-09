#pragma once
#include<string>
#include<fstream>
using namespace std;
class Parser
{
public:
	Parser() :file_path("") {};
	Parser(const char *file_path) : file_path(string(file_path)) {};

	void Parse();
	string GetResult() const;
private:
	bool is_code_before_comment(string& text, int range)const;
	bool is_code_after_comment(string& text, int index) const;
	bool are_only_spaces_and_tabs(string& text)const;
	void c_comment_count(ifstream& read, string& text);

	string file_path = "";
	int void_lines = 0;
	int comment_lines = 0;
	int code_lines = 0;
};
