#include <stdio.h>

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class MySort {
 private:
  void merge(T &arr, int l, int m, int r);
  void heapify(T &arr, int index, int heapSize);
  void heapInsert(T &arr, int index);
  int maxbits(vector<int> &arr);
  int getDigit(int x, int d);

 public:
  MySort();
  ~MySort();
  void sortArray(T &arr, void (MySort::*func)(T &arr, int l, int r));
  void insertionSort(T &arr);
  void bubbleSort(T &arr);
  void selectionSort(T &arr);
  void mergeSort(T &arr, int l, int r);
  void quickSort(T &arr, int l, int r);
  void heapSort(T &arr);
  // 基数排序，只适用于非负整数排序
  void radixSort(vector<int> &arr);
  void radixSort(vector<int> &arr, int l, int r, int digit);
};

template<class T>
MySort<T>::MySort() {}

template<class T>
MySort<T>::~MySort() {}

template <class T>
void MySort<T>::sortArray(T &arr, void (MySort::*func)(T &arr, int l, int r)) {
  (this->*func)(arr, 0, arr.size() - 1);
}
template <class T>
void sortArray(T &arr, void (*func)(T &arr, int l, int r)) {
  func(arr, 0, arr.size() - 1);
}

template <class T>
void MySort<T>::insertionSort(T &arr) {
  if (arr.empty() || arr.size() < 2) return;
  for (int i = 1; i < arr.size(); i++)
    for (int j = i - 1; j >= 0; j--)
      if (arr[j + 1] < arr[j])
        swap(arr[j], arr[j + 1]);
      else
        break;
}
template <class T>
void MySort<T>::bubbleSort(T &arr) {
  if (arr.empty() || arr.size() < 2) return;
  for (int e = arr.size() - 1; e > 0; e--)
    for (int h = 0; h < e; h++)
      if (arr[h] > arr[h + 1]) swap(arr[h], arr[h + 1]);
}

template <class T>
void MySort<T>::selectionSort(T &arr) {
  if (arr.empty() || arr.size() < 2) return;
  for (int i = 0; i < arr.size() - 1; i++) {
    int min = i;
    for (int j = i + 1; j < arr.size(); j++) min = arr[j] < arr[min] ? j : min;
    swap(arr[i], arr[min]);
  }
}

template <class T>
void MySort<T>::mergeSort(T &arr, int l, int r) {
  // if (r == 999999) r = arr.size();
  if (l >= r) return;
  int m = l + (r - l) / 2;
  MySort::mergeSort(arr, l, m);
  MySort::mergeSort(arr, m + 1, r);
  MySort::merge(arr, l, m, r);
}

template <class T>
void MySort<T>::merge(T &arr, int l, int m, int r) {
  T helpArr(r - l + 1);
  int p1 = l, p2 = m + 1;
  int i = 0;
  while (p1 <= m && p2 <= r)
    helpArr[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
  while (p1 <= m) helpArr[i++] = arr[p1++];
  while (p2 <= r) helpArr[i++] = arr[p2++];
  for (int n = 0; n < helpArr.size(); n++) arr[l + n] = helpArr[n];
}

template <class T>
void MySort<T>::quickSort(T &arr, int l, int r) {
  if (l >= r) return;
  int p = arr[r];  // partition point
  int i = l, j = r;
  while (i < j) {
    while (i < j && arr[i] <= p) i++;
    if (i < j) swap(arr[j--], arr[i]);
    while (i < j && arr[j] >= p) j--;
    if (i < j) swap(arr[i++], arr[j]);
  }
  arr[i] = p;
  quickSort(arr, l, i - 1);
  quickSort(arr, i + 1, r);
}

template <class T>
void MySort<T>::heapSort(T &arr) {
  int heapSize = arr.size();
  if (arr.empty() || heapSize < 2) return;
  for (int i = 0; i < heapSize; i++) MySort::heapInsert(arr, i);
  swap(arr[0], arr[--heapSize]);
  while (heapSize > 0) {
    MySort::heapify(arr, 0, heapSize);
    swap(arr[0], arr[--heapSize]);
  }
}

template <class T>
void MySort<T>::heapify(T &arr, int index, int heapSize) {
  int l = index * 2 + 1;
  while (l < heapSize) {
    int r = l + 1;
    int largeOne = r < heapSize && arr[r] > arr[l] ? r : l;
    largeOne = arr[largeOne] >= arr[index] ? largeOne : index;
    if (largeOne == index) break;
    swap(arr[largeOne], arr[index]);
    index = largeOne;
    l = index * 2 + 1;
  }
}

template <class T>
void MySort<T>::heapInsert(T &arr, int index) {
  int parent = (index - 1) / 2;
  while (arr[index] > arr[parent]) {
    swap(arr[index], arr[parent]);
    index = parent;
    parent = (index - 1) / 2;
  }
}

template<class T>
void MySort<T>::radixSort(vector<int> &arr) {
  if (arr.size() < 2) return;
  MySort<T>::radixSort(arr, 0, arr.size() - 1, MySort<T>::maxbits(arr));
}

template<class T>
int MySort<T>::maxbits(vector<int> &arr) {
  // 统计最大值多少位
  int max = INT_MIN;
  for (int i = 0; i < arr.size(); i++) max = arr[i] > max ? arr[i] : max;
  int res = 0;
  while (max != 0) {
    res++;
    max /= 10;
  }
  return res;
}

template<class T>
void MySort<T>::radixSort(vector<int> &arr, int l, int r, int digit) {
  const int radix = 10;  // 以10为基底
  int i = 0, j = 0;
  int bucket[r - l + 1] = {0};
  for (int d = 1; d <= digit; d++) {  // 入桶出桶的次数
    int count[radix] = {0};  // count[i]意味着小于等于i的个数,出桶时依此确定位置
    for (i = l; i <= r; i++) {
      j = MySort::getDigit(arr[i], d);
      count[j]++;
    }
    for (i = 1; i < radix; i++) {
      count[i] = count[i] + count[i - 1];
    }
    for (i = r; i >= l; i--) {
      j = MySort::getDigit(arr[i], d);
      bucket[count[j] - 1] = arr[i];  // 入桶
      count[j]--;
    }
    for (i = l, j = 0; i <= r; i++, j++)
      arr[i] = bucket[j];  // 从辅助数组写入原数组
  }
}

template<class T>
int MySort<T>::getDigit(int x, int d) {  // 获得第d位的数
  return ((x / ((int)pow(10, d - 1))) % 10);
}

int main() {
  // MySort *ms = new MySort;
  MySort<vector<int>> ms;
  // vector<int> data = {0, 1, 44, -63, 321, -221, 70, 390};
  vector<int> data = {0, 1, 44, 63, 321, 221, 70, 390};
  int s = data.size();
  for (int i = 0; i < s; i++) printf("%4d,", data[i]);
  cout << "" << endl;
  ms.insertionSort(data);
  ms.bubbleSort(data);
  ms.selectionSort(data);
  ms.mergeSort(data, 0, s-1);
  ms.sortArray(data, &MySort<vector<int>>::mergeSort);
  ms.sortArray(data, &MySort<vector<int>>::quickSort);
  ms.heapSort(data);
  ms.radixSort(data);
  for (int i = 0; i < s; i++) printf("%4d,", data[i]);
  // cout << "hello" << endl;
  return 0;
}