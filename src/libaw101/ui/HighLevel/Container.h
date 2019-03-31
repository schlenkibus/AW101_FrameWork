#pragma once
#include "Control.h"
#include <memory>

class AW101Layout;

class Container : public Control {
public:
    explicit Container(AW101Layout* parent);

    void computeNode() override;

    Control * addChild(std::unique_ptr<Control> &&ptr) {
        m_children.emplace_back(std::move(ptr));
        onChange();
        return m_children.back().get();
    }
    std::vector<std::unique_ptr<Control>> & getChildren();

    Control *getControlById(std::string &id);

protected:
    std::vector<std::unique_ptr<Control>> m_children;
};


