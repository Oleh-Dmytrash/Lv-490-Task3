#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <regex>

using namespace std;

class DirectoryReader
{
public:
	DirectoryReader() : m_directory_path("") { };
	DirectoryReader(string file_number) : m_directory_path(file_number) { };
	~DirectoryReader() {};

	void ReadDirectory();
	void ReadDirectory(string directory_path);

	int GetFileCount() const;
	string GetPath(int file_number);
	string GetDirectoryPath() const { return m_directory_path; }

	
	
private:	
	vector<string> m_directory_files_path;
	string m_directory_path;
};

