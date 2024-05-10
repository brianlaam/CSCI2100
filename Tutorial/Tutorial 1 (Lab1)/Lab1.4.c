// Q4: Subarray Product (Bonus)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_LEN 1024
#define INT_MIN -2147483648

int num_subarrays_product_between_L_and_R(int* nums, int numsSize, int L, int R) {
    int count = 0;
    
    for (int start = 0; start < numsSize; start++) {
        int product = 1;
        for (int end = start; end < numsSize; end++) {
            product *= nums[end];
            if (product > R) break;
            if (product > L && product < R) count++;
        }
    }
    
    return count;
}

int main() {
    int L = 10;
    int R = 100;

    int size_nums;
    
    scanf("%d", &size_nums);
    scanf("%d", &L);
    scanf("%d", &R);

    int nums[size_nums];

    for (int i = 0; i < size_nums; i++) {
        scanf("%d", &nums[i]);
    }
    
    int result = num_subarrays_product_between_L_and_R(nums, size_nums, L, R);
    printf("%d\n", result);

    return 0;
}