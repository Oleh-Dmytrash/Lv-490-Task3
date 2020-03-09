#include "StatisticsCounter.h"

std::vector<FileInfo> StatisticsCounter::CountProjectStats(std::map<std::string, std::string> files)
{
	std::vector<FileInfo> all_files_info;
	std::vector<std::future<FileInfo>> futures;
	int i{ 0 };
	for (auto current_file : files)
	{
		//futures.push_back(std::async(std::launch::async, &StatisticsCounter::CountFileStats, current_file));
		all_files_info.push_back(StatisticsCounter::CountFileStats(current_file));
		std::cout << i++ << '\n';
	}

	for (auto& th : futures)
	{
		all_files_info.push_back(th.get());
	}

	return all_files_info;
}

FileInfo StatisticsCounter::CountFileStats(std::pair<std::string, std::string> file)
{
	std::string file_text = file.second;
	FileInfo file_data;

	std::map<unsigned, unsigned> comment_intervals = FindCommentSections(file.second);
	std::map<unsigned, unsigned> blank_lines_and_comments;

	file_data.name = file.first;
	file_data.comment_lines_count = CountCommentSections(file_text, comment_intervals);
	file_data.blank_lines_count = CountBlankLineSections(file_text, comment_intervals, blank_lines_and_comments);

	blank_lines_and_comments = MergeCommentsAndBlankLines(blank_lines_and_comments, comment_intervals);

	file_data.code_lines_count = CountCodeLines(file_text, blank_lines_and_comments);

	return file_data;
}

std::map<unsigned, unsigned> StatisticsCounter::FindCommentSections(std::string file_text) {
	std::map<unsigned, unsigned> comment_intervals;
	unsigned found_pos_end{ 0 }, found_pos_start{ 0 };

	while ((found_pos_start = file_text.find("/*", (found_pos_end == 0) ? 0 : found_pos_end + 2)) != std::string::npos)
	{
		found_pos_end = file_text.find("*/", (found_pos_start == 0) ? 0 : found_pos_start + 2);
		if (found_pos_end > file_text.length())
			break;
		comment_intervals.emplace(found_pos_start, found_pos_end + 2);
	}


	found_pos_start = found_pos_end = 0;
	while ((found_pos_start = file_text.find("//", (found_pos_end == 0) ? 0 : found_pos_end + 1)) != std::string::npos)
	{
		found_pos_end = file_text.find("\n", (found_pos_start == 0) ? 0 : found_pos_start + 1);

		// if file_text.find() returns -1
		if (found_pos_end > file_text.length() - 1)
		{
			found_pos_end = file_text.length() - 1;
		}
		auto comment_inside_current = comment_intervals.upper_bound(found_pos_start);

		if (comment_inside_current != comment_intervals.end())
		{
			if (comment_inside_current->first > found_pos_start&& comment_inside_current->first <= found_pos_end)
			{
				comment_intervals.erase(comment_inside_current);
			}

		}

		if (comment_intervals.empty())
		{
			comment_intervals.emplace(found_pos_start, found_pos_end);
		}
		else
		{
			std::map<unsigned, unsigned>::iterator it = comment_intervals.lower_bound(found_pos_start);
			if (it != comment_intervals.begin()) --it;

			if (it->first < found_pos_start)
			{
				if (it->second < found_pos_start)
					comment_intervals.emplace(found_pos_start, found_pos_end);
			}
			else
			{
				comment_intervals.emplace(found_pos_start, found_pos_end);
			}

			if (found_pos_end == std::string::npos)
			{
				// If reached  the end of file
				if (it->second < found_pos_start)
					comment_intervals.emplace(found_pos_start, found_pos_end);
				break;
			}
		}

	}
	return comment_intervals;

}

unsigned StatisticsCounter::CountBlankLineSections(std::string file_text,
	std::map<unsigned, unsigned>& comment_intervals, std::map<unsigned, unsigned>& lines_without_code)
{
	unsigned blank_lines_count{ 0 };
	std::regex blank_line("\n[ |\t]*");
	std::regex first_blank_line("[ |\t]*");
	std::smatch match;

	std::sregex_iterator it{ file_text.begin(), file_text.end(), blank_line };
	std::sregex_iterator end;


	while (it != end)
	{
		unsigned pos1 = it->position();
		unsigned pos2 = it->position() + it->length();
		if (!comment_intervals.empty())
		{
			std::map<unsigned, unsigned>::iterator entry = comment_intervals.lower_bound(pos1);
			if (entry != comment_intervals.begin())
			{
				--entry;
			}

			if ((file_text.length() > pos2&& file_text[pos2] == '\n') || pos2 == file_text.length())
			{
				if (pos1 >= entry->second)
				{
					lines_without_code.emplace(pos1, pos2);
					++blank_lines_count;
				}
			}
		}
		else
		{
			if ((file_text.length() > pos2&& file_text[pos2] == '\n') || pos2 == file_text.length())
			{
				lines_without_code.emplace(pos1, pos2);
				++blank_lines_count;
			}

		}
		++it;
	}

	return blank_lines_count;
}

