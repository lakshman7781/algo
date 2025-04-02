#include <stdio.h>
#include <limits.h>

#define MAX 100

// Function to find the optimal cost of a binary search tree
void optimalBST(int keys[], int freq[], int n) {
    int e[MAX][MAX] = {0};  // e[i][j] stores the minimum search cost for keys[i..j]
    int w[MAX][MAX] = {0};  // w[i][j] stores the sum of frequencies of keys[i..j]
    int root[MAX][MAX] = {0}; // root[i][j] stores the root of the optimal BST for keys[i..j]

    // Initialize w[i][i] and e[i][i] (single key case)
    for (int i = 0; i < n; i++) {
        w[i][i] = freq[i];
        e[i][i] = freq[i];
    }

    // Fill the DP tables
    for (int len = 2; len <= n; len++) { // len is the length of the subarray
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            w[i][j] = w[i][j-1] + freq[j];

            e[i][j] = INT_MAX;
            for (int r = i; r <= j; r++) {
                int cost = e[i][r-1] + e[r+1][j] + w[i][j];
                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Output the result
    printf("Minimum search cost: %d\n", e[0][n-1]);
    printf("Root of the optimal BST is: %d\n", root[0][n-1]);
}

// Main function
int main() {
    int keys[] = {10, 12, 20};
    int freq[] = {34, 8, 50};
    int n = sizeof(keys) / sizeof(keys[0]);

    optimalBST(keys, freq, n);

    return 0;
}
