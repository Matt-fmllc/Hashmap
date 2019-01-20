#pragma once

#include <mutex>
#include <memory>

namespace HashMapTemplate {


	// Hash Function
	// simple hash implementation across the range of buckets
	template<typename K, size_t iSize>
	struct KeyHash {
		virtual unsigned long operator()(const K& Key) const
		{
			return (Key) % iSize;
		}
	};


	// Hash Map Node (Template)
	// Data element of the map
	// maintains the map structure
	// stores the data element

	template<typename K, typename V>
	class TNode {
	public:
		K		Key;
		V		Value;
		TNode*	pNext;

		TNode(const K& key, const V& value) noexcept :
			Key(key), Value(value), pNext(nullptr)
		{}
		~TNode() {}
	};


	// Template Hash Map
	// O(n) = O(1) 
	// Note* - only if bucket is empty, overflow case adds cost
	// as an example, 1024 elements in a single bucket
	// Still consider this as O(1)
	//
	// Generic Hash Map
	// Basic Methods
	//		Put - Adds an element to the Hash Map
	//		Get - Retrieves an element from the Hash Map
	//		Remove - Removes an element from the Hash Map
	//
	// User must implement the Hash function
	// Since the objects are an unknown type
	// an example, or a default one, exists 
	// for use at the top of the file

	template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K, iSize> >
	class THashMap
	{
	private:
		TNode<K, V>*	m_pBuckets[iSize];
		F				HashFunc;

		std::mutex		m_Mutex;


	protected:
	public:
		THashMap() noexcept :
			m_pBuckets{ 0 }
		{

		}
		virtual ~THashMap()
		{
			for (int x = 0; x < iSize; x++) {
				if (m_pBuckets[x]) {
					delete m_pBuckets[x];
				}
			}
		}

		inline virtual  int Put(const K& NewKey, const V& NewValue);
		inline virtual bool Get(const K& Key, V& Value);
		inline virtual bool Remove(const K& Key);
	};

	// Put
	// Adds an element to the hash map
	template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K,iSize>>
	int THashMap<K, V, iSize, F>::Put(const K& NewKey, const V& NewVal)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		unsigned long HashVal = HashFunc(NewKey);
		if (HashVal < 0)
			return -1;
		TNode<K, V>* Node = new TNode<K, V>(0, 0);
		Node->Key = NewKey;
		Node->Value = NewVal;
		Node->pNext = m_pBuckets[HashVal];
		m_pBuckets[HashVal] = Node;

		return HashVal;
	}


	// Get
	// Retrieves an element from the hash map
	template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K,iSize>>
	bool THashMap<K, V, iSize, F>::Get(const K& Key, V& Value)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		unsigned long HashVal = HashFunc(Key);
		if (HashVal < 0)
			return false;

		TNode<K, V>* pNode = m_pBuckets[HashVal];
		while (pNode) {
			if (pNode->Key == Key) {
				Value = pNode->Value;
				return true;
			}
			pNode = pNode->pNext;
		}
		// Not Found
		return false;
	}


	// Remove
	// Removes an element from the hash map
	template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K,iSize>>
	bool THashMap<K, V, iSize, F>::Remove(const K& Key)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		int iHashVal = HashFunc(Key);
		if (iHashVal < 0)
			return false;

		TNode<K, V>* pNode = m_pBuckets[iHashVal];
		TNode<K, V>* pNewList = nullptr;
		// technically don't need this check, but
		// want to indicate nothing was deleted
		// when the bucket is empty
		// if I let it fall through, it will return
		// a false positive
		if (!pNode)
			return false;

		// delete the nodes that match keys
		while (pNode) {
			TNode<K, V>* pTemp = pNode->pNext;
			if (pNode->Key == Key) {
				// keys match, delete this node
				delete pNode;
			}
			else if (!pNewList) {
				// keys did not match, this node 
				// is first in list, start the new list
				pNewList = pNode;
				pNewList->pNext = nullptr;
			}
			else {
				// this node is to be kept, keys did not match
				// add this node to the list
				pNode->pNext = pNewList;
				pNewList = pNode;
			}
			pNode = pTemp;
		}
		m_pBuckets[iHashVal] = pNewList;
		return true;
	}

} // end namespace
