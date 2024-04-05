#include <iostream>


//Exchange Sort
void bubbleSort(int* start, int* end);


//Selection Sort
void selectionSort(int* start, int* end);

//Insertion Sort
/* Straight Insertion Sort */
void insertionSort(int* start, int* end);
/* Shell Sort */
void sortSegment(int* start, int* end, int segment_idx, int cur_segment_total);
void ShellSort(int* start, int* end, int* num_segment_list, int num_phases);