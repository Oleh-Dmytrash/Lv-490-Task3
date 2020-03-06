#pragma once
#include <string>
#include <sstream>
struct FileInfo
{
	std::string name;
	unsigned blank_lines_count{ 0 };
	unsigned comment_lines_count{ 0 };
	unsigned code_lines_count{ 0 };
	friend std::ostream& operator<<(std::ostream& os, FileInfo file_info);
};

inline std::ostream& operator<<(std::ostream& os, FileInfo file_info)
{
	using namespace std;
	stringstream ss;
	ss << "File name: " << file_info.name << "\n" <<
		"Number of blank lines: " << file_info.blank_lines_count << "\n" <<
		"Number of comment lines: " << file_info.comment_lines_count << "\n" <<
		"Number of code lines: " << file_info.code_lines_count << "\n\n";
	os << ss.str();
	return os;
}