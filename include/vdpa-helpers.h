#ifndef __QEMU_VDPA_HELPER_H__
#define __QEMU_VDPA_HELPER_H__

#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static const char* VDPA_PATH="/home/jakob/iproute2/vdpa/vdpa";
extern char* VDPA_MGMTDEV_NAME;
const char* DEFAULT_VDPA_MGMTDEV_NAME = "vdpasim_net";

static int run_command(const char** command) {
    int ret = 0;
    int pid = fork();
    if (pid == 0) {
        return execvp(VDPA_PATH, (char**)command);
    } else if(pid > 0) {
        waitpid(pid, &ret, 0);
    }
    return ret;
}


static int vdpa_create(int id) {
    if (VDPA_MGMTDEV_NAME == NULL) {
    VDPA_MGMTDEV_NAME = (char*)DEFAULT_VDPA_MGMTDEV_NAME; 
   }
   char  name[6] = {'v', 'd', 'p', 'a', (char)('0' + id), 0};

   const char* command[8] = {VDPA_PATH, "dev", "add", "name", name, "mgmtdev", VDPA_MGMTDEV_NAME, NULL};

   run_command(command);
   return EXIT_SUCCESS;
}

static int vdpa_destroy(char* name) {
   const char* command[7] = {VDPA_PATH, "vdpa", "dev", "del", "name", name, NULL};

   run_command(command);
   
   return EXIT_SUCCESS;
}

#endif
