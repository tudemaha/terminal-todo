#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// global variabel
char user_data[100][3][10];
char todo_list[500][6][500];
char username_login[10];

// prototyping function
int try_login();
int todo_option();
int finish_todo();

// fungsi untuk menangani kesalahan input
int salah_input() {
    printf(
        "\nPilihan yang dimasukkan tidak sesuai!"
        "\nTekan sembarang untuk menutup aplikasi..."
    );
    getch();
    return 0;
}

// split isi user csv
void split_user() {
    char buffer[1024];

    int row = 0, column = 0;

    FILE *user_db = fopen("db_user.csv", "r");

    if(!user_db) {
        printf("Database user tidak tersedia, program dihentikan.\n");
        printf("Tekan sembarang untuk keluar dari program...");
        getch();
        exit(1);
    } else {

        while(fgets(buffer, 1024, user_db)) {
            column = 0;

            char *value = strtok(buffer, ";");

            while(value) {
                if(column == 0) strcpy(user_data[row][column], value);
                if(column == 1) strcpy(user_data[row][column], value);

                value = strtok(NULL, ";");

                column++;
            }
            row++;
        }
    }

    fclose(user_db);
}

// fungsi untuk user login
int login() {
    char username[10], pass[10];
    int check = 0;

    printf("Username\t: ");
    scanf("%s", &username);

    printf("Password\t: ");
    scanf("%s", &pass);

    split_user();

    for(int i = 0; i < 100; i++) {
        if((strcmp(username, user_data[i][0]) == 0) && (strcmp(pass, user_data[i][1]) == 0)) {
            check++;
            strcpy(username_login, user_data[i][0]);
        }
    }

    if(check == 1) {
        system("cls");
        printf("Anda berhasil masuk.\n\n");
        return 10;

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
            break;
    }
}

// fungsi daftar user baru
int status = 1;
int signup() {
    char username[10], pass[10];
    int check_same = 0;


    split_user();


    printf("\nKetik username (maksimal 10 karakter tanpa spasi): ");
    scanf("%s", &username);

    while(getchar() != '\n');

    printf("Masukkan password (maksimal 10 karakter): ");
    fgets(pass, 15, stdin);
    pass[strcspn(pass, "\n")] = 0;
    

    int i = 0;
    while(strcmp(username, user_data[i][0]) == 0) {
        check_same++;
        i++;
    }

    if(status < 3 && check_same > 0) {
        printf("\nUsername sudah digunakan. Gunakan username lain!\n");
        status++;
        strcpy(username, "");
        strcpy(pass, "");
        signup();
    } else if(status < 3 && strlen(username) > 10) {
        printf("\nUsername lebih dari 10 karakter. Gunakan username lain!\n");
        status++;
        strcpy(username, "");
        strcpy(pass, "");
        signup();
    } else if(status < 3 && strlen(pass) > 10) {
        printf("\nPassword lebih dari 10 karakter. Gunakan password lain!\n");
        status++;
        strcpy(username, "");
        strcpy(pass, "");
        signup();
    } else {

        if(status == 3) {
            printf("Anda membuat tiga kali kesalahan saat mendaftar, Anda dikembalikan ke main menu.");
            printf("\nTekan sembarang tombol...\n");
            getch();
            system("cls");
            status = 0;
            return 10;
        } else {
            FILE *user_db = fopen("db_user.csv", "a+");

            if(!user_db) {
                printf("Database user tidak tersedia, program dihentikan.\n");
                printf("Tekan sembarang untuk keluar dari program...");
                getch();
                exit(1);
            } else {
                fprintf(user_db, "%s;%s;\n", username, pass);
                fclose(user_db);
                printf(
                    "Username berhasil didaftarkan.\n"
                    "Tekan sembarang tombol untuk kembali ke main menu..."
                );
                getch();
                system("cls");
                return 10;
            }
        }
    }
}


// membuat todo baru
int new_todo() {
    FILE *todo_db = fopen("db_todo.csv", "a+");

    char todo[3][500];

    while(getchar() != '\n');

    printf("\nIngatkan untuk (maks. 500 karakter): ");
    fgets(todo[0], 500, stdin);
    todo[0][strcspn(todo[0], "\n")] = 0;

    if(strlen(todo[0]) == 0) {
        printf("Anda belum memasukkan kegiatan.\n");
        new_todo(username_login);
    }
    

    printf("Deadline (format: dd/mm/yyyy) [opsional]: ");
    fgets(todo[1], 11, stdin);
    todo[1][strcspn(todo[1], "\n")] = 0;
    

    if(!todo_db) {
        printf("Database todo tidak tersedia, program dihentikan.\n");
        printf("Tekan sembarang untuk keluar dari program...");
        getch();
        exit(1);
    } else {
        fprintf(todo_db, "%s;%s;%s;;\n", username_login, todo[0], todo[1]);
        fclose(todo_db);
        printf("\nBerhasil memasukkan kegiatan.\n");
    }

    while(getchar() != '\n');

    char pilihan[2];
    printf("Ingin memasukkan kegiatan lain? (y/n): ");
    scanf("%s", &pilihan);
    switch(pilihan[0]) {
        case 'y':
            //system("cls");
            new_todo();
            break;

        case 'n':
            return 10;
            break;

        default:
            salah_input();
            break;
    }

}

