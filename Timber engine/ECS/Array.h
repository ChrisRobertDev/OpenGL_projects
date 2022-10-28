#pragma once
#include <iostream>
#include <array>

template<typename T,std::size_t size>
class Array {
private:
	std::array<T, size> a;
	std::size_t cursor;
	std::size_t totalSize = size;
	
	Array <T, size>* next;

	
public:
	Array() :cursor(0) { next = nullptr; }
	
	void swap(T& a, T&b) {
		T temp = a;
		a = b;
		b = temp;
	}

	void swap(T& a, T&b) const {
		T temp = a;
		a = b;
		b = temp;
	}

	void add(T element) {
		a[cursor] = element;
		cursor++;
	}
	T pop_back() {
		if (cursor > 0) {
			T t = a[cursor - 1];
			a[cursor - 1] = NULL;
			cursor--;
			return t;
		}
		
		return T();
	}

	void remove_at(std::size_t index) {
		swap(a[index], a[cursor - 1]);
		a[cursor - 1] = NULL;
		cursor--;
	}
	void clear() {
		while(cursor >0){
			a[--cursor] = NULL;
		}
	}
	T& begin() {
		return a[0];
	}

	bool empty() const { if (cursor == 0)return true; return false; }

	bool full() const { if (cursor == totalSize)return true; return false; }

	bool hasNext() const { if (next != nullptr) return true; return false;}

	T& operator [](std::size_t index) {
		if (a.empty() || a[index] == NULL)
			std::cout << "Cannot return a[index]!Array either empty or index out of subscript!" << std::endl;
		return a[index];

	}

	/*T& operator [](std::size_t index) const {
		if (a.empty() || a[index] == NULL)
			std::cout << "Cannot return a[index]!Array either empty or index out of subscript!" << std::endl;
		return  a[index];

	}*/

	T& at(std::size_t index) const {
		return a[index];
	}

	//cursor acts as the element count
	std::size_t getCursor() const { return cursor; }

	std::size_t getTotalSize() { return totalSize; }
	
	Array<T, size>& getNext() const { return *next; }
	
	void setNext(Array<T, size>* a) { next = a; }
};

