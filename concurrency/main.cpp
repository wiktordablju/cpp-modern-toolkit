#include <iostream>
#include <future>
#include <string>
#include <thread>

unsigned int draw(const std::string str, const unsigned int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << str << std::endl;
    }
    return count;
}

void draw_prom(const std::string str, const unsigned int count, std::promise<unsigned int>& p) {
    for (int i = 0 ; i < count ; ++i) {
        std::cout << str << std::endl;
    }
    p.set_value(count);
}

void add_4_prom(const int a, const int b, const int c, const int d, std::promise<int> p) {
    int sum = a + b + c + d;
    p.set_value(sum);
}


int sum(int a, int b) {
    return a + b;
}

int main() {
 
    // Async results
    std::cout << "Async results" << std::endl;
    auto w1 = std::async(std::launch::async, draw, "2", 2);
    auto w2 = std::async(std::launch::async, draw, "1", 1);
    auto w3 = std::async(std::launch::async, draw, "3", 3);
    auto w4 = std::async(std::launch::async, draw, "7", 7);

    int sum = w1.get() + w2.get() + w3.get() + w4.get();
    std::cout << "Suma: " << sum << std::endl;
    std::cout << "------" << std::endl;

    // Promises
    std::cout << "Promises" << std::endl;
    std::promise<unsigned int> p1;
    std::future<unsigned int> f1 = p1.get_future();
    std::promise<unsigned int> p2;
    std::future<unsigned int> f2 = p2.get_future();
    std::promise<unsigned int> p3;
    std::future<unsigned int> f3 = p3.get_future();
    std::promise<unsigned int> p4;
    std::future<unsigned int> f4 = p4.get_future();

    std::thread t1(draw_prom, "2", 2, std::ref(p1));
    std::thread t2(draw_prom, "1", 1, std::ref(p2));
    std::thread t3(draw_prom, "3", 3, std::ref(p3));
    std::thread t4(draw_prom, "7", 7, std::ref(p4));

    std::promise<int> p5;
    std::future<int> f5 = p5.get_future();

    std::thread t5(add_4_prom, f1.get(), f2.get(), f3.get(), f4.get(), std::move(p5));

    std::cout << "Suma: " << f5.get() << std::endl;

    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    std::cout<< "--------" << std::endl;

    // Packaged calls
    std::cout << "Packaged calls" << std::endl;
    std::packaged_task<int(int, int)> task_local(::sum);
    std::future<int> f_local = task_local.get_future();
    task_local(2, 3);

    std::packaged_task<int(int, int)> task_thread(::sum);
    std::future<int> f_thread = task_thread.get_future();
    std::thread t6(std::move(task_thread), 5, 10);

    std::cout << "Wynik lokalnie: " << f_local.get() << std::endl;
    std::cout << "Wynik na threadzie: " << f_thread.get() << std::endl;

    t6.join();
    
    std::cout<< "--------" << std::endl;


    return 0;
}