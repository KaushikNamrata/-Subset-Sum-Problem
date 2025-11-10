#include <bits/stdc++.h>
using namespace std;

// Parameterized Subset Sum using Small Doubling property (optimized)
bool subsetSum_Parameterized(vector<int>& arr, int target) {
    // 'sums' holds all possible sums that can be made so far
    set<int> sums = {0};

    for (int num : arr) {
        set<int> newSums(sums); // copy existing sums
        for (int s : sums) {
            int newSum = s + num;
            if (newSum <= target)
                newSums.insert(newSum);
        }
        sums.swap(newSums); // update compressed set
    }

    return sums.count(target);
}

int main() {
    // Structured dataset (small doubling property)
    vector<int> S = {1, 2, 3, 4, 5, 6, 7};
    int T = 9;

    if (subsetSum_Parameterized(S, T))
        cout << "Subset Found (Parameterized / Small Doubling)" << endl;
    else
        cout << "No Subset Found (Parameterized / Small Doubling)" << endl;

    return 0;
}
