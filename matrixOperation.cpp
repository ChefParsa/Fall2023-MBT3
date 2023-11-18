#include<iostream>                        
#include <fstream>
#include <random>
#include <string>

class Matrix
{
    private:
        float arr2x2[2][2];
        float arr3x3[3][3];
        int size;
        float determinant;
        bool zero_determinant = false;
    public:
        Matrix(int size, bool fill_with_zero, bool fill_with_one, bool eye_matrice);
        void print_matrix();
        static void print_const_matrix(std::string option[], bool zero_arr, bool one_arr, bool eye_arr);
        static void operation_menu(int size);
        bool deterninant_status();
        int random_number_generator();
        Matrix operator+(Matrix const& array);
        Matrix operator-(Matrix const& array);
        Matrix operator*(Matrix const& array);
        Matrix inverse_matrix(int size);
        static void swap(float *num1, float *num2);

};

Matrix::Matrix(int size, bool fill_with_zero = false, bool fill_with_one = false, bool eye_matrice = false) 
{
    int number;
    this->size = size;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (fill_with_zero)
                number = 0;
            else if (fill_with_one)
                number = 1;
            else if (eye_matrice)
                if (i == j)
                    number = 1;
                else
                    number = 0;
            else
                number = random_number_generator();
            if (size == 2)
                arr2x2[i][j] = number;
            else
                arr3x3[i][j] = number;
        }
    if (size == 2)
        determinant = (arr2x2[0][0] * arr2x2[1][1]) - (arr2x2[0][1] * arr2x2[1][0]);
    else 
        determinant = arr3x3[0][0] * ((arr3x3[1][1] * arr3x3[2][2]) - (arr3x3[2][1] * arr3x3[1][2])) -
                        arr3x3[0][1] * ((arr3x3[1][0] * arr3x3[2][2]) - (arr3x3[2][0] * arr3x3[1][2])) +
                        arr3x3[0][2] * ((arr3x3[1][0] * arr3x3[2][1]) - (arr3x3[2][0] * arr3x3[1][1]));
    if (determinant == 0)
        zero_determinant = true;
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

bool Matrix::deterninant_status()
{
    return zero_determinant;
}

