#include "pch.h"
#include "CppUnitTest.h"
#include "../CodeParser/CodeParser.h"
#include "../CodeParser/CodeParser.cpp"
#include "../CodeParser/DirectoryReader.h"
#include "../CodeParser/DirectoryReader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeParserUnitTest
{
	TEST_CLASS(CodeParserUnitTest)
	{
	public:
		static DirectoryReader m_dir_reader;
		static CodeParser m_code_parser;

		TEST_CLASS_INITIALIZE(Setup)
		{
			m_dir_reader.ReadDirectory("D:/programing/softserve/anytype_copy/AnyType/");
		}

		TEST_METHOD(ReadDirectoryTest1)
		{
			Assert::AreEqual(m_dir_reader.GetFileCount(), 5, L"File count should be 5");
		}	

		TEST_METHOD(ReadDirectoryTest2)
		{
			string file_path("D:/programing/softserve/anytype_copy/AnyType/AnyType.cpp");
			Assert::AreEqual(m_dir_reader.GetPath(0), file_path, 
				L"File count should be D:/programing/softserve/anytype_copy/AnyType/AnyType.cpp");
		}

		TEST_METHOD(ReadDirectoryNegativeTest)//negative test
		{
			string file_path("D:/programing/softserve/anytype_copy/AnyType/AnyType.cpp");
			Assert::AreEqual(m_dir_reader.GetPath(1), file_path, L"Negative test");
		}

		TEST_METHOD(ParseFileTest1)
		{
			m_code_parser.Parse(m_dir_reader.GetPath(4));
			Assert::AreEqual(m_code_parser.GetBlankLinesCount(), 4, L"Blank lines count should be 4");
		}

		TEST_METHOD(ParseFileTest2)
		{
			m_code_parser.Parse(m_dir_reader.GetPath(0));
			Assert::AreEqual(m_code_parser.GetCommentLinesCount(), 2, L"Comment lines count should be 2");
		}

		TEST_METHOD(ParseFileTest3)
		{
			m_code_parser.Parse(m_dir_reader.GetPath(2));
			Assert::AreEqual(m_code_parser.GetCodeLinesCount(), 8, L"Code lines count should be 8");
		}

		TEST_METHOD(ParseFileNegativeTest)//negative test
		{
			m_code_parser.Parse(m_dir_reader.GetPath(0));
			Assert::AreEqual(m_code_parser.GetCommentLinesCount(), 20, L"Comment lines count should be 2");
		}
	};
	DirectoryReader CodeParserUnitTest::m_dir_reader;
	CodeParser CodeParserUnitTest::m_code_parser;
}
