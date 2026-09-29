#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void search_file(char opt, char *filename, char *pattern) {
FILE *fp = fopen(filename, "r");
if(!fp) {
printf("Cannot open file %s\n", filename);
return;
}
char line[512];
int line_num = 0, count = 0, found_first = 0;
while(fgets(line, sizeof(line), fp)) {
line_num++;
char *pos = strstr(line, pattern);
if(pos) {
count++;
if(opt == 'f' && !found_first) {
printf("First occurrence at line %d: %s", line_num, line);
found_first = 1;
break;
} else if(opt == 'a') {
printf("Line %d: %s", line_num, line);
}
}
}
fclose(fp);
if(opt == 'f' && !found_first) printf("Pattern '%s' not found in %s\n", pattern, filename);
if(opt == 'c') printf("Pattern '%s' occurred %d times in %s\n", pattern, count, filename);
}
int main() {
char line[256];
char *args[32];
while(1) {
printf("$ ");
fflush(stdout);
if(!fgets(line, sizeof(line), stdin)) break;
line[strcspn(line, "\n")] = 0;
if(strlen(line) == 0) continue;
int argc = 0;
char *token = strtok(line, " ");
while(token != NULL && argc < 31) {
args[argc++] = token;
token = strtok(NULL, " ");
}
args[argc] = NULL;
if(argc == 0) continue;
if(strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) break;
if(strcmp(args[0], "search") == 0) {
if(argc < 4) {
printf("Usage: search <f|a|c> <filename> <pattern>\n");
} else {
search_file(args[1][0], args[2], args[3]);
}
continue;
}
pid_t pid = fork();
if(pid == 0) {
execvp(args[0], args);
perror("Execution failed");
exit(1);
} else if(pid > 0) {
wait(NULL);
} else {
perror("Fork failed");
}
}
return 0;
}
