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
		result = (int) (i - 1) / d;

	return result;
}

template <typename Comparable>
int getBiggestChild(Comparable arr[], int parent, int d, int n)
{
	int child = parent * d + 1;
	int biggestChild = 0;

	for (int i = 1; i < d; i++)
		if ((child + i < n) && (arr[child + biggestChild] <	arr[child + i])) //Make sure the child is not out of array bounds if so compare size of children.
			biggestChild = i;

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
			{
				swap(arr[biggestChild], arr[parent]);
			}
			else
				heap = true;

			parent = biggestChild;
			child = parent * d + 1;

		}
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
		arr[i] = rand() % maxValue;
}

string intToStr(int i)
{
	ostringstream oss;
	oss << i;

	return oss.str();

}

void testOfTopDownConstructionOfHeap(int arr[], int n, int d)
{

	fillArrayWithRandomNumbers(arr, n, 100000);

	buildHeapTopDown(arr, n, d);
	cout << "Test of top-down construction where d = " << intToStr(d) << " and n = " << intToStr(n) << endl << "Amount of comparisons: " << comparisons << endl;
	comparisons = 0;

}

void testOfBottomUpConstructionOfHeap(int arr[], int n, int d)
{
	fillArrayWithRandomNumbers(arr, n, 100000);

	buildHeapBottomUp(arr, n, d);
	cout << "Test of bottom-up construction where d = " << intToStr(d) << " and n = " << intToStr(n) << endl << "Amount of comparisons: " << comparisons << endl;
	comparisons = 0;
}

//Returns current root value and sets root value to -1
template <typename Comparable>
Comparable removeFromHeap(Comparable heap[], int n, int d)
{
	int root = heap[0];
	heap[0] = -1;

	return root;
}

template <typename Comparable>
void sortUsingTopDownConstructionOfHeap(Comparable arr[], int n, int d)
{
	fillArrayWithRandomNumbers(arr, n, d);
	buildHeapTopDown(arr, n, d);
	for (int i = 0; i < n; i++)
	{
		removeFromHeap(arr, n, d);
	}

}

template <typename Comparable>
void sortUsingBottomUpConstructionOfHeap(Comparable arr[], int n, int d)
{

}

int main(void)
{
	const int n = 50;
	const int maxValue = 100;

	int arr[n];
	
	cout << "****** Heap Construction Tests ******" << endl << endl;

	testOfTopDownConstructionOfHeap(arr, n, 4);
	testOfBottomUpConstructionOfHeap(arr, n, 4);

	testOfTopDownConstructionOfHeap(arr, n, 7);
	testOfBottomUpConstructionOfHeap(arr, n, 7);

	removeFromHeap(arr, n, 7);

	getchar();
	return 0;


}