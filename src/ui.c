#include <stdio.h>
#include <unistd.h>
#include "../include/ui.h"
void show_logo()
{
    printf(CYAN BOLD);
    printf("\n=========================================\n");
    printf("            ParkOS v1.0                  \n");
    printf("=========================================\n");
    printf(RESET);
    sleep(1);
    printf(YELLOW "[BOOT] Initializing kernel modules...\n" RESET);
    usleep(400000);
    printf(YELLOW "[BOOT] Loading device drivers...\n" RESET);
    usleep(400000);
    printf(YELLOW "[BOOT] Startup IPC mechanisms...\n" RESET);
    usleep(400000);
    printf(YELLOW "[BOOT] Initializing memory manager...\n" RESET);
    usleep(400000);
    printf(YELLOW "\n[SUCESS] System Ready \n\n" RESET);
    usleep(400000);
    printf(CYAN BOLD);
    printf("=========================================\n");
    printf("               ParkOS                    \n");
    printf("=========================================\n");
    printf(RESET);
    printf(GREEN "Smart Parking Management System\n\n" RESET);
}

void show_menu(int role)
{
    printf(BOLD BLUE "\n========== ParkOS Control Panel ==========\n" RESET);

    if(role==1) // Employee
    {
        printf(CYAN "1. Park Vehicle\n");
        printf("2. Remove Vehicle\n");
        printf("3. Logout\n" RESET);
    }
    else if(role==2) // Manager
    {
        printf(CYAN "1. Park Vehicle\n");
        printf("2. Remove Vehicle\n");
        printf("3. View System Status\n");
        printf("4. Logout\n" RESET);
    }

    printf(YELLOW "Enter choice: " RESET);
}
