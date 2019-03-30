#pragma once
#include "Control.h"
#include <memory>

class AW101Layout;

class Container : public Control {
public:
    explicit Container(AW101Layout* parent);

    void computeNode() override;

    void addChild(std::unique_ptr<Control>&& ptr) {
        m_children.emplace_back(std::move(ptr));
        computeNode();
    }
    const std::vector<std::unique_ptr<Control>>& getChildren() const;
protected:
    std::vector<std::unique_ptr<Control>> m_children;
};


