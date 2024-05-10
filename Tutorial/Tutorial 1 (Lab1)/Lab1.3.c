// Q3 Finding Valley Index

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valley(int arr[], int low, int high, int n){
    // Find index of middle element
    int mid = (low + high)/2 ;  
    if ((mid == 0 || arr[mid-1] > arr[mid]) && (mid == n-1 || arr[mid+1] > arr[mid])) return mid;
    else if (mid > 0 && arr[mid-1] < arr[mid]) return valley(arr, low, (mid -1), n);
    return valley(arr, (mid + 1), high, n);
}

int findValleyIndex(int arr[], int n) {
	// WRITE YOUR CODE HERE
    return valley(arr, 0, n-1, n);
}

int main(int argc, char *argv[]) {
	int N;
	scanf("%d", &N);
	
	int nums[N];
	
	for (int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	
	int index;
	
	for(int i = 0; i < 50; i++){
		index = findValleyIndex(nums, N);
	}
	printf("%d", index);
}