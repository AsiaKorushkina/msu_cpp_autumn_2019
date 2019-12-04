#include "ThreadPool.h"
#include<cassert>
using namespace std;


int main()
{ 
    size_t size = 10;
    ThreadPool pool(size);
    std::vector<std::future<int>> res;

    for(int i = 0; i < size; ++i) {
        res.emplace_back(
            pool.exec([i] {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return i*i + 1;
            })
        );
    }

    for(size_t i = 0; i < size; i++){
        std::cout << res[i].get()<<' ';
    }
    
    return 0;
}