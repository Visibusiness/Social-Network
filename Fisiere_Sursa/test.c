#include <stdio.h>
#include <stdlib.h>

void print_x(int *x, int n)
{
    for(int i=0; i<n; i++)
        printf("%d ", x[i]);
     printf("\n");
}

void print_starts(int *x, int depth, int n)
{
    //printf("depth=%d:\n", depth);
    // for(int i=0;i<depth;i++)
    //     printf("\t");
    for(int i=0; i<depth; i++)
        printf("%d", x[i]);
    // for(int i=depth; i<n; i++)
    //     printf("*");
    printf("\n");
}

void backt(int *x, int *used, int depth, int n)
{
    print_starts(x, depth, n);
    if(depth >= n) {
        return;
    }
    int start = 0;
    if(depth)
        start = x[depth-1];
    for(int i=start; i<n; i++)
        if(used[i]==0) {
            used[i] = 1;
            x[depth] =  i+1;
            backt(x, used, depth+1, n);
            used[i] = 0;
        }
}

void print_submultimi(int *used, int n)
{
    for(int i=0; i<n; i++)
        if(used[i])
            printf("%d", i+1);
    printf("\n");
}

/*
void submultimi(int *used, int depth, int n)
{
    print_submultimi(used, depth);
    if(depth>=n)
        return;
    int start = 0;
    if(depth)
        start = ;
    for(int i=start; i<n; i++)
        if(used[i]==0) {
            used[i] = 1;
            submultimi(used, depth+1, n);
            used[i] = 0;
        }
}
*/

int main()
{
    int n = 4;
    int *x;
    x = calloc(n, sizeof(int));
    int *used = calloc(n, sizeof(int));
    backt(x, used, 0, n);
    free(x);
    free(used);

    // x = calloc(n, sizeof(int));
    // submultimi(x, 0, n);
    // free(x);
}   