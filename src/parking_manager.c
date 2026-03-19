#include <stdio.h>
#include<pthread.h>
#include<fcntl.h>
#include <string.h>
#include<signal.h>
#include<unistd.h>
#include "../include/parking_manager.h"
#include"../include/database.h"
int parking_slots[TOTAL_SLOTS];
pthread_mutex_t lock;
char parked_cars[TOTAL_SLOTS][20];

void handle_status(int sig)
{
    printf("\n[Signal] Status Requested!\n");
}

//Monitor Thread
void* monitor_thread(void* arg){
	int prev=-1;
	while(1){
	sleep(3);
	pthread_mutex_lock(&lock);
	int count=0;
	for(int i=0;i<TOTAL_SLOTS;i++){
		if(parking_slots[i]==1)
		count++;
		}
	if(count!=prev){
	printf("[Monitor] Occupied: %d / %d\n", count, TOTAL_SLOTS);
	prev=count;
	}
	pthread_mutex_unlock(&lock);
	}
	return NULL;
}

//Logger
void log_event(char* msg){
	int fd=open("data/parking_log.txt", O_WRONLY|O_APPEND|O_CREAT, 0644);
	if(fd<0){
	perror("log file error");
	return;
	}
	lseek(fd, 0,SEEK_END);
	write(fd, msg, strlen(msg));
	write(fd,"\n", 1);
	close(fd);
}

//Start Threads
void start_threads(){
	pthread_t t1;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&t1, NULL, monitor_thread, NULL);
	pthread_detach(t1);
}

//Initialize Parking
void init_parking(){
	for(int i=0;i<TOTAL_SLOTS;i++){
	parking_slots[i]=0;
	strcpy(parked_cars[i],"");
	}
	printf("Parking Initialized With %d Slots\n", TOTAL_SLOTS);
}

//Exit Parking
void remove_car(char car_no[]){
	pthread_mutex_lock(&lock);
	for(int i=0;i<TOTAL_SLOTS;i++){
		if(strcmp(parked_cars[i], car_no)==0){
		parking_slots[i]=0;
		strcpy(parked_cars[i], "");
		printf("Car %s exited from slot %d\n", car_no, i+1);
		char log_msg[100];
		sprintf(log_msg, "[EXIT] %s removed", car_no);
		log_event(log_msg);
		pthread_mutex_unlock(&lock);
		return;
		}
	}
	pthread_mutex_unlock(&lock);
	printf("Car Not Found\n");
}

//status
void view_status(){
	pthread_mutex_lock(&lock);
	printf("\n===== Parking Status =====\n");
	for(int i=0;i<TOTAL_SLOTS;i++){
		if(parking_slots[i]==1)
		printf("Slot %d: %s\n", i+1, parked_cars[i]);
		else
		printf("Slot %d: Empty\n", i+1);
	}
	pthread_mutex_unlock(&lock);
}
//Park Car
void park_car(char car_no[]){
	pthread_mutex_lock(&lock);
	char type[20];
	//get vehicle type from database
	get_vehicle_type(car_no, type);
	printf("Vehicle Type: %s\n", type);
	
	//Decide floor logic
	if(strcmp(type, "SMALL")==0)
	printf("Assigned Floor: 1\n");
	else if(strcmp(type, "LARGE")==0)
	printf("Assigned Floor: 3\n");
	else if(strcmp(type, "EMERGENCY")==0)
	printf("Assigned Reserved Parking\n");
	else
	printf("Unknown Type -> Default Floor 1\n");
	
	//slot allocation
	for(int i=0;i<TOTAL_SLOTS;i++){
	if(parking_slots[i]==0){
		parking_slots[i]=1;
		strcpy(parked_cars[i], car_no);
		printf("Car %s Slot Assigned, Slot %d\n", car_no, i+1);
		sleep(2);
		printf("Car %s Parked At Slot %d\n", car_no, i+1);
		//Logging
		char log_msg[100];
		sprintf(log_msg, "[ENTRY] %s parked", car_no);
		log_event(log_msg);
		
		pthread_mutex_unlock(&lock);
		return;
		}
	}
	pthread_mutex_unlock(&lock);
	printf("Parking Full\n");
}
