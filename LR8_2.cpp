#include <iostream>

using namespace std;

template <typename T, int size>

struct List {
	T elements[size];
	int true_size = 0;
};

template <typename T, int size>

void constructor(List<T, size>& list) {
	for (T& i : list.elements) {
		i = NULL;
	}
}

template <typename T, int size>

void destructor(List<T, size>& list) {
	for (int i = 0; i < list.true_size; ++i) { 
		list.elements[i] = NULL;
	}
}

template <typename T, int size>

int count(const List<T, size>& list) {
	return list.true_size;
}

template <typename T, int size>

void add_last(List<T, size>& list, T new_information) {
	list.elements[list.true_size] = new_information;
	++list.true_size;
}

template <typename T, int size>

void add_by_index(List<T, size>& list, T new_information, int index) {
	if (index >= list.true_size) {
		list.elements[list.true_size] = new_information;
	}
	else {
		list.elements[index] = new_information;
	}
	++list.true_size;
}

template <typename T, int size>

T pop_first(List<T, size>& list) {
	T tmp = list.elements[0];
	list.elements[0] = NULL;
	for (int i = 0; i < list.true_size - 1; i++) {
		swap(list.elements[i], list.elements[i + 1]);
	}
	if (tmp != NULL)
	{
		--list.true_size;
	}
	return tmp;
}

template <typename T, int size>

T pop_last(List<T, size>& list) {
	T tmp = list.elements[list.true_size - 1];
	list.elements[list.true_size - 1] = NULL;
	if (list.true_size != 0) {
		--list.true_size;
	}
	return tmp;
}

template <typename T, int size>

T pop_by_index(List<T, size>& list, int index) {
	T tmp = list.elements[index];
	list.elements[index] = NULL;
	if (index < list.true_size) {
		for (int i = index; i < list.true_size - 1; ++i) {
			swap(list.elements[i], list.elements[i + 1]);
		}
	}
	if (tmp != NULL)
	{
		--list.true_size;
	}
	return tmp;
}

template <typename T, int size>

int get_pos(List<T, size>& list, int information) {
	for (int i = 0; i < list.true_size; i++)
	{
		if (list.elements[i] == information) {
			return i;
		}
	}
}

template <typename T, int size>

void print(List<T, size>& list) {
	for (int i = 0; i < size; i++)
	{
		cout << list.elements[i] << ' ';
	}
	cout << endl;
}

int main() {
	List<int, 5> list;
	constructor(list);
	add_last(list, 1);
	print(list);
	add_last(list, 2);
	print(list);
	add_last(list, 3);
	print(list);
	add_by_index(list, 4, 4);
	print(list);
	cout << pop_first(list) << endl;
	print(list);
	cout << pop_last(list) << endl;
	print(list);
	cout << get_pos(list, 3) << endl;
	destructor(list);
	print(list);
	return 0;
}