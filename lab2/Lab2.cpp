//
// Created by df on 3/10/23.
//
#include "../Pins.h"
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
/*
LEDs:
    12
    18
    19
    23
*/

using namespace std;

int gpio_unexport(unsigned int gpio) {
  int fd, len;
  char buf[64];

  fd = open("/sys/class/gpio/unexport", O_WRONLY);
  if (fd < 0) {
    perror("gpio/unexport");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%d", gpio);
  write(fd, buf, len);
  close(fd);
  return 0;
}

int gpio_export(unsigned int gpio) {
  int fd, len;
  char buf[64];

  fd = open("/sys/class/gpio/export", O_WRONLY);
  if (fd < 0) {
    perror("gpio/export");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%d", gpio);
  write(fd, buf, len);
  close(fd);
  return 0;
}

int gpio_set_dir(unsigned int gpio, string dir) {
  int fd;
  char buf[64];

  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

  fd = open(buf, sizeof(buf));

  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("gpio/direction");
    return fd;
  }

  if (dir == "out") {
    write(fd, "out", 4);
  } else {
    write(fd, "in", 3);
  }
  close(fd);
  return 0;
}

int gpio_set_value(unsigned int gpio, int val) {
  int fd;
  char buf[64];

  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

  fd = open(buf, sizeof(buf));

  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("gpio/set-value");
    return fd;
  }

  if (val == 0) {
    write(fd, "0", 2);
  } else {
    write(fd, "1", 2);
  }
  close(fd);
  return 0;
}

int main(int argc, char *argv[]) {
  vector<vector<int>> vec = {{PIN_12, PIN_18}, {PIN_21, PIN_23}};
  string str(argv[1]);
  if (str == "Mode_Shine") {
    for (auto &i : vec) {
      for (auto &j : i) {
        gpio_export(j);
        gpio_set_dir(j, "out");
        gpio_set_value(j, 0);
      }
    }
    int cnt = (argv[2][0] - '0') * 2;
    while (cnt--) {
      for (auto i : vec[0]) {
        gpio_set_value(i, (cnt % 2 == 0) ? 0 : 1);
      }
      for (auto i : vec[1]) {
        gpio_set_value(i, (cnt % 2 == 0) ? 1 : 0);
      }
      sleep(1);
    }
    for (auto &i : vec) {
      for (auto &j : i) {
        gpio_unexport(j);
      }
    }
  } else {
    int led = argv[1][3] - 49;
    str = string(argv[2]);
    gpio_export(led);
    gpio_set_dir(led, "out");
    gpio_set_value(vec[led / 2][led % 2], str == "ON" ? 1 : 0);
    gpio_unexport(led);
  }
}