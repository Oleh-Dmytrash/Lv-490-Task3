#include "CodeParser.h"
#include <iostream>

void CodeParser::Parse(string file_path)
{	
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
		if (is_comment_block)
		{
			++m_comment_lines_count;
		}
		else
			if (regex_match(text, expresion = "^\\s*"))
			{
				++m_blank_lines_count;
			}
			else
				if (regex_search(text, finded_words, expresion = "\\/\\*"))
				{
					++m_comment_lines_count;
					is_comment_block = true;

					int comment_position = finded_words.position(0);
					if (regex_search(text, finded_words, expresion = "[a-zA-Z0-9{}]+"))
					{
						if (finded_words.position(0) < comment_position)
						{
							++m_code_lines_count;
						}
					}
				}
				else
					if (is_comment_block)
					{
						++m_comment_lines_count;
						if (regex_search(text, finded_words, expresion = "\\*\\/"))
						{
							is_comment_block = false;
							int comment_position = finded_words.position(0);
							if (regex_search(text, finded_words, expresion = "[a-zA-Z0-9{}]+"))
							{
								if (finded_words.position(finded_words.size() - 1) < comment_position)
								{
									++m_code_lines_count;
								}
							}
						}
					}
					else
						if (regex_search(text, finded_words, expresion = "(\\/\\/)"))
						{
							++m_comment_lines_count;
							int comment_position = finded_words.position(0);
							if (regex_search(text, finded_words, expresion = "([a-zA-Z0-9{}]+)"))
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

		//cout << text << '\n';
	}
	
	// Close the file
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
