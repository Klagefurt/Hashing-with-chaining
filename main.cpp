#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>

using namespace std;

struct Hash {

    Hash(unsigned size) : _size(size) {
        _table.resize(size);
    }
    ~Hash() {}

    void add(string s) {
        int hash_index = hasher(s);
        if (!_table[hash_index].empty()) {
            for (auto ptr = _table[hash_index].begin(); ptr != _table[hash_index].end(); ++ptr) {
                if (*ptr == s) { return; }
            }
        }
        _table[hash_index].push_front(s);
    }

    void del(string s) {
        int hash_index = hasher(s);
        if (!_table[hash_index].empty()) {
            for (auto ptr = _table[hash_index].begin(); ptr != _table[hash_index].end(); ++ptr) {
                if (*ptr == s) { 
                    _table[hash_index].erase(ptr);
                    return; 
                    }
            }
        }
    }

    void find(string s) {
        int hash_index = hasher(s);
        if (!_table[hash_index].empty()) {
            for (auto ptr = _table[hash_index].begin(); ptr != _table[hash_index].end(); ++ptr) {
                if (*ptr == s) { 
                    cout << "yes" << endl;
                    return; 
                    }
            }
        }
        cout << "no" << endl;
    }

    void check(int number) {
        if (number < _size and !_table[number].empty()) {
            for (auto i : _table[number]) { cout << i << " "; }
        }
        cout << endl;
    }

    long long pow(long long base, int power) {
        long long res = 1;
        int B = 1000000007;
        if (power == 0) return 1;
        for (int i = 0; i < power; ++i) {
            res *= base;
            res %= B;
        }
        return res;
    }
    
    int hasher(string s) {
        int len = s.length();
        int A = 263;
        int B = 1000000007;
        long long res = 0;
        for (int i = 0; i < len; ++i) {
            res += s[i] * pow(A, i);
        }
        res %= B;
        res %= _size;
        return (int)res;
    }

    unsigned _size;
    vector<list<string>> _table;
};


int main() {
    unsigned tableSize, numRequests;
    string command;
    string argument;
    int number;

    cin >> tableSize >> numRequests;

    Hash table(tableSize);

    for (int i = 0; i < numRequests; ++i) {
        cin >> command;

        if (command == "add") {
            cin >> argument;
            table.add(argument);
        }
        else if (command == "del") {
            cin >> argument;
            table.del(argument);
        }
        else if (command == "find") {
            cin >> argument;
            table.find(argument);
        }
        else if (command == "check") {
            cin >> number;
            table.check(number);
        }
    }

    return 0;
}
