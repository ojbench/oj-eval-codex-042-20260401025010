#ifndef SPEEDCIRCULARLIST_H
#define SPEEDCIRCULARLIST_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

constexpr int s_prime = 31;

inline int log2(int x) {
    int ans = 0;
    while (x != 1) {
        x /= 2;
        ++ans;
    }
    return ans;
}

template<typename T, int b_prime>
class SpeedCircularLinkedList {
public:
    struct Node {
        // You may add more members, but cannot modify existing ones
        std::map<std::string, T> kv_map;
        int bound = 0;
        Node* next = nullptr;
        Node** fast_search_list = nullptr;

        Node(int bound_, int fast_search_list_size) : bound(bound_), next(nullptr) {
            if (fast_search_list_size > 0) {
                fast_search_list = new Node*[fast_search_list_size];
                for (int i = 0; i < fast_search_list_size; ++i) fast_search_list[i] = nullptr;
            } else {
                fast_search_list = nullptr;
            }
        }

        ~Node() {
            if (fast_search_list) {
                delete[] fast_search_list;
                fast_search_list = nullptr;
            }
        }
    };

private:
    // You cannot add more member variables
    Node* head = nullptr;
    int fast_search_list_size = 0;
    int list_size = 0;

    static int GetHashCode(std::string str) {
        long long ans = 0;
        for (auto& ch : str) {
            ans = (ans * s_prime + ch) % b_prime;
        }
        return static_cast<int>((ans + b_prime) % b_prime);
    }

    void BuildFastSearchList() {
        if (list_size <= 1 || fast_search_list_size <= 0) return;
        std::vector<Node*> nodes;
        nodes.reserve(list_size);
        Node* cur = head;
        for (int i = 0; i < list_size; ++i) {
            nodes.push_back(cur);
            cur = cur->next;
        }
        for (int i = 0; i < list_size; ++i) {
            for (int k = 0; k < fast_search_list_size; ++k) {
                int idx = (i + (1 << k)) % list_size;
                nodes[i]->fast_search_list[k] = nodes[idx];
            }
        }
    }

    Node* FindNodeByCode(int code) const {
        if (!head) return nullptr;
        if (code <= head->bound) return head;
        Node* cur = head;
        // Greedily jump without wrapping past the first bound >= code
        for (int k = fast_search_list_size - 1; k >= 0; --k) {
            Node* nxt = (cur->fast_search_list ? cur->fast_search_list[k] : nullptr);
            if (!nxt) continue;
            if (nxt->bound >= cur->bound && nxt->bound < code) {
                cur = nxt;
            }
        }
        return cur->next; // The next node has bound >= code
    }

public:
    explicit SpeedCircularLinkedList(std::vector<int> node_bounds) {
        list_size = static_cast<int>(node_bounds.size());
        fast_search_list_size = (list_size > 0 ? log2(list_size) : 0);
        if (list_size == 0) return;

        head = new Node(node_bounds[0], fast_search_list_size);
        Node* prev = head;
        for (int i = 1; i < list_size; ++i) {
            Node* node = new Node(node_bounds[i], fast_search_list_size);
            prev->next = node;
            prev = node;
        }
        prev->next = head; // close the ring
        BuildFastSearchList();
    }

    ~SpeedCircularLinkedList() {
        if (!head || list_size == 0) return;
        Node* cur = head;
        for (int i = 0; i < list_size; ++i) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = nullptr;
        list_size = 0;
        fast_search_list_size = 0;
    }

    void put(std::string str, T value) {
        int code = GetHashCode(str);
        Node* target = FindNodeByCode(code);
        if (target) {
            target->kv_map[str] = value;
        }
    }

    T get(std::string str) {
        int code = GetHashCode(str);
        Node* target = FindNodeByCode(code);
        if (target) {
            auto it = target->kv_map.find(str);
            if (it != target->kv_map.end()) return it->second;
        }
        return T();
    }

    void print() {
        Node* cur = head;
        for (int i = 0; i < list_size; ++i) {
            std::cout << "[Node] Bound = " << cur->bound << ", kv_map_size = " << cur->kv_map.size() << '\n';
            cur = cur->next;
        }
    }

    int size() const { return list_size; }
};
#endif //SPEEDCIRCULARLIST_H

