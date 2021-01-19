#include <iostream>

using namespace std;

struct Example {
    int number = 0;
};

template <typename T>

struct Node {
	T information;
	Node<T> *next = nullptr;
	Node<T> *prev = nullptr;
};

template <typename T>

struct List {
    Node<T> *head = nullptr;
    bool is_empty() {
        if (head == nullptr) {
            return true;
        }
        return false;
    }
};

template <typename T>

List<T>* constructor(T new_information) {
	auto new_list = new List<T>;
	auto new_head = new Node<T>;
	new_head->next = new_head;
	new_head->prev = new_head;
	new_head->information = new_information;
	new_list->head = new_head;
	return new_list;
}

template <typename T>

void destructor(List<T>* list) {
	if (list->is_empty()) {
	    cout << "Ring is already destructed!" << endl;
	} else {
	    Node<T>* tmp = list->head->prev;
	    while (list->head != tmp) {
	        list->head = list->head->next;
	        delete list->head->prev;
	    }
        tmp = list->head;
	    list->head = nullptr;
	    delete tmp;
	}
}

template <typename T>

int count(List<T>* list) {
    if (list->is_empty()) {
        return 0;
    }
	int cnt = 1;
	Node<T>* tmp = list->head->next;
	while (tmp != list->head) {
		tmp = tmp->next;
		++cnt;
	}
	return cnt;
}

template <typename T>

void add_first(List<T>* list, T new_information) {
    if (list->is_empty()) {
        cout << "Before adding new element you should construct a ring!";
        return;
    }
	auto tmp = new Node<T>;
    tmp->information = new_information;
	if (list->head == list->head->next) { //если 1 элемент
		tmp->next = list->head;
		tmp->prev = list->head;
		list->head->next = tmp;
		list->head->prev = tmp;
		list->head = tmp;
	} else {
        tmp->next = list->head;
        list->head->prev->next = tmp;
        tmp->prev = list->head->prev;
        list->head->prev = tmp;
        list->head = tmp;
    }
}

template <typename T>

void add_last(List<T>* list, T new_information) {
    if (list->is_empty()) {
        cout << "Before adding new element you should construct a ring!";
        return;
    }
	auto tmp = new Node<T>;
    tmp->information = new_information;
	if (list->head == list->head->next) {
        tmp->next = list->head;
        tmp->prev = list->head;
        list->head->next = tmp;
        list->head->prev = tmp;
	} else {
        tmp->next = list->head;
        list->head->prev->next = tmp;
        tmp->prev = list->head->prev;
        list->head->prev = tmp;
    }
}

template <typename T>

void add_by_index(List<T>* list, T new_information, int index) {
    if (list->is_empty()) {
        cout << "Before adding new element you should construct a ring!";
        return;
    }
	int cnt = 0;
	if (index == 0) {
	    add_first(list, new_information);
	} else {
	    Node<T>* tmp = list->head;
	    while (cnt != index) {
	        tmp = tmp->next;
	        ++cnt;
	    }
	    auto new_node = new Node<T>;
	    new_node->information = new_information;
	    new_node->prev = tmp->prev;
	    new_node->next = tmp;
	    tmp->prev->next = new_node;
	    tmp->prev = new_node;
	}
}

template <typename T>

void add_by_pointer(List<T>* list, Node<T>* pointer, T new_information) {
    if (list->is_empty()) {
        cout << "Before adding new element you should construct a ring!";
        return;
    }
	if (list->head->prev == pointer) {
	    add_first(list, new_information);
	} else {
	    Node<T>* tmp = list->head;
	    while (tmp != pointer) {
	        tmp = tmp->next;
	    }
        auto new_node = new Node<T>;
        new_node->information = new_information;
        new_node->prev = tmp;
        new_node->next = tmp->next;
        tmp->next->prev = new_node;
        tmp->next = new_node;
	}
}

template <typename T>

