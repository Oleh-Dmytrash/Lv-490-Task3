#include "ProjectAnalyser.h"
using namespace std;

ProjectAnalyser::ProjectAnalyser(string paths ):path(paths) {};
void ProjectAnalyser::process(int num_threads)
{
	clock_t start;
	start = clock();
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		paths_vec.push_back(p.path().u8string());
	}
	for (int i = 0; i < num_threads; ++i)
	{
		vector<string> cur = vector(paths_vec.begin() + i * paths_vec.size() / num_threads, paths_vec.begin() + (i + 1) * paths_vec.size() / num_threads);
		threads.push_back(thread(&ProjectAnalyser::analyze, this, cur));
	}
	for (int i = 0; i < threads.size(); ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
}
void ProjectAnalyser::create_file()
{
	std::ofstream outstream("statistics.txt");
	outstream << "all lines: " << all_lines << endl << "blank lines: " << blank_lines << endl << "comment lines: " << comment_lines << endl;
	for (int i = 0; i < paths_vec.size(); ++i)
	{
		if (map.find(paths_vec[i]) != map.end())
			outstream << "path: " << paths_vec[i] <<endl<< map[paths_vec[i]] << endl;
	}
	outstream << "Time of execution: " << duration << endl;
}
void ProjectAnalyser::analyze(vector<string> str)
{
	for (string file_path : str) {
		std::ifstream f(file_path);
		std::string res((std::istreambuf_iterator<char>(f)),
			std::istreambuf_iterator<char>());
		f.close();
		Parser parser(res, file_path);
		if (!parser.isCFile())
			return;
		map[file_path] = parser.info();
		
		all_lines += parser.num_of_lines;
		blank_lines += parser.num_of_white_lines;
		comment_lines += parser.num_of_coments;
	}
}