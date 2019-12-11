#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int matrix_x, matrix_y, police_station, policemen[10], robber_x, robber_y;
    printf("enter the number of rows and columns:\n");
    scanf("%d %d", &matrix_x, &matrix_y);
    printf("enter the number of police stations and policemen for each one:\n");
    scanf("%d", &police_station);
    for (int i = 1; i <= police_station; i++) {
        scanf("%d", &policemen[i]);
    }
    int matrix[matrix_x][matrix_y];
    for (int i = 0; i < matrix_x; i++)
        for (int j = 0; j < matrix_y; ++j)
            matrix[i][j] = 0;

    srand(time(0));

    //random place of policemen at the beginning
    for (int i = 1; i <= police_station; i++)
        for (int j = 0; j < policemen[i]; j++) {
            int x, y;
            x = rand() % matrix_x;
            y = rand() % matrix_y;
            if (matrix[x][y] == 0)
                matrix[x][y] = i;
            else
                j--;
        }
    //random place of robber at the beginning
    while (1) {
        int x, y;
        x = rand() % matrix_x;
        y = rand() % matrix_y;
        if (matrix[x][y] == 0) {
            matrix[x][y] = -1;
            break;
        }

    }

    //displaying the matrix
    for (int i = 0; i < matrix_x; i++) {
        for (int j = 0; j < matrix_y; ++j) {
            if (matrix[i][j] == 0)
                printf(".  ");
            else if (matrix[i][j] > 0)
                printf("D%d ", matrix[i][j]);
            else
                printf("T  ");
        }
        printf("\n");
    }

    return 0;
}