#include <stdio.h>

#define NMAX 20
#define MMAX ((NMAX)*(NMAX))

int N, M, k;

int map[NMAX][NMAX];

int direct[MMAX][4][4];

typedef struct
{
        int alive=1, which;
} Shark;

Shark shark[MMAX];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int ans = 0;

void solve(void)
{
        ans++;


int main(void)
{
        int i, j, k;
        scanf("%d %d %d", &N, &M, &k);

        for(i=0; i<N; i++)
                for(j=0; j<N; j++)
                        scanf("%d", &map[i][j]);

        for(i=0; i<M; i++)
                scanf("%d", &shark[i].which);
        for(i=0; i<M; i++)
                for(j=0; j<4; j++)
                        for(j=0; k<4; k++)
                                scanf("%d", &direct[i][j][k]);


        solve();
        printf("%d", ans);
        return 0;
}
