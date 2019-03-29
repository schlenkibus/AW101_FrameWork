#pragma once
#include <vector>
#include <functional>

template <class T>
class Trackable {
public:
    typedef std::function<void(T*)> tCallback;
    void registerCallback(tCallback);
    void onChange();
protected:
    std::vector<tCallback> m_callbacks;
};

template<class T>
void Trackable<T>::registerCallback(Trackable::tCallback cb) {
    m_callbacks.emplace_back(cb);
}

template<class T>
void Trackable<T>::onChange() {
    for(auto& cb: m_callbacks) {
        cb((T*)this);
    }
}


