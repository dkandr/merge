#include <iostream>
#include <future>
#include <chrono>
#include <random>

using namespace std;

bool make_thread = true;

void merge(int* arr, int l, int m, int r)
{
	int nl = m - l + 1;
	int nr = r - m;

	// ������� ��������� �������
	//int left[nl], right[nr];
	int* left = new int[nl];
	int* right = new int[nr];

	// �������� ������ �� ��������� �������
	for (int i = 0; i < nl; i++)
		left[i] = arr[l + i];
	for (int j = 0; j < nr; j++)
		right[j] = arr[m + 1 + j];

	long i = 0, j = 0;
	long k = l;  // ������ ����� �����

	while (i < nl && j < nr)
	{
		// ���������� ����������� �������� ������� �� ������� ������
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else {
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	// ���������� ���������� �������� ����� �����
	while (i < nl)
	{
		arr[k++] = left[i++];
	}
	// ���������� ���������� �������� ������ �����
	while (j < nr)
	{
		arr[k++] = right[j++];
	}

	delete[] left;
	delete[] right;
}

void mergeSort(int* arr, long l, long r)
{
	if (l >= r)
		return;

	long m = (l + r - 1) / 2;
	
	if (make_thread && (m - l > 10000))
	{
		auto f = async(launch::async, [&]()
			{
				mergeSort(arr, l, m);
			});
		mergeSort(arr, m + 1, r);
	}
	else
	{
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
	}

	merge(arr, l, m, r);
}

int main()
{
	srand(time(NULL));
	int arr_size = 10000000;
	int* array = new int[arr_size];

	for (long i = 0; i < arr_size; i++)
	{
		array[i] = rand() % 90 + 10;
	}

	time_t start, end;

	time(&start);
	mergeSort(array, 0, arr_size - 1);
	time(&end);

	double seconds = difftime(end, start);
	cout << "The time: " << seconds << " seconds" << endl;

	return 0;
}