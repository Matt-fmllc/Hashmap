
#include "pch.h"
#include <iostream>
#include "CHashmap.h"
#include <unordered_map>

#include "THashmap.h"

using namespace HashMapTemplate;

void TemplateHashMapPractice()
{
//	THashMap<int, int, 1024, THashMap<typename K,typename V,size_t 1024,typename F>::KeyHash> HashMap;

	THashMap<int, int, 1024, KeyHash<int, 1024> > HashMap;

	HashMap.Put(1, 5);
	HashMap.Put(2, 2);
	HashMap.Put(3, 7);
	HashMap.Put(2, 3);

	int iVal1, iVal2, iVal3, iVal4 = 0;
	HashMap.Get(1, iVal1);
	HashMap.Get(2, iVal2);
	HashMap.Get(3, iVal3);

	HashMap.Remove(2);
	HashMap.Get(2, iVal4);

	printf("\n iVal1 = %d, iVal2 = %d, iVal3 = %d, iVal4 = %d", iVal1, iVal2, iVal3, iVal4);


	THashMap<int, int, 3, KeyHash<int, 3> > HashMap2;
	HashMap2.Put(1, 1);
	HashMap2.Put(2, 2);
	HashMap2.Put(3, 3);
	HashMap2.Put(7, 7);
	HashMap2.Put(6, 6);
	HashMap2.Put(4, 4);
	HashMap2.Put(5, 5);

	int iVal5 = 0, iVal6 = 0, iVal7 = 0;
	HashMap2.Get(1, iVal1);
	HashMap2.Get(2, iVal2);
	HashMap2.Get(3, iVal3);

	HashMap2.Remove(2);
	HashMap2.Get(2, iVal4);
	
	HashMap2.Get(5, iVal5);
	HashMap2.Get(6, iVal6);
	HashMap2.Get(7, iVal7);

	printf("\n iVal1 = %d, iVal2 = %d, iVal3 = %d, iVal4 = %d, iVal5 = %d, iVal6 = %d, iVal7 = %d", iVal1, iVal2, iVal3, iVal4, iVal5, iVal6, iVal7);

}

void CustomHashMapPractice()
{
	Custom::CHashMap* pHashMap = new Custom::CHashMap();
	int iData[] = { 0,2000,1,30000,4,6,5000,9,7,8 };
	int iInputCount = sizeof(iData) / sizeof(int);

	for (int x = 0; x < iInputCount; x++) {
		pHashMap->InsertItem(iData[x]);
	}
	for (int x = 0; x < iInputCount; x++) {
		int iVal = pHashMap->GetItem(iData[x]);
		printf("\n # %d = %d", x, iVal);
	}
}


void CountCharacters(std::string szString)
{
	std::unordered_map<char, int> Characters;

	for (unsigned int x = 0; x < szString.size(); x++) {
		Characters[szString[x]] = Characters[szString[x]]++;
	}

	for (auto itMap = Characters.begin(); itMap != Characters.end(); ++itMap) {
		printf("\nKey: %c,  Value: %d", itMap->first, itMap->second);
	}

}


void STDHashMapPractice()
{
	int iInput[] = { 6,1,5,2,4,3 };
	std::unordered_map<int*, int> iHashMap;

	std::string szString = "abccccdd";
	CountCharacters(szString);

	// input
	for (int x = 0; x < (sizeof(iInput) / sizeof(int)); x++) {
		iHashMap.insert({ iInput + x, iInput[x] });

	}
	for (auto itMap = iHashMap.begin(); itMap != iHashMap.end(); ++itMap) {
		printf("\nKey: 0x%x,  Value: %d", (unsigned int)itMap->first, itMap->second);
	}

	// 2x insert
	printf("\n 2x");
	for (int x = 0; x < (sizeof(iInput) / sizeof(int)); x++) {
		iHashMap.insert({ iInput + x, iInput[x] });

	}
	for (auto itMap = iHashMap.begin(); itMap != iHashMap.end(); ++itMap) {
		printf("\nKey: 0x%x,  Value: %d, count: %d", (unsigned int)itMap->first, itMap->second, iHashMap.count(itMap->first));
	}
}




int main()
{
	STDHashMapPractice();
	CustomHashMapPractice();
	TemplateHashMapPractice();
}