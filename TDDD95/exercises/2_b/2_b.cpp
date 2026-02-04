#include <iostream>
#include <vector>

class FenwickTree {
    int size;
    std::vector<int> tree;

public:
    FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    void add(int i, int delta) {
        i++;
        while (i <= size) {
            tree[i] += delta;
            i += i & (-i);
        }
    }

    int query(int i) {
        i++;
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);
        }
        return sum;
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main(void) {
    int length;
    if (!(std::cin >> length)) return 1;
    std::vector<int> position_of(length + 1);

    int val;
    for (int i = 0; i < length; i++) {
        std::cin >> val;
        position_of[val] = i;
    } std::cout << std::endl;

    FenwickTree bit(length); //Binary Indexed Tree
    for (int i = 0; i < length; i++) {
        bit.add(i, 1);
    }
    
    int l_ptr = 1;
    int r_ptr = length;

    for (int phase = 1; phase <= length; phase++) {
        int target_val;
        long long swaps = 0;
        int original_idx;

        if (phase % 2 != 0) {
            target_val = l_ptr++;
            original_idx = position_of[target_val];
            swaps = bit.query(0, original_idx - 1);
        } else {
            target_val = r_ptr--;
            original_idx = position_of[target_val];
            swaps = bit.query(original_idx + 1, length - 1);
        }

        std::cout << swaps << std::endl;
        bit.add(original_idx, -1);
    }

    return 0;
}