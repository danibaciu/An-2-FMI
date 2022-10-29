#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//------------------KNAPSACK-------------------

int max_sum_a (int K, const vector<int> &nums) {
    int k_max = 0;

    unordered_set<int> sums, aux;
    sums.insert(0);

    for (auto &number : nums) {
        for (auto &sum : sums) {
            if (number + sum <= K) {
                k_max = max(k_max, number + sum);
                aux.insert(number + sum);
            }
        }
        for (auto &x : aux)
            sums.insert(x);
        aux.clear();
    }

    return k_max;
}


int max_sum_b (int K, const vector<int> &nums) {
    int k_max = 0;

    for (auto &number : nums) {
        if (k_max + number <= K) {
            k_max += number;
        } else
                if (k_max < number) {
                    k_max = number;
                }
    }
    return k_max;
}

int main() {
    vector<int> numbers = {10,2,3,4,5};
    int K = 50;
    cout << max_sum_a(K, numbers); // afiseaza 44
    return 0;
}
