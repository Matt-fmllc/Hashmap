#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Hashmap\THashMap.h"
using namespace HashMapTemplate;

#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashMapTemplateUnitTests
{		

	const int iTestRuns = 10000;

	void HitMap(THashMap<int, int, 1024, KeyHash<int, 1024>>* HashMap)
	{
		int iTestValues[iTestRuns] = { 0 };

		std::srand(7654321);

		for (int x = 0; x < iTestRuns; x++) {
			iTestValues[x] = std::rand();
			HashMap->Put(x, iTestValues[x]);
		}

		int iRetVal;
		for (int x = 0; x < iTestRuns; x++) {
			HashMap->Get(x, iRetVal);
			Assert::AreEqual(iRetVal, iTestValues[x]);
		}

		// remove the first half
		for (int x = 0; x < (iTestRuns / 2); x++) {
			HashMap->Remove(x);
		}
		// test that the first 1/2 were removed
		for (int x = 0; x < (iTestRuns / 2); x++) {
			HashMap->Get(x, iRetVal);
			Assert::AreNotEqual(iRetVal, iTestValues[x]);
		}
		// test that the second 1/2 are still there
		for (int x = (iTestRuns / 2); x < iTestRuns; x++) {
			HashMap->Get(x, iRetVal);
			Assert::AreEqual(iRetVal, iTestValues[x]);
		}
	}


	TEST_CLASS(HashMapTemplateUnitTest)
	{
	public:
		
		TEST_METHOD(TestPutsGetsOverflow)
		{
			THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;
			int iTestValues[iTestRuns] = { 0 };

			std::srand(7654321);

			for (int x = 0; x < iTestRuns; x++) {
				iTestValues[x] = std::rand();
				HashMap.Put(x, iTestValues[x]);
			}

			int iRetVal;
			for (int x = 0; x < iTestRuns; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreEqual(iRetVal, iTestValues[x]);
			}
		}

		TEST_METHOD(TestPutsGets)
		{
			THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;
			int iTestValues[iTestRuns] = { 0 };

			std::srand(7654321);

			for (int x = 0; x < 1024; x++) {
				iTestValues[x] = std::rand();
				HashMap.Put(x, iTestValues[x]);
			}

			int iRetVal;
			for (int x = 0; x < 1024; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreEqual(iRetVal, iTestValues[x]);
			}
		}
		TEST_METHOD(TestPutsGetsNegativeCases)
		{
			THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;
			int iTestValues[iTestRuns] = { 0 };

			std::srand(7654321);

			for (int x = 0; x < 1024; x++) {
				iTestValues[x] = std::rand();
				HashMap.Put(x, -1 * iTestValues[x]);
			}

			int iRetVal;
			for (int x = 0; x < 1024; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreNotEqual(iRetVal, iTestValues[x]);
			}
		}

		TEST_METHOD(TestPutsRemovesGetsOverflow)
		{
			THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;
			int iTestValues[iTestRuns] = { 0 };

			std::srand(7654321);

			for (int x = 0; x < iTestRuns; x++) {
				iTestValues[x] = std::rand();
				HashMap.Put(x, iTestValues[x]);
			}

			int iRetVal;
			for (int x = 0; x < iTestRuns; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreEqual(iRetVal, iTestValues[x]);
			}

			// remove the first half
			for (int x = 0; x < (iTestRuns / 2); x++) {
				HashMap.Remove(x);
			}
			// test that the first 1/2 were removed
			for (int x = 0; x < (iTestRuns / 2); x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreNotEqual(iRetVal, iTestValues[x]);
			}
			// test that the second 1/2 are still there
			for (int x = (iTestRuns / 2); x < iTestRuns; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreEqual(iRetVal, iTestValues[x]);
			}
		}

		TEST_METHOD(TestPutsRemovesGets)
		{
			THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;
			int iTestValues[iTestRuns] = { 0 };

			std::srand(7654321);

			for (int x = 0; x < 1024; x++) {
				iTestValues[x] = std::rand();
				HashMap.Put(x, iTestValues[x]);
			}

			int iRetVal;
			for (int x = 0; x < 1024; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreEqual(iRetVal, iTestValues[x]);
			}

			// remove the first half
			for (int x = 0; x < (1024 / 2); x++) {
				HashMap.Remove(x);
			}
			// test that the first 1/2 were removed
			for (int x = 0; x < (1024 / 2); x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreNotEqual(iRetVal, iTestValues[x]);
			}
			// test that the second 1/2 are still there
			for (int x = (1024/2); x < 1024; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreEqual(iRetVal, iTestValues[x]);
			}
		}

		TEST_METHOD(TestPutsRemovesGetsNegativeCases)
		{
			THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;
			int iTestValues[iTestRuns] = { 0 };

			std::srand(7654321);

			for (int x = 0; x < 1024; x++) {
				iTestValues[x] = std::rand();
				HashMap.Put(x, iTestValues[x]);
			}

			int iRetVal;
			for (int x = 0; x < 1024; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreNotEqual(iRetVal, -1 * iTestValues[x]);
			}

			// remove the first half
			for (int x = 0; x < (1024 / 2); x++) {
				HashMap.Remove(x);
			}
			// test that the first 1/2 were removed
			for (int x = 0; x < (1024 / 2); x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreNotEqual(iRetVal, iTestValues[x]);
			}
			// test that the second 1/2 are still there
			for (int x = (1024 / 2); x < 1024; x++) {
				HashMap.Get(x, iRetVal);
				Assert::AreEqual(iRetVal, iTestValues[x]);
			}
		}
		TEST_METHOD(TestMultithreadSafety)
		{
			THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;

			std::srand(7654321);
			// TODO: Your test code here
			std::thread T1(HitMap, &HashMap);
			std::thread T2(HitMap, &HashMap);
			std::thread T3(HitMap, &HashMap);

			T1.join();
			T2.join();
			T3.join();
		}

	};
}