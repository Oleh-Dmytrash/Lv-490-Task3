#include "pch.h"
#include "CppUnitTest.h"

#include"..//Task3/FilesFinder.h"
#include"..//Task3/FilesFinder.cpp"
#include"..//Task3/Parser.h"
#include"..//Task3/Parser.cpp"
#include"..//Task3/FilesHandler.h"
#include"..//Task3/FilesHandler.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTask3
{
	TEST_CLASS(UnitTestTask3)
	{		
	public:
		static FilesFinder ffm;
		static Parser prs;

		TEST_CLASS_INITIALIZE(ctor)
		{
			ffm.FilesFind("C:\\Users\\Dell\\source\\repos\\Task3\\Task3\\TEST");
			ffm.FilesFind();
		}
		TEST_METHOD(Files_finder_count_files)
		{
			Assert::IsTrue(ffm.GetFilesCount() == 2);
		}
		TEST_METHOD(Files_finder_invalid)//negative test
		{
			FilesFinder a("");
			auto foo = [&a]() {a.FilesFind(); };
			Assert::ExpectException<std::exception>(foo);
		}
		TEST_METHOD(Files_finder_GetPath)
		{
			Assert::IsTrue(ffm.GetPath() == string("C:\\Users\\Dell\\source\\repos\\Task3\\Task3\\TEST\\test.cpp"));
		}
		TEST_METHOD(Files_finder_GetDirectory)
		{
			Assert::IsTrue(ffm.GetDirectory() == string("C:\\Users\\Dell\\source\\repos\\Task3\\Task3\\TEST"));
		}
		TEST_METHOD(Parser_result)
		{
			prs.Parse();
			Assert::IsTrue(prs.GetResult()== "test.cpp  void lines: 7  comment lines: 14  code lines: 6\n");
		}	
		TEST_METHOD(FilesHandler_result)
		{
			FilesHandler a("C:\\Users\\Dell\\source\\repos\\Task3\\Task3\\TEST");
			string str = a.ParseFiles();
			Assert::IsTrue(str.substr(0,str.find("\n")+1)== "test.cpp  void lines: 7  comment lines: 14  code lines: 6\n");
		}
	};
	FilesFinder UnitTestTask3::ffm("C:\\Users\\Dell\\source\\repos\\Task3\\Task3\\TEST");
	Parser UnitTestTask3::prs("C:\\Users\\Dell\\source\\repos\\Task3\\Task3\\TEST\\test.cpp");
}
