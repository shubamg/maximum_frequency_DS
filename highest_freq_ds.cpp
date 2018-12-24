# include<list>
# include<unordered_map>
# include<unordered_set>
# include <utility>
# include<iostream>
// Let us design a data structure for max frequency,
// where each element is of type long
// We can templatize it later

using node_type = std::pair<int, std::unordered_set<long>>;

class Node {
	node_type node;

public:
	Node(int freq, long element): node{freq, std::unordered_set<long>{element}} {}
	int& get_frequency() { return node.first;}
	std::unordered_set<long>& get_elements_with_frequency(){ return node.second; }

	void print() {
		std::cout<<"Frequency = "<<get_frequency()<<".\n List of elements is: ";
		auto it = get_elements_with_frequency().begin();
		std::cout<<(*it);
		for (++it; it != get_elements_with_frequency().end(); ++it)
			std::cout<<", "<<(*it);
		std::cout<<"\n\n";
	}
};

using list_type = std::list<Node>;
using list_iterator = list_type::iterator;
using hash_map = std::unordered_map<long, list_iterator>;

class Frequencies_and_elements {
	list_type frequencies_and_elements;

	// element guaranteed to be at element position
	list_iterator remove_element(list_iterator element_position, long element) {
		auto& hash_set = element_position->get_elements_with_frequency();
		hash_set.erase(element);
		if(element_position->get_elements_with_frequency().empty())
			return frequencies_and_elements.erase(element_position);
		return element_position;
	}

public:
	// returns new iterator to the position where the element was inserted
	// no removal of any element is done
	list_iterator insert_element(list_iterator insert_position,long element, int frequency) {
		if(insert_position != frequencies_and_elements.end() &&
				insert_position->get_frequency() == frequency) {
			insert_position->get_elements_with_frequency().insert(element);
			return insert_position;
		}
		else
			return frequencies_and_elements.insert(insert_position, Node{frequency, element});
	}

	list_iterator increment_frequency(list_iterator original_position,long element) {
		int frequency = original_position->get_frequency();
		auto insert_itr = original_position;
		++insert_itr;
		remove_element(original_position, element);
		return insert_element(insert_itr, element, frequency+1);
	}

	list_iterator decrement_frequency(list_iterator element_position, long element) {
		int frequency = element_position->get_frequency()-1;
		element_position = remove_element(element_position, element);
		if (!frequency)
			return frequencies_and_elements.end();
		if(element_position != begin() ) {
			auto temp_position = element_position;
			--temp_position;
			if (temp_position->get_frequency() == frequency)
				return insert_element(temp_position, element, frequency);
		}
		return insert_element(element_position, element, frequency);
	}


	list_iterator begin() { return frequencies_and_elements.begin();}
	list_iterator end() { return frequencies_and_elements.end();}

	void print_all() {
		if(frequencies_and_elements.empty())
			std::cout<<"The data structure is empty. No elements to show"<<std::endl;
		for(auto& lit: frequencies_and_elements) {lit.print();}
		std::cout<<"####################################################"<<std::endl;
	}

	void print_max_frequency() {
			auto end_iterator = frequencies_and_elements.end();
			if(end_iterator == frequencies_and_elements.begin())
				std::cout<<"Oops! The data structure is empty. No max frequency elements!!"<<std::endl;
			else {
				std::cout<<"Here are the elements with max frequency"<<std::endl;
				--end_iterator;
				end_iterator->print();
			}
			std::cout<<"####################################################"<<std::endl;
		}
};
class Max_frequency_DS {
	// list of (freq:int, elements with that freq: hash_set(long))
	// node of list is of type (int, hash_set(long))
	// hash_map of (elem:long -> (list of nodes))

	Frequencies_and_elements frequencies_and_elements;
	hash_map elements;

public:
	Max_frequency_DS (std::initializer_list<long> initializer_list):
		frequencies_and_elements{Frequencies_and_elements{}},
		elements{hash_map{}}  {
		for(auto element: initializer_list) {
			add(element);
		}
	}

	void add(long element) {
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

	void remove(long element) {
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
	Max_frequency_DS max_frequency_DS{400L, 500L};
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
