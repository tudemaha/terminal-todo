#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "functions.h"

int main_menu();

int main() {

    printf(
        "\n===== SELAMAT DATANG DI  TERMINAL TO-DO ====="
        "\n==== PROGRAM PENGINGAT BERBASIS TERMINAL ===="
        "\n=============================================\n"
    );

    main_menu();
    

    return 0;
}

int main_menu() {
        char pilihan_menu[2], pilihan_keluar[2];

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
        break;

        case '2':
        break;

        case '3':
        printf("\nYakin untuk keluar (y/n)? : ");
        scanf("%s", &pilihan_keluar);
        switch (pilihan_keluar[0]) {
            case 'y':
            return 0;
            break;

            case 'n':
            main_menu();
            break;

            default:
            salah_input();
        }
        break;

        default:
        salah_input();

    }

}