#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include <cstddef>
#include <iostream>
#include <forward_list>
#include <vector>

namespace pr {

template <typename K, typename V>
class HashMap {


public:
    class Entry {
    public:
        const K key;
        V value;;
        Entry(const K &k, const V &v) : key(k), value(v) {}
    };

    class iterateur{

    		std::vector<std::forward_list<Entry>> & buckets;
    		typedef typename std::vector<std::forward_list<Entry>>::iterator vit_t;
    		vit_t  vit;
    		typedef typename std::forward_list<Entry>::iterator lit_t;
    		lit_t  lit;
    	public:
    		    iterateur(std::vector<std::forward_list<Entry>> & buckets_, vit_t & vit, lit_t & lit)
    		    	:buckets(buckets),vit(vit),lit(lit)
    		    { }
    			iterateur & operator++() //incrementer
				{
    				lit++;
    				if(lit==vit->end())
    				{
    					// au bout de la liste
    					// chercher une liste non vide
    					++vit;
    					while (vit->empty() && vit != buckets.end()) {
    						++vit;
    					}
    					if (vit != buckets.end()) {
    						lit = vit->begin();
    					}
    				}
				}

    			Entry & operator*() {
    				return *lit;
    			}

    			bool operator != (const iterateur & other) {
    				return vit != other.vit || lit != other.lit;
    			}

    	};


private:
    std::vector<std::forward_list<Entry>> buckets; // Tableau de listes chaînées
    size_t sz;         // Nombre total d'entrées

public:
    // Constructeur
    HashMap(size_t size): buckets(size), sz(0) {
        // Initialisation de la table de hachage avec la taille spécifiée
    }

    // Destructeur
    ~HashMap()
    {
    	sz = 0;
    }


    iterateur begin() {
    	auto vit = buckets.begin();
    	// devclaer vit sur non vide
    	auto lit = vit->begin();
    	return iterateur(buckets,vit,lit);
    }

    iterateur end() {

    }

    // Obtient la valeur associée à une clé
    V* get(const K &key){
        size_t h = std::hash<K>()(key);
        size_t target = h % buckets.size();
        for (Entry& ent : buckets[target]) {
            if (ent.key == key) {
                return &ent.value;
            }
        }
        return nullptr;
    }

    // Insère une paire clé-valeur
    // Si la clé existe déjà, met à jour la valeur
    // Retourne true si la mise à jour a été effectuée, sinon false
    bool put(const K &key, const V &value){
        size_t h = std::hash<K>()(key);
        size_t target = h % buckets.size();
        for (Entry& ent : buckets[target]) {
            if (ent.key == key) {
                ent.value = value;
                return true;
            }
        }
        sz++;
        buckets[target].emplace_front(key, value);
        return false;
    }

    // Retourne le nombre d'entrées dans le HashMap
    size_t size() const{
        return sz;
    }

    // Redimensionne le HashMap pour augmenter sa capacité
    void grow()
    {
		HashMap other = HashMap(buckets.size() * 2);
		for (auto& list : buckets) {
			for (auto& entry : list) {
				other.put(entry.key, entry.value);
			}
		}
		buckets = other.buckets;
    }

    void show()
    {
    	std::cout<<"Eleme 1 : "<<*(get("e"))<<std::endl;
    }

};

} // namespace pr


#endif /* SRC_HASHMAP_H_ */
