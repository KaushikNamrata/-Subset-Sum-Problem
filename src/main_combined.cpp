#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

// -----------------------------------
// 1️⃣ Bellman’s DP Algorithm
// -----------------------------------
bool subsetSum_Bellman(vector<int>& arr, int T) {
    vector<bool> dp(T + 1, false);
    dp[0] = true;

    for (int a : arr)
        for (int j = T; j >= a; j--)
            if (dp[j - a]) dp[j] = true;

    return dp[T];
}

// -----------------------------------
// 2️⃣ Fast Low-Space (Meet-in-the-Middle)
// -----------------------------------
vector<long long> subsetSums(vector<int>& arr) {
    int n = arr.size();
    vector<long long> sums;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) sum += arr[i];
        sums.push_back(sum);
    }
    return sums;
}

bool subsetSum_FastLowSpace(vector<int>& arr, int target) {
    int n = arr.size();
    vector<int> left(arr.begin(), arr.begin() + n / 2);
    vector<int> right(arr.begin() + n / 2, arr.end());

    vector<long long> leftSums = subsetSums(left);
    vector<long long> rightSums = subsetSums(right);
    sort(rightSums.begin(), rightSums.end());

    for (auto x : leftSums)
        if (binary_search(rightSums.begin(), rightSums.end(), target - x))
            return true;

    return false;
}

// -----------------------------------
// 3️⃣ Parameterized (Small Doubling)
// -----------------------------------
bool subsetSum_Parameterized(vector<int>& arr, int target) {
    set<int> sums = {0};
    for (int num : arr) {
        set<int> newSums(sums);
        for (int s : sums)
            if (s + num <= target) newSums.insert(s + num);
        sums.swap(newSums);
    }
    return sums.count(target);
}

// -----------------------------------
// 🧮 MAIN FUNCTION (Comparison)
// -----------------------------------
int main() {
    vector<int> S = {3, 34, 4, 12, 5, 2};
    int T = 9;

    cout << "========== SUBSET SUM COMPARISON ==========\n";
    cout << "Array: {3, 34, 4, 12, 5, 2}, Target = 9\n\n";

    // Bellman’s DP
    auto start1 = high_resolution_clock::now();
    bool r1 = subsetSum_Bellman(S, T);
    auto end1 = high_resolution_clock::now();
    auto t1 = duration_cast<microseconds>(end1 - start1).count();

    // Fast Low-Space
    auto start2 = high_resolution_clock::now();
    bool r2 = subsetSum_FastLowSpace(S, T);
    auto end2 = high_resolution_clock::now();
    auto t2 = duration_cast<microseconds>(end2 - start2).count();

    // Parameterized
    auto start3 = high_resolution_clock::now();
    bool r3 = subsetSum_Parameterized(S, T);
    auto end3 = high_resolution_clock::now();
    auto t3 = duration_cast<microseconds>(end3 - start3).count();

    // print on console
    cout << "Bellman DP Result: " << (r1 ? "Subset Found" : "No Subset") 
         << " | Time: " << t1 << " µs\n";
    cout << "Fast Low-Space Result: " << (r2 ? "Subset Found" : "No Subset") 
         << " | Time: " << t2 << " µs\n";
    cout << "Parameterized Result: " << (r3 ? "Subset Found" : "No Subset") 
         << " | Time: " << t3 << " µs\n";

    cout << "\n==========================================\n";

    // ---------- STEP 3: WRITE RESULTS TO FILE ----------
    ofstream fout("../results/output.txt"); // go one folder up to results/
    if (fout.is_open()) {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        fout << "Experiment Run Time: " << ctime(&now_time) << "\n";
        fout << "========== SUBSET SUM COMPARISON ==========\n";
        fout << "Array: {3, 34, 4, 12, 5, 2}, Target = 9\n\n";
        fout << "Bellman DP Result: " << (r1 ? "Subset Found" : "No Subset")
             << " | Time: " << t1 << " µs\n";
        fout << "Fast Low-Space Result: " << (r2 ? "Subset Found" : "No Subset")
             << " | Time: " << t2 << " µs\n";
        fout << "Parameterized Result: " << (r3 ? "Subset Found" : "No Subset")
             << " | Time: " << t3 << " µs\n";
        fout << "==========================================\n";
        fout.close();
        cout << "\nOutput saved to results/output.txt ✅\n";
    } else {
        cerr << "Error: Could not open results/output.txt\n";
    }

    return 0;
}
