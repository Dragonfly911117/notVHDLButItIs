// Lab7_mutax.cpp
#include <bits/stdc++.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>

using namespace std;

#include <bits/stdc++.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <mutex>

using namespace std;

string s;
mutex mtx;
constexpr unsigned PIN_12 = 392;
constexpr unsigned PIN_18 = 481;
constexpr unsigned PIN_21 = 428;
constexpr unsigned PIN_23 = 427;
vector<int> vec = {PIN_12, PIN_18, PIN_21, PIN_23};


void initGPIOThings();

int gpio_unexport(unsigned int gpio);

int gpio_set_dir(unsigned int gpio, string dir);

int gpio_export(unsigned int gpio);

int gpio_set_value(unsigned int gpio, const string &val);

void doThingsWiths();

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <timer>" << endl;
    return 1;
  }
  int notTimer = stoi(argv[1]); // in seconds
  vector<pair<string, string>> notTar;
  notTar.emplace_back("1100", "0011");
  notTar.emplace_back("1010", "0000");
  initGPIOThings();

  vector<thread> workers;
  for (const auto &i : notTar) {
    workers.emplace_back([](const int timer, const pair<string, string> &tar) {
      printf("{Enqueuing process: %lld }\n", this_thread::get_id());
      mtx.lock();
      cout << "Entering process: " << this_thread::get_id() << endl;
      for (int i = 0; i < timer; ++i) {
        s = tar.first;
        doThingsWiths();
        sleep(1);
        s = tar.second;
        doThingsWiths();
        sleep(1);
      }
      cout << "Leaving process: " << this_thread::get_id() << endl << endl;
      mtx.unlock();
    }, notTimer, i);
  }
  for (auto &i : workers) {
    i.join();
  }
  // unexport the gpio pins
  for (auto &i : vec) {
    gpio_unexport(i);
  }
  
    return 0;
}

void initGPIOThings() {
    for (auto &i: vec) {
        gpio_export(i);
        gpio_set_dir(i, "out");
        gpio_set_value(i, "0");
    }
}


void doThingsWiths() {
  
    printf((s+"\n").c_str() ); 
    for (int i = 0; i < 4; ++i) {
        gpio_set_value(vec[i], s.substr(i, 1));
    }
}


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

int gpio_set_value(unsigned int gpio, const string &val) {
    int fd;
    char buf[64];

    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

    fd = open(buf, sizeof(buf));

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/set-value");
        return fd;
    }
    write(fd, val.c_str(), 2);

    close(fd);
    return 0;
}