// split csv todo sesuai dengan mode yang diinginkan
void split_todo(char mode[]) {
    char buffer[4000];
    int row = 0, column = 0;

    FILE *todo_db = fopen("db_todo.csv", mode);

    if(!todo_db) {
        printf("Database todo tidak tersedia, program dihentikan.\n");
        printf("Tekan sembarang untuk keluar dari program...");
        getch();
        exit(1);
    } else {

        while(fgets(buffer, 4000, todo_db)) {
            column = 0;

            char *value = strtok(buffer, ";");

            while(value) {
                if(column == 0) strcpy(todo_list[row][column], value);
                if(column == 1) strcpy(todo_list[row][column], value);
                if(column == 2) strcpy(todo_list[row][column], value);
                if(column == 3) strcpy(todo_list[row][column], value);

                value = strtok(NULL, ";");
                column++;
            }
            row++;
        }
    }
    fclose(todo_db);

    for(int i = 0; i < 500; i++) {
        for(int j = 0; j < 5; j++) {
            todo_list[i][j][strcspn(todo_list[i][j], "\n")] = 0;
        }
        
    }

    int count = 1;
    system("cls");
    printf("\nDaftar kegiatanmu:\n");
    for(int i = 0; i < 500; i++) {
        if(strcmp(todo_list[i][0], username_login) == 0) {
            printf("%d. ", count++);
            printf("%d - ", i);
            printf("%s - ", todo_list[i][1]);
            printf("%s - ", todo_list[i][2]);
            printf("%s\n", todo_list[i][3]);
        }
    }
}

// menampilkan todo dari user login
void show_todo() {
    split_todo("r");

    printf("\n\nTekan sembarang tombol untuk kembali ke menu sebelumnya...\n");
    getch();
    system("cls");
    todo_option();
}


// menampilkan pilihan aksi user saat berhasil login
int todo_option() {
    char pilihan[2];
    int status = 0;

    printf("Anda masuk sebagai %s.\n\n", username_login);
    printf(
        "Pilihan Menu:\n"
        "1. Buat To-Do List\n"
        "2. Lihat To-Do List\n"
        "3. Tandai To-Do List telah Dilakukan\n"
        "4. Keluar\n"
        "Masukkan pilihan: "
    );
    scanf("%s", &pilihan);

    switch (pilihan[0]) {
        case '1':
            status = new_todo();
            if(status == 10) {
                system("cls");
                todo_option();
            }
            break;
        
        case '2':
            show_todo();
            break;

        case '3':
            finish_todo();
            break;

        case '4':
            system("cls");
            return 10;
            break;

        default:
            salah_input();
            break;
    }
}

// menyelesaikan todo berdasarkan id
int finish_todo() {
    int selesai, count = 0;
    char pilihan[2];

    split_todo("r");

    printf("\n\nMasukkan ID kegiatan untuk ditandai selesai (masukkan -1 untuk membatalkan): ");
    scanf("%d", &selesai);

    if(selesai == -1) {
        system("cls");
        todo_option();
    } else {

        int i = 0;
        while(strcmp(todo_list[i][0], "") != 0) {
            count++;
            i++;
        }

        if(strcmp(username_login, todo_list[selesai][0]) == 0) {
            strcpy(todo_list[selesai][3], "*");

            FILE *finish_fp = fopen("db_todo.csv", "w+");

            if(!finish_fp) {
                printf("\nDatabase todo tidak tersedia, program dihentikan.\n");
                printf("Tekan sembarang untuk keluar dari program...");
                getch();
                exit(1);
            } else {
                for(int i = 0; i < count; i++) {
                    fprintf(finish_fp, "%s;%s;%s;%s;\n", todo_list[i][0], todo_list[i][1], todo_list[i][2], todo_list[i][3]); 
                }
                fclose(finish_fp);

                printf("\n\nIngin menyelesaikan daftar yang lain? (y/n): ");
                scanf("%s", &pilihan);

                switch(pilihan[0]) {
                    case 'y':
                        system("cls");
                        finish_todo();
                        break;
                    case 'n':
                        system("cls");
                        todo_option();
                        break;
                    default:
                        salah_input();
                        break;
                }
            }
        } else {
            printf("\nID yang dimasukkan tidak valid!");
            printf("\nTekan sembarang untuk mengulagi...");
            getch();
            system("cls");
            finish_todo();
        }
    }
}