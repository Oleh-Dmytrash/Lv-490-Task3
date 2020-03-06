#pragma once
#include <vector>
#include <map>
#include <regex>
#include <thread>
#include <future>
#include <iostream>

#include "FileInfo.h"

class StatisticsCounter
{
public:
	std::vector<FileInfo> CountProjectStats(std::map<std::string, std::string> files);
private:
	FileInfo CountFileStats(std::pair<std::string, std::string> file);
	std::map<unsigned, unsigned> FindCommentSections(std::string file_text);
	unsigned CountCommentSections(std::string file_text, const std::map<unsigned, unsigned>& comment_intervals);
	unsigned CountBlankLineSections(std::string file_text,
		std::map<unsigned, unsigned>& comment_intervals, std::map<unsigned, unsigned>& lines_without_code);
	unsigned CountCodeLines(std::string file_text, std::map<unsigned, unsigned>& comment_and_blank_intervals);

};

