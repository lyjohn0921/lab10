#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int usage();
int tempread(char *d, int v);
int main(int argc, char *argv[])
{
    char *device = "28-0118423e95ff";
    int verbose = 0;
    /* process the arguments */
    argc--;
    argv++;
    while (argc > 0)
    {
        printf("%d %s\n", argc, argv[0]);
        if (!strcmp("-v", argv[0]))
        {
            verbose = 1;
        }
        else if (!strcmp("-d", argv[0]))
        {
            argc--;
            argv++;
            if (argc == 0)
                usage();

            device = argv[0];
        }
        else
            usage();
        argc--;
        argv++;
    }
    tempread(device, verbose);
    exit(0);
}
int usage() {
    fprintf(stderr, "user not pass the correctcommand line arguments.\n");
    exit(1);
}

int tempread(char * d, int v){
    int fd;
    char *file;
    char buff[73];
    char *pre, *nm;
    char *t;
    int temp;
    int sign;
    pre = "/sys/bus/w1/devices/";
    nm = "/w1_slave";
    if ((file = malloc(strlen(pre) + strlen(d) + strlen(nm) + 1)) == NULL){
        usage();
    }
    sprintf(file, "%s%s%s", pre, d, nm);

    if((fd = open(file, O_RDONLY)) == -1){
        usage();
    }
    free(file);
	fprintf(stdout,"%d\n", fd);
    if(read(fd, buff, 74) < 0){
        usage();
    }
	buff[75]='\0';
    if (v == 1) {
        fprintf(stdout, "%s\n", buff);
    }
    if (strstr(buff, "YES") == NULL) {
        fprintf(stderr, "crc not work");
        exit(1);
    }
    else
    {
        t = strstr(buff, "t=");
        t += 2;
        if (*t == '-'){
            sign = -1;
		t++;
        }
        else
        {
            sign = 1;
        }
	temp = 0;
        while(*t >= '0' && *t <= '9'){
            temp = temp * 10 + (*t - '0');
            t++;
        }
        temp = sign * temp;
        fprintf(stdout, "%d\n", temp);
        return 0;
    }
    exit(1);
}


