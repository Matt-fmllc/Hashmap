#pragma once


namespace Custom {

	class CHashMap;


	// Hash Object
	// stores data element
	// overflow strategy is a simple linked
	// list of objects that land in the same bucket
	class CHashObject
	{
		friend CHashMap;

	private:
	protected:
		int m_Data;
		CHashObject* m_pNext;

	public:
		CHashObject();
		~CHashObject() {}
	};

	CHashObject::CHashObject() :
		m_Data(0),
		m_pNext(nullptr)
	{

	}


	// HashMap
	// Simple implementation
	// int data type

	#define iNumBuckets 1024
	class CHashMap
	{
	private:
		CHashObject*	m_Buckets[iNumBuckets];

	protected:
		int GenerateBucketLocation(int _iValue);

	public:
		CHashMap();
		~CHashMap();
		
		inline int InsertItem(int Data);
		inline int GetItem(int Val);
	};

	CHashMap::CHashMap() :
		m_Buckets{ 0 }
	{
	}
	CHashMap::~CHashMap()
	{
		for (int x = 0; x < iNumBuckets; x++) {
			if (m_Buckets[x]) {
				delete (m_Buckets[x]);
			}
		}
	}

	int CHashMap::GenerateBucketLocation(int _iValue)
	{
		//if (_iValue == 0)
		//	return 0;

		return _iValue % iNumBuckets;
	}

	int CHashMap::InsertItem(int Data)
	{
		int HashingValue = Data;

		CHashObject* pHashObj = new CHashObject();
		if (!pHashObj) {
			return -1;
		}
		pHashObj->m_Data = Data;
		int HashLocation = -1;
		HashLocation = GenerateBucketLocation(HashingValue);
		if (HashLocation < 0)
			return -1;

		//<TODO> insert hashing bucket overflow strategy
		m_Buckets[HashLocation] = pHashObj;

		return HashLocation;
	}

	int CHashMap::GetItem(int _iValue)
	{
		int iLoc = GenerateBucketLocation(_iValue);
		if (iLoc < 0)
			return -1;
		return m_Buckets[iLoc]->m_Data;
	}

}