#include <stdio.h>

int M[500][500];

int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", &M[i][j]);

    long long count = 0;
    for (int i = 0; i < R - 1; i++) {        // punta en fila i, colas en fila i+1
        for (int j = 1; j < C - 1; j++) {    // j-1 y j+1 deben existir
            if (M[i][j] == M[i+1][j-1] && M[i][j] == M[i+1][j+1])
                count++;
        }
    }
    printf("%lld\n", count);
}
