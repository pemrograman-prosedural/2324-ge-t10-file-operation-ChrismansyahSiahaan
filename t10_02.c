// 12S23003 - Chrismansyah T Siahaan
// 12S23012 - Genesis Tombak Dapot Tua Panjaitan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/gender.h"
#include "./libs/repository.h"

#define MAX_INPUT_LENGTH 75
#define MAX_TOKEN_LENGTH 10

typedef enum {
    DORM_ADD,
    DORM_PRINT_ALL,
    DORM_PRINT_ALL_DETAIL,
    STUDENT_ADD,
    STUDENT_PRINT_ALL,
    STUDENT_PRINT_ALL_DETAIL,
    ASSIGN_STUDENT,
    MOVE_STUDENT,
    DORM_EMPTY,
    EXIT
} Command;

void handle_command(Command command, char *input, struct dorm_t *drm, int *zdrm, struct student_t *mhs, int *zstd) {
    switch (command) {
        case DORM_ADD:
            (*zdrm)++;
            drm = realloc(drm, (*zdrm) * sizeof(struct dorm_t));
            drm[(*zdrm) - 1] = create_dorm(input);
            break;
        case DORM_PRINT_ALL:
            for (int i = 0; i < *zdrm; i++) {
                print_dorm(drm[i]);
            }
            break;
        case DORM_PRINT_ALL_DETAIL:
            for (int i = 0; i < *zdrm; i++) {
                print_dorm_detail(drm[i]);
            }
            break;
        case STUDENT_ADD:
            (*zstd)++;
            mhs = realloc(mhs, (*zstd) * sizeof(struct student_t));
            mhs[(*zstd) - 1] = create_student(input);
            break;
        case STUDENT_PRINT_ALL:
            for (int i = 0; i < *zstd; i++) {
                print_student(mhs[i]);
            }
            break;
        case STUDENT_PRINT_ALL_DETAIL:
            for (int i = 0; i < *zstd; i++) {
                print_student_detail(mhs[i]);
            }
            break;
        case ASSIGN_STUDENT:
            char *nim = strtok(NULL, "#");
            char *asrama = strtok(NULL, "#");
            assign_student(drm, mhs, nim, asrama, *zstd, *zdrm, find_id, find_dorm);
            break;
        case MOVE_STUDENT:
            char *nim = strtok(NULL, "#");
            char *asrama = strtok(NULL, "#");
            move_student(drm, mhs, nim, asrama, *zstd, *zdrm, find_id, find_dorm);
            break;
        case DORM_EMPTY:
            char *asrama = strtok(NULL, "#");
            dorm_empty(asrama, *zstd, *zdrm, mhs, drm, find_dorm);
            break;
        default:
            printf("Invalid command\n");
            break;
    }
}

int main(int argc, char **argv) {
    char input[MAX_INPUT_LENGTH];
    int zdrm = 0;
    struct dorm_t *drm = malloc(zdrm * sizeof(struct dorm_t));
    int zstd = 0;
    struct student_t *mhs = malloc(zstd * sizeof(struct student_t));

    FILE *mahasiswa;
    FILE *asrama;
    asrama = fopen("storage/dorm-repository.txt", "r");
    mahasiswa = fopen("storage/student-repository.txt", "r");

    while (1) {
        zdrm++;
        drm = realloc(drm, zdrm * sizeof(struct dorm_t));
        fscanf(asrama, "%[^\n]\n", input);
        drm[zdrm - 1] = create_dorm_repository(input);
        if (feof(asrama)) {
            break;
        }
    }

    while (1) {
        zstd++;
        mhs = realloc(mhs, zstd * sizeof(struct student_t));
        fscanf(mahasiswa, "%[^\n]\n", input);
        mhs[zstd - 1] = create_student_repository(input);
        if (feof(mahasiswa)) {
            break;
        }
    }

    while (1) {
        fgets(input, MAX_INPUT_LENGTH, stdin);
        while (1) {
            if (input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\r') {
                input[strlen(input) - 1] = '\0';
            } else {
                break;
            }
        }

        char *token = strtok(input, "#");
        Command command;
        if (strcmp(token, "---") == 0) {
            break;
        } else if (strcmp(token, "dorm-add") == 0) {
            command = DORM_ADD;
        } else if (strcmp(token, "dorm-print-all") == 0) {
            command = DORM_PRINT_ALL;
        } else if (strcmp(token, "dorm-print-all-detail") == 0) {
            command = DORM_PRINT_ALL_DETAIL;
        } else if (strcmp(token, "student-add") == 0) {
            command = STUDENT_ADD;
        } else if (strcmp(token, "student-print-all") == 0) {
            command = STUDENT_PRINT_ALL;
        } else if (strcmp(token, "student-print-all-detail") == 0) {
            command = STUDENT_PRINT_ALL_DETAIL;
        } else if (strcmp(token, "assign-student") == 0) {
            command = ASSIGN_STUDENT;
        } else if (strcmp(token, "move-student") == 0) {
            command = MOVE_STUDENT;
        } else if (strcmp(token, "dorm-empty") == 0) {
            command = DORM_EMPTY;
        } else {
            command = EXIT;
        }

        handle_command(command, input, drm, &zdrm, mhs, &zstd);
    }

    free(mhs);
    free(drm);

    return 0;
}