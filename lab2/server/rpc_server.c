#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "rpc_transfer.h"

int* open_rpc_1_svc(filename* argp, struct svc_req* rqstp)
{
        static int result;

        /*
         * insert server code here
         */
        printf("Proc ID: %d\n", getpid());
        printf("[DEBUG] open file: %s\n", argp->filename_val);
        result = open(argp->filename_val, O_RDONLY, 0666);

        return &result;
}

void* close_rpc_1_svc(int* argp, struct svc_req* rqstp)
{
        static char* result;

        /*
         * insert server code here
         */
        printf("Proc ID: %d\n", getpid());
        close(*argp);

        return (void*)&result;
}

data* read_rpc_1_svc(int* argp, struct svc_req* rqstp)
{
        static data result;
        static char buffer[500];

        /*
         * insert server code here
         */
        result.data_val = buffer;

        memset(buffer, 0, sizeof(buffer));

        printf("Proc ID: %d\n", getpid());
        printf("Server debug: %d\n", *argp);
        result.data_len = read(*argp, result.data_val, 500);
        printf("Resp of read: %d\n", result.data_len);
        //printf("Data [%d]: %s\n", result.data_len, result.data_val);

        return &result;
}
