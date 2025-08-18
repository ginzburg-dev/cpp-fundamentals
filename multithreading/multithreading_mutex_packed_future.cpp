#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::mutex car1Mutex; // for locking driveCar
std::mutex car2Mutex; // for locking driveCar2

void driveCar(std::string name)
{
    std::unique_lock<std::mutex> carLock(car1Mutex);
    std::cout << name << " is driving car1\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << name << " is done driving car1\n";
    //carLock.unlock();
}

void driveCar2(std::string name)
{
    std::unique_lock<std::mutex> carLock(car2Mutex);
    std::cout << name << " is driving car2\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << name << " is done driving car2\n";
    //carLock.unlock(); - we're able to lock / unlock mutex inside a block's local scope
}

float filter_func(int chunk_size, int thread)
{
    std::cout << "Start filtering " << thread << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "End filtering " << thread << '\n';
    return static_cast<float>(thread * thread);
}

int main()
{
    std::cout << "Hardware concurrency: " << std::thread::hardware_concurrency() << '\n';
    std::thread t1(driveCar, "John");
    std::thread t2(driveCar, "Hannah");
    std::thread t3(driveCar2, "George");
    std::thread t4(driveCar2, "Kai");

    t1.join(); // Wait for t1
    std::cout << "-John joined()\n"; // Print it after t1 is done
    t2.join();
    std::cout << "-Hannah joined()\n";
    t3.join();
    std::cout << "-Georg joined()\n";
    t4.join();
    std::cout << "-Kai joined()\n";

    std::cout << "Finish\n";


    // std::packaged_task and std::future

    // Task bind
    std::packaged_task<float(int, int)> task_bind(filter_func);
    std::future<float> result_task_bind = task_bind.get_future();
    
    task_bind(10, 1);
    
    std::cout << "task_bind:\t" << result_task_bind.get() << '\n'; // get() waits untill the result is ready

    // Task thread
    std::packaged_task<float(int, int)> task_thread(filter_func);
    std::future<float> result_task_thread = task_thread.get_future();

    std::thread task_td(std::move(task_thread), 10, 2);

    task_td.join(); // wait
    std::cout << "task_td:\t" << result_task_thread.get() << '\n';
    
    return 0;
}
