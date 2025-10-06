// Copyright 2024 Julia Zabytia
//#define EASY_EXAMPLE
//#define CIRCLES_AND_SPHERES

#define MATRIX
#ifdef EASY_EXAMPLE
#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif
#ifdef CIRCLES_AND_SPHERES
#include <iostream>
#include <cmath>
#include "../lib_sphere/sphere.h"
#include "../lib_circle/circle.h"
#include "../lib_point/point.h"
#include "../lib_point3d/point3d.h"
enum result_of_compare
{
    Equal,
    Intersecting,
    NotIntersecting,
    FirstTouchSecond,
    OneInsideOther,
    OneInsideOtherTouching
};
result_of_compare Compare(int d, int r1, int r2, int sum, int diff) {
    if (d == 0 && r1 == r2) {
        return Equal;
    }
    if (d > sum) {
        return NotIntersecting;
    }
    if (d == sum) {
        return FirstTouchSecond;
    }
    if (d > diff && d < sum) {
        return Intersecting;
    }
    if (d == diff && d > 0) {
        return OneInsideOtherTouching;
    }
    if (d < diff) {
        return OneInsideOther;
    }
    return result_of_compare::NotIntersecting;
}
result_of_compare CompareCircles(const Circle& circle1, const Circle& circle2) {
    int d = circle1.getDistanceTo(circle2);
    int r1 = circle1.getR();
    int r2 = circle2.getR();
    int sum = r1 + r2;
    int diff = std::abs(r1 - r2);
    return Compare(d, r1, r2, sum, diff);
}
result_of_compare CompareSpheres(const Sphere& sphere1, const Sphere& sphere2) {
    int d = sphere1.getDistanceTo(sphere2);
    int r1 = sphere1.getR();
    int r2 = sphere2.getR();
    int sum = r1 + r2;
    int diff = std::abs(r1 - r2);
    return Compare(d, r1, r2, sum, diff);
}
int main() {

    Point center1(0, 0);
    Circle circle1(center1, 5);
    Point center2(6, 0);
    Circle circle2(center2, 4);
    result_of_compare circle_result = CompareCircles(circle1, circle2);

    switch (circle_result) {
    case Equal:
        std::cout << "Circles is equal\n";
        break;
    case Intersecting:
        std::cout << "Circles is intersecting\n";
        break;
    case NotIntersecting:
        std::cout << "Circles is not intersecting\n";
        break;
    case FirstTouchSecond:
        std::cout << "First circle touch second circle\n";
        break;
    case OneInsideOther:
        std::cout << "One circle inside other circle\n";
        break;
    case OneInsideOtherTouching:
        std::cout << "One circle inside other circle (with touching)\n";
        break;
    default:
        std::cout << "Unknown result\n";
        break;
    }
    return 0;
}
#endif
#ifdef MATRIX
#include <iostream>
#include "../lib_math_vector/math_vector.h"
#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/triangle_matrix.h"

void printMainMenu() {
    std::cout << "==========================================\n";
    std::cout << "|     CALCULATOR FOR VARIOUS MATRICES     |\n";
    std::cout << "|       (REGULAR AND TRIANGULAR)          |\n";
    std::cout << "==========================================\n";
    std::cout << "\n";
    std::cout << "MAIN MENU =====\n";
    std::cout << " 1. Matrix addition\n";
    std::cout << " 2. Matrix subtraction\n";
    std::cout << " 3. Matrix multiplication\n";
    std::cout << " 4. Add scalar to matrix\n";
    std::cout << " 5. Subtract scalar from matrix\n";
    std::cout << " 6. Multiply matrix by scalar\n";
    std::cout << " 7. Division by scalar\n";
    std::cout << " 8. Multiply matrix by vector\n";
    std::cout << " 9. Exit\n";
}

template<typename T>
void fillMatrix(Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.getM(); ++i) {
        for (size_t j = 0; j < matrix.getN(); ++j) {
            T value;
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> value;
            matrix[i][j] = value;
        }
    }
}

template<typename T>
void fillTriangleMatrix(TriangleMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.getSize(); ++i) {
        for (size_t j = i; j < matrix.getSize(); ++j) {
            T value;
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> value;
            matrix[i][j] = value;
        }
    }
}

