#include"Parser.h"

bool Parser::is_code_before_comment(string& text, int range) const
{
	for (size_t i = 0; i < range; ++i)	//check if it's only comment, or we also have code before comment
		if (isalpha(text[i]))
			return true;
	return false;
}

bool Parser::is_code_after_comment(string& text, int index) const
{
	for (size_t i = index; i < text.size(); ++i)	//check if it's only comment, or we also have code after comment
		if (isalpha(text[i]))
			return true;
	return false;
}

bool Parser::are_only_spaces_and_tabs(string& text) const
{
	bool empty = true;//cheak for tabs and spaces==void
	for (auto& c : text)
		if (c != '\t' && c != ' ')
			empty = false;
	return empty;
}

void Parser::c_comment_count(ifstream& read, string& text)
{	
	do //now we should to find the end of c-comment
	{
		if (text.size() == 0)
		{
			++void_lines;
			continue;
		}
		else
		{
			if (are_only_spaces_and_tabs(text))
			{
				++void_lines;
				continue;
			}
		}
		if (text.find("*/") == string::npos)// didn't find end of c-comment
		{
			++comment_lines;
			continue;
		}
		else //found
		{
			++comment_lines;
			if (is_code_after_comment(text, text.find("*/")))
				++code_lines;
			break;
			//i do not check for comment line ,which could be after */
			//because comment already counted
		}

	} while (getline(read, text));
}

void Parser::Parse()
{
	if (file_path == "")throw exception("No filepath for parsing");

	ifstream read(file_path);
	string text;
	while (std::getline(read, text))
	{
		
		if (text.size() == 0)//line contains only \n symbol
		{
			++void_lines;
			continue;
		}
		else
			if (are_only_spaces_and_tabs(text))//try to check if line contains only tabs and spaces == void line
			{
				++void_lines;
				continue;
			}
		if (text.find("\"") == string::npos
			&& text.find("\'") == string::npos)//if string don't contains quotes
		{
			if (text.find("/*") != string::npos)//finded start of c-comment
			{
				if (text.rfind("*/") != string::npos)//it's c-comment for 1 line
				{
					++comment_lines;
					if (is_code_before_comment(text, text.find("/*"))
						|| is_code_after_comment(text, text.find("*/")))
						++code_lines;
					continue;
				}
				c_comment_count(read, text);//multiple line c-comment
				continue;
			}
			if (text.find("//") != string::npos)//finded line comment
			{
				++comment_lines;
				if (is_code_before_comment(text, text.find("//")))
					++code_lines;
				continue;
			}
		}
		else //line contains quotes
		{
			if ((text.find("//") < text.find("\"")//line comment before string  containers
				|| (text.find("//") < text.find("\'")))//line comment before char containers
				&& (text.find("//") != string::npos))
			{
				++comment_lines;
				if (is_code_before_comment(text, text.find("//")))
					++code_lines;
				continue;
			}
			if ((text.rfind("//") > text.rfind("\"")//line comment after string  containers
				|| (text.rfind("//") > text.rfind("\'")))//line comment after char containers
				&& (text.rfind("//") != string::npos))
			{
				++comment_lines;
				++code_lines;
				continue;
			}

			if ((text.find("*/") < text.find("\"")//c-comment before char containers
				|| (text.find("*/") < text.find("\'")))//c-comment before char containers
				&& (text.find("*/") != string::npos))
			{
				++comment_lines;
				if (is_code_before_comment(text, text.find("/*")))
					++code_lines;
				continue;
			}

			if ((text.rfind("/*") > text.rfind("\"")//c-comment after char containers
				|| (text.rfind("/*") > text.rfind("\'")))//c-comment after char containers
				&& (text.rfind("/*") != string::npos))
			{
				++code_lines;
				++comment_lines;
				if (text.rfind("/*") != string::npos)
				{
					if (text.rfind("*/") != string::npos)//it's c-comment for 1 line
						continue;
					c_comment_count(read, text);//multiple line c-comment
					continue;
				}
				//then it was line comment
			}

			//comment could be somewhere between string or char containers
			//I do not consider complex cases with multiple " "

			int quotes_for_char = 0;
			int quotes_for_string = 0;
			for (size_t comment = text.find("*/"); comment != string::npos; comment = text.find("*/"))
			{
				if (text.find("\'") < comment)//we know that comment couldn't be after all containers
					++quotes_for_char;
				else if (quotes_for_char % 2 == 0)//we are not in the one of containers, so it's comment
				{
					++comment_lines;
					break;
				}

				if (text.find("\"") < comment)
					++quotes_for_string;
				else if (quotes_for_string % 2 == 0)//we are not in the one of containers, so it's comment
				{
					++comment_lines;
					break;
				}
			}
			continue;
		}
		++code_lines;//if nothig was found, it's code
	}
}

string Parser::GetResult() const
{
	string file = file_path;
	file.erase(0, file.rfind("\\")+1);
	return file +"  void lines: " + to_string(void_lines) + "  comment lines: " + to_string(comment_lines) + "  code lines: " + to_string(code_lines) + "\n";
}