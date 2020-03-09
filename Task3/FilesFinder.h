#pragma once
#include<list>
#include<string>
#include<filesystem>
using namespace std;
using namespace filesystem;

class FilesFinder
{
public:
	FilesFinder(string path) :current_directory(path) {};
	FilesFinder(const char* str) :current_directory(string(str)) {};
	FilesFinder():current_directory("") {};
	~FilesFinder() {};

	void FilesFind();
	void FilesFind(const char* str);

	int GetFilesCount();
	string GetPath();
	string GetDirectory()const;
private:	
	string current_directory{""};
	list<string> files_to_parse;
};


