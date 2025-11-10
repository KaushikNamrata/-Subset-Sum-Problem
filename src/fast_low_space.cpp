#include <bits/stdc++.h>
using namespace std;

// Function to generate all possible subset sums for a given half
vector<long long> subsetSums(vector<int>& arr) {
    int n = arr.size();
    vector<long long> sums;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) sum += arr[i];
        }
        sums.push_back(sum);
    }
    return sums;
}

// Fast Low-Space Subset Sum using Meet-in-the-Middle approach
bool subsetSum_FastLowSpace(vector<int>& arr, int target) {
    int n = arr.size();
    vector<int> left(arr.begin(), arr.begin() + n / 2);
    vector<int> right(arr.begin() + n / 2, arr.end());

    vector<long long> leftSums = subsetSums(left);
    vector<long long> rightSums = subsetSums(right);
    sort(rightSums.begin(), rightSums.end());

    // For each left sum, check if target - leftSum exists in right sums
    for (auto x : leftSums) {
        long long need = target - x;
        if (binary_search(rightSums.begin(), rightSums.end(), need))
            return true;
    }

    return false;
}

int main() {
    vector<int> S = {3, 34, 4, 12, 5, 2};
    int T = 9;

    if (subsetSum_FastLowSpace(S, T))
        cout << "Subset Found (Fast Low-Space / Meet-in-the-Middle)" << endl;
    else
        cout << "No Subset Found (Fast Low-Space / Meet-in-the-Middle)" << endl;

    return 0;
}
