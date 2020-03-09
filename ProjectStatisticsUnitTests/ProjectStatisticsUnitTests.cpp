#include "CppUnitTest.h"
#include "DirectoryReader.h"
#include "DirectoryReader.cpp"
#include "StatisticsCounter.h"
#include "StatisticsCounter.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectStatisticsUnitTests
{
	TEST_CLASS(ProjectStatisticsUnitTests)
	{
	public:

		TEST_METHOD(DirectoryReaderTest1)
		{
			auto files = DirectoryReader::GetCppFilesInFolder("D:/Danylo_sad/Task3/ProjectStatistics/ProjectStatisticsUnitTests/test_data");
			Assert::IsTrue(files.size() == 5, L"files' size must be 4");
		}

		TEST_METHOD(DirectoryReaderTest2)
		{
			try
			{
				auto files = DirectoryReader::GetCppFilesInFolder("Wrong_path");
				Assert::Fail(L"The GetCppFilesInFolder must throw an exception");
			}
			catch (std::runtime_error & e)
			{
			}
		}


		// A file with only comments (various types)
		TEST_METHOD(StatisticsCounterTest1)
		{
			auto files = DirectoryReader::GetCppFilesInFolder("D:/Danylo_sad/Task3/ProjectStatistics/ProjectStatisticsUnitTests/test_data");
			auto all_files = StatisticsCounter::CountProjectStats(files);
			Assert::IsTrue(all_files[0].blank_lines_count == 0 &&
				all_files[0].code_lines_count == 0 &&
				all_files[0].comment_lines_count == 6, L"Comment lines count must be 6");
		}

		// A blank file
		TEST_METHOD(StatisticsCounterTest2)
		{
			auto files = DirectoryReader::GetCppFilesInFolder("D:/Danylo_sad/Task3/ProjectStatistics/ProjectStatisticsUnitTests/test_data");
			auto all_files = StatisticsCounter::CountProjectStats(files);
			Assert::IsTrue(all_files[1].blank_lines_count == 0 &&
				all_files[1].code_lines_count == 0 &&
				all_files[1].comment_lines_count == 0, L"All 3 results must be 0");
		}

		// A file with only blank lines
		TEST_METHOD(StatisticsCounterTest3)
		{
			auto files = DirectoryReader::GetCppFilesInFolder("D:/Danylo_sad/Task3/ProjectStatistics/ProjectStatisticsUnitTests/test_data");
			auto all_files = StatisticsCounter::CountProjectStats(files);
			Assert::IsTrue(all_files[2].blank_lines_count == 5 &&
				all_files[2].code_lines_count == 0 &&
				all_files[2].comment_lines_count == 0, L"The number of blank lines must be 5");
		}

		//A file with only code
		TEST_METHOD(StatisticsCounterTest4)
		{
			auto files = DirectoryReader::GetCppFilesInFolder("D:/Danylo_sad/Task3/ProjectStatistics/ProjectStatisticsUnitTests/test_data");
			auto all_files = StatisticsCounter::CountProjectStats(files);
			Assert::IsTrue(all_files[3].blank_lines_count == 0 &&
				all_files[3].code_lines_count == 6 &&
				all_files[3].comment_lines_count == 0, L"The number of code lines must be 6");
		}

		//Mixed code and comment lines
		TEST_METHOD(StatisticsCounterTest5)
		{
			auto files = DirectoryReader::GetCppFilesInFolder("D:/Danylo_sad/Task3/ProjectStatistics/ProjectStatisticsUnitTests/test_data");
			auto all_files = StatisticsCounter::CountProjectStats(files);
			Assert::IsTrue(all_files[4].blank_lines_count == 0 &&
				all_files[4].code_lines_count == 2 &&
				all_files[4].comment_lines_count == 2, L"The number of code/comment lines must be 2");
		}




	};
}
