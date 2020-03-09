#include"FilesFinder.h"
#include <iostream>
using namespace std;

void FilesFinder::FilesFind()
{

	if (current_directory == "") throw exception("Directory was not matched");

	if (!filesystem::is_directory(current_directory)) throw exception("invalid directory path");

	files_to_parse.clear();
	for (const auto& direc_entry : directory_iterator(current_directory))
	{
		string extension = direc_entry.path().extension().string();
		if ((extension == ".cpp"
			|| extension == ".hpp"
			|| extension == ".c"
			|| extension == ".h")
			&& is_regular_file(direc_entry))
			files_to_parse.emplace_front(direc_entry.path().string());
	}
}

void FilesFinder::FilesFind(const char*str)
{
	if (str == "") throw exception("Directory was not matched");

	if (!filesystem::is_directory(str)) throw exception("invalid directory path");

	for (const auto& direc_entry : directory_iterator(str))
	{
		string extension = direc_entry.path().extension().string();
		if ((extension == ".cpp"
			|| extension == ".hpp"
			|| extension == ".c"
			|| extension == ".h")
			&& is_regular_file(direc_entry))
			files_to_parse.emplace_front(direc_entry.path().string());
	}
}

int FilesFinder::GetFilesCount()
{
	return files_to_parse.size();
}

string FilesFinder::GetPath()
{
	if (files_to_parse.size() == 0) return "";
	string temp = files_to_parse.front();
	files_to_parse.pop_front();
	return temp;
}

string FilesFinder::GetDirectory()const
{
	return current_directory;
}