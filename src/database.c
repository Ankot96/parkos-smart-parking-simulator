#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include"../include/database.h"
void get_vehicle_type(char car_no[], char type[]){
	int fd;
	char buff[1024];
	fd=open("data/vehicle_db.txt", O_RDONLY);
	if(fd<0){
		printf("Error opening the database\n");
		return;
		}
	int bytes=read(fd, buff, sizeof(buff) -1);
	buff[bytes]='\0'; //null terminate
	close(fd);
	
	//search by line
	char *line=strtok(buff, "\n");
	while(line !=NULL){
		char db_car[20], db_type[20];
		sscanf(line, "%s%s", db_car, db_type);
		if(strcmp(car_no, db_car)==0){
			strcpy(type, db_type);
			return;
		}
	line=strtok(NULL, "\n");
	}
	//if not found
	strcpy(type, "UNKNOWN or New Vehicle");
}
