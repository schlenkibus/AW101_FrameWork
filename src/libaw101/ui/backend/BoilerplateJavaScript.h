#pragma once
#include "../Intermediate/JavaScript.h"

class BoilerplateJavaScript : public JavaScript {
public:
    BoilerplateJavaScript() { computeNode(); };
    const std::string getScriptContent() const override;
};


