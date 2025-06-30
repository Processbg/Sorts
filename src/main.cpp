#include <iostream>
#include <new>

template<typename T>
void swap(T& a, T& b)
{
    T oldA = a;
    a = b;
    b = oldA;
}

template<typename T>
void maxHeapify(T* container, int size, int index)
{
    if (!container) return;
    
    int left = 2 * index + 1; // left child
    int right = 2 * index + 2; // right child

    int largest = index;

    if (left < size && container[left] > container[largest])
    {
        largest = left;
    }

    if (right < size && container[right] > container[largest])
    {
        largest = right;
    } 

    if (largest != index)
    {
        swap(container[largest], container[index]);
        maxHeapify(container, size, largest);
    }
}

template<typename T>
void buildMaxHeap(T* container, int size)
{
    if (!container) return;
    // We start heapifying from this last non-leaf node
    // and move backward to the root 
    // to ensure the entire tree satisfies the max-heap property.
    for (int i = (size / 2) - 1; i >= 0; --i)
    {
        maxHeapify(container, size, i);
    }
}

template<typename T>
void heapSort(T* container, int size)
{
    if (!container) return;

    buildMaxHeap(container, size);
    
    for (int i = size - 1; i >= 1; --i)
    {
        swap(container[0], container[i]);
        maxHeapify(container, i, 0);
    }
}

template<typename T>
int partition(T* container, int l, int r)
{
    if (!container) return -1;

    int i = l - 1, j = r;
    T v = container[r];
    
    for (;;)
    {
        while (container[++i] < v);
        while (v < container[--j]) if (j == l) break; 
        // j == l protects agains the case 
        // if the part. elem. is the smallest in the container
        
        if (i >= j) break;

        swap(container[i], container[j]);
    }

    swap(container[i], container[r]);

    return i;
}

template<typename T>
void quickSort(T* container, int l, int r)
{
    if (!container) return;
    if (r <= l) return;

    int i = partition(container, l, r);

    quickSort(container, l, i - 1);
    quickSort(container, i + 1, r);
}

template<typename T>
void merge(T* c, T* a, int N, T* b, int M)
{
    if (!c || !a || !b) return;

    int i = 0, j = 0, k = 0;

    while (k < N + M)
    {
        if (i == N) 
        {
            c[k] = b[j];
            ++j;
            ++k;
            continue;
        }

        if (j == M)
        {
            c[k] = a[i];
            ++i;
            ++k;
            continue;
        }

        if (a[i] < b[j])
        {
            c[k] = a[i];
            ++i;
        }
        else
        {
            c[k] = b[j];
            ++j;
        }

        ++k;
    }
}

template<typename T>
void mergeSort(T* container, int l, int r)
{
    if (!container) return;
    if (r <= l) return;

    int m = l + (r - l) / 2;

    mergeSort(container, l, m);
    mergeSort(container, m + 1, r);

    int leftSize = m - l + 1;
    int rightSize = r - m;

    T* merged = new(std::nothrow) T[leftSize + rightSize];
    if (!merged)
    {
        std::cerr << "Not enough memory in merge sort for " << sizeof(T)*(leftSize + rightSize) << " bytes for merged.\n";
        return;
    }

    merge(merged, container + l, leftSize, container + m + 1, rightSize);

    // Copy back to container
    for (int i = 0; i < leftSize + rightSize; ++i)
    {
        container[l + i] = merged[i];
    }

    delete[] merged;
}

template<typename T>
void selectionSort(T* container, int size)
{
    if (!container) return;

    int l = 0, r = size - 1;

    for (int i = l; i <= r; ++i)
    {
        int min = i;
        for (int j = i + 1; j <= r; ++j)
        {
            if (container[j] < container[min])
            {
                min = j;
            }
        }
        swap(container[i], container[min]);
    }
}

template<typename T>
void insertionSort(T* container, int size)
{
    if (!container) return;

    int l = 0, r = size - 1; 

    // put first the smallest element into position so it can serve as a sentinel
    for (int i = r; i > l; --i)
    {
        if (container[i] < container[i - 1])
        {
            swap(container[i - 1], container[i]);
        }
    }

    for (int i = l + 2; i <= r; ++i)
    {
        int j = i;
        T v = container[i];

        while (v < container[j - 1])
        {
            container[j] = container[j - 1];
            --j;
        }
        container[j] = v;
    }
}

template<typename T>
void bubleSort(T* container, int size)
{
    if (!container) return;

    int l = 0, r = size -1;

    for (int i = l; i < r; ++i)
    {
        for (int j = r; j > i; --j)
        {
            if (container[j] < container[j - 1])
            {
                swap(container[j - 1], container[j]);
            }
        }
    }
}

template<typename T>
void inputContainer(T* container, int size)
{
    if (!container) return;

    for (int i = 0; i < size; ++i)
    {
        std::cin >> container[i];
    }
}

template<typename T>
void printContainer(const T* container, int size)
{
    if (!container) return;

    std::cout << container[0];
    for (int i = 1; i < size; ++i)
    {
        std::cout << ' ' << container[i];
    }
    std::cout << '\n';
}

template<typename T>
int binarySearch(T x, const T* container, int size)
{
    if (!container) return -1;

    int l = 0, r = size - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;

        if (x > container[mid]) l = mid + 1;
        else if (x < container[mid]) r = mid - 1;
        else return mid; 
    }

    return -1;
}

int main()
{
    std::cout << "Please input how many numbers you will input after.\n";
    std::cout << "Number N must be in interval: [1, 10 000].\n";
    int N;
    do std::cin >> N;
    while (N <= 0 || N >= 10001);

    int* container = new(std::nothrow) int[N];
    if (!container)
    {
        std::cerr << "Not enough memory for " << sizeof(int)*N << " bytes.\n";
        return -1;
    }
    
    std::cout << "Please input N numbers separated by a whitespace character:\n";
    inputContainer(container, N);
    std::cout << "You have inputed:\n";
    printContainer(container, N);

    std::cout << "Selection sort.\n";
    selectionSort(container, N);
    printContainer(container, N);
    
    std::cout << "Insertion Sort.\n";
    insertionSort(container, N);
    printContainer(container, N);

    std::cout << "Buble Sort.\n";
    bubleSort(container, N);
    printContainer(container, N);

    std::cout << "Quick Sort.\n";
    quickSort(container, 0, N - 1);
    printContainer(container, N);

    std::cout << "Merge Sort.\n";
    mergeSort(container, 0, N - 1);
    printContainer(container, N);

    std::cout << "Heap Sort.\n";
    heapSort(container, N);
    printContainer(container, N);

    std::cout << "Type value to find:\n";
    
    int value;
    std::cin >> value;
    
    int foundIndex = binarySearch(value, container, N);
    if (foundIndex < 0)
        std::cout << value << " is not found.\n";
    else
        std::cout << "Found " << value << " on index: " << foundIndex << '\n'; 

    delete[] container;
    container = nullptr;

    return 0;
}