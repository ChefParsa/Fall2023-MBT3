#include<iostream>                        
#include <fstream>
#include <random>

class Matrix
{
    private:
        int arr2x2[2][2];
        int arr3x3[3][3];
        int size;
    public:
        Matrix(int size, bool fill_with_zero);
        void print_matrix();
        static void operation_menu(int size);
        int random_number_generator();
        Matrix operator+(Matrix const& array);
        Matrix operator-(Matrix const& array);
        Matrix operator*(Matrix const& array);

};

Matrix::Matrix(int size, bool fill_with_zero = false) 
{
    int number;
    this->size = size;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (fill_with_zero)
                number = 0;
            else
                number = random_number_generator();
            if (size == 2)
                arr2x2[i][j] = number;
            else
                arr3x3[i][j] = number;
        }
}

void Matrix::print_matrix()
{
    std::cout << "printing matrix ...\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            if (size == 2)
                std::cout << arr2x2[i][j] << ' ';
            else
                std::cout << arr3x3[i][j] << ' ';
        std::cout << '\n';
    }
}

int Matrix::random_number_generator()
{
    // Create a random number generator engine
    std::random_device rd;            // Obtain a random number from hardware
    std::mt19937 engine(rd());         // Standard Mersenne Twister engine

    // Define a distribution
    std::uniform_int_distribution<int> distribution(1, 10); // Range from 1 to 10

    // Generate a random number
    int random_number = distribution(engine);

    // Return the random number
    return random_number;
}

Matrix Matrix::operator+(Matrix const& array)
{
    Matrix resault(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (size == 2)
                resault.arr2x2[i][j] = arr2x2[i][j] + array.arr2x2[i][j];
            else
                resault.arr3x3[i][j] = arr3x3[i][j] + array.arr3x3[i][j];
    return resault;
}

Matrix Matrix::operator-(Matrix const& array)
{
    Matrix resault(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (size == 2)
                resault.arr2x2[i][j] = arr2x2[i][j] - array.arr2x2[i][j];
            else
                resault.arr3x3[i][j] = arr3x3[i][j] - array.arr3x3[i][j];
    return resault;
}

Matrix Matrix::operator*(Matrix const& array)
{
    Matrix resault(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                if (size == 2)
                    resault.arr2x2[i][j] = arr2x2[i][k] - array.arr2x2[k][j];
                else
                    resault.arr3x3[i][j] = arr3x3[i][k] - array.arr3x3[k][j];
    return resault;
}

void Matrix::operation_menu(int size)
{
        Matrix array1(size);
        Matrix array2(size);
        Matrix resualt(size, true);
        bool resualt_use = false;
    while (true)
    {
        int choice;
        std::cout << "1. print matrix.\n";
        std::cout << "2. matrice addition\n";
        std::cout << "3. matrice subtraction\n";
        std::cout << "4. matrice multiplication\n";
        std::cout << "5. matrice inverse\n";
        std::cout << "6. matrice determinant\n";
        std::cout << "7. exit\n";
        std::cin >> choice;
        if (choice == 1)
        {
            while (true)
            {
                std::cout << "1. print matrice 1.\n";
                std::cout << "2. print matrice 2.\n";
                std::cout << "3. print resault matrice.\n";
                std::cout << "4. exit.\n";
                int choice;
                std::cin >> choice;
                if (choice == 1)
                    array1.print_matrix();
                else if (choice == 2)
                    array2.print_matrix();
                else if (choice == 3)
                    if (resualt_use)
                        resualt.print_matrix();
                    else
                        std::cout << "you dont use resault matrice, first of all make some operation.\n";
                else if (choice == 4)
                    break;
                else
                    break;
            }  
        }
        else if (choice == 2)
        {
            resualt = array1 + array2;
            resualt_use = true;
        }
        else if (choice == 3)
        {
            resualt = array1 - array2;
            resualt_use = true;
        }
        else if (choice == 4)
        {
            resualt = array1 * array2;
            resualt_use = true;
        }
        else if (choice == 7)
            break;
    }
    
}

void init_menu()
{
    while(true)
    {
        int choice;
        std::cout << "1. make 2 x 2 matrix.\n";
        std::cout << "2. make 3 x 3 matrix.\n";
        std::cout << "3. exit.\n";
        std::cin >> choice;
        if (choice == 1)
            Matrix::operation_menu(2);
        else if (choice == 2)
            Matrix::operation_menu(3);
        else if (choice == 3)
            break;
        else
            break;
    }
}

int main() 
{
    init_menu();
    return 0;
}