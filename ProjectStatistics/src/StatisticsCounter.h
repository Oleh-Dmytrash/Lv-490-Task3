#pragma once
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
	static std::vector<FileInfo> CountProjectStats(std::map<std::string, std::string> files);
private:
	static FileInfo CountFileStats(std::pair<std::string, std::string> file);
	static std::map<unsigned, unsigned> FindCommentSections(std::string file_text);
	static unsigned CountCommentSections(std::string file_text, const std::map<unsigned, unsigned>& comment_intervals);
	static unsigned CountBlankLineSections(std::string file_text,
		std::map<unsigned, unsigned>& comment_intervals, std::map<unsigned, unsigned>& lines_without_code);
	static unsigned CountCodeLines(std::string file_text, std::map<unsigned, unsigned>& comment_and_blank_intervals);
	static std::map<unsigned, unsigned> MergeCommentsAndBlankLines(std::map<unsigned, unsigned> comment_intervals,
		std::map<unsigned, unsigned> blank_lines_intervals);

};

