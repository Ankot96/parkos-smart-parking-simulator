#include <stdio.h>
#include <string.h>
#include "../include/auth.h"
#include "../include/ui.h"

int login()
{
    char username[20], password[20];

    printf(BOLD CYAN "\n======= ParkOS Login =======\n" RESET);

    printf(YELLOW "Username: " RESET);
    scanf("%s", username);

    printf(YELLOW "Password: " RESET);
    scanf("%s", password);

    // 👷 Employee Login
    if(strcmp(username, "employee") == 0 && strcmp(password, "123") == 0)
    {
        printf(GREEN "\n✔ Login Successful (Employee)\n" RESET);
        return 1;
    }

    // 🧑‍💼 Manager Login
    if(strcmp(username, "manager") == 0 && strcmp(password, "admin") == 0)
    {
        printf(GREEN "\n✔ Login Successful (Manager)\n" RESET);
        return 2;
    }

    // ❌ Invalid
    printf(RED "\n✖ Invalid Credentials\n" RESET);
    return 0;
}
