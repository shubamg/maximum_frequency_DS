#include <list>
#include <unordered_map>
#include "node.h"

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
