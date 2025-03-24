template <typename T>
constexpr T qpow(T a, i64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}
template <typename T>
struct Matrix {
    vector<vector<T>> arr;
    int n, m;
    Matrix() = default;
    Matrix(int n, int m) : n(n), m(m) { arr.resize(n, vector<T>(m)); }
    Matrix(int n) : n(n), m(n) { arr.resize(n, vector<T>(n)); }
    Matrix(const vector<vector<T>> &arr) : arr(arr), n(arr.size()), m(arr[0].size()) {}
    Matrix operator*(const Matrix &b) {
        assert(m == b.n);
        Matrix res(n, b.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                for (int k = 0; k < m; k++)
                    res.arr[i][j] += arr[i][k] * b.arr[k][j];
        return res;
    }
    Matrix operator+(const Matrix &b) {
        assert(n == b.n && m == b.m);
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.arr[i][j] = arr[i][j] + b.arr[i][j];
        return res;
    }
    Matrix operator-(const Matrix &b) {
        assert(n == b.n && m == b.m);
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.arr[i][j] = arr[i][j] - b.arr[i][j];
        return res;
    }
    Matrix operator-() {
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.arr[i][j] = -arr[i][j];
        return res;
    }
    Matrix &operator*=(const Matrix &b) { return *this = *this * b; }
    Matrix &operator+=(const Matrix &b) { return *this = *this + b; }
    Matrix &operator-=(const Matrix &b) { return *this = *this - b; }
    Matrix &operator-() { return *this = -*this; }
    vector<T> &operator[](int i) { return arr[i]; }
    const vector<T> &operator[](int i) const { return arr[i]; }
    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << arr[i][j] << " ";
            cout << "\n";
        }
    }
    
};
