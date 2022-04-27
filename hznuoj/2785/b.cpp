#include <stdio.h>
#include <string.h>
int main() {
    int a, b, m, n, i, j, flag, x, f = 5, m3;
    char m1[1100], m2[1100];
    scanf("%d", &n);

    while (n--) {
        j = 0;
        i = 0;
        flag = 1;
        scanf("%s %s", m1, m2);

        m = strlen(m1);
        m3 = strlen(m2);

        f = 5;
        while (j <= m - 1) {
            if (m1[j] != m2[i] && !(m2[i] >= '1' && m2[i] <= '9')) {
                flag = 0;
            }
            if (m2[i] >= '1' && m2[i] <= '9') {
                j = j + m2[i] - '0';
                i = i + 1;
                if (f == 1) {
                    flag = 0;
                }
                f = 1;
                if (j > m) {
                    flag = 0;
                }
            } else {
                j += 1;
                i += 1;
                f = 2;
            }
        }
        /*	if(j>m&&f==1)
                        {
                                flag=0;
                        }  */
        if (i != m3) {
            flag = 0;
        }
        if (flag == 1) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
}
