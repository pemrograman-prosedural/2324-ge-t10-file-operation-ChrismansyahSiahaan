// 12S23003 - Chrismansyah T Siahaan
// 12S23012 - Genesis Tombak Dapot Tua Panjaitan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/gender.h"
#include "./libs/repository.h"

int main(int _argc, char **_argv)
{
  char input[100];
  int size = 0;
  int size2 = 0;
  int sizestd = 0;
  int sizedrm = 0;
  char *token;
  struct student_t *mhs = malloc(size2 * sizeof(struct student_t));
  struct dorm_t *drm = malloc(size * sizeof(struct dorm_t));


  FILE *mahasiswa;
  FILE *asrama;
  asrama = fopen("storage/dorm-repository.txt", "r");
  mahasiswa = fopen("storage/student-repository.txt", "r");

  while (1)
  {
    size++;
    drm = realloc(drm, size * sizeof(struct dorm_t));
    fscanf(asrama, "%[^\n]\n", input);
    drm[sizedrm] = create_dorm_repository(input);
    sizedrm++;
    if (feof(asrama))
    {
      break;
    }
  }

  while (1)
  {
    size2++;
    mhs = realloc(mhs, size2 * sizeof(struct student_t));
    fscanf(mahasiswa, "%[^\n]\n", input);
    mhs[sizestd] = create_student_repository(input);
    sizestd++;
    if (feof(mahasiswa))
    {
      break;
    }
  }

  while (1 == 1)
  {
    fgets(input, sizeof input, stdin);
    while (1)
    {
      if (input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\r')
      {
        input[strlen(input) - 1] = '\0';
      }
      else
      {
        break;
      }
    }

    token = strtok(input, "#");
    if (strcmp(token, "---") == 0)
    {
      break;
    }
    else if (strcmp(token, "dorm-add") == 0)
    {
      size++;
      drm = realloc(drm, size * sizeof(struct dorm_t));
      drm[sizedrm] = create_dorm(input);
      sizedrm++;
    }
    else if (strcmp(token, "dorm-print-all") == 0)
    {
      for (int m = 0; m < sizedrm; m++)
      {
        print_dorm(drm[m]);
      }
    }
    else if (strcmp(token, "dorm-print-all-detail") == 0)
    {
      for (int m = 0; m < sizedrm; m++)
      {
        print_dorm_detail(drm[m]);
      }
    }
    else if (strcmp(token, "student-add") == 0)
    {
      size2++;
      mhs = realloc(mhs, size2 * sizeof(struct student_t));
      mhs[sizestd] = create_student(input);
      sizestd++;
    }
    else if (strcmp(token, "student-print-all") == 0)
    {
      for (int m = 0; m < sizestd; m++)
      {
        print_student(mhs[m]);
      }
    }
    else if (strcmp(token, "student-print-all-detail") == 0)
    {
      for (int m = 0; m < sizestd; m++)
      {
        print_student_detail(mhs[m]);
      }
    }
    else if (strcmp(token, "assign-student") == 0)
    {
      char *nim = strtok(NULL, "#");
      char *asrama = strtok(NULL, "#");
      assign_student(drm, mhs, nim, asrama, sizestd, sizedrm, find_id, find_dorm);
    }
    else if (strcmp(token, "move-student") == 0)
    {
      char *nim = strtok(NULL, "#");
      char *asrama = strtok(NULL, "#");
      move_student(drm, mhs, nim, asrama, sizestd, sizedrm, find_id, find_dorm);
    }
    else if (strcmp(token, "dorm-empty") == 0)
    {
      char *asrama = strtok(NULL, "#");
      dorm_empty(asrama, sizestd, sizedrm, mhs, drm, find_dorm);
    }
  }
  free(mhs);
  free(drm);

  return 0;
}
