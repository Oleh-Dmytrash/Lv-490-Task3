#pragma once
#include "CounterOfCode.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <atomic>
#include <exception>
#include <future>
using namespace std;

atomic<int > countFiles = 0;


void findFiles(string path, vector<filesystem::directory_entry>& a)
{
	for (const auto& entry : filesystem::directory_iterator(path))
	{
		string fileExtension = (entry.path()).string();
		fileExtension = fileExtension.substr(fileExtension.find_last_of(".") + 1);
		if (fileExtension == "h" ||
			fileExtension == "cpp" ||
			fileExtension == "c" ||
			fileExtension == "hpp")
		{
			a.push_back(entry);
		}
	}
}

bool isSpases(string line, int l, int r)
{
	for (int i = l; i < r; i++)
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			return false;
		}
	}
	return true;
}

string parse(filesystem::directory_entry path, string pathOutput)
{
	int countCode = 0;
	int countComment = 0;
	int countBlank = 0;
	ifstream file(path);
	string line;
	while (!file.eof())
	{
		std::getline(file, line);
		bool lineIsComment = false;
		if (isSpases(line, 0, line.size()))
		{
			countBlank++;
			continue;
		}

	tryAgain:
		int sleshStarIndex = line.find("/*");
		int starSleshIndex = line.find("*/");

		while (sleshStarIndex != string::npos && starSleshIndex != string::npos && sleshStarIndex < starSleshIndex)
		{
			lineIsComment = true;
			line.erase(sleshStarIndex, starSleshIndex + 2 - sleshStarIndex);
			sleshStarIndex = line.find("/*");
			starSleshIndex = line.find("*/");
		}
		int doubleSleshIndex = line.find("//");

		if (doubleSleshIndex != string::npos && (sleshStarIndex == string::npos || doubleSleshIndex < sleshStarIndex))
		{
			if (!lineIsComment)
			{
				countComment++;
			}
			if (!isSpases(line, 0, doubleSleshIndex))
			{
				countCode++;
			}
		}
		else if (sleshStarIndex != string::npos)
		{
			if (!isSpases(line, 0, sleshStarIndex))
			{
				countCode++;
			}
			countComment++;
			starSleshIndex = line.find("*/");
			while (starSleshIndex == string::npos)
			{
				countComment++;
				getline(file, line);
				starSleshIndex = line.find("*/");
			}
			if (lineIsComment)
			{
				countComment--;
			}
			lineIsComment = true;
			line.erase(0, starSleshIndex + 2);
			goto tryAgain;
		}
		else
		{
			if (!isSpases(line, 0, line.size()))
			{
				countCode++;
			}
		}
		if (lineIsComment)
		{
			countComment++;
		}
	}
	file.close();
	countFiles++;
	return "File name: " + path.path().string() + "\n"
		+ "Blank lines: " + to_string(countBlank) + "\n"
		+ "Comment lines: " + to_string(countComment) + "\n"
		+ "Code lines: " + to_string(countCode) + "\n\n";
}

void counter(string pathDirectory, string pathOutput)
{
	auto start = chrono::high_resolution_clock::now();
	vector<filesystem::directory_entry> filesPath;
	findFiles(pathDirectory, filesPath);
	ofstream output(pathOutput);
	if (!output.good())
	{
		string exc = "The system cannot find the path specified.: ";
		exc += pathOutput;
		throw exception(exc.c_str());
	}
	vector<std::future<string>> futureResults;
	for (int i = 0; i < filesPath.size(); i++)
	{
		futureResults.push_back(std::async(launch::async | launch::deferred, parse, filesPath[i], pathOutput));
	}
	for (int i = 0; i < filesPath.size(); i++)
	{
		output << futureResults[i].get();
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	output << "Amount files: " << countFiles << "\n";
	output << "Time of execution: " << duration.count() << "\n";
	output.close();
	//cout << "Time of execution: " << duration.count() << " microseconds\n";
}
