#include <iostream>
#include <vector>
#include <cstring>
#include <forward_list>

template <typename K,typename V>

class HashMap
{
	class Entry{
		K key;
		V value;
	};
	std::vector<std::forward_list<Entry>> buckets;
	public:
	Hash(size_t s); // s : nombre de buckets
	~Hash();
	void Put(const & Entry);
	//pour trouver la case indice : fonction hachage : x/modulo
	void Get(const K);
	//si pas trouvé ret nullptr

};
