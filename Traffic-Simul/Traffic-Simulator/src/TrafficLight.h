#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"


class Vehicle;


template <class T>
class MessageQueue
{
public:
    void send(T &&msg);
    T receive();

private:
    std::deque<T> _queue;
    std::mutex _mutex;
    std::condition_variable _cond;
};


enum TrafficLightPhase{
    red,
    green
};

class TrafficLight : public TrafficObject
{
public:

    TrafficLight();

    TrafficLightPhase getCurrentPhase();

    void waitForGreen();
    void simulate();
    

private:

    void cycleThroughPhases();
    TrafficLightPhase _currentPhase;

    MessageQueue<TrafficLightPhase> _messageQueue;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif