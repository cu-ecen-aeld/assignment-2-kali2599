#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <syslog.h>

void print_usage_and_exit() {
    fprintf(stderr, "Usage: ./program <writefile> <writestr>\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    // Open connection to syslog
    openlog("WRITER", LOG_PERROR | LOG_PID, LOG_USER);

    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        syslog(LOG_ERR, "Incorrect number of arguments.");
        print_usage_and_exit();
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Extract the parent directory from the file path
    char *last_slash = strrchr(writefile, '/');
    if (last_slash == NULL) {
        fprintf(stderr, "Invalid file path: %s\n", writefile);
        syslog(LOG_ERR, "Invalid file path: %s", writefile);
        exit(1);
    }

    size_t dir_len = last_slash - writefile;
    char parent_dir[dir_len + 1];
    strncpy(parent_dir, writefile, dir_len);
    parent_dir[dir_len] = '\0';

    // Check if the parent directory exists
    struct stat st;
    if (stat(parent_dir, &st) != 0 || !S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Parent directory does not exist: %s\n", parent_dir);
        syslog(LOG_ERR, "Parent directory does not exist: %s", parent_dir);
        exit(1);
    }

    // Create and write to the file
    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        fprintf(stderr, "Could not create file %s: %s\n", writefile, strerror(errno));
        syslog(LOG_ERR, "Could not create file %s: %s", writefile, strerror(errno));
        exit(1);
    }

    if (fprintf(file, "%s\n", writestr) < 0) {
        fprintf(stderr, "Error writing to file %s: %s\n", writefile, strerror(errno));
        syslog(LOG_ERR, "Error writing to file %s: %s", writefile, strerror(errno));
        fclose(file);
        exit(1);
    }

    fclose(file);
    printf("File %s created and written successfully.\n", writefile);
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    // Close connection to syslog
    closelog();

    return 0;
}
