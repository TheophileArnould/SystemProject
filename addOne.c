#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(){
        int number;
        printf("entrez un nombre : ");
        scanf("%d", &number);
        printf("ton nombre est : %i\n",number+1);

    return 0;
}