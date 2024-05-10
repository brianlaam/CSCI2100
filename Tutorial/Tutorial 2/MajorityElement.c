#include <stdio.h>
int CountInRange(int* arr, int target_element, int left, int right)
{ 
    int count = 0;
    for (int i = left; i <= right; i++) 
    {
        if (arr[i] == target_element)
            count++;
    }
    return count;
}

int MajorityElement(int* arr, int left, int right)
{
    if (left == right) // base case
        return arr[left];
	int middle = (left + right) / 2;
	int left_majority = MajorityElement(arr, left, middle);
	int right_majority = MajorityElement(arr, middle + 1, right); 
    if (left_majority == right_majority) 
	    return left_majority;
	if (CountInRange(arr, left_majority, left, right) > (right - left + 1) / 2) 
		return left_majority;
	if (CountInRange(arr, right_majority, left, right) > (right - left + 1) / 2) 
	    return right_majority;
    return -1;
}

int main()
{
    int arr[7] = {3, 3, 1, 1, 3, 2, 3};
    printf("The major element of the array is %d\n", MajorityElement(arr, 0, 6));
    return 0;
}