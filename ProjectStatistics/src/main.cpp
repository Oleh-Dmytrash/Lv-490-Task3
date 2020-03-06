#include <iostream>
#include <fstream>
#include "DirectoryReader.h"
#include "StatisticsCounter.h"
#include "Timer.h"
int main()
{
	Timer timer;
	DirectoryReader reader;
	StatisticsCounter counter;
	timer.Start();
	std::ofstream output_file( "files_info.txt" );
	auto files = reader.GetCppFilesInFolder("NewFolder1");
	auto datas = counter.CountProjectStats(files);
	output_file << "Time in ms  = " << timer.GetTimePassed() << std::endl;
	for (auto file_data : datas)
	{
		output_file << file_data;
	}
}

