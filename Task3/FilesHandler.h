#pragma once
#include"FilesFinder.h"
#include"Parser.h"
#include<thread>
#include<chrono>
#include<iostream>
using namespace std;

class FilesHandler
{
public:
	FilesHandler(string directory_path) :ff(directory_path){ff.FilesFind();};
	
	string ParseFiles ();

private:
	FilesFinder ff;
	vector<string> results;

	vector<shared_ptr<Parser>> ptr_parsers;
};