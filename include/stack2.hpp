// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>

#ifndef INCLUDE_STACK2_HPP_
#define INCLUDE_STACK2_HPP_

#include <iostream>

template <typename T>
struct Element1{
    T value;
    Element1<T>* previous;
};
template <typename T>
class stack1
{
public:
    stack1(){
        _top = nullptr;
        count = 0;
    }
    ~stack1(){
        while (count) {
            Element1<T>* _local = _top->previous;
            delete _top;
            _top = _local;
            --count;
        }
        delete _top;
    }
    void push(T&& value){
        auto* new_elem = new Element1<T>;
        new_elem->previous = _top;
        new_elem->value = value;
        _top = new_elem;
        ++count;
    }
    void push(const T& value){
        auto* new_elem = new Element1<T>;
        new_elem->previous = _top;
        new_elem->value = value;
        _top = new_elem;
        ++count;
    }
    void pop(){
        if (count) {
            Element1<T>* stakan;
            stakan = _top;
            std::cout << _top->value << std::endl;
            _top = _top->previous;
            delete stakan;
            --count;
        } else {
            std::cout << "Stack is empty!" << std::endl;
        }
    }
    const T& head() const{
        return _top->value;
    }
    Element1<T>* _top;
    unsigned count;
};

#endif //INCLUDE_STACK2_HPP_
