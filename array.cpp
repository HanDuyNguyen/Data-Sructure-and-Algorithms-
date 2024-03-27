#include <iostream>
#include <string>

using namespace std;

class Array {
private:
  int *A;
  int size;
  int length;
  static void merge(int *A, int l, int m, int r);
  static void merge_sort(int *A, int l, int r);
  static int partition(int *A, int start, int end);
  static void quick_sort(int *A, int l, int r);
  static int linear_search(int *A, int length, int k);
  static int binary_search(int *A, int length, int k);

public:
  Array(int size=10);
  Array(Array &r);
  ~Array();

  int get_size();
  int get_length();
  void set_size(int size);
  friend ostream &operator<<(ostream &out, Array &a);
  void append(int x);
  void insert(int index, int x);
  void extend(Array a);
  void del(int index);
  bool is_sorted();
  void sort(string method="merge_sort");
  int search(int k, string method="linear_search");
  int get(int index);
  void set(int index, int x);
  int max();
  int min();
  void reverse();
  void rotate();
  void left_shift();
  void sorted_insert(int x);
  void arrange(int x);
};

int main() {
  Array arr(5);
  arr.append(1);
  arr.append(4);
  arr.append(3);
  arr.append(6);
  arr.append(7);
  arr.append(2);
  arr.insert(1, 10);
  arr.del(1);
  Array arr_1(arr);
  cout << arr_1.get_size() << endl;
  cout << arr_1.get_length() << endl;
  cout << arr_1 << endl;
  cout << arr_1.is_sorted() << endl;
  arr_1.sort("quick_sort");
  cout << arr_1 << endl;
  cout << arr_1.search(4, "binary_search") << endl;
  cout << arr_1 << endl;
  cout << arr_1.get(4) << endl; 
  arr_1.set(4, 100);
  cout << arr_1 << endl;
  arr_1.reverse();
  cout << arr_1 << endl;
  arr_1.rotate();
  cout << arr_1 << endl;
  arr_1.arrange(3);
  cout << arr_1 << endl;
  arr_1.extend(arr);
  cout << arr_1 << endl;
  return 0;
}

Array::Array(int size) {
  this->size = size;
  length = 0;
  A = new int[size];
}

Array::Array(Array &r) {
  size = r.size;
  length = r.length;
  A = new int[size];
  if (length > 0) {
    for (int i=0; i<length; i++)
      A[i] = r.A[i];
  }
}

Array::~Array() {
  delete []A;
}

int Array::get_size() {
  return size;
}

int Array::get_length() {
  return length;
}

void Array::set_size(int size) {
  if (size > 0) {
    this->size = size;
    if (this->size < length)
      length = this->size;

    int *T = new int[this->size];
    if (length > 0) {
      for (int i=0; i<length; i++)
        T[i] = A[i];
    }
    delete []A;
    A = T;
  }
}

ostream &operator<<(ostream &out, Array &a) {
  out << "[";
  for (int i=0; i<a.length; i++) {
    if (i < a.length-1)
      out << a.A[i] << " ";
    else
      out << a.A[i];
  }
  out << "]";
  return out;
}

void Array::append(int x) {
  if (length == size)
    set_size(size + 10);
  A[length] = x;
  length++;
}

void Array::insert(int index, int x) {
  if (length == size)
    set_size(size + 10);
  if (index >= 0 && index < length) {
    for (int i=length; i>index; i--)
      A[i] = A[i-1];
    A[index] = x;
    length++;
  }
}

void Array::extend(Array a) {
  int new_length = length + a.length;
  if (size < new_length)
    set_size(new_length + 1);
  for (int i=length; i<new_length; i++)
    A[i] = a.A[i-length];
  length = new_length;
}

void Array::del(int index) {
  int x;
  if (index >= 0 and index < length) {
    x = A[index];
    for (int i=index; i<length-1; i++)
      A[i] = A[i+1];
  }
  length--;
}

bool Array::is_sorted() {
  for (int i=0; i<length-1; i++) {
    if (A[i] > A[i+1])
      return false;
  }
  return true;
}

