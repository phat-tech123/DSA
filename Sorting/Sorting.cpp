#include"Sorting.h"

void bubbleSort(int* start, int* end) {
	int size = end - start;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (*(start + j) > *(start + j + 1)) {
				std::swap(*(start + j), *(start + j + 1));
			}
		}
	}
}	

void selectionSort(int* start, int* end) {
	int size = end - start;
	for (int i = 0; i < size - 1; i++) {
		int min = start[i];
		int index = i;
		for (int j = i + 1; j < size; j++) {
			if (start[j] < min) {
				min = start[j];
				index = j;
			}
		}
		std::swap(start[i], start[index]);
	}
}

void insertionSort(int* start, int* end) {
	int size = end - start;
	for (int i = 1; i < size; i++) {
		for (int j = i - 1 ; j >= 0; --j) {
			if (start[j] > start[j + 1]) {
				std::swap(start[i], start[j + 1]);
			}
		}
	}
}

void sortSegment(int* start, int* end, int segment_idx, int cur_segment_total) {
	for (int i = segment_idx + cur_segment_total; start + i < end; i += cur_segment_total) {
		for (int j = i - cur_segment_total; j >= 0; j -= cur_segment_total) {
			if (start[j] > start[j + cur_segment_total]) {
				std::swap(start[j], start[j + cur_segment_total]);
			}
		}
	}
}
void ShellSort(int* start, int* end, int* num_segment_list, int num_phases) {
	// TODO
	// Note: You must print out the array after sorting segments to check whether your algorithm is true.
	while (num_phases) {
		--num_phases;
		for (int i = 0; i < num_segment_list[num_phases]; i++) {
			sortSegment(start, end, i , num_segment_list[num_phases]);
		}
		std::cout << num_segment_list[num_phases] << " segments: ";
		for (int i = 0; i < end - start; i++) {
			std::cout << *(start + i) << " ";
		}
		std::cout << std::endl;
	}
}