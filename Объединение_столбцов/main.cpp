#include <iostream>
#include <algorithm>

int** concat_rows(const int* const* lhs, size_t n1, size_t m1, const int* const* rhs, size_t n2, size_t m2) 
{
    size_t n = std::max(n1, n2), m = m1 + m2;
    int** res = new int*[n];
    for (size_t i = 0; i < n; ++i) 
    {
        res[i] = new int[m];
        for (size_t j = 0; j < m; ++j) 
        {
            if (j < m1) res[i][j] = (i < n1) ? lhs[i][j] : 0;
            else res[i][j] = (i < n2) ? rhs[i][j - m1] : 0;
        }
    }
    return res;
}

int read(int**& a, size_t& n, size_t& m) 
{
    if (!(std::cin >> n >> m)) return 1;
    try 
    {
        a = new int*[n];
        for (size_t i = 0; i < n; ++i) 
        {
            a[i] = new int[m];
            for (size_t j = 0; j < m; ++j) if (!(std::cin >> a[i][j])) return 1;
        }
    } catch (const std::bad_alloc&) { return 2; }
    return 0;
}

void free_mat(int** a, size_t n) 
{
    if (!a) return;
    for (size_t i = 0; i < n; ++i) delete[] a[i];
    delete[] a;
}

int main() {
    size_t n1, m1, n2, m2;
    int **a = nullptr, **b = nullptr, **c = nullptr;
    int e;
    
    if ((e = read(a, n1, m1))) return e;
    if ((e = read(b, n2, m2))) return e;
    
    try 
    {
        c = concat_rows(a, n1, m1, b, n2, m2);
    } catch (const std::bad_alloc&) { return 2; }
    
    size_t n = std::max(n1, n2), m = m1 + m2;
    for (size_t i = 0; i < n; ++i) 
    {
        for (size_t j = 0; j < m; ++j)
	{
 	   std::cout << c[i][j] << " ";
	}
        std::cout << "\n";
    }
    
    free_mat(a, n1);
    free_mat(b, n2); 
    free_mat(c, n);
    return 0;
}