template<typename T>
void fillVector(MathVector<T>& vector) {
    for (size_t i = 0; i < vector.get_size(); ++i) {
        T value;
        std::cout << "Element [" << i << "]: ";
        std::cin >> value;
        vector[i] = value;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int user_choice;

    do {
        printMainMenu();
        std::cout << "Your choice: ";
        std::cin >> user_choice;

        if (user_choice == 9) {
            break;
        }

        int matrix_type;
        std::cout << "Choose matrix type:\n";
        std::cout << "1. Regular matrix\n";
        std::cout << "2. Triangular matrix\n";
        std::cin >> matrix_type;

        if (matrix_type == 1) {
            // Regular Matrix operations
            size_t M, N;
            std::cout << "Enter dimensions of matrix 1 (M - rows, N - columns)\n";
            std::cout << "M = ";
            std::cin >> M;
            std::cout << "N = ";
            std::cin >> N;

            Matrix<int> matrix1(M, N);
            std::cout << "Enter elements of matrix 1:\n";
            fillMatrix(matrix1);

            switch (user_choice) {
            case 1: {
                std::cout << "Enter dimensions of matrix 2 (must be " << M << " x " << N << ")\n";
                Matrix<int> matrix2(M, N);
                std::cout << "Enter elements of matrix 2:\n";
                fillMatrix(matrix2);
                Matrix<int> result = matrix1 + matrix2;
                std::cout << "Result:\n" << result;
                break;
            }
            case 2: {
                std::cout << "Enter dimensions of matrix 2 (must be " << M << " x " << N << ")\n";
                Matrix<int> matrix2(M, N);
                std::cout << "Enter elements of matrix 2:\n";
                fillMatrix(matrix2);
                Matrix<int> result = matrix1 - matrix2;
                std::cout << "Result:\n" << result;
                break;
            }
            case 3: {
                size_t K;
                std::cout << "Enter number of columns for matrix 2 (must be " << N << " rows)\n";
                std::cout << "K = ";
                std::cin >> K;
                Matrix<int> matrix2(N, K);
                std::cout << "Enter elements of matrix 2:\n";
                fillMatrix(matrix2);
                Matrix<int> result = matrix1 * matrix2;
                std::cout << "Result:\n" << result;
                break;
            }
            case 4: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                Matrix<int> result = matrix1 + scalar;
                std::cout << "Result:\n" << result;
                break;
            }
            case 5: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                Matrix<int> result = matrix1 - scalar;
                std::cout << "Result:\n" << result;
                break;
            }
            case 6: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                Matrix<int> result = matrix1 * scalar;
                std::cout << "Result:\n" << result;
                break;
            }
            case 7: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                try {
                    Matrix<int> result = matrix1 / scalar;
                    std::cout << "Result:\n" << result;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 8: {
                size_t size;
                std::cout << "Enter vector size (must be " << N << "): ";
                std::cin >> size;
                if (size != N) {
                    std::cout << "Error: Vector size must match matrix columns!\n";
                    break;
                }
                MathVector<int> mathvector(size);
                std::cout << "Enter vector elements:\n";
                fillVector(mathvector);
                try {
                    MathVector<int> result = matrix1 * mathvector;
                    std::cout << "Result:\n" << result;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            default: {
                std::cout << "Invalid input! Please try again\n";
                break;
            }
            }
        }
        else if (matrix_type == 2) {
            // Triangular Matrix operations
            size_t size;
            std::cout << "Enter size of triangular matrix: ";
            std::cin >> size;

            TriangleMatrix<int> matrix1(size);
            std::cout << "Enter elements of triangular matrix (only upper triangle):\n";
            fillTriangleMatrix(matrix1);

            switch (user_choice) {
            case 1: {
                TriangleMatrix<int> matrix2(size);
                std::cout << "Enter elements of second triangular matrix:\n";
                fillTriangleMatrix(matrix2);
                try {
                    TriangleMatrix<int> result = matrix1 + matrix2;
                    std::cout << "Result:\n" << result;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                TriangleMatrix<int> matrix2(size);
                std::cout << "Enter elements of second triangular matrix:\n";
                fillTriangleMatrix(matrix2);
                try {
                    TriangleMatrix<int> result = matrix1 - matrix2;
                    std::cout << "Result:\n" << result;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "Matrix multiplication for triangular matrices not implemented in this example\n";
                break;
            }
            case 4: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                TriangleMatrix<int> result = matrix1 + scalar;
                std::cout << "Result:\n" << result;
                break;
            }
            case 5: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                TriangleMatrix<int> result = matrix1 - scalar;
                std::cout << "Result:\n" << result;
                break;
            }
            case 6: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                TriangleMatrix<int> result = matrix1 * scalar;
                std::cout << "Result:\n" << result;
                break;
            }
            case 7: {
                int scalar;
                std::cout << "Enter scalar: ";
                std::cin >> scalar;
                try {
                    TriangleMatrix<int> result = matrix1 / scalar;
                    std::cout << "Result:\n" << result;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 8: {
                MathVector<int> mathvector(size);
                std::cout << "Enter vector elements:\n";
                fillVector(mathvector);
                try {
                    MathVector<int> result = matrix1 * mathvector;
                    std::cout << "Result:\n" << result;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            default: {
                std::cout << "Invalid input! Please try again\n";
                break;
                }
            }
        }
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        system("cls");

    } while (true);
    return 0;
}
#endif