T pop_first(List<T>* list) {
    if (list->is_empty()) {
        cout << "Ring is empty!";
        return -1;
    }
    T info = list->head->information;
	if (list->head == list->head->next) {
	    list->head = nullptr;
	} else {
	    list->head->next->prev = list->head->prev;  //меняем связи
	    list->head->prev->next = list->head->next;  //меняем связи
        Node<T>* tmp = list->head;
	    list->head = list->head->next;
	    delete tmp;
	}
    return info;
}

template <typename T>

T pop_last(List<T>* list) {
    if (list->is_empty()) {
        cout << "Ring is empty!";
        return -1;
    }
    T info = list->head->prev->information;
    Node<T> *tmp = list->head->prev;
    list->head->prev->prev->next = list->head;
    list->head->prev = list->head->prev->prev;
    delete tmp;
    return info;
}

template <typename T>

T pop_by_index(List<T>* list, int index) {
    int cnt = 0;
    if (list->is_empty()) {
        cout << "Ring is empty!";
        return -1;
    }
    if (index == 0) {
        return pop_first(list);
    }
    Node<T>* tmp = list->head;
    while (cnt != index) {
        tmp = tmp->next;
        ++cnt;
    }
	tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    T info = tmp->information;
    delete tmp;
    return info;
}

template <typename T>

T pop_by_pointer(List<T>* list, Node<T>* pointer) {
    if (list->is_empty()) {
        cout << "Ring is empty!";
        return -1;
    }
    if (pointer == list->head) {
        return pop_first(list);
    }
	Node<T>* tmp = list->head;
	while (tmp != pointer) {
	    tmp = tmp->next;
	    if (tmp == list->head) {
	        cout << "No such pointer in ring!" << endl;
            return -1;
	    }
	}
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    T info = tmp->information;
    delete tmp;
    return info;
}

template <typename T>

T get_information_by_index(List<T>* list, int index) {
    int cnt = 0;
    if (list->is_empty()) {
        cout << "Ring is empty!";
        return -1;
    }
    Node<T>* tmp = list->head;
    while (cnt != index) {
        tmp = tmp->next;
        ++cnt;
    }
    return tmp->information;
}

template <typename T>

int get_pos(List<T>* list, T information) {
    int cnt = 0;
    if (list->is_empty()) {
        cout << "Ring is empty!";
        return -1;
    }
    Node<T>* tmp = list->head;
    while (tmp->information != information) {
        tmp = tmp->next;
        ++cnt;
    }
    return cnt;
}

template <typename T>

void print(List<T>* list) {
    if (list->is_empty()) {
        cout << "Ring is empty!" << endl;
        return;
    }
	if (list->head == list->head->next) {
		cout << list->head->information;
	} else {
	    cout << list->head->information << ' ';
	    Node<T> *tmp = list->head->next;
	    while (tmp != list->head) {
	        cout << tmp->information << ' ';
	        tmp = tmp->next;
	    }
	}
	cout << endl;
}

ostream& operator<<(ostream& stream, Example ex) {
    stream << '?' << ex.number << '?';
    return stream;
}

int main() {
	List<int>* list = constructor(2);
	print(list);
    add_first(list, 3);
    add_first(list, 4);
    print(list);
    add_last(list, 5);
    print(list);
    cout << "Size: " << count(list) << endl;
    add_by_index(list, 6, 2);
    print(list);
    add_by_pointer(list, list->head, 7);
    print(list);
    add_by_pointer(list, list->head->prev, 9);
    print(list);
    cout << pop_first(list) << endl;
    print(list);
    cout << pop_last(list) << endl;
    print(list);
    cout << pop_by_index(list, 2) << endl;
    print(list);
    cout << pop_by_pointer(list, list->head->next) << endl;
    print(list);
    cout << get_information_by_index(list, 0) << endl;
    print(list);
    cout << get_pos(list, 6) << endl;
    print(list);
    destructor(list);
    print(list);

    Example new_example_1, new_example_2, new_example_3;
    new_example_1.number = 5;
    new_example_2.number = 25;
    new_example_3.number = 125;
    List<Example> *ex_list = constructor(new_example_1);
    add_first(ex_list, new_example_2);
    add_last(ex_list, new_example_3);
    print(ex_list);

	return 0;
}
