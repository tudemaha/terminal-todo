#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "functions.h"

int main_menu();

int main() {
    char pilihan_menu[2], pilihan_keluar[2];
    int status = 0;

    printf(
        "\n===== SELAMAT DATANG DI  TERMINAL TO-DO ====="
        "\n==== PROGRAM PENGINGAT BERBASIS TERMINAL ===="
        "\n=============================================\n"
    );

    printf(
    "\nMENU UTAMA\n"
    "1. Masuk\n"
    "2. Daftar\n"
    "3. Keluar Program\n"
    "Masukkan pilihan: "
    );
    scanf("%s", &pilihan_menu);

    switch (pilihan_menu[0]) {
        case '1':
            status = 0;
            status = login();
            
            if(status == 10) {
                status = 0;
                status = todo_option();
                if(status == 10)main();
            }
            break;

        case '2':
            status = 0;
            status = signup();
            if(status == 10) main();
            break;

        case '3':
            printf("\nYakin untuk keluar (y/n)? : ");
            scanf("%s", &pilihan_keluar);
            switch (pilihan_keluar[0]) {
            case 'y':
                return 0;
                break;

            case 'n':
                system("cls");
                main();
                break;

            default:
                salah_input();
            }
            break;
        default:
            salah_input();
            break;
    }

    return 0;
}