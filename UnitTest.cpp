#include "pch.h"
#include "CppUnitTest.h"
//#include "..//Task_3/CountOfCode.h"
//#include "..//Task_3/CounterOfCode.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestCounter
{
	TEST_CLASS(UnitTestCounter)
	{
	public:

		TEST_METHOD(Exception)
		{
			string path("C://SoftSerw//non-existent");
			string pathOutput("C:/SoftSerw/example/output.txt");
			try
			{
				counter(path, pathOutput);
				Assert::IsTrue(0);
			}
			catch (exception & exc)
			{
				Assert::IsTrue(1);
			}
		}
		TEST_METHOD(CorrectCount)
		{
			string path("C://Test");
			string pathOutput("C:/Test/output.txt");
			counter(path, pathOutput);
			ifstream output(pathOutput);
			string line;
			getline(output, line);
			getline(output, line);
			Assert::IsTrue(line == "Blank lines: 3");
			getline(output, line);
			Assert::IsTrue(line == "Comment lines: 3");
			getline(output, line);
			Assert::IsTrue(line == "Code lines: 3");
			getline(output, line);
			getline(output, line);
			Assert::IsTrue(line == "Amount files: 1");
			output.close();
		}
	};
}
