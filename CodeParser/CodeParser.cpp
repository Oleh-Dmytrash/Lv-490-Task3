#include "CodeParser.h"
#include <iostream>
#include <map>

void CodeParser::Parse(string file_path)
{
	m_blank_lines_count = 0;
	m_code_lines_count = 0;
	m_comment_lines_count = 0;
	if (file_path == "" || !filesystem::is_regular_file(file_path)) return;//check if file path is valid

	m_file_path = file_path;
	string text;

	//open file
	ifstream read_file(file_path);
	if (!read_file.is_open()) throw exception((string("can't open file ").append(file_path)).c_str());

	bool is_comment_block = false;//boolean for comment block
	regex expresion("");
	smatch finded_words;//finded word array
	while (getline(read_file, text))
	{
		text += '\n';
		if (is_comment_block)//readed line is a comment block
		{
			++m_comment_lines_count;
			if (regex_search(text, finded_words, expresion = "\\*/"))//readed line is the end of comment block
			{
				is_comment_block = false;
				int comment_position = finded_words.position(0);
				if (regex_search(text, finded_words, expresion = "[a-zA-Z0-9{}]+"))//search code lines
				{
					if (finded_words.position(finded_words.size() - 1) < comment_position)
					{
						++m_code_lines_count;
					}
				}
			}
		}
		else
			if (regex_match(text, expresion = "^\\s*"))//readed line is empty
			{
				++m_blank_lines_count;
			}
			else
				if (regex_search(text, finded_words, expresion = "(/\\*([\\S\\s]*?)\\*/)"))//readed line includes block comments, linear comments and code
				{
					++m_comment_lines_count;
										
					regex_iterator<std::string::iterator> reg_iter_begin(text.begin(), text.end(), expresion);
					regex_iterator<std::string::iterator> reg_iter_end;

					vector<int> block_comment_position(text.length(), 0);

					while (reg_iter_begin != reg_iter_end)//in vector remember the comment block position
					{
						for (size_t i = reg_iter_begin->position(); i < reg_iter_begin->position() + reg_iter_begin->str().length(); ++i)
						{
							block_comment_position[i] = 1;
						}
						++reg_iter_begin;
					}					 					
										
					size_t block_begin_position = -1;
					if (regex_search(text, finded_words, expresion = "/\\*([^\\*]*?[^/]*?)\n"))//readed line include the begin of comment block
					{
						is_comment_block = true;
						block_begin_position = finded_words.position(0);
						for(size_t i = finded_words.position(0); i < finded_words.position(0) + finded_words.str(0).length() - 1; ++i)
						{
							block_comment_position[i] = 1;
						}
					}

					bool is_code = false;
					int slash_count = 0;
					for (size_t i = 0; i < block_comment_position.size(); ++i)
					{						
						if (block_comment_position[i] == 0 && text[i] != ' ' && text[i] != '\t')
						{
							is_code = true;
							if (text[i] == '/')
							{
								++slash_count;
								if (slash_count == 2)
								{
									if (i < block_begin_position) is_comment_block = false;
									if (is_code) ++m_code_lines_count;
									break;
								}
							}
							else
							{
								slash_count = 0;
							}
						}
					}										
				}
				else
					if (regex_search(text, finded_words, expresion = "/\\*"))//readed line is the begin of comment block
					{
						++m_comment_lines_count;
						is_comment_block = true;

						int comment_position = finded_words.position(0);
						if (regex_search(text, finded_words, expresion = "[a-zA-Z0-9{}]+"))//search code lines
						{
							if (finded_words.position(0) < comment_position)
							{
								++m_code_lines_count;
							}
						}
					}
					else
						if (regex_search(text, finded_words, expresion = "(//)"))//readed line is linear comment
						{
							++m_comment_lines_count;
							int comment_position = finded_words.position(0);
							if (regex_search(text, finded_words, expresion = "([a-zA-Z0-9{}]+)"))//search code lines
							{
								if (finded_words.position(0) < comment_position)
								{
									++m_code_lines_count;
								}
							}
						}
						else
						{
							++m_code_lines_count;
						}
	}
	read_file.close();
}

string CodeParser::GetResult()
{
	string result_string;
	result_string.append("File path: \t" + m_file_path + '\n');
	result_string.append("Blank lines count: \t" + to_string(m_blank_lines_count) + '\n');
	result_string.append("Comment lines count: \t" + to_string(m_comment_lines_count) + '\n');
	result_string.append("Code lines count: \t" + to_string(m_code_lines_count) + "\n\n");
	return result_string;
}
