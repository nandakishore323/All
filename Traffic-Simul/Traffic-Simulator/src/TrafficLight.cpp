#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // lock and wait to retrieve the message, and return the message
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_queue.empty(); });

    // dequeue
    T msg = std::move(_queue.back());
    _queue.clear();

    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // queue up the message.
    std::lock_guard<std::mutex> gLock(_mutex);
    _queue.push_back(std::move(msg));
    _cond.notify_one();
}



TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // Once it receives TrafficLightPhase::green, the method returns.
    while (true) {
        TrafficLightPhase phase = _messageQueue.receive();
        if (phase == TrafficLightPhase::green)
            return;
    }
}


TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    
    threads.emplace_back( std::thread(&TrafficLight::cycleThroughPhases, this) );
}



// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{

    // a cycleTime is set, that toggles between red and green, and update the message queue. 

    float cycleTime = 5;

    auto start = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed;

    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        elapsed = std::chrono::high_resolution_clock::now() - start;

        if(elapsed.count()>cycleTime){
            start = std::chrono::high_resolution_clock::now();

            _currentPhase = (_currentPhase==green) ? red : green;

            TrafficLightPhase p = _currentPhase;
            _messageQueue.send(std::move(p));
        }
    }
}

