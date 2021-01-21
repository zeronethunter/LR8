#include <iostream>

using namespace std;

struct Example {
    int first;
    char second;
    Example& operator= (int exit) {
        first = 0;
        second = 0;
        return *this;
    }
};

bool operator== (const Example& left, const Example& right) {
    if (left.first == right.first) {
        if (left.second == right.second) {
            return true;
        }
    }
    return false;
}

ostream& operator<<(ostream& stream, Example ex) {
    stream << ex.second << ex.first;
    return stream;
}

template <typename T>

T make_it_clear () {
    T clear;
    clear = 0;
    return clear;
}

template <typename T, int size>

struct List {
    T elements[size];
    int true_size = 0;
};

template <typename T, int size>

void constructor(List<T, size>& list) {
    for (T& i : list.elements) {
        i = make_it_clear<T>();
    }
}

template <typename T, int size>

void destructor(List<T, size>& list) {
    for (int i = 0; i < list.true_size; ++i) {
        list.elements[i] = make_it_clear<T>();
    }
}

template <typename T, int size>

int count(const List<T, size>& list) {
    return list.true_size;
}

template <typename T, int size>

void add_last(List<T, size>& list, T new_information) {
    if (list.true_size >= size) {
        cout << "Cannot add anything else!" << endl;
        return;
    }
    list.elements[list.true_size] = new_information;
    ++list.true_size;
}

template <typename T, int size>

void add_by_index(List<T, size>& list, T new_information, int index) {
    if (index > size) {
        cout << "Enter correct index!" << endl;
        return;
    } else if (list.true_size >= size) {
        cout << "Cannot add anything else!" << endl;
        return;
    }
    if (index >= list.true_size) {
        list.elements[list.true_size] = new_information;
    }
    else {
        for (int i = index; i < list.true_size; ++i) {
            T tmp = list.elements[i + 1];
            list.elements[i + 1] = list.elements[index];
            list.elements[index] = tmp;
        }
        list.elements[index] = new_information;
    }
    ++list.true_size;
}

template <typename T, int size>

T pop_first(List<T, size>& list) {
    if (list.true_size == 0) {
        cout << "Empty!" << endl;
        return make_it_clear<T>();
    }
    T tmp = list.elements[0];
    list.elements[0] = make_it_clear<T>();
    for (int i = 0; i < list.true_size - 1; i++) {
        list.elements[i] = list.elements[i + 1];
    }
    list.elements[list.true_size - 1] = make_it_clear<T>();
    if (list.true_size != 0) {
        --list.true_size;
    }
    return tmp;
}

template <typename T, int size>

T pop_last(List<T, size>& list) {
    if (list.true_size == 0) {
        cout << "Empty!" << endl;
        return make_it_clear<T>();
    }
    T tmp = list.elements[list.true_size - 1];
    list.elements[list.true_size - 1] = make_it_clear<T>();
    if (list.true_size != 0) {
        --list.true_size;
    }
    return tmp;
}

template <typename T, int size>

T pop_by_index(List<T, size>& list, int index) {
    if (list.true_size == 0) {
        cout << "Empty!" << endl;
        return make_it_clear<T>();
    }
    if (index >= size) {
        cout << "Enter correct index!" << endl;
        return make_it_clear<T>();
    }
    T tmp = list.elements[index];
    if (index < list.true_size) {
        list.elements[index] = make_it_clear<T>();
        for (int i = index; i < list.true_size - 1; ++i) {
            list.elements[i] = list.elements[i + 1];
        }
        if (tmp != make_it_clear<T>()) {
            --list.true_size;
        }
    }
    return tmp;
}

template <typename T, int size>

int get_pos(List<T, size>& list, T information) {
    for (int i = 0; i < list.true_size; i++) {
        if (list.elements[i] == information) {
            return i;
        }
    }
    cout << "Element doesn't exist!" << endl;
    return -1;
}

template <typename T, int size>

T get_by_index(List<T, size>& list, int index) {
    if (index > size) {
        cout << "No such element in index " << index << endl;
        return make_it_clear<T>();
    }
    if (index >= list.true_size) {
        return make_it_clear<T>();
    }
    return list.elements[index];
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
    add_by_index(list, 5, 1);
    print(list);
    cout << pop_first(list) << endl;
    print(list);
    cout << pop_last(list) << endl;
    print(list);
    cout << pop_by_index(list, 2) << endl;
    print(list);
    cout << get_pos(list, 2) << endl;
    cout << get_by_index(list, 0) << endl;
    cout << count(list) << endl;
    destructor(list);
    print(list);

    List<Example, 5> ex_list;
    constructor(ex_list);
    Example ex1 = {5, 'a'}, ex2 = {25, 'b'}, ex3 = {125, 'c'};
    add_last(ex_list, ex1);
    add_last(ex_list, ex2);
    print(ex_list);
    add_by_index(ex_list, ex3, 1);
    print(ex_list);
    cout << get_by_index(ex_list, 2) << endl;
    cout << get_pos(ex_list, ex1);

    return 0;
}
