#pragma once

template<typename K, size_t iSize>
struct KeyHash {
	virtual unsigned long operator()(const K& Key) const
	{
		return (Key) % iSize;
	}
};


template<typename K, typename V>
class TNode {
public:
	K		Key;
	V		Value;
	TNode*	pNext;

	TNode(const K& key, const V& value) :
		Key(key), Value(value), pNext(nullptr)
	{}
	~TNode() {}
};

template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K,iSize> >
class THashMap
{
private:
	TNode<K,V>*	m_pBuckets[iSize];
	F			HashFunc;


protected:
public:
	THashMap() :
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

	inline int Put( const K& NewKey, const V& NewValue);
	inline bool Get( const K& Key, V& Value) const; 
	inline bool Remove(const K& Key);
};

template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K>>
int THashMap<K,V,iSize,F>::Put(const K& NewKey, const V& NewVal)
{
	unsigned long HashVal = HashFunc(NewKey);
	if (HashVal < 0)
		return -1;
	TNode<K, V>* Node = new TNode<K,V>(0,0);
	Node->Key = NewKey;
	Node->Value = NewVal;
	Node->pNext = m_pBuckets[HashVal];
	m_pBuckets[HashVal] = Node;
	
	return HashVal;
}

template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K>>
bool THashMap<K,V,iSize,F>::Get(const K& Key, V& Value) const
{
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

template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K>>
bool THashMap<K, V, iSize, F>::Remove(const K& Key)
{
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
