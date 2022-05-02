#pragma once
#include "Map.h"
#include <iostream>

using namespace std;

int main() {

	cout << "My map:" << endl;
	Map<int, int> map;
	map.insert(1, 1);
	map.insert(2, 4);
	map.insert(3, 9);
	map.insert(4, 16);
	map.insert(5, 25);
	map.insert(6, 36);
	map.insert(7, 12);
	map.insert(8, 10);
	map.print();
	cout << "Map without key 7:" << endl;
	map.removeNode(7);
	map.print();
	cout << "Map with key 7 and another value:" << endl;
	map.insert(7, 49);
	map.print();
	cout << "The list of Maps's keys:" << endl;
	DLinkedList<int> keysList = map.getKeys();
	for (size_t i = 0; i < keysList.get_size(); i++)
	{	
		cout << keysList.at(i) << endl;
	}
	cout << "The list of Map's values:" << endl;
	DLinkedList<int> valuesList = map.getValues();
	for (size_t i = 0; i < valuesList.get_size(); i++)
	{
		cout << valuesList.at(i) << endl;
	}
	return 0;
}