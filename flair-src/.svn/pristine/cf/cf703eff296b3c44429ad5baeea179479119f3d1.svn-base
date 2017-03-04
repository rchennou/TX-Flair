//  created:    17/12/2015
//  updated:    25/07/2016
//  filename:   CallbackTimer.h
//
//  author:     Milan Erdelj
//
//  version:    $Id: $
//
//  purpose:    Callback timer class (executing functions periodically)
//
//
/*********************************************************************/

#ifndef CALLBACKTIMER_H
#define CALLBACKTIMER_H

#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <iostream>

class CallbackTimer {
public:
    CallbackTimer() :_execute(false) {}

    ~CallbackTimer() {
        if(_execute.load(std::memory_order_acquire)) {
            stop();
        }
    }

    void stop() {
        _execute.store(false, std::memory_order_release);
        if(_thd.joinable()) _thd.join();
    }

    void start(uint64_t interval, std::function<void(void)> callback) {
        if(_execute.load(std::memory_order_acquire)) {
            stop();
        }
        _execute.store(true, std::memory_order_release);
        _thd = std::thread([this, interval, callback]() {
            while (_execute.load(std::memory_order_acquire)) {
                callback();
                std::this_thread::sleep_for(std::chrono::microseconds(interval));
            }
        });
    }

    bool is_running() const noexcept {
        return ( _execute.load(std::memory_order_acquire) && _thd.joinable() );
    }

private:
    std::atomic<bool> _execute;
    std::thread _thd;
};

#endif // CALLBACKTIMER_H