void Matrix::print_const_matrix(std::string option[], bool zero_arr = false, bool one_arr = false, bool eye_arr = false)
{
    while (true)
    {
        int choice;
        bool make_zero_matrice = false;
        for (int i = 0; i < 3; i++)
            std::cout << option[i];
        std::cin >> choice;
        if (zero_arr)
        {
            if (choice == 1)
            {
                Matrix zero_matrice(2, true);
                zero_matrice.print_matrix();
            }
            else if (choice == 2)
            {
                Matrix zero_matrice(3, true);
                zero_matrice.print_matrix();
            }    
            else if (choice == 3)
                break;
            else
                break;
        }
        else if (one_arr)
        {
            if (choice == 1)
            {
                Matrix one_matrice(2, false, true);
                one_matrice.print_matrix();
            }
            else if (choice == 2)
            {
                Matrix one_matrice(3, false, true);
                one_matrice.print_matrix();
            }    
            else if (choice == 3)
                break;
            else
                break;
        }
        else if (eye_arr)
        {
            if (choice == 1)
            {
                Matrix eye_matrice(2, false, false,true);
                eye_matrice.print_matrix();
            }
            else if (choice == 2)
            {
                Matrix eye_matrice(3, false, false, true);
                eye_matrice.print_matrix();
            }    
            else if (choice == 3)
                break;
            else
                break;
        }
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

void Matrix::swap(float *num1, float *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

Matrix Matrix::operator+(Matrix const& array)
{
    Matrix resault(size, true);
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
    Matrix resault(size, true);
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
    Matrix resault(size, true);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                if (size == 2)
                    resault.arr2x2[i][j] = arr2x2[i][k] - array.arr2x2[k][j];
                else
                    resault.arr3x3[i][j] = arr3x3[i][k] - array.arr3x3[k][j];
    return resault;
}

Matrix Matrix::inverse_matrix(int size)
{
    float invDet = 1.0 / determinant; 
    if (size == 2)
    {
        Matrix temp(2, true);
        swap(&arr2x2[0][0], &arr2x2[1][1]);
        arr2x2[1][0] *= -1;
        arr2x2[0][1] *= -1;
        
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                temp.arr2x2[i][j] = arr2x2[i][j] * invDet;
        return temp;
    }
    else
    {
        Matrix temp(3, true);
        temp.arr3x3[0][0] = (arr3x3[1][1] * arr3x3[2][2] - arr3x3[2][1] * arr3x3[1][2]) * invDet;
        temp.arr3x3[0][1] = (arr3x3[0][2] * arr3x3[2][1] - arr3x3[0][1] * arr3x3[2][2]) * invDet;
        temp.arr3x3[0][2] = (arr3x3[0][1] * arr3x3[1][2] - arr3x3[0][2] * arr3x3[1][1]) * invDet;
        temp.arr3x3[1][0] = (arr3x3[1][2] * arr3x3[2][0] - arr3x3[1][0] * arr3x3[2][2]) * invDet;
        temp.arr3x3[1][1] = (arr3x3[0][0] * arr3x3[2][2] - arr3x3[0][2] * arr3x3[2][0]) * invDet;
        temp.arr3x3[1][2] = (arr3x3[1][0] * arr3x3[0][2] - arr3x3[0][0] * arr3x3[1][2]) * invDet;
        temp.arr3x3[2][0] = (arr3x3[1][0] * arr3x3[2][1] - arr3x3[2][0] * arr3x3[1][1]) * invDet;
        temp.arr3x3[2][1] = (arr3x3[2][0] * arr3x3[0][1] - arr3x3[0][0] * arr3x3[2][1]) * invDet;
        temp.arr3x3[2][2] = (arr3x3[0][0] * arr3x3[1][1] - arr3x3[1][0] * arr3x3[0][1]) * invDet;
        return temp;
    }
}

void Matrix::operation_menu(int size)
{
        Matrix matrix1(size);
        Matrix matrix2(size);
        Matrix result(size, true);
        bool use_result = false;
    while (true)
    {
        int choice;
        std::cout << "1. print matrix.\n";
        std::cout << "2. matrice addition\n";
        std::cout << "3. matrice subtraction\n";
        std::cout << "4. matrice multiplication\n";
        std::cout << "5. matrice inverse\n";
        std::cout << "6. exit\n";
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
                    matrix1.print_matrix();
                else if (choice == 2)
                    matrix2.print_matrix();
                else if (choice == 3)
                    if (use_result)
                        result.print_matrix();
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
            result = matrix1 + matrix2;
            use_result = true;
        }
        else if (choice == 3)
        {
            result = matrix1 - matrix2;
            use_result = true;
        }
        else if (choice == 4)
        {
            result = matrix1 * matrix2;
            use_result = true;
        }
        else if (choice ==5)
        {
            Matrix invMatrix(size, true);
            while (true)
            {
                std::cout << "1. inverse matrice 1.\n";
                std::cout << "2. inverse matrice 2.\n";
                std::cout << "3. inverse result matrice.\n";
                std::cout << "4. exit.\n";
                int choice;
                std::cin >> choice;
                if (choice == 1)
                {
                    if (matrix1.deterninant_status())
                    {
                        std::cout << "matrix 1 is not invertible.\n";
                        continue;
                    }
                    invMatrix = matrix1.inverse_matrix(size);
                    invMatrix.print_matrix();
                }
                else if (choice == 2)
                {
                    if (matrix2.deterninant_status())
                    {
                        std::cout << "matrix 2 is not invertible.\n";
                        continue;
                    }
                    invMatrix = matrix2.inverse_matrix(size);
                    invMatrix.print_matrix();
                }
                else if (choice == 3)
                    if (use_result)
                    {
                        if (matrix2.deterninant_status())
                        {
                            std::cout << "result matrix is not invertible.\n";
                            continue;
                        }
                        invMatrix = result.inverse_matrix(size);
                        invMatrix.print_matrix();
                    }
                    else
                        std::cout << "you dont use resault matrice, first of all make some operation.\n";
                else if (choice == 4)
                    break;
                else
                    break;
            }
        }
        else if (choice == 6)
            break;
        else
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
        std::cout << "3. print matrix fill with zeros\n";
        std::cout << "4. print matrix fill with ones\n";
        std::cout << "5. print eye matrix\n";
        std::cout << "6. exit.\n";
        std::cin >> choice;
        if (choice == 1)
            Matrix::operation_menu(2);
        else if (choice == 2)
            Matrix::operation_menu(3);
        else if (choice == 3)
        {
            std::string option[] = {"1. make 2 x 2 matrix fill with zeros.\n", "2. make 3 x 3 matrix fill with zeros.\n", "3. exit.\n"};
            Matrix::print_const_matrix(option, true);
        }   
        else if (choice == 4)
        {
            std::string option[] = {"1. make 2 x 2 matrix fill with ones.\n", "2. make 3 x 3 matrix fill with ones.\n", "3. exit.\n"};
            Matrix::print_const_matrix(option, false, true);
        }
        else if (choice == 5)
        {
            std::string option[] = {"1. make 2 x 2 eye matrix.\n", "2. make 3 x 3 eye matrix.\n", "3. exit.\n"};
            Matrix::print_const_matrix(option, false, false,true);
        }
        else if (choice == 6)
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