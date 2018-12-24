#include <unordered_set>
#include <utility>

#ifndef NODE_H
#define NODE_H
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

#endif /*NODE_H*/

