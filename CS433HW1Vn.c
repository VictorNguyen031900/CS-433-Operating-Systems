/*
    Assignment 1
    Name: Victor Nguyen
    Professor: Sahar Mosleh
    Course: CS 433
    Date Created: 10-8-2020

    Homework Description: Create a program to emulate a unix shell environment that can run basic commands.
    In the homework we have to use system calls like fork(), execvp(), and wait() to complete the homework.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAXLINE 80

void parseline(char *command, char **args)
{
  /* Splits all words into array for later execvp system call*/
  char delim[] = " ";
  int i = 0;
  char *ptr = strtok(command, delim);
  while(ptr != NULL)
    {
      args[i++] = ptr;
      ptr = strtok(NULL, delim);
    }
}


int main(void)
{

  int should_run = 1;

  char *args[MAXLINE/2+1];

  while(should_run != 0)
    {
      /* String for command */
      char command[MAXLINE];

      /* Clear arrays */
      memset(command, 0, sizeof command);
      memset(args, 0, sizeof args);

      /* Shell Line */
      printf("\nosh> ");

      /* Get input from user and put into command variable */
      scanf("%[^\n]%*c", command);

      /* Clear input buffer for next time */
      fflush(stdin);

      /* Call parseline command */
      parseline(command, args);

      /* Clear output buffer for next time */
      fflush(stdout);
 
      /* Checks if the command entered was exit to exit program */
      if(strcmp(args[0], "exit") == 0)
	{
	  printf("\nExiting Program.\n");
	  /* Break out of while loop */
	  should_run = 0;
	  return 0;
	}

      /* Fork a process */
      pid_t pid;
      pid = fork();

      if(pid < 0)
	{
	  /* Error Occurred */
	  printf("\nFork Failed.\n");
	  return 1;
	}
      else if(pid == 0)
	{
	  /* Fork succesful and execute the command the user entered */
	  if(execvp(args[0], args) < 0)
	    {
	      /* If the command entered returned an error meaning invalid command */
	      printf("\nUnknown Command.\n");
	      return 0;
	    }
	}
      else
	{
	  /* Wait for the child process to complete */
	  wait(NULL);
	  printf("\nChild Complete.\n");
	}
    }
   return 0;
}
