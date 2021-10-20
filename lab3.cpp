#include "labs.h"

enum Direction {
    LEFT, RIGHT, UP, DOWN
};

void square_matrix(const int n, int **matrix) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            *(*(matrix + i) + j) *= *(*(matrix + i) + j);
}

void print_matrix(const int n, int **matrix) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << *(*(matrix + i) + j) << "\t";
        std::cout << std::endl;
    }
}

int lab3() {
    int n;
    std::cin >> n;
    int a[n][n];
    Direction direction = Direction::RIGHT;
    Direction previousDirection;
    for (int i = 1, l = n * n, x = 0, y = n - 1, xCorner = y, yCorner = y - 1; i <= l; ++i) {
        *(*(a + y) + x) = i;
        switch (direction) {
            case Direction::RIGHT:
                if (x != xCorner) {
                    ++x;
                } else {
                    previousDirection = direction;
                    direction = Direction::UP;
                    --xCorner;
                    --y;
                }
                break;
            case Direction::UP:
                if (previousDirection == Direction::RIGHT) {
                    if (y != 0)
                        --y;
                    else {
                        previousDirection = direction;
                        direction = Direction::LEFT;
                        --x;
                    }
                } else if (previousDirection == Direction::LEFT) {
                    previousDirection = direction;
                    direction = Direction::RIGHT;
                    --yCorner;
                    ++x;
                }
                break;
            case Direction::LEFT:
                if (previousDirection == Direction::UP) {
                    --xCorner;
                    previousDirection = direction;
                    direction = Direction::DOWN;
                    ++y;
                } else if (previousDirection == DOWN) {
                    if (x != 0)
                        --x;
                    else {
                        previousDirection = direction;
                        direction = Direction::UP;
                        --y;
                    }
                }
                break;
            case Direction::DOWN:
                if (y != yCorner)
                    ++y;
                else {
                    previousDirection = direction;
                    direction = Direction::LEFT;
                    --yCorner;
                    --x;
                }
                break;
        }
    }

//    Convert 2D array to pointer matrix
    int *matrix[n];
    for (int i = 0; i < n; ++i)
        *(matrix + i) = *(a + i);

    print_matrix(n, matrix);
    square_matrix(n, matrix);
    std::cout << std::string(1 << 6, '=') << std::endl;
    print_matrix(n, matrix);

    return 0;
}
