#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

char user_data[100][3][10];
int status = 1;

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

// fungsi login
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

// menangani kesalahan login
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

// fungsi daftar user baru
int signup() {
    char username[10], pass[10];
    int check = 0;
    split_user("db\\db_user.csv");

    printf("\nKetik username (maksimal 10 karakter tanpa spasi): ");
    scanf("%s", username);

    while(getchar() != '\n');

    printf("Masukkan password (maksimal 10 karakter): ");
    gets(pass);
    

    for(int i = 0; i < 100; i++) {
        if(strcmp(username, user_data[i][0]) == 0)
        check++;
    }

    if(status == 3) {
        printf("Anda membuat tiga kali kesalahan saat mendaftar, Anda dikembalikan ke state awal!");
        printf("\nTekan sembarang tombol...\n");
        getch();
        system("cls");
        status = 0;
        return 10;
    }

    if(check > 0) {
        printf("\nUsername sudah digunakan. Gunakan username lain!\n");
        status++;
        signup();
    } else if(strlen(username) > 10) {
        printf("\nUsername lebih dari 10 karakter. Gunakan username lain!\n");
        status++;
        signup();
    } else if(strlen(pass) > 10) {
        printf("\nPassword lebih dari 10 karakter. Gunakan password lain!\n");
        status++;
        signup();
    } else {
        status = 0;
    }

    
}