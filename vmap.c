#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pmap_to_file(const char* pid, const char* filename) {
    char buffer[256];
    char buffer2[256];

    FILE* output = fopen(filename, "r");
    if(!output){
        printf("Такого файла не существует, создаём...\n");
        output = fopen(filename, "w");
        if(!output){
            perror("Ошибка создания файла...");
            return;
        }
        memset(buffer, 0, 256);
        snprintf(buffer, 256, "%s %s %s %s", "pmap", pid, ">>", filename);
        system(buffer);
        close(output);
        printf("Запись в файл прошла успешно!\n");
    } else {
        printf(
                "Внимание! Файл %s уже существует, возможные варианты разрешения:\n"
               "\t1.Перезаписать файл\n"
               "\t2.Переименовать новый файл\n"
               "\t3.Выйти\n",
        filename);
        int selected;
        memset(buffer, 0, 256);
        while(1) {
            int status = scanf("%s", buffer);
            if (status < 0 || !sscanf(buffer, "%d", &selected) || (selected < 1 || selected > 3)) {
                printf("Некорректный ввод, попробуйте ещё раз\n");
                continue;
            }
            break;
        }
        if (selected == 1){
            printf("Перезапись файла...\n");
            memset(buffer, 0, 256);
            snprintf(buffer, 256, "%s %s %s %s", "pmap", pid, ">", filename);
            system(buffer);
            printf("Запись в файл прошла успешно!\n");
        }
        else if (selected == 2){
            printf("Введите новое имя файла:\n");
            memset(buffer2, 0, 256);
            scanf("%s", buffer2);
            memset(buffer, 0, 256);
            snprintf(buffer, 256, "%s %s %s %s", "pmap", pid, ">", buffer2);
            system(buffer);
            printf("Запись в файл прошла успешно!\n");
        } else{
            printf("Программа завершила работу!\n");
            return;
        }
        close(output);
    }
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf(
                "Использовать:\n"
                "\t./vmap <pid> <output_filename>\n"
        );
        return 1;
    }
    pmap_to_file(argv[1], argv[2]);
    return 0;
}
