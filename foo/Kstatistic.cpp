#include <iostream>
#include <vector>

int* findMedian(int* first, int* last) {
	int* middle = first + ((last - first) / 2);

	if (*first < *middle) {

		if (*middle < *last) {
			return middle;
		}
		else if (*first < *last) {
			return last;
		}
		else {
			return first;
		}
	}
	else {
		if (*first < *last) {
			return first;
		}
		else if (*middle < *last) {
			return last;
		}
		else {
			return middle;
		}
	}
}
int* Partition(int* begin, int* end) {
	int* pivot = findMedian(begin, end);

	std::iter_swap(begin, pivot);

	int *i = end;
	int *j = end;

	for (; j > begin; --j) {

		if (*j >= *begin) {
			std::iter_swap(i, j);
			--i;
		}
	}

	std::iter_swap(begin, i);

	return i;
}
int FindKStatistics(int* begin, int* end, size_t index) {

	int* first = begin;
	int* last = end;

	while (true) {
		int* pivot = Partition(first, last);
		int pivot_element_position = pivot - begin;

		if (pivot_element_position == index) {
			return *(begin + index);
		}
		else if (pivot_element_position > index) {
			last = pivot;
		}
		else {
			first = pivot + 1;
		}
	}
}
int main() {
	int n;
	std::cin >> n;

	int index;
	std::cin >> index;
	int *a = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; ++i) {
		int item;
		std::cin >> item;
		a[i] = item;
	}

	std::cout << FindKStatistics(a, a + n - 1, index);
	free(a);
	return 0;
}
