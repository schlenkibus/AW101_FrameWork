#pragma once
#include "Control.h"
#include <memory>

class AW101Layout;

class Container : public Control {
public:
    explicit Container(AW101Layout* parent);

    void computeNode() override;

    template<class T, typename ... tArgs>
    T* addChild(tArgs ... args);
    std::vector<std::unique_ptr<Control>> & getChildren();

    template<class T>
    T *getControlById(const std::string &id);

protected:
    std::vector<std::unique_ptr<Control>> m_children;
};

template<class T, typename ... tArgs>
T* Container::addChild(tArgs... args) {
    m_children.emplace_back(std::make_unique<T>(args...));
    return dynamic_cast<T*>(m_children.back().get());
}

template<class T>
T *Container::getControlById(const std::string &id) {
    for(auto& c: m_children) {
        if(c->getID().id == id)
            return dynamic_cast<T*>(c.get());
    }
    return nullptr;
}


