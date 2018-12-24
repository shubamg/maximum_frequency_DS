# include<list>
# include<unordered_map>
# include<unordered_set>
# include <utility>
# include<iostream>
# include "node.h"
#include "frequencies_and_elements.h"

// Let us design a data structure for max frequency,
// where each element is of type long
// We can templatize it later


template <typename T>
using list_type = std::list<Node<T>>;

template <typename T>
using list_iterator = typename list_type<T>::iterator;

template <typename T>
using hash_map = std::unordered_map<T, list_iterator<T>>;

template <typename T>
class Max_frequency_DS {
	// list of (freq:int, elements with that freq: hash_set(long))
	// node of list is of type (int, hash_set(long))
	// hash_map of (elem:long -> (list of nodes))

	Frequencies_and_elements<T> frequencies_and_elements;
	hash_map<T> elements;

public:
	Max_frequency_DS (std::initializer_list<T> initializer_list):
		frequencies_and_elements{Frequencies_and_elements<T>{}},
		elements{hash_map<T>{}}  {
		for(auto element: initializer_list) {
			add(element);
		}
	}

	void add(T element) {
		std::cout<<"Adding "<<element<<std::endl;
		auto iterator_in_map = elements.find(element);
		if(iterator_in_map == elements.end()) {// element does not exist yet
			elements.insert(make_pair(element,
				frequencies_and_elements.insert_element(
						frequencies_and_elements.begin(), element, 1)));
		} else { // element already exists in hash map
			iterator_in_map->second =
			frequencies_and_elements.increment_frequency(iterator_in_map->second, element);
		}
		print_all();
	}

	void remove(T element) {
		std::cout<<"Removing "<<element<<std::endl;
		auto iterator_in_map = elements.find(element);
		if(iterator_in_map == elements.end()) {
			std::cout<<"ERROR: element does not exist"<<std::endl;
			throw "ERROR: element does not exist";
		}
		auto node_with_element = frequencies_and_elements.decrement_frequency(iterator_in_map->second, element);
		if (node_with_element == frequencies_and_elements.end())
			elements.erase(element);
		else
			iterator_in_map->second = node_with_element;
		print_all();
	}

	void print_all() { frequencies_and_elements.print_all(); }
	
	void print_max_frequency() { frequencies_and_elements.print_max_frequency(); }
};

int main() {
	Max_frequency_DS<long> max_frequency_DS{400L, 500L};
//	max_frequency_DS.add(1L);
//	max_frequency_DS.add(100L);
//	max_frequency_DS.add(93L);
//	max_frequency_DS.add(100L);
	max_frequency_DS.print_max_frequency();
	//	max_frequency_DS.remove(23L);
	max_frequency_DS.remove(400L);
	max_frequency_DS.print_max_frequency();
	max_frequency_DS.remove(500L);
	max_frequency_DS.print_max_frequency();
	max_frequency_DS.print_all();
	max_frequency_DS.remove(400L);
	return 0;
}
