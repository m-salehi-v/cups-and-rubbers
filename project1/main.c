#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


int matrix_x , matrix_y , police_station, policemen[10];
int matrix[50][50];

void rand_movement(int *x, int *y);

void targeted_movement(int *police_x, int *police_y, int dst_x, int dst_y);

void display_matrix();

void find_robber(int *x, int *y);

void spotting_robber(int robber_x, int robber_y, int informed_stations[]);

int main() {

    int robber_x, robber_y, informed_stations[15] = {0};

    printf("enter the number of rows and columns:\n");
    scanf("%d %d", &matrix_x, &matrix_y);
    printf("enter the number of police stations and policemen for each one:\n");
    scanf("%d", &police_station);
    for (int i = 1; i <= police_station; i++) {
        scanf("%d", &policemen[i]);
    }

    //matrix initialization to 0
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
    display_matrix();
    printf("\n\n");


    /*just checking targeted_movement
    int k = 1;
    while (k < 200) {
        for (int i = 0; i < matrix_x; ++i) {
            for (int j = 0; j < matrix_y; ++j) {
                if (matrix[i][j] > 0) {
                    find_robber(&robber_x, &robber_y);
                    targeted_movement(&i, &j, robber_x, robber_y);
                }
            }
        }
        display_matrix();
        printf("\n\n");
        sleep(2);

    k++;
    }
*/


    return 0;
}

void rand_movement(int *x, int *y) {
    int tmp = matrix[*x][*y], k;
    matrix[*x][*y] = 0;
    while (1) {
        k = (rand() % 3) - 1;
        *x += k;
        *y += k;
        if ((*x >= 0) && (*x < matrix_x) && (*y >= 0) && (*y < matrix_y) && (matrix[*x][*y] == 0)) {
            matrix[*x][*y] = tmp;
            break;
        }
        *x -= k;
        *y -= k;
    }


}

void display_matrix() {
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
}

void targeted_movement(int *police_x, int *police_y, int dst_x, int dst_y) {
    int tmp = matrix[*police_x][*police_y];
    matrix[*police_x][*police_y] = 0;
    if (*police_x > dst_x && *police_y > dst_y) { //4
        if (matrix[*police_x - 1][*police_y - 1] <= 0) {
            (*police_x)--;
            (*police_y)--;
        } else if (matrix[*police_x][*police_y - 1] <= 0)
            (*police_y)--;
        else if (matrix[*police_x - 1][*police_y] <= 0)
            (*police_x)--;
        else;
    } else if (*police_x < dst_x && *police_y > dst_y) { //1
        if (matrix[*police_x + 1][*police_y - 1] <= 0) {
            (*police_x)++;
            (*police_y)--;
        } else if (matrix[*police_x + 1][*police_y] <= 0)
            (*police_x)++;
        else if (matrix[*police_x][*police_y - 1] <= 0)
            (*police_y)--;
        else;
    } else if (*police_x < dst_x && *police_y < dst_y) { //2
        if (matrix[*police_x + 1][*police_y + 1] <= 0) {
            (*police_x)++;
            (*police_y)++;
        } else if (matrix[*police_x][*police_y + 1] <= 0)
            (*police_y)++;
        else if (matrix[*police_x + 1][*police_y] <= 0)
            (*police_x)++;
        else;
    } else if (*police_x > dst_x && *police_y < dst_y) { //3
        if (matrix[*police_x - 1][*police_y + 1] <= 0) {
            (*police_x)--;
            (*police_y)++;
        } else if (matrix[*police_x][*police_y + 1] <= 0)
            (*police_y)++;
        else if (matrix[*police_x - 1][*police_y] <= 0)
            (*police_x)--;
        else;
    } else if (*police_x == dst_x && *police_y < dst_y) {
        if (matrix[*police_x][*police_y + 1] <= 0)
            (*police_y)++;
    } else if (*police_x == dst_x && *police_y > dst_y) {
        if (matrix[*police_x][*police_y - 1] <= 0)
            (*police_y)--;
    } else if (*police_y == dst_y && *police_x > dst_x) {
        if (matrix[*police_x - 1][*police_y] <= 0)
            (*police_x)--;
    } else if (*police_y == dst_y && *police_x < dst_x) {
        if (matrix[*police_x + 1][*police_y] <= 0)
            (*police_x)++;
    } else;
    matrix[*police_x][*police_y] = tmp;

}

void find_robber(int *x, int *y) {
    for (int i = 0; i < matrix_x; ++i) {
        for (int j = 0; j < matrix_y; ++j) {
            if (matrix[i][j] == -1) {
                *x = i;
                *y = j;
                break;
            }
        }
    }
}

void spotting_robber(int robber_x, int robber_y, int informed_stations[]){
    int k = 0;
    for (int i = fmax(robber_x - 2, 0); i <= fmin(robber_x + 2, matrix_x - 1); ++i) {
        for (int j = fmax(robber_y - 2, 0); j <= fmin(robber_y + 2, matrix_y - 1); ++j) {
            if (matrix[i][j] > 0) {
                informed_stations[k] = matrix[i][j];
                k++;
            }
        }
    }


}