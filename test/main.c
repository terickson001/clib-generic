#define _LIB_IMPLEMENTATION
#include "../lib.h"

#include <stdio.h>

HASHMAP(Foo, foo, int);

int array_test()
{
    printf("### ARRAY TEST (START) ###\n\n");
    Array(int) arr;
    array_init(&arr);

    printf("array_capacity: %d\n", array_capacity(arr));
    printf("array_size: %d\n", array_size(arr));

    for (int i = 0; i < 25; i++)
        array_append(&arr, i);

    for (int i = 0; i < array_size(arr); i++)
        printf("Reading %d\n", arr[i]);

    array_free(arr);
    
    printf("\n### ARRAY TEST (END) ###\n");
    
    return 0;
}

int hashmap_test()
{
    printf("### HASHMAP TEST (START) ###\n\n");
    Foo_Map map = {0};
    foo_map_init(&map);

    for (int i = 1; i < 256; i *= 2)
    {
        printf("Adding %d\n", i);
        foo_map_set(&map, hash_crc64(&i, sizeof(int)), i);
    }
    
    for (int i = 1; i < 256; i *= 2)
        printf("Reading %d: %d\n", i, *foo_map_get(&map, hash_crc64(&i, sizeof(int))));

    printf("\n### HASHMAP TEST (END) ###\n");
    return 0;
}

int file_test()
{   
    printf("### FILE TEST (START) ###\n\n");
    
    File file;
    FileError res = file_open(&file, "test.txt");
    if (res != FileError_NONE)
        printf("There was an error opening file 'test.txt'\n");

    printf("File size: %ld\n", get_file_size(&file));
    
    char foo[4];
    char bar[4];
    char baz[4];
    file_read(&file, foo, 4);
    file_read(&file, bar, 4);
    file_read(&file, baz, 4);
    foo[3] = 0;
    bar[3] = 0;
    baz[3] = 0;
    printf("Line 1: %s\n", foo);
    printf("Line 2: %s\n", bar);
    printf("Line 3: %s\n", baz);

    file_seek(&file, 0);

    char *line = 0;
    file_get_line(&file, &line, 0);
    printf("\nLine 1: %s\n", line);
    free(line); line = 0;
    file_get_line(&file, &line, 0);
    printf("Line 2: %s\n", line);
    free(line); line = 0;
    file_get_line(&file, &line, 0);
    printf("Line 3: %s\n", line);
    free(line);

    file_close(&file);
    
    FileContents fc = get_file_contents("test.txt");
    printf("File Contents: \n\"\"\"\n%s\n\"\"\"\n", (char *)fc.data);
    printf("\n### FILE TEST (END) ###\n");
    return 0;
}

int main(int argc, char **argv)
{
    int arr_test_result = array_test();
    //    int hash_test_result = hashmap_test();
    int file_test_result = file_test();
    
    return arr_test_result + file_test_result;
}
