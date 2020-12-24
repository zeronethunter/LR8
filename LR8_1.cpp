#include <iostream>

using namespace std;

template <typename T>

struct Node {
	T information = 0;
	Node<T> *next = nullptr;
	Node<T> *prev = nullptr;
};

template <typename T>

Node<T>* constructor(T new_information) {
	Node<T>* root = new Node<T>;
	root->information = new_information;
	root->next = root;
	root->prev = root;
	return(root);
}

template <typename T>

void destructor(Node<T>* list) {
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		list = list->next;
		delete list->prev;
	};
	delete list;
}

template <typename T>

int count(Node<T>* list) {
	int cnt = 1;
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		list = list->next;
		++cnt;
	}
	return cnt;
}

template <typename T>

Node<T>* add_first(Node<T>* list, T new_information) {
	Node<T>* tmp = new Node<T>;
	if (count(list) == 1) {
		tmp->next = list;
		tmp->prev = list;
		list->next = tmp;
		list->prev = tmp;
		tmp->information = new_information;
		return tmp;
	}
	tmp->prev = list->prev;
	list->prev = tmp;
	tmp->next = list;
	list->prev->next = tmp;
	tmp->information = new_information;
	list = tmp;
	tmp = tmp->prev;
	return tmp;
}

template <typename T>

Node<T>* add_last(Node<T>* list, T new_information) {
	Node<T>* tmp = new Node<T>;
	if (count(list) == 1) {
		tmp->next = list;
		tmp->prev = list;
		list->next = tmp;
		list->prev = tmp;
		tmp->information = new_information;
		return list;
	}
	tmp->next = list;
	list->prev->next = tmp;
	tmp->prev = list->prev;
	list->prev = tmp;
	tmp->information = new_information;
	return list;
}

template <typename T>

Node<T>* add_by_index(Node<T>* list, T new_information, int index) {
	int cnt = 0;
	if (index == 0) {
		return(add_first(list, new_information));
	}
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		if (cnt == index) {
			Node<T>* tmp1 = new Node<T>;
			tmp1->next = list;
			tmp1->prev = list->prev;
			list->prev = tmp1;
			tmp1->information = new_information;
			return(tmp->next);
		}
		list = list->next;
		++cnt;
	}
	return(add_last(tmp->next, new_information));
}

template <typename T>

Node<T>* add_by_pointer(Node<T>* list, Node<T>* pointer, T new_information) {
	int cnt = 0;
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		if (list == pointer) {
			return(add_by_index(list, new_information, cnt));
		}
		list = list->next;
		++cnt;
	}
	return(add_by_index(list, new_information, cnt + 1));
}

template <typename T>

Node<T>* pop_first(Node<T>* list) {
	if (count(list) == 1) {
		return(list);
	}
	list->next->prev = list->prev;
	list->prev->next = list->next;
	list->next = list;
	list->prev = list;
	return list;
}

template <typename T>

Node<T>* pop_last(Node<T>* list) {
	if (count(list) == 1) {
		return(list);
	}
	Node<T>* tmp = list->prev;
	list->prev->prev->next = list;
	list->prev = list->prev->prev;
	list->next = list;
	list->prev = list;
	return tmp;
}

template <typename T>

Node<T>* pop_by_index(Node<T>* list, int index) {
	int cnt = 0;
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		if (cnt == index) {
			list->next = list;
			list->prev = list;
			return(pop_first(list));
		}
		list = list->next;
		++cnt;
	}
	list->next = list;
	list->prev = list;
	return(pop_first(list));
}

template <typename T>

Node<T>* pop_by_pointer(Node<T>* list, Node<T>* pointer) {
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		if (list == pointer) {
			list->next = list;
			list->prev = list;
			return(pop_first(list));
		}
		list = list->next;
	}
	list->next = list;
	list->prev = list;
	return(pop_first(tmp));
}

template <typename T>

T get_information_by_index(Node<T>* list, int index) {
	int cnt = 0;
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		if (cnt == index) {
			return(list->information);
		}
		list = list->next;
		++cnt;
	}
	return(tmp->information);
}

template <typename T>

int get_pos(Node<T>* list, T information) {
	int cnt = 0;
	Node<T>* tmp = list->prev;
	while (list != tmp) {
		if (list->information == information) {
			return(cnt);
		}
		list = list->next;
		++cnt;
	}
	return(cnt);
}

template <typename T>

void print(Node<T>* list) {
	if (list == list->prev) {
		cout << list->information;
		return;
	}
	else {
		Node<T>* tmp = list->prev;
		while (list != tmp) {
			cout << list->information << ' ';
			list = list->next;
		}
		cout << tmp->information;
	}
	cout << endl;
}


int main() {
	Node<int>* node = constructor(2);
	print(node);
	node = add_first(node, 3);
	print(node);
	node = add_last(node, 5);
	print(node);
	node = add_by_index(node, 10, 2);
	cout << count(node) << endl;
	cout << get_pos(node, 5) << endl;
	print(node);
	node = pop_first(node);
	print(node);

	return 0;
}