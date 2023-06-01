// Alexis Urias
// CSE 310 Summer 23


#include <iostream>
#include <cmath>	// libraries for math, time, and clocks
#include <ctime>
#include <string>
#include <chrono>

using namespace std;

void insertionSort(int a[], int n);		// forward declaration
void selectionSort(int a[], int n);
void quickSort(int a[], int p, int r);
int partition(int a[], int p, int r);
void mergeSort(int a[], int p, int r);
void merge(int a[], int p, int q, int r);


int main() {

	//int array[5] = { 1, 3, 9, 6, 3};
	//int n = sizeof(array) / sizeof(array[0]);

	int n;
	
	cout << "Enter the size of the array: ";		// get the size of the array from user 
	cin >> n;

	int* array = new int[n];		// dynamically allocate array

	srand(time(0));

	for (int i = 0; i < n; i++) {
		array[i] = rand() % 901 + 100;
	}

	auto start = chrono::high_resolution_clock::now(); // starts the clock

		/* PLEASE READ: commented out the algorithms that are not being tested,
			basically set it up to where one algorithm is tested at a time.
			Uncomment the algorithm you want to test and comment out the others */
	
	insertionSort(array, n);
	//selectionSort(array, n);
	//quickSort(array, 0, n - 1);
	//mergeSort(array, 0, n - 1);

	auto end = chrono::high_resolution_clock::now(); // stops the clock

	auto time = chrono::duration_cast<chrono::microseconds>(end - start); // get the time

	double output = static_cast<double>(time.count()); // conversion to double for milliseconds

	cout << "Run time for algorithm (microseconds): " << output << endl;
	cout << "Run time for algorithm (milliseconds): " << output / 1000 << " ms"; 

	cout << "\nSorted array: ";
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;


	delete[] array;		// delete block of memory

	return 0;
}

void insertionSort(int a[], int n) {

	for (int j = 2; j < n; j++) {		// iterate from 2 to n
		int key = a[j];					// set index of j to key
		int i = j - 1;					// set i position to one less
		while (i >= 0 && a[i] > key) {		// while i is greather than 0 and index position is greater than the key
			a[i + 1] = a[i];				// shift
			i = i - 1;						
		}
		a[i + 1] = key;
	}
}

void selectionSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {		// iterate from 0 to n - 1...  going from 1 does not include all elements
		int min = i;						// set i to min
		for (int j = i + 1; j < n; j++) {		// iterate from i + 1 to n
			if (a[j] < a[min]) {				// set j to min if it is less than min
				min = j;
			}
		}
		swap(a[min], a[i]);				// perform swap
	}
}

int partition(int a[], int p, int r) { // purpose of partition is to split the array around a specific pivot
											// smaller subproblems
	int x = a[r];		
	int i = p - 1;

	for (int j = p; j <= r - 1; j++) {
		if (a[j] <= x) {
			i = i + 1;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[r]);
	return i + 1;
}

void quickSort(int a[], int p, int r) { // quick sort calls itself and partition

	if (p < r) {
		int q = partition(a, p, r);
		quickSort(a, p, q - 1);		// left
		quickSort(a, q + 1, r);		// right
	}

}

void merge(int a[], int p, int q, int r) { // merge is supposed to do just that

	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;
	int* L = new int[n1 + 1];		// dynamically allocate memory for left and right array
	int* R = new int[n2 + 1];

	for (i = 0; i <= n1; i++) {		// left
		L[i] = a[p + i];
	}

	for (j = 0; j <= n2; j++) {		// right
		R[j] = a[q + j + 1];
	}

	L[n1] = numeric_limits<int>::max();		// infinite integers
	R[n2] = numeric_limits<int>::max();

	i = 0;
	j = 0;

	for (k = p; k <= r; k++) { // merge into a[]
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i = i + 1;
		}
		else {
			a[k] = R[j];
			j = j + 1;
		}
	}
	
	delete[] L;		// delete block of memory
	delete[] R;

}

void mergeSort(int a[], int p, int r) {		// merge sort implements divide and conquer method
	if (p < r) {
		int q = floor((p + r) / 2);
		mergeSort(a, p, q);
		mergeSort(a, q + 1, r);
		merge(a, p, q, r);
	}
}
