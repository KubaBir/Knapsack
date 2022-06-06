#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct Item {
    int weight;
    int value;
};
typedef struct Item Item;

void dynamic(Item Items[], int n, int size) {
    const int rows = n + 1;
    const int cols = size + 1;
    int res[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || j == 0) {
                res[i][j] = 0;
                continue;
            }
            if (Items[i].weight > j) {
                res[i][j] = res[i - 1][j];
            } else {
                if (res[i - 1][j] >= res[i - 1][j - Items[i].weight] + Items[i].value)
                    res[i][j] = res[i - 1][j];
                else
                    res[i][j] = res[i - 1][j - Items[i].weight] + Items[i].value;
            }
        }
    }

    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         printf("%d ", res[i][j]);
    //         if (res[i][j] < 10) printf(" ");
    //     }
    //     printf("\n");
    // }

    int current = 1;
    int x = size, y = n;
    int res_weight = 0;
    printf("Optymalna kombinacja: ");
    while (res[y][x] != 0) {
        if (res[y][x] != res[y - 1][x]) {
            printf("%d ", y);
            x -= Items[y].weight;
            res_weight += Items[y].weight;
        }
        y--;
    }
    printf("\nWartosc: %d, Waga: %d\n", res[n][size], res_weight);
}

void dec_to_bin(int *res, int number, int size) {
    int i;
    size--;
    for (i = 0; number > 0; i++) {
        res[size--] = number % 2;
        number /= 2;
    }
}

void brute_force(Item Items[], int n, int size) {
    int comb[n];
    int max_value = 0, max_weight = 0;
    int res_comb[n];
    int cur_weight, cur_value;

    for (int i = 0; i <= pow(2, n) - 1; i++) {
        for (int j = 0; j < n; j++) {
            comb[j] = 0;
        }
        dec_to_bin(comb, i, n);

        cur_weight = 0;
        cur_value = 0;
        for (int j = 0; j < n; j++) {
            if (comb[j] == 1) {
                cur_weight += Items[j + 1].weight;
                if (cur_weight > size) break;
                cur_value += Items[j + 1].value;
            }
        }
        if (cur_weight <= size) {
            if (cur_value > max_value) {
                max_value = cur_value;
                max_weight = cur_weight;
                for (int o = 0; o < n; o++)
                    res_comb[o] = comb[o];
            }
        }

        // for (int j = 0; j < n; j++) {
        //     printf("%d ", comb[j]);
        // }
        // printf("%d %d", cur_value, cur_weight);
        // printf("\n");
    }
    printf("Optymalna kombinacja: ");
    for (int i = 0; i < n; i++) {
        if (res_comb[i] == 1) printf("%d ", i + 1);
    }
    printf("\nWartosc: %d, Waga: %d\n", max_value, max_weight);
}

int main() {
    const int N = 25, C = 30;
    FILE *dane = fopen("./dane2.txt", "w");
    srand(time(NULL));
    fprintf(dane, "%d\n", C);
    fprintf(dane, "%d\n", N);
    for (int i = 0; i < N; i++) {
        fprintf(dane, "%d %d\n", (rand() % 14) + 1, (rand() % 14) + 1);
    }
    fclose(dane);

    // FILE *fp = fopen("./dane.txt", "r");
    // int size;
    // fscanf(fp, " %d", &size);
    // int n;
    // fscanf(fp, " %d", &n);
    // struct Item Items[n + 1];
    // for (int i = 1; i < n + 1; i++) {
    //     fscanf(fp, "%d %d", &Items[i].value, &Items[i].weight);
    // }
    FILE *fp = fopen("./dane2.txt", "r");
    int size;
    fscanf(fp, " %d", &size);
    int n;
    fscanf(fp, " %d", &n);
    struct Item Items[n + 1];
    for (int i = 1; i < n + 1; i++) {
        fscanf(fp, "%d %d", &Items[i].value, &Items[i].weight);
    }
    fclose(fp);
    clock_t start = clock();
    dynamic(Items, n, size);
    brute_force(Items, n, size);
    // sleep(4);
    clock_t end = clock();
    printf("Time: %d", end - start);
}