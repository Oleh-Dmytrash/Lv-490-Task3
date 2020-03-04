#include "pch.h"
#include "CppUnitTest.h"
#include "../AnyType/AnyType.h"
#include "../AnyType/AnyType.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnyTypeUnitTest
{
	TEST_CLASS(AnyTypeUnitTest)
	{
	public:
		
		TEST_METHOD(InitTest1)
		{
			AnyType anyType(5);
			Assert::AreEqual(anyType.GetType(), std::string("int"), L"Should be int");
		}

		TEST_METHOD(InitTest2)
		{
			AnyType anyType(5);
			AnyType anyType1 = anyType;
			Assert::AreEqual(anyType1.GetType(), std::string("int"), L"Should be int");
		}

		TEST_METHOD(InitTest3)
		{
			AnyType anyType(5);
			AnyType anyType1(anyType);
			Assert::AreEqual(anyType1.GetType(), std::string("int"), L"Should be int");
		}

		TEST_METHOD(GetTypeTest1)
		{
			AnyType anyType = 5;			
			Assert::AreEqual(anyType.GetType(), std::string("int"), L"Should be int");
		}

		TEST_METHOD(GetTypeTest2)
		{
			AnyType anyType = 5;
			Assert::AreEqual(anyType.GetType(), std::string("bool"), L"Should be int");
		}
	};
}
