#include"FilesHandler.h"

string FilesHandler::ParseFiles()
{	
	auto start = chrono::system_clock::now();

	vector<thread> threads;
	for(int i = 0; ff.GetFilesCount() != 0;++i)
	{
		ptr_parsers.emplace_back(new Parser(ff.GetPath().c_str()));
		threads.emplace_back(thread(&Parser::Parse,ptr_parsers[i]));
	}
	
	
	for (auto& c : threads)
	{
		if(c.joinable())
			c.join();
	}
	string info;

	for (auto parser : ptr_parsers)
			info += parser->GetResult();

	auto end = chrono::system_clock::now();
	info.append(to_string(threads.size()) + " file(s) was(re) parsed\n");
	info.append(to_string(chrono::duration_cast<std::chrono::milliseconds > (end - start).count()) + " milliseconds left\n");

	ofstream output(ff.GetDirectory() + "\\result.txt");
	if (!output.is_open()) throw exception("output file was not created");
	output << info;
	output.close();
	
	return info;
}