#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

int get_valid_int(int upper_bound, std::vector<int>& duplicates);
int get_valid_int(int upper_bound);

int main() {
    int length = get_valid_int(100000);
    std::vector<int> array(length), duplicates;
    for (int i=0; i < length; i++) {
        int x = get_valid_int(length, duplicates);
        array[i] = x;
    }
    std::cout << "\n";
    int left_bound = 0;
    int right_bound = length - 1;
    int target_value, current_pos, swaps, tmp;

    for (int phase = 1; phase <= length; phase++) {
        if (phase % 2 != 0) { //odd phase, move low number
            target_value = (phase + 1) / 2;
        } else { //even phase, move high number
            target_value = length - (phase/2) + 1;
        }
        for (int i = left_bound; i <= right_bound; i++) {
            if (array[i] == target_value) {
                current_pos = i;
                break;
            }
        }
        if (phase % 2 != 0) {
            swaps = current_pos - left_bound;
            tmp = array[current_pos];
            for (int i = current_pos; i > left_bound; i--) {
                array[i] = array[i - 1];
            }
            array[left_bound] = tmp;
            left_bound++;
        } else {
            swaps = right_bound - current_pos;
            tmp = array[current_pos];
            for (int i = current_pos; i < right_bound; i++) {
                array[i] = array[i+1];
            }
            array[right_bound] = tmp;
            right_bound--;
        }   
        std::cout << swaps << "\n";
    }
    return 0;
}

int get_valid_int(int upper_bound, std::vector<int>& duplicates) {
    int x;
    if (!(std::cin >> x) || x < 1 || x > upper_bound) {
        std::cout << "You must enter an integer between 1 and " << upper_bound << ".\n";
        std::exit(1); 
    }
    if (std::find(duplicates.begin(), duplicates.end(), x) != duplicates.end()) {
        std::cout << "Duplicates not allowed; you must enter unique values.\n";
        std::exit(1); 
    }
    duplicates.push_back(x);
    return x;
}

int get_valid_int(int upper_bound) {
    int x;
    if (!(std::cin >> x) || x < 1 || x > upper_bound) {
        std::cout << "You must enter an integer between 1 and " << upper_bound << ".\n";
        std::exit(1); 
    }
    return x;
}