/*
 * hw03p01.cpp
 *
 *  Created on: Feb 23, 2015
 *      Author: cheng109
 */
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include <assert.h>
#include <cmath>

using namespace std;
template<typename T>
void  selectionSort(vector<T> & v) {
	int smallIndex;

	for(int i=0; i<v.size(); i++) {
			smallIndex = findSmallest(v,i);
			T temp = v[i];
			v[i] = v[smallIndex];
			v[smallIndex] = temp;
	}
}

template<typename T>
void insertionSort(vector<T> & v) {
	int i, j, currentIter;

	for(i=0 ; i<v.size(); i++) {
		j=i-1;
		currentIter = i;
		while(j>=0 && v[currentIter] < v[j]  ) {
			swap(v[j], v[currentIter]);
			currentIter--;
			j--;
		}
	}
}


template<typename T>
vector<T> mergeSort(vector<T> & v) {
	if(v.size()==1)
		return v;
	typename vector<T>::iterator middle = v.begin()+v.size()/2;

	vector<T> left(v.begin(), middle);
	vector<T> right(middle, v.end());
	left = mergeSort(left);
	right = mergeSort(right);

	return merge(left, right);
}

template<typename T>
vector<T> merge(vector<T> &left, vector<T> &right) {
	vector<T> result;
	int iL=0;
	int iR=0;
	while(iL < left.size() && iR < right.size()) {
		if(left[iL]<right[iR]) {
			result.push_back(left[iL]);
			iL++;
		}
		if(left[iL]>=right[iR]) {
			result.push_back(right[iR]);
			iR++;
		}
	}
	while(iL<left.size()){
		result.push_back(left[iL]);
		iL++;

	}
	while(iR<right.size()) {
		result.push_back(right[iR]);
		iR++;
	}

	return result;
}


template<typename T>
int findSmallest(vector<T> & v, int istart) {
	T smallValue = v[istart];
	T smallIndex = istart;

	for (int i=istart; i<v.size(); i++) {
		if(v[i]<smallValue) {
			smallValue = v[i];
			smallIndex = i;
		}
	}
	return smallIndex;
}

template<typename T>
void quickSort(vector<T> &v, int left, int right) {

	int i = left, j = right;
	T pivot = v[(left + right) / 2];

	/* partition */

	while (i <= j) {
		while (v[i] < pivot)
			i++;
		while (v[j] > pivot)
			j--;
		if (i <= j) {
			swap(v[i],v[j]);
			i++;
			j--;
		}
	};

	if (left < j)
		quickSort(v, left, j);
	if (i < right)
		quickSort(v, i, right);

}

template<typename T>
void heapSort(vector<T> &v) {
	buildHeap(v);
	int size = v.size();
	while(size >0) {
		swap(v[0], v[size-1]);
		size --;
		heaplify(v, size);
	}
}

// Only the root is not heaplified.
template<typename T>
void heaplify(vector<T> &v, int size) {
	int i=0;
	while(2*i+2<size) {
		if (v[i]<=v[2*i+1] && v[2*i+2]<=v[2*i+1])	{
			swap(v[i], v[2*i+1]);
			i=2*i+1;
		}
		else if (v[i]<v[2*i+2] && v[2*i+1]<v[2*i+2]){
			swap(v[i], v[2*i+2]);
			i=2*i+2;
		}
		else break;
	}
	if(size==2*i+2 && v[i]<v[2*i+1])
		swap(v[i], v[2*i+1]);
}

template<typename T>
void myswap(T &a, T &b) {
	T temp = a;
	a= b;
	b=temp;
}

template<typename T>
void buildHeap(vector<T> &v) {
	assert(v.size()>0);
	for(int i=1; i<v.size(); i++) {
		int j=i;
		while(j>0) {
			if(v[j]>v[floor((j-1)/2)]) {
				swap(v[j], v[floor((j-1)/2)]);
				j = floor((j-1)/2);
			}
			else break;
		}
	}
}

template<typename T>
void vectorPrint(vector<T> const v) {
	cout << "[";
	typename vector<T>::const_iterator i;
	for(i=v.begin(); i!=v.end()-1; ++i) {
		cout << *i << ", " ;
	}
	cout << *i << "]" << endl;
}

template<typename T>
void bubbleSort(vector<T> &v) {
	int i=0;
	while(i<v.size()) {
		for(int j=0; j<v.size()-1; j++) {
			if(v[j]>v[j+1])
				swap(v[j], v[j+1]);
		}
		i++;
	}
}

template<typename T>
vector<T> randVector(int size, T min, T max) {
	vector<T> v;
	double b;
	for(int i=0; i<size; i++ ) {
		b = (double)rand()/RAND_MAX;
		b = b*(max-min) + min;
		v.push_back((T)b);
	}
	return v;
}


int main () {
	// Part 1
	vector<double> v, v1, v2 , v3 , v4 ,v5 , v6, v7, vv;
	v1=v2=v3=v5 =v4 =v6=v7= v= randVector(10, 0.0, 10.0);

	cout << "Original vector:  "<< endl;
	vectorPrint(v);
	selectionSort(v);
	cout << "Selection Sort result:  " << endl;
	vectorPrint(v);
	insertionSort(v2);
	cout << "Insertion Sort result:  "<< endl;
	vectorPrint(v2);

	vv= mergeSort(v3);
	cout << "Merge Sort result:  "<< endl;

	vectorPrint(vv);

	quickSort(v4, 0, v4.size()-1);
	cout << "Quick Sort result:  "<< endl;
	vectorPrint(v4);

	heapSort(v5);
	cout << "Bubble Sort result:  "<< endl;
	vectorPrint(v5);

	heapSort(v6);
	cout << "Heap Sort result:  "<< endl;
	vectorPrint(v6);


	// Part 2

	int size[] = {100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	cout << "Quick Sort times: ";
	for(int i=0; i<12; i++) {
		double elapse = 0;
		for (int j=0; j<10; j++) {
			int min=0;
			int max=size[i];
			vector<int> v = randVector(size[i], min, max);
			double start = double(clock())/CLOCKS_PER_SEC;
			quickSort(v, 0, v.size()-1);
			//heapSort(v);
			//mergeSort(v);
			//insertionSort(v);
			//selectionSort(v);
			//bubbleSort(v);
			double finish = double(clock())/CLOCKS_PER_SEC;
			elapse = finish - start +elapse;
		}
		cout <<  elapse/10  << "  ";
	}
	cout << endl; 
	return 0; 

}

