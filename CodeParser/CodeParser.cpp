#include "CodeParser.h"
#include <iostream>
#include <map>

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
			if (regex_search(text, finded_words, expresion = "\\*/"))
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
			if (regex_match(text, expresion = "^\\s*"))
			{
				++m_blank_lines_count;
			}
			else
				if (regex_search(text, finded_words, expresion = "(/\\*([\\S\\s]*?)\\*/)"))
				{
					regex_iterator<std::string::iterator> reg_iter_begin(text.begin(), text.end(), expresion);
					regex_iterator<std::string::iterator> reg_iter_end;

					vector<int> block_comment_position(text.length(), 0);

					while (reg_iter_begin != reg_iter_end)
					{
						for (unsigned int i = reg_iter_begin->position(); i < reg_iter_begin->position() + reg_iter_begin->str().length(); ++i)
						{
							block_comment_position[i] = 1;
						}
						++m_comment_lines_count;
						++reg_iter_begin;
					}

					regex_iterator<std::string::iterator> reg_iter_begin1(text.begin(), text.end(), expresion = "/{2,}");
					regex_iterator<std::string::iterator> reg_iter_end1;

					while (reg_iter_begin1 != reg_iter_end1)
					{
						if (block_comment_position[reg_iter_begin1->position()] == 0)
						{
							++m_comment_lines_count;

							for (unsigned int i = reg_iter_begin1->position(); i < block_comment_position.size() - 1; ++i)
							{
								if (block_comment_position[i] != block_comment_position[i + 1]) --m_comment_lines_count;
							}

							bool is_code = false;
							for (int i = 0; i < reg_iter_begin1->position(); ++i)
							{
								if (block_comment_position[i] != block_comment_position[i + 1] && block_comment_position[i] == 0) is_code = false;
								if (is_code)
								{
									continue;
								}
								else
								{
									if (block_comment_position[i] == 0 && text[i] != ' ' && text[i] != '\t')
									{
										++m_code_lines_count;
										is_code = true;
									}
									else
									{
										is_code = false;
									}
								}
							}

							break;
						}
						++reg_iter_begin1;
					}
				}
				else
					if (regex_search(text, finded_words, expresion = "/\\*"))
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
						if (regex_search(text, finded_words, expresion = "(//)"))
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