void Array::merge(int *A, int l, int m, int r) {
  int left_count = m - l + 1;
  int right_count = r - m;
  // Create temp arrays
  int *la = new int[left_count];
  int *ra = new int[right_count];
  for (int i = 0; i < left_count; i++)
    la[i] = A[l + i];
  for (int i = 0; i < right_count; i++)
    ra[i] = A[m + 1 + i];

  int i = 0, j = 0, k = l;
  while (i < left_count && j < right_count) {
    if (la[i] < ra[j]) {
      A[k] = la[i];
      i++;
    }
    else {
      A[k] = ra[j];
      j++;
    }
    k++;
  }

  while (i < left_count) {
    A[k] = la[i];
    i++;
    k++;
  }
  while (j < right_count) {
    A[k] = ra[j];
    j++;
    k++;
  }
  delete[] la;
  delete[] ra;
}
  
void Array::merge_sort(int *A, int l, int r) {
  if (l >= r)
    return;

  int m = (l + r)/2;
  merge_sort(A, l, m);
  merge_sort(A, m+1, r);
  merge(A, l, m, r);
}

int Array::partition(int *A, int start, int end) {
  int p = A[start];
  int i = start;
  int j = end;

  while (i < j) {
    while (A[i] <= p && i < end)
      i++;
    while (A[j] > p && j > start)
      j--;
    if (i < j) {
      int temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  int temp = A[start];
  A[start] = A[j];
  A[j] = temp;
  return j;
}

void Array::quick_sort(int *A, int l, int r) {
  if (l < r) {
    int j = partition(A, l, r);
    quick_sort(A, l, j-1);
    quick_sort(A, j+1, r);
  } 
}

void Array::sort(string method) {
  if (method=="merge_sort")
    Array::merge_sort(A, 0, length-1);
  else if (method=="quick_sort")
    Array::quick_sort(A, 0, length-1);
  else
    cout << "Your sorting method is not defined" << endl;
}

int Array::linear_search(int *A, int length, int k) {
  for (int i=0; i<length; i++) {
    if (A[i] == k) {
      int t = A[0];
      A[0] = A[i];
      A[i] = t;
      return i;
    }
  }
  return -1;
}

int Array::binary_search(int *A, int length, int k) {
  Array::merge_sort(A, 0, length-1);
  int l = 0;
  int m = 0;
  int h = length-1;

  while (l<=h) {
    m = (l+h)/2;
    if (A[m] == k)
      return m;
    else if (A[m] < k)
      l = m+1;
    else
      h = m-1;
  }
  return -1;
}

int Array::search(int k, string method) {
  if (method=="linear_search")
    return Array::linear_search(A, length, k);
  else if (method=="binary_search")
    return Array::binary_search(A, length, k);
  return -1;
}

int Array::get(int index) {
  if (index >= 0 && index < length)
    return A[index];
  return -1;
}

void Array::set(int index, int x) {
  if (index >= 0 && index < length)
    A[index] = x;
}

void Array::reverse() {
  int temp = 0;
  for (int i=0, j=length-1; i < j; i++, j--) {
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
  }
}

void Array::rotate() {
  int temp = 0;
  int first_ele = A[0];
  for (int i = 0; i < length-1; i++) {
    temp = A[i];
    A[i] = A[i+1];
  }
  A[length-1] = first_ele;
}

void Array::left_shift() {
  for (int i=0; i<length-1; i++) {
    A[i] = A[i+1];
  }
  length--;
}

void Array::sorted_insert(int x) {
  if (length == size)
    set_size(size + 10);
  int i = length-1;
  while (x < A[i] && i >= 0) {
    A[i+1] = A[i];
    i--;
  }
  A[i+1] = x;
}

void Array::arrange(int x) {
  int i = 0;
  int j = length-1;
  while (i < j) {
    while (A[i] < x)
      i++;
    while (A[j] >= x)
      j--;
    if (i < j) {
      int temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
}
