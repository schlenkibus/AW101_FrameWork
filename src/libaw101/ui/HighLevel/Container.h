#pragma once
#include "Control.h"
#include <memory>

class AW101Layout;

class Container : public Control {
public:
    explicit Container(AW101Layout* parent);
    CTML::Node getNode() const override;

    void addChild(std::unique_ptr<Control>&& ptr) {
        m_children.emplace_back(std::move(ptr));
    }
    const std::vector<std::unique_ptr<Control>>& getChildren() const;
protected:
    std::vector<std::unique_ptr<Control>> m_children;
};


