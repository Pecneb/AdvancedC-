#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <vector>

class Queue {
    std::list<std::string> elements;
public:
    void add(const std::string& s) { elements.push_back(s); }
    std::string get() {
        if (!elements.empty()) {
            std::string retval = elements.front();
            elements.pop_front();
            return retval;
        }
        else {
            // toltse ki! dobjon kivetelt!
            throw -1;
        }
    }
};

void producer(Queue* queue) {
    int numItemsToProducePerRound[5] = { 0, 2, 1, 0, 0 };
    for (int i = 0; i < 5; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (int j = 0; j < numItemsToProducePerRound[i]; j++) {
            queue->add("round " + std::to_string(i) + " - item " + std::to_string(j));
            std::cout << "Added to queue: " << ("round " + std::to_string(i) + " - item " + std::to_string(j)) << std::endl;
        }
    }
}

void consumer(Queue* queue) {
    // toltse ki! kapja el a fent dobott kivetelt es irja ki, hogy "nothing to consume"
    try {
        std::string val = queue->get();
        std::cout << "  --> consumed value: " << val << std::endl;
    } catch(int e) {
        std::cout << "nothing to consume" << std::endl;
    }
}

void f() {
    Queue myqueue;
    // toltse ki! 1 kodsor hianyzik, egy producerThread nevu szalat hozzon letre amely a producer fv-t futtatja
    std::thread producerThread(producer, &myqueue);
    for (int i = 0; i < 5; i++) {
        consumer(&myqueue);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    // toltse ki! producerThread-et be kell varni!
    producerThread.join();
}
