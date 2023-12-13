#include<mutex>
#include<condition_variable>
#include<thread>
#include<iostream>

class ReadersWriters
{
    private:
        std::mutex mutext_t_;
        std::condition_variable cv_t;
        int readers = 0;
        bool writer = false;
    public:
        void startRead()
        {
            std::unique_lock<std::mutex> lock(mutext_t_);
            cv_t.wait(lock, [this](){return !writer;});
            ++readers;
        }
        void endRead()
        {
            std::unique_lock<std::mutex> lock(mutext_t_);
            --readers;
            if(readers == 0)
                cv_t.notify_all();
        }
        void startWrite()
        {
            std::unique_lock<std::mutex> lock(mutext_t_);
            cv_t.wait(lock, [this]()
                      { return !writer && readers == 0; });
            writer = true;
        }
        void endWrite()
        {
            std::unique_lock<std::mutex> lock(mutext_t_);
            writer = false;
            cv_t.notify_all();
        }
};
int main()
{
    ReadersWriters rw;
    std::thread t1([&rw]()
                   {
                      rw.startRead();
                      std::cout << "Thread 1: start read" << std::endl;
                      std::this_thread::sleep_for(std::chrono::seconds(1));
                      std::cout << "Thread 1: end read" << std::endl;
                      rw.endRead();
                  });
    std::thread t2([&rw]()
                   {
                      rw.startRead();
                      std::cout << "Thread 2: start read" << std::endl;
                      std::this_thread::sleep_for(std::chrono::seconds(1));
                      std::cout << "Thread 2: end read" << std::endl;
                      rw.endRead(); });
    std::thread t3([&rw]()
                   { rw.startWrite();
                     std::cout << "Thread 3: start write" << std::endl;
                     std::this_thread::sleep_for(std::chrono::seconds(1));
                     std::cout << "Thread 3: end write" << std::endl;
                     rw.endWrite(); });
    std::thread t4([&rw]() {
        rw.startWrite();
        std::cout << "Thread 4: start write" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thread 4: end write" << std::endl;
        rw.endWrite();
    });
    t1.join();
    t2.join();

    t3.join();
    t4.join();
    return 0;
}
