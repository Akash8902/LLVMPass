#include <bits/stdc++.h>
using namespace std;

template <typename T>
class TrackedMemory
{
public:
    TrackedMemory(T *ptr) : ptr_(ptr) {}

    T &operator*()
    {
        cout << "Reading from memory location: " << ptr_ << endl;
        return *ptr_;
    }

    TrackedMemory<T> &operator->()
    {
        cout << "Reading from memory location: " << ptr_ << endl;
        return *this;
    }

    void operator=(const T &val)
    {
        cout << "Writing to memory location: " << ptr_ << endl;
        *ptr_ = val;
    }

private:
    T *ptr_;
};

int main()
{
    int x = 10;
    int n;
    int k;
    cin >> k;
    TrackedMemory<int> data(&n);
    int kk = *data;
    data = k;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        TrackedMemory<int> data(&arr[i]);
        int kk = *data;
        cout << "Reading  " << i + 1 << "st memory location .............." << endl;
        int assign = *data;
        cout << "Writing " << i + 1 << "st memory location .............." << endl;
        data = 100;
    }
    return 0;
}
