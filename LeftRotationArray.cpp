#include <vector>
#include <iostream>
#include <numeric>

// The core function to perform the left rotation
std::vector<int> rotateLeft(int d, std::vector<int> arr) {
    int n = arr.size();
    
    // Calculate the effective number of rotations
    int effective_d = d % n;

    // Create a new vector to store the rotated array
    std::vector<int> rotated_arr(n);

    // Use the formula: arr'[j] = arr[(j + effective_d) % n]
    for (int j = 0; j < n; ++j) {
        int original_index = (j + effective_d) % n;
        rotated_arr[j] = arr[original_index];
    }

    return rotated_arr;
}

// Main function to handle input and output
int main() {
    // 1. Read n and d from the first line of stdin
    int n;
    int d;
    if (!(std::cin >> n >> d)) return 0;
    
    // 2. Read the n space-separated integers for the array
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> arr[i])) return 0;
    }

    // 3. Call the rotation function
    std::vector<int> result = rotateLeft(d, arr);

    // 4. Print the result as a single line of space-separated integers
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    std::cout << std::endl; // Newline at the end is required

    return 0;
}
