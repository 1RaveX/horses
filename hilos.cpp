#include<iostream>
#include<thread>
#include <mutex>
std::mutex mtx;

void printMessageData(int count) {
    for (int i = 0; i < count; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << i << "\n";
    }
}

int main() {
    std::thread t1(printMessageData, 5);
    std::thread t2(printMessageData, 5);
    std::thread t3(printMessageData, 5);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}