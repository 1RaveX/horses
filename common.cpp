#include <iostream>


void hola() {
    std::cout << "hola como estamos" << std::endl;
}

template<typename T> void add(T &funct,T value, int nthreads) {
    for(auto i : nthreads) {
        std::thread t1(&funct, value);
        t1.join();
    }
}