//#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<pair<int, int>> heap;
int t = 1;
void Heapsort(int v)
{
	if (v == 1)
		return;
	if (heap[v] > heap[v / 2])
	{
		swap(heap[v], heap[v / 2]);
		Heapsort(v / 2);
	}
}
void heapify(int v)
{
	if (v * 2 >= t)
	{
		return;
	}
	if (heap[v * 2].first > heap[v].first)
	{
		swap(heap[v * 2], heap[v]);
		heapify(v * 2);
	}
	if (v * 2 + 1 >= t)
	{
		return;
	}
	if (heap[v * 2 + 1].first > heap[v].first)
	{
		swap(heap[v * 2 + 1], heap[v]);
		heapify(v * 2 + 1);
	}

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;
	vector<int> A(n);
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
	}
	int k;
	cin >> k;
	heap.resize(n + 1);

	for (int i = 0; i < k; i++)
	{
		heap[t].first = A[i];
		heap[t].second = i;
		Heapsort(t);
		t++;
	}
	cout << heap[1].first << " ";
	for (int i = k; i < n; i++)
	{
		while (heap[1].second <= i - k && t>1)
		{
			swap(heap[t - 1], heap[1]);
			t--;
			heapify((int)1);


		}
		heap[t].first = A[i];
		heap[t].second = i;
		Heapsort(t);
		t++;
		cout << heap[1].first << " ";
	}
	return 0;
}
