#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <atomic>
#include <array>
#include <map>
#include <algorithm>
#include <iostream>
#include <regex>
#include <thread>


class DirectoryReader
{
public:
	std::map<std::string, std::string> GetCppFilesInFolder(std::string path_to_folder);
	
};

