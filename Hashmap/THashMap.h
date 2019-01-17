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
		Key(key), Value(value)
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

	int Put( const K& NewKey, const V& NewValue);
	bool Get( const K& Key, V& Value);
	bool Remove(const K& Key);
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
	if (m_pBuckets[HashVal]) {
		// something exists in the bucket
		Node->pNext = m_pBuckets[HashVal];
		m_pBuckets[HashVal] = Node;
	}
	else {
		// nohing exists in bucket
		m_pBuckets[HashVal] = Node; 
	}
	return HashVal;
}

template<typename K, typename V, size_t iSize, typename F = KeyHashFunc<K>>
bool THashMap<K,V,iSize,F>::Get(const K& Key, V& Value)
{
	unsigned long HashVal = HashFunc(Key);
	if (HashVal < 0)
		return false;
	
	if (!m_pBuckets[HashVal])
		return false;
	TNode<K, V>* pNode = m_pBuckets[HashVal];

	// handle non-overflow case( ie-> only 1 thing in the bucket )
	if (pNode->pNext == nullptr) {
		Value = pNode->Key;
		return true;
	}
	
	// more than one thing in the bucket
	while (pNode->pNext) {
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
	return true;
}
