#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/signal.h>

int main() {
    //Used to create a parent for the fork
    pid_t pid;
    int status; //Used for tracking
    
    //print the parent pid
    printf("Parent process PID: %d\n", getpid());


    int const numOfchildren = 10; //Variable for how many children to create

    //Create an array of commands
    char *commands[][10] = {
        {"pwd", NULL},
        {"echo", "Hello Vicente Garcia", NULL},
        {"date", NULL},
        {"history", "5", NULL},
        {"touch", "file.txt", NULL},
        {"ls", "-l", NULL},
        {"cp", "file.txt", "file2.txt", NULL},
        {"mv", "file.txt", "file1.txt", NULL},
        {"rm", "file1.txt", NULL},
        {"time", "sleep", "2", NULL}
    };

    //Create a loop for going through array comands and createing children
    for (int i = 0; i < numOfchildren; i++){
        //create a child proccess
        pid = fork();

        if(pid < 0){//Run some error checking
            perror("Fork Failure");
            exit(EXIT_FAILURE);
        }else if (pid == 0) { //Forking worked execute the child process comand

            //Print information about the child pid and what command is being executed
            printf("Child process PID: %d - Executing command: %s\n", getpid(), commands[i][0]);
            //execute command
            execvp(commands[i][0], commands[i]);
            perror("Exec Failure.");//Error checking
            exit(EXIT_FAILURE);

        }
    }
    //Print the parent history
    printf("Printing out History:---------\n");

    /* Print out the child proccess that finished excuting by seeing their 
    *  status throught the wait command. 
    */
    while ((pid=wait(&status)) > 0){
        //Check if child proccess was terminated due to a signal
        if (WIFSIGNALED(status)){

            int signal = WTERMSIG(status); //Get the signal number
            printf("Child proccess terminated due to signal: %d\n", signal);

        }else{ //Child proccess finished normally

            printf("Child process with PID %d finished.\n", pid);
        }
    }
    //Print the parent proccess after the parent is done waiting
    printf("The parent proccess %d is finished waiting.\n", getpid());

    return EXIT_SUCCESS;
}