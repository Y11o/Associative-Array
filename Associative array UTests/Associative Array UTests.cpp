#include "pch.h"
#include "CppUnitTest.h"
#include "..\Associative array\Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AssociativeArrayUTests
{
	TEST_CLASS(AssociativeArrayUTests)
	{
	public:
		TEST_METHOD(mapConstructor)
		{
			Map<int, int> map;
			map.insert(0, 1);
			Assert::IsTrue(map.findByKey(0)->value == 1);
			try
			{
				map.findByKey(10);
			}
			catch (const invalid_argument e)
			{
				Assert::AreEqual("Key not found", e.what());
			}
		}

		TEST_METHOD(mapInsert) {
			Map<int, int> map;
			map.insert(0, 1);
			map.insert(11, 10);
			map.insert(-5, 3);
			Assert::IsTrue(map.findByKey(0)->value == 1);
			Assert::IsTrue(map.findByKey(11)->value == 10);
			Assert::IsTrue(map.findByKey(-5)->value == 3);
			try
			{
				map.findByKey(18);
			}
			catch (const invalid_argument e)
			{
				Assert::AreEqual("Key not found", e.what());
			}
		}

		TEST_METHOD(mapClear) {
			Map<int, int> map;
			map.insert(0, 1);
			map.insert(12, 144);
			map.insert(11, 121);
			map.clear();
			try
			{
				map.print();
			}
			catch (const invalid_argument e)
			{
				Assert::AreEqual("Map is empty", e.what());
			}
		}

		TEST_METHOD(mapGetKeys) {
			Map<int, int> map;
			DLinkedList<int> keys;
			map.insert(0, 0);
			map.insert(1, 1);
			map.insert(2, 4);
			map.insert(3, 9);
			keys = map.getKeys();
			Assert::AreEqual(keys.at(0), 0);
			Assert::AreEqual(keys.at(1), 1);
			Assert::AreEqual(keys.at(2), 2);
			Assert::AreEqual(keys.at(3), 3);
		}

		TEST_METHOD(mapGetValues) {
			Map<int, int> map;
			DLinkedList<int> values;
			map.insert(0, 0);
			map.insert(1, 1);
			map.insert(2, 4);
			map.insert(3, 9);
			values = map.getValues();
			Assert::AreEqual(values.at(0), 0);
			Assert::AreEqual(values.at(1), 1);
			Assert::AreEqual(values.at(2), 4);
			Assert::AreEqual(values.at(3), 9);
		}

		TEST_METHOD(mapRemoveNode) {
			Map<int, int> map;
			map.insert(0, 0);
			map.insert(1, 1);
			map.insert(2, 4);
			map.insert(3, 9);
			map.removeNode(0);
			map.removeNode(2);
			Assert::IsTrue(map.findByKey(1)->value == 1);
			Assert::IsTrue(map.findByKey(3)->value == 9);
			try
			{
				map.findByKey(0);
			}
			catch (const invalid_argument e)
			{
				Assert::AreEqual("Key not found", e.what());
			}
			try
			{
				map.findByKey(2);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual("Key not found", e.what());
			}
		}

		TEST_METHOD(mapFindByKey) {
			Map<int, int> map;
			map.insert(0, 0);
			map.insert(1, 1);
			map.insert(2, 4);
			map.insert(3, 9);
			Assert::IsTrue(map.findByKey(0)->value == 0);
			Assert::IsTrue(map.findByKey(1)->value == 1);
			Assert::IsTrue(map.findByKey(2)->value == 4);
			Assert::IsTrue(map.findByKey(3)->value == 9);
			try
			{
				map.findByKey(4);
			}
			catch (const invalid_argument e)
			{
				Assert::AreEqual("Key not found", e.what());
			}
		}
	};
}
