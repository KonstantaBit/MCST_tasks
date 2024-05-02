#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) { // Проверяем, что кол-во аргументов валидно, иначе выходим из
                   // программы
    printf("Некорректные данные\n");
    exit(EXIT_FAILURE);
  }

  struct stat data;
  int status = syscall(SYS_stat, argv[1], &data);

  if (status != 0) { // Проверяем, что системный вызов завершился успешно, иначе
                     // выходим из программы
    printf("Ошибка во время работы stat");
    exit(EXIT_FAILURE);
  }

  printf("Тип файла: ");

  switch (data.st_mode & S_IFMT) {
  case S_IFBLK:
    printf("блочное устройство\n");
    break;
  case S_IFCHR:
    printf("символьное устройство\n");
    break;
  case S_IFDIR:
    printf("директория\n");
    break;
  case S_IFIFO:
    printf("FIFO канал\n");
    break;
  case S_IFLNK:
    printf("символьная ссылка\n");
    break;
  case S_IFREG:
    printf("обычный файл\n");
    break;
  case S_IFSOCK:
    printf("сокет\n");
    break;
  default:
    printf("неизвестно?\n");
    break;
  }

  printf("ID устройства с файлом: %lu\n", data.st_dev);
  printf("Инода:                  %lu\n", data.st_ino);
  printf("Права:                  %lo\n", (unsigned long)data.st_mode);
  printf("Жёстких ссылок:         %lu\n", data.st_nlink);
  printf("UID:                    %u\n", data.st_uid);
  printf("GID:                    %u\n", data.st_gid);
  printf("ID устройства:          %lu\n", data.st_rdev);
  printf("Размер:                 %lu байт\n", data.st_size);

  printf("Доступ:        %s", ctime(&data.st_atim.tv_sec));

  printf("Модифицирован: %s", ctime(&data.st_mtim.tv_sec));

  printf("Изменён:       %s", ctime(&data.st_ctim.tv_sec));

  return EXIT_SUCCESS;
}
