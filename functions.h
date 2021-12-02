#include <stdio.h>
#include <string.h>
#include <conio.h>

char user_data[100][3][10];

// fungsi untuk menangani kesalahan input
int salah_input() {
    printf(
        "\nPilihan yang dimasukkan tidak sesuai!"
        "\nTekan sembarang untuk menutup aplikasi..."
    );
    getch();
    return 0;
}

// split isi scv
void split_user(char db_user[]) {
    char buffer[1024];

    int row = 0, column = 0;

    FILE *fp = fopen(db_user, "r");

    if(!fp) {
        printf("Database user tidak tersedia!");
    } else {

        while(fgets(buffer, 1024, fp)) {
            column = 0;

            char *value = strtok(buffer, ",");

            while(value) {
                if(column == 0) strcpy(user_data[row][column], value);
                if(column == 1) strcpy(user_data[row][column], value);

                value = strtok(NULL, ",");

                column++;
            }
            row++;
        }
    }

    fclose(fp);
}