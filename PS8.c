// Write a program to demonstrate any 5 system calls.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <utime.h>
#include <errno.h>
#include <sys/utsname.h>
#include <time.h>
#include <dirent.h>

// Function prototypes
void processRelatedSystemCalls();
void fileRelatedSystemCalls();
void communicationSystemCalls();
void informationRelatedSystemCalls();
void advancedFileOperations();

int main() {
    int choice;
    while(1) {
        printf("\nSystem Call Demonstration\n");
        printf("1. Process Related System Calls (fork, exit, wait)\n");
        printf("2. File Related System Calls (open, read, write, close, link, unlink, stat)\n");
        printf("3. Communication Related System Calls (pipe, fifo)\n");
        printf("4. Information Related System Calls\n");
        printf("5. Advanced File Operations (Directory manipulation, timestamp)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                processRelatedSystemCalls();
                break;
            case 2:
                fileRelatedSystemCalls();
                break;
            case 3:
                communicationSystemCalls();
                break;
            case 4:
                informationRelatedSystemCalls();
                break;
            case 5:
                advancedFileOperations();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Process Related System Calls: fork, exit, wait, exec
void processRelatedSystemCalls() {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) { // Child process
        printf("Child process (PID = %d) created. Now executing `ls` command using exec().\n", getpid());
        execlp("ls", "ls", "-l", NULL);  
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else { // Parent process
        int status;
        wait(&status); 
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        printf("Parent process (PID = %d) continues.\n", getpid());
    }
}


void fileRelatedSystemCalls() {
    int fd;
    char buffer[100];
    ssize_t bytesRead;

    
    fd = open("testfile.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd < 0) {
        perror("File open failed");
        return;
    }

    // Write to the file
    char *data = "Advanced system call demonstration write.\n";
    write(fd, data, strlen(data));

    // Read from the file
    lseek(fd, 0, SEEK_SET); 
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("File read failed");
    } else {
        buffer[bytesRead] = '\0';
        printf("Data read from file: %s", buffer);
    }

    // Get file metadata using stat
    struct stat fileStat;
    if (stat("testfile.txt", &fileStat) == 0) {
        printf("\nFile: 'testfile.txt'\n");
        printf("File size: %ld bytes\n", fileStat.st_size);
        printf("Last modified: %s", ctime(&fileStat.st_mtime));
        printf("File permissions: %o (octal)\n", fileStat.st_mode & 0777);
    } else {
        perror("Stat failed");
    }

    // Close the file
    close(fd);
}

// Communication Related System Calls: pipe, fifo, enhanced pipe communication
void communicationSystemCalls() {
    int pipefd[2];
    char buffer[100];
    pid_t pid;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return;
    }

    pid = fork(); // Create a child process
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) { // Child process
        close(pipefd[0]); // Close reading end
        char *message = "Advanced message from child to parent through pipe\n";
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]); // Close writing end
        exit(0);
    } else { // Parent process
        close(pipefd[1]); // Close writing end
        read(pipefd[0], buffer, sizeof(buffer) - 1);
        printf("Parent received: %s", buffer);
        close(pipefd[0]); // Close reading end
        wait(NULL); // Wait for child to finish
    }

    // FIFO demonstration (Named pipe) with advanced features
    char *fifo = "/tmp/my_advanced_fifo";
    mkfifo(fifo, 0666);
    printf("FIFO created at /tmp/my_advanced_fifo\n");

    if (fork() == 0) {
        // Child process writes to FIFO
        int fd = open(fifo, O_WRONLY);
        write(fd, "Advanced FIFO communication\n", 28);
        close(fd);
        exit(0);
    } else {
        // Parent process reads from FIFO
        int fd = open(fifo, O_RDONLY);
        read(fd, buffer, sizeof(buffer) - 1);
        printf("Parent read from FIFO: %s", buffer);
        close(fd);
        wait(NULL); // Wait for child to finish
    }

    unlink(fifo); // Remove FIFO
    printf("FIFO removed\n");
}

// Information Related System Calls: uname, getpid, getppid, getcwd, getuid, getgid
void informationRelatedSystemCalls() {
    pid_t pid = getpid();  // Get current process ID
    pid_t ppid = getppid(); // Get parent process ID
    uid_t uid = getuid();  // Get user ID
    gid_t gid = getgid();  // Get group ID
    char cwd[1024];

    printf("Current PID: %d, Parent PID: %d\n", pid, ppid);
    printf("User ID: %d, Group ID: %d\n", uid, gid);

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd failed");
    }

    // Print system name using uname
    struct utsname sysInfo;
    if (uname(&sysInfo) == 0) {
        printf("System Information:\n");
        printf("  System name: %s\n", sysInfo.sysname);
        printf("  Node name: %s\n", sysInfo.nodename);
        printf("  Release: %s\n", sysInfo.release);
        printf("  Version: %s\n", sysInfo.version);
        printf("  Machine: %s\n", sysInfo.machine);
    } else {
        perror("uname failed");
    }
}

// Advanced File Operations: Directory manipulation, timestamp
void advancedFileOperations() {
    DIR *dir;
    struct dirent *entry;

    // Open current directory
    if ((dir = opendir(".")) == NULL) {
        perror("opendir failed");
        return;
    }

    printf("Files in current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dir);

    // Change file modification time
    struct utimbuf new_times;
    new_times.actime = time(NULL);   // Set access time to current time
    new_times.modtime = time(NULL);  // Set modification time to current time

    if (utime("testfile.txt", &new_times) == 0) {
        printf("Modification time updated for 'testfile.txt'\n");
    } else {
        perror("utime failed");
    }
}
