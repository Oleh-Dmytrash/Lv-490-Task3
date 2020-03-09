#pragma once
#include "Parser.h"
#include <fstream>
#include <string>
#include <streambuf>
#include <regex>
#include <filesystem>
#include <thread>
#include <unordered_map>
#include <atomic>
#include <ctime>
namespace fs = std::filesystem;
using namespace std;
class ProjectAnalyser 
{
public:
	ProjectAnalyser(string paths);
	void process(int num_threads);
	atomic<int> all_lines;
	atomic<int> blank_lines;
	atomic<int> comment_lines;
	double duration;
	unordered_map <string, string> map;
	void create_file();
private:	
	vector<thread> threads;
	vector<string> paths_vec;
	string path;
	void analyze(vector<string> str);
	

};