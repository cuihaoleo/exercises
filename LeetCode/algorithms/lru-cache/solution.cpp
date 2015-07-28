#include <iostream>
#include <list>
#include <iterator>
#include <unordered_map>

class LRUCache{
private:
    std::list<int> list;
    struct map_node {
        decltype(list.begin()) p;
        int value;
    };
    std::unordered_map<int, map_node> map;
    size_t capacity;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    void access(int key) {
        if (map.find(key) != map.end()) {
            auto p = map[key].p;
            if (p != list.begin())
                list.splice(list.begin(), list, p, std::next(p));
        }
    }

    int get(int key) {
        if (map.find(key) != map.end()) {
            access(key);
            return map[key].value;
        }
        return -1;
    }

    void set(int key, int value) {
        if (map.find(key) != map.end()) {
            map[key].value = value;
            access(key);
        }
        else {
            if (list.size() == capacity) {
                int key = *list.rbegin();
                map.erase(key);
                list.pop_back();
            } 

            list.push_front(key);
            map[key] = map_node{ list.begin(), value };
        }
    }
};

int main () {
    int cap;

    std::cout << "Capacity: ";
    std::cin >> cap;

    LRUCache lru(cap);
    char cmd = '\0';
    while (cmd != 'q') {
        int key, value;
        std::cin >> cmd;
        switch (cmd) {
            case 's':
                std::cin >> key >> value;
                lru.set(key, value);
                break;
            case 'g':
                std::cin >> key;
                value = lru.get(key);
                std::cout << "Result: " << value << std::endl;
                break;
            case 'q':
                continue;
            default:
                std::cout << "What?" << std::endl;
        }
    }

    return 0;
}

