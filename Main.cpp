/*
PARENT: i/d
*/
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;

int comparisons = 0;

int parent(int i, int d)
{
	int result;
	if (i == 1 || i == 0)
		result = 0;
	else
		result = (int)(i - 1) / d;

	return result;
}

template <typename Comparable>
int getBiggestChild(Comparable arr[], int parent, int d, int n)
{
	int child = parent * d + 1;
	int biggestChild = 0;

	for (int i = 1; i < d; i++)
	{

		comparisons++;
		if ((child + i < n) && (arr[child + biggestChild] < arr[child + i]))
			biggestChild = i;
	}

	return (biggestChild + child);

}

template <typename Comparable>
void buildHeapTopDown(Comparable arr[], int n, int d)
{

	for (int i = 0; i < n; i++)
	{
		int pos = i;

		while (arr[pos] > arr[parent(pos, d)])
		{
			swap(arr[parent(pos, d)], arr[pos]);
			pos = parent(pos, d);
			comparisons++;
		}
	}

}

template <typename Comparable>
void buildHeapBottomUp(Comparable arr[], int n, int d)
{
	for (int i = (n - 2) / d; i >= 0; i--)
	{
		bool heap = false; //Assume that we don't have a heap
		int parent = i;

		int child = parent * d + 1;

		while (!heap && child < n)
		{
			int biggestChild = getBiggestChild(arr, parent, d, n);

			/*
			If one of the children's values ends up being bigger than that of the parent -
			- swap them. This is not a heap)
			If all the children are smaller in value than the parent this "branch" is a heap.
			*/
			comparisons++;
			if (arr[biggestChild] > arr[parent])
				swap(arr[biggestChild], arr[parent]);
			else
				heap = true;

			parent = biggestChild;
			child = parent * d + 1;

		}
	}
}

template <typename Comparable>
void siftDown(Comparable arr[], int n, int d)
{
	bool isHeap = false;
	int parent = 0;
	int child = parent * d + 1;

	while (!isHeap && child < n)
	{
		int biggestChild = getBiggestChild(arr, parent, d, n);

		comparisons++;
		if (arr[biggestChild] > arr[parent])
			swap(arr[biggestChild], arr[parent]);
		else
			isHeap = true;

		parent = biggestChild;
		child = parent * d + 1;

	}
}

template <typename Comparable>
bool checkIfHeap(Comparable arr[], int n, int d)
{
	bool isHeap = true;
	for (int i = n; i > 0; i--)
		if (arr[i] > arr[parent(i, d)])
			isHeap = false;

	return isHeap;
}

void fillArrayWithRandomNumbers(int arr[], int n, int maxValue)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		arr[i] = rand() * rand() % maxValue;
}

string intToStr(int i)
{
	ostringstream oss;
	oss << i;

	return oss.str();

}

void testOfTopDownConstructionOfHeap(int arr[], int n, int d)
{
	comparisons = 0;
	fillArrayWithRandomNumbers(arr, n, 100000);

	buildHeapTopDown(arr, n, d);
	cout << "Test Top-Down Construction: " << endl << "d = " << intToStr(d) << " n = " << intToStr(n) << " Comparisons: " << comparisons << " Is heap: " << checkIfHeap(arr, n, d) << endl << endl;
	comparisons = 0;

}

void testOfBottomUpConstructionOfHeap(int arr[], int n, int d)
{
	comparisons = 0;
	fillArrayWithRandomNumbers(arr, n, 100000);

	buildHeapBottomUp(arr, n, d);
	cout << "Test Bottom-Up Construction: " << endl << "d = " << intToStr(d) << " n = " << intToStr(n) << " Comparisons: " << comparisons << " Is heap: " << checkIfHeap(arr, n, d) << endl << endl;
	comparisons = 0;
}

//Returns current root value and sets root value to -1
template <typename Comparable>
Comparable removeFromHeap(Comparable heap[], int n, int d)
{
	int root = heap[0];
	heap[0] = heap[n - 1];

	siftDown(heap, n, d);
	heap[n - 1] = root;
	return root;
}

template <typename Comparable>
void sortUsingTopDownConstructionOfHeap(Comparable arr[], int n, int d)
{
	//Fill the array and turn it into a heap
	fillArrayWithRandomNumbers(arr, n, 100000);
	buildHeapTopDown(arr, n, d);
	comparisons = 0;

	for (int i = 0; i < n; i++)
		arr[n - i - 1] = removeFromHeap(arr, n - i, d);

	cout << "Top Down Sort:" << endl << "d = " << intToStr(d) << " n = " << intToStr(n) << " Comparisons: " << intToStr(comparisons) << endl << endl;
}

template <typename Comparable>
void sortUsingBottomUpConstructionOfHeap(Comparable arr[], int n, int d)
{
	fillArrayWithRandomNumbers(arr, n, 100000);
	buildHeapBottomUp(arr, n, d);
	comparisons = 0;

	for (int i = 0; i < n; i++)
		arr[n - i - 1] = removeFromHeap(arr, n - i, d);

	cout << "Test Bottom-Up Sort: " << endl << "d = " << intToStr(d) << " n = " << intToStr(n) << " Comparisons: " << intToStr(comparisons) << endl << endl;
}

int main(void)
{
	const int n = 100000;
	const int maxValue = 1000000;

	int sortArr[n];
	int constructArr[50];

	cout << "***** Heap Construction Tests *****" << endl << endl;

	testOfTopDownConstructionOfHeap(constructArr, 50, 4);
	testOfBottomUpConstructionOfHeap(constructArr, 50, 4);

	testOfTopDownConstructionOfHeap(constructArr, 50, 7);
	testOfBottomUpConstructionOfHeap(constructArr, 50, 7);

	cout << "Heap Sort Tests" << endl << endl;
	for (int i = 2; i <= 5; i++)
	{
		sortUsingTopDownConstructionOfHeap(sortArr, n, i);
		sortUsingBottomUpConstructionOfHeap(sortArr, n, i);
	}
	sortUsingTopDownConstructionOfHeap(sortArr, n, 8);
	sortUsingBottomUpConstructionOfHeap(sortArr, n, 8);

	getchar();
	return 0;


}