#include <dirent.h>
#include <libc.h>
int main(int argc, char **argv)
{
    DIR *dirp;
    struct dirent *dp;

    dirp = opendir(argv[1]);
    while ((dp = readdir(dirp)) != NULL)
        printf("%s\n", dp->d_name);
    closedir(dirp);
    return (0);
}