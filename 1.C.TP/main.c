
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define max_str_size 1000

/*
Первая задача.
Составить программу построчной обработки текста. Суть обработки - отбор строк, содержащих одинаковое количество открывающих и закрывающих круглых скобок.

Программа считывает входные данные со стандартного ввода, и печатает результат в стандартный вывод.

Процедура отбора нужных строк должна быть оформлена в виде отдельной функции, которой на вход подается массив строк (который необходимо обработать), количество переданных строк, а также указатель на переменную, в которой необходимо разместить результат - массив отобранных строк.
В качестве возвращаемого значения функция должна возвращать количество строк, содержащихся в результирующем массиве.

Программа должна уметь обрабатывать ошибки - такие как неверные входные данные(отсутствие входных строк) или ошибки выделения памяти и т.п.
В случае возникновения ошибки нужно выводить об этом сообщение "[error]" и завершать выполнение программы.
*/

int halt() {
    fprintf(stderr, "[error]");
    exit(0);
}

void check(void* ptr) {
    if (ptr == 0) {
        halt();
    }
}

bool is_valid(const char* str) {
    int c = 0, i = 0;
    size_t size = strlen(str);
    for (i = 0; i < size; i++){
        if (str[i] == '(') c++;
        if (str[i] == ')') c--;
        if (c < 0) return false;
    }
    return c == 0;
}

size_t f(char** in, char** out, size_t length) {
    size_t size = 0, i = 0;
    for (i = 0; i < length; i++) {
        if (is_valid(in[i])) {
            out[size] = in[i];
            size++;
        }
    }
    return size;
}

int main() {
    size_t size = 0, real_size = 20;
    char **array = (char**) malloc(sizeof(char*) * real_size);
    check(array);
    size_t i;
    char c[max_str_size];
    while (fgets(c, max_str_size, stdin) != 0){
        if ((strlen(c) > 0) && (c[strlen(c) - 1] == '\n'))
            c[strlen(c) - 1] = '\0';
        
        array[size] = (char*) malloc(sizeof(char) * (strlen(c) + 1));
        check(array[size]);
        strcpy(array[size], c);
        size++;
        // выделяем дополнительно память, если не хватает
        if (size == real_size) {
            real_size = size * 2;
            
            char** new_array = (char**) malloc(sizeof(char*) * real_size);
            check(new_array);
            memcpy(new_array, array, sizeof(char*) * size);
            free(array);
            array = new_array;
        }
    }
    if (size == 0) {
        halt();
    }
    
    char** out = (char**) malloc(sizeof(char*) * size);
    check(out);
    
    size_t out_size = f(array, out, size);
    
    for (i = 0; i < size; i++) {
        if (i < out_size) {
            printf("%s\n", out[i]);
        }
        
        free(array[i]);
    }
    free(array);
    free(out);
    return 0;
}