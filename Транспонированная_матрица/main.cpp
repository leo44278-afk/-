#include <iostream>

int main()
{
    int a = 0;
    int b = 0;
    int** mt ;
    std::cin >> a >> b;
    if (std::cin.fail())
    {
        return 1;
    }
    try
    {
        mt = new int*[a];
    }
    catch (std::bad_alloc& e)
    {
        std::cerr <<e.what() << std::endl;
        return 1;
    }
    for (int i = 0; i < a; i++)
    {
        try
        {
            mt[i] = new int[b];
        }
        catch (std::bad_alloc& e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }

        for (int j = 0; j < b; j++)
        {
            std::cin >> mt[i][j];
            if (std::cin.fail())
            {
                return 1;
            }
        }
    }
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a; j++)
        {
            std::cout << mt[j][i] << " ";
        }
        
        std::cout << std::endl;
    }
    for (int i = 0; i < a; ++i)
        delete[] mt[i];
    delete[] mt;
    return 0;
}