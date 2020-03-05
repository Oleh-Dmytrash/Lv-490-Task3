#pragma once

#include <fstream>
#include <filesystem>
#include <regex>
#include <string>

using namespace std;

class CodeParser
{
public:
	CodeParser() : m_blank_lines_count(0),
		m_comment_lines_count(0), m_code_lines_count(0) {};
	CodeParser(string& file_path) : m_file_path(file_path), m_blank_lines_count(0),
	m_comment_lines_count(0), m_code_lines_count(0) {};
	~CodeParser() {};

	void Parse(string file_path);

	string GetResult();
	string GetFilePath() const { return m_file_path; }
	int GetBlankLinesCount() const { return m_blank_lines_count; };
	int GetCommentLinesCount() const { return m_comment_lines_count; };
	int GetCodeLinesCount() const { return m_code_lines_count; };	
private:
	string m_file_path;
	int m_blank_lines_count;
	int m_comment_lines_count;
	int m_code_lines_count;	
};

