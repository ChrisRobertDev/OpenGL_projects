#pragma once

#include <deque>
#include "Array.h"

// Returns id with the items position in the pool
template <typename T, std::size_t chunkSize>
class Pool {
public:
	Pool() { 
		elementCount = 0; 
		elements.emplace_back(Array<T, chunkSize>());
		tail = &elements[0];
	}
	
	std::size_t addElement(T el) {
		//T* c(new T(std::forward<Targs>(mArgs)...));

		if (elementCount % chunkSize == 0) {
			elements.emplace_back(Array<T, chunkSize>());

			elements[elements.size() - 2].setNext(&elements[elements.size() - 1]);
		}
		std::size_t i = elementCount / chunkSize;
		std::size_t j = elementCount % chunkSize;

		elements[i].add(el);
		elementCount++;

		return i * chunkSize + j;
		//return *c;
	}

	void reorder() {
		for (auto& c : elements) {
			if (c.hasNext())
				while (!c.full() && !c.getNext().empty())
					c.add(c.getNext().pop_back());
 		}
	}
	
	void pop_back(std::size_t index) {
		elements[index].pop_back();
		elementCount--;
	}

	void remove_at(std::size_t i, std::size_t j) {
		if (i < elements.size() && j < elements[i].getCount())
			if (elements[i][j] != NULL) {
				elements[i].remove_at(j);
				elementCount--;
			}
			else
				std::cout << "Element: " << i << "," << j << " is already gone!" << std::endl;
		else
			std::cout << "Indices out of range!!" << std::endl;
	}

	std::size_t size() { return elements.size(); }
	std::size_t getElementCount() { return elementCount; }
	T& getElementById(std::size_t id) {
		std::size_t i = id / chunkSize;
		std::size_t j = id % chunkSize;
		return elements[i][j];
	}
	Array<T, chunkSize>& getTail() const { return *tail; }
	Array<T, chunkSize>& at(std::size_t index) { return elements[index]; }

	std::deque<Array<T, chunkSize>> & getElements()  { return elements; }
private:
	std::deque<Array<T, chunkSize>> elements;
	std::size_t elementCount;
	Array<T, chunkSize>* tail;
	
};