/*
Copyright (C) 2016       Javid Karimbayli karimbayli@javid.ws
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
/* C code .  The program scans the files and collects all the files in a txt file called sum.txt. In this way = 1 txt file in folder is the one line in sum.txt.  */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define green "\x1B[32m"
static void scan_dir(const char *dir)
{
    struct dirent * entry;
    DIR *d = opendir( dir );
    int id_of_file= 10000;
    char count[5];
    char t[2] ="t";
    char id[7];
    FILE *fp = fopen("sum.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file for write!\n");
        exit(1);
    }


    if (d == 0) {
        perror("opendir");
        return;
    }


    while ((entry = readdir(d)) != 0) {
        //printf("%s\n", entry->d_name);

        if( access( entry->d_name, F_OK ) != -1 ) {
          printf("%s NOT OK\n",entry->d_name);
        } else {
            printf("%s OK\n",entry->d_name);

            sprintf(count, "%d", id_of_file);
            strcpy(id, t);
            strcat(id,count);
            fprintf(fp,"%s ", id);
            char str[999999];
            char name[80];
            //char link[10] ="test/";
            strcpy(name,dir);
            strcat(name, "/");
            strcat (name,entry->d_name);
            FILE *f = fopen(name, "r+");

            while(fgets(str, 255, (FILE*) f)) {
                printf("%s", str);
                char *p = str;
                while (isspace(*p)) // skip whitespace
                p++;
                printf("%s", p);

                        char *r;
                        if ((r = strchr(p, '\r')) != NULL || (r = strchr(p, '\n')) != NULL || (r = strchr(p, '\t')) != NULL || (r = strchr(p, '\b')) != NULL || (r = strchr(p, '\v')) != NULL)
                            *r = '\0';  /* Clears carriage return */
                        fprintf(fp, "%s", p);

            }
            fprintf(fp, "\n");
            fclose(f);
            id_of_file++;
            printf("######################\n");


        }
    }
    closedir(d);
    fclose(fp);
}


int main(int argc, char ** argv)
{
    if(argv[1]==NULL){
      printf("give the name of folder\n");
      exit(0);
    }
    scan_dir(argv[1]);
    printf("\033[32;1m-----DATASET FILE IS DONE-----\033[0m\n");
    return 0;
}
