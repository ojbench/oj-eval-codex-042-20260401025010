#include <iostream>
#include <vector>
#include <string>
#include "solution.h"

int main() {
    // Basic self-check using sample from attachments
    {
        std::cout << "======== Constructor Test ========\n";
        std::vector<int> node_bounds({10, 20, 30, 40, 50, 60, 70, 80, 90, 97});
        SpeedCircularLinkedList<int, 97> sll(node_bounds);
        sll.print();
    }
    {
        std::cout << "============ Size Test ============\n";
        std::vector<int> node_bounds({10, 30, 40, 50, 53});
        SpeedCircularLinkedList<int, 53> sll(node_bounds);
        std::cout << "size = " << sll.size() << "\n";
    }
    {
        std::cout << "============ Put Test ============\n";
        std::vector<int> node_bounds({10, 30, 50, 70, 90, 110, 130, 150, 170, 197});
        SpeedCircularLinkedList<int, 197> sll(node_bounds);
        sll.put("19260817", 0);
        sll.put("What a pity!", 1);
        sll.put("ACM2025", 6);
        sll.print();
    }
    {
        std::cout << "=========== Get Test =============\n";
        std::vector<int> node_bounds({50, 250, 450, 800, 1000, 1300, 1350, 1600, 1850, 2017});
        SpeedCircularLinkedList<std::string, 2017> sll(node_bounds);
        sll.put("Butterworth", "07:50");
        sll.put("Ipoh", "09:37");
        sll.put("KL Sentral", "12:15");
        sll.put("Seremban", "13:38");
        sll.put("Gemas", "14:42");
        sll.put("Segamat", "14:57");
        std::cout << sll.get("KL Sentral") << "\n";
        std::cout << sll.get("Gemas") << "\n";
        std::cout << sll.get("Butterworth") << "\n";
    }
    return 0;
}

