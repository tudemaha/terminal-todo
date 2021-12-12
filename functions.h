#include <stdio.h>
#include <string.h>
#include <conio.h>

char user_data[100][3][10];

int try_login();

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

char *login() {
    char username[10], pass[10];
    int check = 0;
    char *username_return;

    printf("Username\t: ");
    scanf("%s", &username);

    printf("Password\t: ");
    scanf("%s", &pass);

    split_user("db\\db_user.csv");

    for(int i = 0; i < 100; i++) {
        if(strcmp(username, user_data[i][0]) == 0)
        check++;
        username_return = user_data[i][0];
    }

    if(check == 1) {
        printf("Anda berhasil masuk!\n\n");
        printf("Anda masuk sebagai %s.", username);
        return username_return;

    } else {
        printf("Percobaan masuk tidak berhasil!\n\n");
        try_login();
    }

}

int try_login() {
    char check[2];
    printf(
        "Pilihan:\n"
        "1. Login Ulang\n"
        "2. Keluar Aplikasi\n"
        "Masukkan pilihan: "
    );
    scanf("%s", check);

    switch (check[0]) {
        case '1':
        login();
        break;

        case '2':
        return 0;
        break;

        default:
        salah_input();
    }
}