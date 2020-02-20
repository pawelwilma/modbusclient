/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <pwilma@wp.pl> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.               Pawel
 * ----------------------------------------------------------------------------
 */

#include <modbus/modbus.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
        READ,
        WRITE
} mode_type;


void usage(const char* progName)
{
        fprintf(stderr, "Usage: %s host_ip port read|write reg_start reg_count [write_val1,write_val2...]\n", progName);
}

int toInt(const char* str, int* err)
{
        errno = 0;
        long val = strtol(str, NULL, 10);
        *err = errno;
        return (int) val;
}

int  getWriteValues(uint16_t* tab_reg, int num_regs, char **argv)
{

        char* token = NULL;
        char* savePtr = NULL;
        int err;
        int i = 0;
        do {
                if(i == num_regs)
                {
                        fprintf(stderr, "ERROR: too much values. Expected : %d\n", num_regs);
                        return -1;
                }
                token = strtok_r(argv[5], ",", &savePtr);
                tab_reg[i] = toInt(token, &err);
                if(err) {
                        fprintf(stderr, "ERROR: parsing value failed: %s\n", token);
                        return -1;
                }
                i++;
        } while(token != NULL);

        if(i < num_regs) {
                fprintf(stderr, "ERROR: not enough values. Expected %d, got %d\n", num_regs, i);
                return -1;
        }
        return 0;
}

int parseArgs(int argc, char** argv, char** host_ip, int* port, mode_type* mode, int* start, int* num_regs)
{
        int err = 0;
        // Num args
        if(argc < 5)
        {
                fprintf(stderr, "ERROR: incorrect argument numbers\n");
                return -1;
        }
        // Host IP address
        *host_ip = argv[1];
        // TCP port
        *port = toInt(argv[2], &err);
        if(err) {
                fprintf(stderr, "ERROR: error parsing TCP port\n");
                return err;
        }
        // Mode - READ/WRITE
        if(!strcmp(argv[3], "read")) {
                *mode = READ;
        } else if(!strcmp(argv[3], "write")) {
                *mode = WRITE;
        } else {
                fprintf(stderr, "ERROR: incorect mode: %s allowed values are \"read\" or \"write\"\n", argv[3]);
                return -1;
        }
        // Start register address
        *start = toInt(argv[4], &err);
        if(err) {
                fprintf(stderr, "ERROR: error parsing start register address: %s\n", argv[4]);
                return err;
        }
        // Number of registers to read/write
        *num_regs = toInt(argv[4], &err);
        if(err) {
                fprintf(stderr, "ERROR: error parsing number of registers to %s: %s\n", (*mode == READ ? "read": "write"), argv[4]);
                return err;
        }

        if(*mode == WRITE && argc<6)
        {
                fprintf(stderr, "ERROR: missing write values\n");
                return -1;
        }

        return 0;
}


int main(int argc, char** argv)
{

        modbus_t *ctx = NULL;
        uint16_t* tab_reg = NULL;
        int rc = 0;
        int i = 0;
        int start = 0;
        int num_regs = 0;
        char* host_ip;
        int port = 1502;
        mode_type mode = READ;

        rc = parseArgs(argc, argv, &host_ip, &port, &mode, &start, &num_regs);
        if(rc != 0)
        {
                usage(argv[0]);
                rc = -1;
                goto ErrorHandler;
        }
        // Allocate memory
        tab_reg = (uint16_t*)malloc(sizeof(uint16_t) * num_regs);
        if(tab_reg == NULL){
                fprintf(stderr, "ERROR: cannot allocate memory for %d registers\n", num_regs);
                rc = -1;
                goto ErrorHandler;
        }

        if(mode == WRITE)
        {
                rc = getWriteValues(tab_reg, num_regs, argv);
                if(rc != 0) {
                        goto ErrorHandler;
                }

        }

        ctx = modbus_new_tcp(host_ip, port);
        if (modbus_connect(ctx) == -1) {
                fprintf(stderr, "ERROR: Connection failed: %s\n", modbus_strerror(errno));
                modbus_free(ctx);
                rc =  -1;
                goto ErrorHandler;
        }

        if(mode == READ) {
                rc = modbus_read_registers(ctx, start, num_regs, tab_reg);
        } else {
                rc = modbus_write_registers(ctx, start, num_regs, tab_reg);
        }
        if (rc != 0) {
                fprintf(stderr, "ERROR: %s\n", modbus_strerror(errno));
                rc = -1;
                goto ErrorHandler;
        }

        if(mode == READ) {
                for (i=0; i < rc; i++) {
                        printf("[%x] = 0x%X (%d)\n", start + i, tab_reg[i], tab_reg[i]);
                }
        }
ErrorHandler:
        modbus_close(ctx);
        modbus_free(ctx);
        free(tab_reg);
        return rc;
}

