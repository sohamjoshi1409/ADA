#include <iostream>
#include <ctime>
using namespace std;

int linearSearch(int arr[], int n, int key)
{
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            index = i;
            break;
        }
    }

    return index;
}

int recursiveLinearSearch(int arr[], int i, int n, int key)
{
    if (i >= n)
        return -1;

    if (arr[i] == key)
        return i;
    else
        recursiveLinearSearch(arr, ++i, n, key);
}

int binarySearch(int arr[], int n, int key)
{
    int index = -1;
    int high = n - 1, low = 0;

    while (high >= low)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
        {
            index = mid;
            break;
        }
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return index;
}

int recursiveBinarySearch(int arr[], int low, int high, int key)
{
    if (low >= high)
    {
        return -1;
    }

    int mid = (high + low) / 2;

    if (arr[mid] == key)
    {
        return mid;
    }
    else if (arr[mid] < key)
        recursiveBinarySearch(arr, mid + 1, high, key);
    else
        recursiveBinarySearch(arr, low, mid - 1, key);
}

int main()
{
    int n, key, index;
    int arr[100];
    cout << "Enter the size of the array: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter the element to be searched: ";
    cin >> key;

    auto start = clock();
    index = linearSearch(arr, n, key);
    auto end = clock();

    if (index != -1)
        cout << "Element " << key << " found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    cout << "Time Taken : " << (double)(end - start) / CLOCKS_PER_SEC << " by Iterative Linear Search" << endl;

    start = clock();
    index = recursiveLinearSearch(arr, 0, n, key);
    end = clock();

    if (index != -1)
        cout << "Element " << key << " found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    cout << "Time Taken : " << (double)(end - start) / CLOCKS_PER_SEC << " by Recursive Linear Search" << endl;

    start = clock();
    index = binarySearch(arr, n, key);
    end = clock();

    if (index != -1)
        cout << "Element " << key << " found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    cout << "Time Taken : " << double(end - start) / CLOCKS_PER_SEC << " by Iterative Binary Search" << endl;

    start = clock();
    index = binarySearch(arr, n, key);
    end = clock();

    if (index != -1)
        cout << "Element " << key << " found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    cout << "Time Taken : " << double(end - start) / CLOCKS_PER_SEC << " by Recursive Binary Search" << endl;

    return 0;
}