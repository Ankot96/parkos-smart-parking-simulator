#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

#include "../include/parking_manager.h"
#include "../include/ui.h"
#include "../include/auth.h"

void handle_sigint(int sig){
	printf("\n\n[ParkOS] Graceful Shutdown Initiated...\n");
	printf("[ParkOS] Cleaning Resources...\n");
	printf("[ParkOS] System Shutdown Complete\n");
	exit(0);
}

int main(){
	signal(SIGINT, handle_sigint);
	int choice;
	char car[20];
	show_logo();
	int role = login();
	if(role == 0){
		printf("Invalid Login\n");
		return 0;
	}
	init_parking();
	start_threads();
	while(1){
		show_menu(role);
		scanf("%d", &choice);
		if(role == 1 && choice == 3) break;
		if(role == 2 && choice == 4) break;
		if(choice == 1){
		int fd[2];
		if(pipe(fd) == -1){
		perror("Pipe failed");
		return 1;
		}
		pid_t pid = fork();
		if(pid == 0){			
		close(fd[0]);
		printf("\n[Entry Process]\n");
		printf("Enter Car Number: ");
		scanf("%s", car);
		write(fd[1], car, sizeof(car));
		close(fd[1]);
		return 0;
		}
		else{
		close(fd[1]);
		read(fd[0], car, sizeof(car));
		printf("\n[Manager Received]: %s\n", car);
		park_car(car);
		close(fd[0]);
		waitpid(pid, NULL, 0);
		}
	}
	else if(choice == 2){
	pid_t pid = fork();
	if(pid == 0){
	int fifo_fd = open("exit_pipe", O_WRONLY);
	if(fifo_fd < 0){
	perror("FIFO open failed");
	return 1;
	}
	printf("\n[Exit Process]\n");
	printf("Enter Car Number: ");
	scanf("%s", car);
	write(fifo_fd, car, sizeof(car));
	close(fifo_fd);
	return 0;
	}
	else{
	int fifo_fd = open("exit_pipe", O_RDONLY);
	if(fifo_fd < 0){
	perror("FIFO open failed");
	return 1;
	}
	read(fifo_fd, car, sizeof(car));
	printf("\n[Manager Received Exit]: %s\n", car);
	remove_car(car);
	close(fifo_fd);
	waitpid(pid, NULL, 0);
	}
}

	else if(choice == 3 && role == 2){
	view_status();
	}
	else{
	printf("Invalid choice\n");
	}
}

	printf("Exiting ParkOS...\n");
	return 0;
}
