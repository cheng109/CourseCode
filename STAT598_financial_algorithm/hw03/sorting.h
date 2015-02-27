/*
 * sorting.h
 *
 *  Created on: Feb 26, 2015
 *      Author: cheng109
 */

#ifndef SORTING_H_
#define SORTING_H_

#include <vector>

using namespace std;

template<typename T> int findSmallest(vector<T> & v, int istart);


template<typename T> void selectionSort(vector<T> & v);
template<typename T> void insertionSort(vector<T> & v);
template<typename T> vector<T> mergeSort(vector<T> & v);

template<typename T> vector<T> merge(vector<T> &left, vector<T> &right) ;
template<typename T> void myswap(T &a, T &b) ;
template<typename T> void heaplify(vector<T> &v, int size);
template<typename T> void buildHeap(vector<T> &v);
template<typename T> void vectorPrint(vector<T> const v);
template<typename T> void bubbleSort(vector<T> &v);
template<typename T> void quickSort(vector<T> &v, int left, int right);
#endif /* SORTING_H_ */
