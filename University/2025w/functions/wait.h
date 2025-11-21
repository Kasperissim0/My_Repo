#ifndef WAIT_H
#define WAIT_H

#include <thread>
#include <chrono>
void wait(unsigned seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds)); }

#endif