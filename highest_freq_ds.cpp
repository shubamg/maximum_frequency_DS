# include<list>
# include<unordered_map>
# include<unordered_set>
# include <utility>
# include<iostream>
// Let us design a data structure for max frequency,
// where each element is of type long
// We can templatize it later

template <typename T>
using node_type = std::pair<int, std::unordered_set<T>>;

template <typename T>
class Node {
	node_type<T> node;

public:
	Node(int freq, T element): node{freq, std::unordered_set<T>{element}} {}
	int& get_frequency() { return node.first;}
	std::unordered_set<T>& get_elements_with_frequency(){ return node.second; }

	void print() {
		std::cout<<"Frequency = "<<get_frequency()<<".\n List of elements is: ";
		auto it = get_elements_with_frequency().begin();
		std::cout<<(*it);
		for (++it; it != get_elements_with_frequency().end(); ++it)
			std::cout<<", "<<(*it);
		std::cout<<"\n\n";
	}
};

template <typename T>
using list_type = std::list<Node<T>>;

template <typename T>
using list_iterator = typename list_type<T>::iterator;

template <typename T>
using hash_map = std::unordered_map<T, list_iterator<T>>;

template <typename T>
class Frequencies_and_elements {
	list_type<T> frequencies_and_elements;

	// element guaranteed to be at element position
	list_iterator<T> remove_element(list_iterator<T> element_position, T element) {
		auto& hash_set = element_position->get_elements_with_frequency();
		hash_set.erase(element);
		if(element_position->get_elements_with_frequency().empty())
			return frequencies_and_elements.erase(element_position);
		return element_position;
	}

public:
	// returns new iterator to the position where the element was inserted
	// no removal of any element is done
	list_iterator<T> insert_element(list_iterator<T> insert_position,T element, int frequency) {
		if(insert_position != frequencies_and_elements.end() &&
				insert_position->get_frequency() == frequency) {
			insert_position->get_elements_with_frequency().insert(element);
			return insert_position;
		}
		else
			return frequencies_and_elements.insert(insert_position, Node<T>{frequency, element});
	}

	list_iterator<T> increment_frequency(list_iterator<T> original_position,T element) {
		int frequency = original_position->get_frequency();
		auto insert_itr = original_position;
		++insert_itr;
		remove_element(original_position, element);
		return insert_element(insert_itr, element, frequency+1);
	}

	list_iterator<T> decrement_frequency(list_iterator<T> element_position, T element) {
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


	list_iterator<T> begin() { return frequencies_and_elements.begin();}
	list_iterator<T> end() { return frequencies_and_elements.end();}

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
