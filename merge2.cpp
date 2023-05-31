#include <iostream>
#include <vector>
#include <thread>

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    for (int i = 0; i < n1; ++i)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArray[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
            arr[k++] = leftArray[i++];
        else
            arr[k++] = rightArray[j++];
    }

    while (i < n1)
        arr[k++] = leftArray[i++];
    while (j < n2)
        arr[k++] = rightArray[j++];
}

void mergeSortParallel(std::vector<int> &arr, int left, int right, int threads)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        if (threads > 1)
        {
            std::thread t1(mergeSortParallel, std::ref(arr), left, mid, threads / 2);
            std::thread t2(mergeSortParallel, std::ref(arr), mid + 1, right, threads / 2);

            t1.join();
            t2.join();
        }
        else
        {
            mergeSortParallel(arr, left, mid, 1);
            mergeSortParallel(arr, mid + 1, right, 1);
        }

        merge(arr, left, mid, right);
    }
}

void printArray(const std::vector<int> &arr)
{
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int size = arr.size();

    std::cout << "Original array: ";
    printArray(arr);

    int threads = std::thread::hardware_concurrency();
    mergeSortParallel(arr, 0, size - 1, threads);

    std::cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
