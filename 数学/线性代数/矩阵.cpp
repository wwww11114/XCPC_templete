#include <bits/stdc++.h>

template<std::regular T>
class Matrix {
private:
    size_t rows_, cols_;
    std::vector<std::vector<T>> data_;

    static constexpr T epsilon = 1e-10; // 浮点精度阈值

    // 初等行操作
    void swap_rows(size_t i, size_t j) { std::swap(data_[i], data_[j]); }

    void scale_row(size_t i, T scalar) {
        std::transform(data_[i].begin(), data_[i].end(), data_[i].begin(),
            [scalar](T val) { return val * scalar; });
    }

    void add_scaled_row(size_t target, size_t src, T scalar) {
        std::transform(data_[target].begin(), data_[target].end(), data_[src].begin(), data_[target].begin(), [scalar](T t, T s) { return t + s * scalar; });
    }

public:

    Matrix() : rows_(0), cols_(0) {}
    // 构造器
    Matrix(size_t r, size_t c, T init = T{}) : rows_(r), cols_(c),
        data_(r, std::vector<T>(c, init)) {
    }

    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        rows_ = init.size();
        cols_ = init.begin()->size();
        data_.reserve(rows_);
        for (const auto &row : init) {
            data_.emplace_back(row);
        }
    }

    // 基本属性
    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
    bool is_square() const { return rows_ == cols_; }

    // 元素访问
    std::vector<T> &operator[](size_t i) { return data_[i]; }
    const std::vector<T> &operator[](size_t i) const { return data_[i]; }

    // 矩阵运算
    Matrix operator+(const Matrix &rhs) const {
        if (rows_ != rhs.rows_ || cols_ != rhs.cols_)
            throw std::invalid_argument("Matrix dimensions mismatch");

        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            std::transform(data_[i].begin(), data_[i].end(), rhs[i].begin(), result[i].begin(), std::plus<T>());
        }
        return result;
    }

    Matrix operator*(const Matrix &rhs) const {
        if (cols_ != rhs.rows_)
            throw std::invalid_argument("Matrix multiplication dimensions mismatch");

        Matrix result(rows_, rhs.cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t k = 0; k < cols_; ++k) {
                for (size_t j = 0; j < rhs.cols_; ++j) {
                    result[i][j] += data_[i][k] * rhs[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator*(T scalar) const {
        Matrix result = *this;
        for (auto &row : result.data_) {
            for (auto &val : row) {
                val *= scalar;
            }
        }
        return result;
    }

    Matrix transposed() const {
        Matrix result(cols_, rows_);
        for (size_t i = 0; i < cols_; ++i) {
            for (size_t j = 0; j < rows_; ++j) {
                result[i][j] = data_[j][i];
            }
        }
        return result;
    }

    // 高斯消元（返回行阶梯形式）
    Matrix gaussian_elimination() const {
        Matrix mat = *this;
        size_t pivot = 0;

        for (size_t col = 0; col < cols_ && pivot < rows_; ++col) {
            // 寻找主元
            size_t max_row = pivot;
            for (size_t i = pivot + 1; i < rows_; ++i) {
                if (std::abs(mat[i][col]) > std::abs(mat[max_row][col])) {
                    max_row = i;
                }
            }

            if (std::abs(mat[max_row][col]) < epsilon) continue;

            mat.swap_rows(pivot, max_row);

            // 归一化主元行
            T scalar = T(1) / mat[pivot][col];
            mat.scale_row(pivot, scalar);

            // 消去下方元素
            for (size_t i = pivot + 1; i < rows_; ++i) {
                T factor = mat[i][col];
                mat.add_scaled_row(i, pivot, -factor);
            }
            ++pivot;
        }
        return mat;
    }

    // 行列式计算
    T determinant() const {
        if (!is_square()) throw std::logic_error("Non-square matrix has no determinant");

        Matrix mat = *this;
        T det = 1;
        size_t sign = 1;

        for (size_t col = 0; col < cols_; ++col) {
            size_t max_row = col;
            for (size_t i = col + 1; i < rows_; ++i) {
                if (std::abs(mat[i][col]) > std::abs(mat[max_row][col])) {
                    max_row = i;
                }
            }

            if (max_row != col) {
                mat.swap_rows(col, max_row);
                sign *= -1;
            }

            if (std::abs(mat[col][col]) < epsilon) return 0;

            det *= mat[col][col];

            for (size_t i = col + 1; i < rows_; ++i) {
                T factor = mat[i][col] / mat[col][col];
                mat.add_scaled_row(i, col, -factor);
            }
        }
        return det * sign;
    }

    // 矩阵求逆
    Matrix inverse() const {
        if (!is_square()) throw std::logic_error("Non-square matrix cannot be inverted");

        size_t n = rows_;
        Matrix aug(n, 2 * n, T{0});

        // 构造增广矩阵 [A|I]
        for (size_t i = 0; i < n; ++i) {
            std::copy(data_[i].begin(), data_[i].end(), aug[i].begin());
            aug[i][n + i] = 1;
        }

        // 高斯-约旦消元
        for (size_t col = 0; col < n; ++col) {
            size_t pivot = col;

            // 寻找主元
            for (size_t i = col; i < n; ++i) {
                if (std::abs(aug[i][col]) > std::abs(aug[pivot][col])) {
                    pivot = i;
                }
            }

            if (std::abs(aug[pivot][col]) < epsilon)
                throw std::runtime_error("Matrix is singular");

            aug.swap_rows(col, pivot);

            // 归一化主元行
            T scalar = T(1) / aug[col][col];
            aug.scale_row(col, scalar);

            // 消去其他行
            for (size_t i = 0; i < n; ++i) {
                if (i != col && std::abs(aug[i][col]) > epsilon) {
                    T factor = aug[i][col];
                    aug.add_scaled_row(i, col, -factor);
                }
            }
        }

        // 提取逆矩阵
        Matrix inv(n, n);
        for (size_t i = 0; i < n; ++i) {
            std::copy(aug[i].begin() + n, aug[i].end(), inv[i].begin());
        }
        return inv;
    }

    // 流操作符
    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
        for (const auto &row : mat.data_) {
            for (const auto &val : row) {
                if constexpr (std::is_floating_point_v<T>) {
                    os << std::setw(10) << std::fixed << std::setprecision(4) << val;
                } else {
                    os << std::setw(10) << val;
                }
            }
            os << '\n';
        }
        return os;
    }
};

// 测试用例
int main() {
    try {
        Matrix<double> A = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        Matrix<double> B = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1}
        };

        // 基本运算
        std::cout << "A + B:\n" << A + B << "\n";
        std::cout << "A * B:\n" << A * B << "\n";
        std::cout << "A * 2.5:\n" << A * 2.5 << "\n";

        // 高斯消元
        std::cout << "Row echelon form of A:\n" << A.gaussian_elimination() << "\n";

        // 逆矩阵
        Matrix<double> C = {
            {1, 2, 3},
            {0, 1, 4},
            {5, 6, 0}
        };
        std::cout << "Inverse of C:\n" << C.inverse() << "\n";

        // 行列式
        std::cout << "Determinant of C: " << C.determinant() << "\n";

    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}