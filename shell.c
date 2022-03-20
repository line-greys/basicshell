#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *shell_readline();
char **shell_splitline(char *line);
int shell_loop();

int shell_loop(){

  int running = 1;

  do {
    //printf("Entered do loop\n");
    char *line;
    char **split_line;

    printf(">>> ");
    line = shell_readline();
    split_line = shell_splitline(line);

    if(strcmp(split_line[0],"\n") == 0){
      free(line);
      free(split_line);
      continue;
    }

    if (strcmp(split_line[0], "hello") == 0){
      printf("Hi there, hope you're well! \n");
    }
    else if (strcmp(split_line[0], "bye") == 0){
      running = 0;
    }
    else if (strcmp(split_line[0], "author") == 0){
      printf("Aline Grobys\n");
    }
    else if (strcmp(split_line[0], "help") == 0){
      printf("\nBuilt-in commands: \n \"hello\" for a friendly greeting\n \"author\" to print the program's writer\n \"help\" to print available commands\n \"bye\" to end the program. \nThe shell supports other commands as long as they exist within /bin/ of the standard library.\nArguments may be passed into those commands. Try \"echo\", \"date" or \"dir\". \nThank you for using my program!\n");
    }
    else {
      //printf("Entered fork path\n");
      //char *args[] = {line, NULL};

      //pid_t parent = getpid();
      pid_t pid = fork();

      if (pid == 0){

        //printf("in child");
        char path[50] = "/bin/";
        strcat(path, line);
        printf("%s", path);
        execve(path, split_line, NULL);
        perror( "execve failed" );
        printf("\n");
        exit( EXIT_FAILURE );

      } else if (pid > 0) {

        int status;
        waitpid(pid, &status, 0);
        if(WEXITSTATUS(status) != 0){
          printf("Command failed. Please try again.\n");
        }

      } else {
        printf("fork failed");
      }

      //free(args);
    }

    free(line);
    free(split_line);
  } while (running);

  return 0;
}

char *shell_readline(){

  int line_size = 50;
  char *line = malloc(sizeof(char)*line_size);

  fgets(line, line_size, stdin);
  return line;
};

char **shell_splitline(char *line){

  char **split_line = malloc(sizeof(char *)*64);
  char *segment;
  int i = 0;

  segment = strtok(line, " ");
  while (segment != NULL){
    split_line[i] = segment;
    i++;
    segment = strtok(NULL, " ");
  }
  strtok(split_line[i-1], "\n");
  split_line[i] = NULL;
  return split_line;
};

int main(){

  int exit;
  printf("\nHi, this is Aline Grobys' simple shell. \nBuilt-in commands: \n \"hello\" for a friendly greeting\n \"author\" to print the program's writer\n \"help\" to print available commands\n \"bye\" to end the program. \nThe shell supports other commands as long as they exist within /bin/ of the standard library.\nArguments may be passed into those commands. Try \"echo\", \"date" or \"dir\". \nThank you for using my program!\n");
  printf("\nWelcome to the shell! Enter your first command below: \n\n");

  exit = shell_loop();

  if (exit == 0) {
    printf("Exited successfully. See you soon!\n");
  } else {
    printf("Exited from failure. Please relaunch.\n");
  }
}
