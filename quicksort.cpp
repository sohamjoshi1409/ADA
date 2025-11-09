#include <iostream>
#include <ctime>
using namespace std;

int findPIndex(int arr[], int low, int high)
{
    int pivot = low;
    int i = low, j = high;

    while (i < j)
    {
        while (arr[i] <= arr[pivot] && i <= high)
            i++;

        while (arr[j] > arr[pivot] && j >= low)
            j--;

        if (i < j)
        {
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[pivot], arr[j]);

    return j;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pIndex = findPIndex(arr, low, high);
        quickSort(arr, low, pIndex - 1);
        quickSort(arr, pIndex + 1, high);
    }
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr = new int[n];
    int *arr2 = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
        arr2[i] = arr[i];
    }

    cout << "Original Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    auto start = clock();
    bubbleSort(arr2, n);
    auto end = clock();

    cout << "\n\nSorted Array using Bubble Sort: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr2[i] << " ";
    }

    auto start2 = clock();
    quickSort(arr, 0, n - 1);
    auto end2 = clock();

    cout << "\n\nSorted Array using Quick Sort: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\nTime Taken by Bubble Sort: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    cout << "\nTime Taken by Quick Sort: " << (double)(end2 - start2) / CLOCKS_PER_SEC << endl;

    free(arr);
    free(arr2);
    return 0;
}