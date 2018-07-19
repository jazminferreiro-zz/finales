#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]){
	time_t     now;
    struct tm *t;
    char       buf[80];

    /* Obtener la hora actual */
    now = time(0);

    /* Formatear e imprimir el tiempo, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    t = localtime(&now);
    int year = 1900+ t->tm_year;
    int month = t->tm_mon +1;
    printf("%d/%d/%d %d:%d:%d\n", t->tm_mday, month, year ,t->tm_hour,t->tm_min, t->tm_sec);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S ", t);
    printf("%s\n", buf);
}				