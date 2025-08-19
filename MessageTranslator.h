#pragma once
#include "VitalTypes.h"
#include <map>
#include <string>

class MessageTranslator {
private:
    std::map<std::pair<ConditionType, Language>, std::string> messages;
    void initializeMessages();

public:
    MessageTranslator();
    std::string getMessage(ConditionType condition, Language lang) const;
};
