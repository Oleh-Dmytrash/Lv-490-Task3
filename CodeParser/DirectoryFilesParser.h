#pragma once

#include <thread>
#include <vector>
#include <chrono>
#include <memory>
#include "CodeParser.h"
#include "DirectoryReader.h"

class DirectoryFilesParser
{
public:
	DirectoryFilesParser() {};
	~DirectoryFilesParser() {};
	string ParseFiles(string& directory_path);
private:
	vector<shared_ptr<CodeParser>> m_parsers;
};

