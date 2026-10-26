#include <iostream>
#include <algorithm>
#include <new>

void free_mat(int** a, size_t n) {
    if (!a) return;
    for (size_t i = 0; i < n; ++i) delete[] a[i];
    delete[] a;
}

// Возвращает указатель на матрицу, e = 1 (ошибка ввода) или 2 (ошибка памяти)
int** read(size_t n, size_t m, int& e) {
    if (n == 0 || m == 0) { e = 1; return nullptr; }
    e = 0;
    int** a = nullptr;
    try {
        a = new int*[n];
        for (size_t i = 0; i < n; ++i) a[i] = nullptr; // Чтобы free_mat не упал при сбое
        for (size_t i = 0; i < n; ++i) {
            a[i] = new int[m];
            for (size_t j = 0; j < m; ++j) {
                if (!(std::cin >> a[i][j])) { 
                    free_mat(a, n); 
                    e = 1; 
                    return nullptr; 
                }
            }
        }
    } catch (const std::bad_alloc&) { 
        free_mat(a, n); 
        e = 2; 
        return nullptr; 
    }
    return a;
}

int** concat_rows(const int* const* lhs, size_t n1, size_t m1, const int* const* rhs, size_t n2, size_t m2) {
    size_t n = std::max(n1, n2), m = m1 + m2;
    int** res = nullptr;
    try {
        res = new int*[n];
        for (size_t i = 0; i < n; ++i) res[i] = nullptr;
        for (size_t i = 0; i < n; ++i) {
            res[i] = new int[m];
            for (size_t j = 0; j < m; ++j) {
                if (j < m1) res[i][j] = (i < n1) ? lhs[i][j] : 0;
                else res[i][j] = (i < n2) ? rhs[i][j - m1] : 0;
            }
        }
    } catch (const std::bad_alloc&) { 
        free_mat(res, n); 
        return nullptr; 
    }
    return res;
}

int main() {
    size_t n1, m1, n2, m2;
    int e = 0;

    if (!(std::cin >> n1 >> m1)) return 1;
    int** a = read(n1, m1, e);
    if (e) return e;

    if (!(std::cin >> n2 >> m2)) { free_mat(a, n1); return 1; }
    int** b = read(n2, m2, e);
    if (e) { free_mat(a, n1); return e; }

    int** c = concat_rows(a, n1, m1, b, n2, m2);
    if (!c) { free_mat(a, n1); free_mat(b, n2); return 2; }

    size_t n = std::max(n1, n2), m = m1 + m2;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) std::cout << c[i][j] << " ";
        std::cout << "\n";
    }

    free_mat(a, n1); free_mat(b, n2); free_mat(c, n);
    return 0;
}