unsigned StatisticsCounter::CountCommentSections(std::string file_text, const std::map<unsigned, unsigned>& comment_intervals)
{
	unsigned comment_lines_count{ 0 };


	auto next_map_item = comment_intervals.begin();
	auto current_map_item = next_map_item;
	if (next_map_item != comment_intervals.end())
	{
		next_map_item++;
	}
	else return 0;

	unsigned current_block_end{ 0 };
	unsigned next_block_start{ current_map_item->first };
	std::string::iterator text_start = file_text.begin();
	while (current_map_item != comment_intervals.end())
	{
		std::string non_comment_substring = file_text.substr(current_block_end, next_block_start);

		if (current_block_end != 0)
		{
			if (std::count(non_comment_substring.begin(), non_comment_substring.end(), '\n') > 0)
			{
				comment_lines_count++;
			}
		}
		else comment_lines_count++;

		std::string comment_substring = file_text.substr(current_map_item->first, current_map_item->second - current_map_item->first);
		comment_lines_count += std::count(comment_substring.begin(), comment_substring.end(), '\n');


		current_block_end = current_map_item->second;
		current_map_item = next_map_item;
		next_block_start = (next_map_item != comment_intervals.end()) ? next_map_item->first : 0;
		if (next_map_item != comment_intervals.end())
			next_map_item++;
	}
	return comment_lines_count;
}

unsigned StatisticsCounter::CountCodeLines(std::string file_text, std::map<unsigned, unsigned>& comment_and_blank_intervals)
{
	if (comment_and_blank_intervals.empty())
	{
		int count = std::count(file_text.begin(), file_text.end(), '\n');
		count = (count != 0) ? count + 1 : 0;
		return count;
	}
	unsigned code_lines_count{ 0 };
	std::map<unsigned, unsigned>::iterator map_iter{ comment_and_blank_intervals.begin() }, prev_map_iter = map_iter;
	if (map_iter->first != 0)
		code_lines_count += std::count(file_text.begin(), file_text.begin() + map_iter->first, '\n') + 1;
	map_iter++;
	while (map_iter != comment_and_blank_intervals.end())
	{
		if (std::count(file_text.begin() + prev_map_iter->first, file_text.begin() + prev_map_iter->second, '\n') > 0)
		{
			code_lines_count++;
		}
		code_lines_count += std::count(file_text.begin() + prev_map_iter->second + 1,
			file_text.begin() + map_iter->first - 1, '\n');

		map_iter++;
		prev_map_iter++;
	}
	if (prev_map_iter->second + 1 < file_text.length())
	{
		code_lines_count += std::count(file_text.begin() + prev_map_iter->second + 1,
			file_text.begin() + file_text.length() - 1, '\n') + 1;
	}

	return code_lines_count;
}

std::map<unsigned, unsigned> StatisticsCounter::MergeCommentsAndBlankLines(std::map<unsigned, unsigned> comment_intervals,
	std::map<unsigned, unsigned> blank_lines_intervals)
{

	std::map<unsigned, unsigned> comments_and_blank_lines = comment_intervals;
	comments_and_blank_lines.merge(blank_lines_intervals);
	std::map<unsigned, unsigned>::iterator current_iterator = comments_and_blank_lines.begin();
	std::map<unsigned, unsigned>::iterator next_iterator = std::next(comments_and_blank_lines.begin());

	while (next_iterator != comments_and_blank_lines.end())
	{
		if (current_iterator->second == next_iterator->first ||
			current_iterator->second == next_iterator->first - 1)
		{
			auto new_element = std::make_pair(current_iterator->first, next_iterator->second);
			comments_and_blank_lines.erase(current_iterator);
			comments_and_blank_lines.erase(next_iterator);
			comments_and_blank_lines.emplace(new_element);
			current_iterator = comments_and_blank_lines.find(new_element.first);
			next_iterator = std::next(current_iterator);
		}
		else
		{
			current_iterator = next_iterator;
			next_iterator++;
		}
	}
	return comments_and_blank_lines;

}