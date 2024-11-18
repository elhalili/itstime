#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_PATH 512

int parse_time(char *str_time);
int init_alarm_sound(char *path, char *cmd);
int alarm_ae(char *cmd);

int main(int argc, char **argv) {

  if (argc < 3) {
    fprintf(stderr, "itstime: missing arguments\n");
    fprintf(stderr, "Usage: itstime HH:MM:SS [path]\n");

    exit(1);
  }

  char *time_str = argv[1];
  char *alarm_music = argv[2];
  char cmd[MAX_PATH + 6] = {0};

  if (init_alarm_sound(alarm_music, cmd) == -1) {
    fprintf(stderr, "Error: Can not the alarm sound\n");
    exit(1);
  }

  int secs = parse_time(time_str);
  if (secs == -1) {
    fprintf(stderr, "Failed to parse time.\n");
    exit(1);
  }
  sleep(secs);

  if (alarm_ae(cmd) == -1) {
    fprintf(stderr, "Failed to play alarm sound.\n");
    exit(1);
  }

  return 0;
}

int init_alarm_sound(char *path, char *cmd) {
  if (strcmp(path + strlen(path) - 3, "wav")) {
    return -1;
  }

  if (access(path, F_OK)) {
    return -1;
  }

  strcat(cmd, "aplay ");
  strcat(cmd, path);

  return 0;
}

int parse_time(char *str_time) {
  if (strlen(str_time) != 8) {
    return -1;
  }

  char hours[3], minutes[3], seconds[3];
  *(str_time + 2) = 0;
  *(str_time + 5) = 0;

  strcpy(hours, str_time);
  hours[2] = '\0';

  strcpy(minutes, str_time + 3);
  minutes[2] = '\0';

  strcpy(seconds, str_time + 6);
  seconds[2] = '\0';

  int secs = atoi(seconds);
  secs += atoi(minutes) * 60;
  secs += atoi(hours) * 3600;

  if (secs <= 0) {
    return -1;
  }

  return secs;
}

int alarm_ae(char *cmd) {
  printf("It's time ;) \n");
  int res = system(cmd);

  return res;
}
