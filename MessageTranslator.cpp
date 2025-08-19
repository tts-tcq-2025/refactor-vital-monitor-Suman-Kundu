#include "MessageTranslator.h"

MessageTranslator::MessageTranslator() { initializeMessages(); }

void MessageTranslator::initializeMessages() {
    // Temperature messages
    messages[{ConditionType::HYPO_THERMIA, Language::ENGLISH}] = "Temperature is critical!";
    messages[{ConditionType::HYPO_THERMIA, Language::GERMAN}] = "Temperatur ist kritisch!";
    messages[{ConditionType::NEAR_HYPO, Language::ENGLISH}] = "Warning: Approaching hypothermia";
    messages[{ConditionType::NEAR_HYPO, Language::GERMAN}] = "Warnung: Annäherung an Unterkühlung";
    messages[{ConditionType::NEAR_HYPER, Language::ENGLISH}] = "Warning: Approaching hyperthermia";
    messages[{ConditionType::NEAR_HYPER, Language::GERMAN}] = "Warnung: Annäherung an Überhitzung";
    messages[{ConditionType::HYPER_THERMIA, Language::ENGLISH}] = "Temperature is critical!";
    messages[{ConditionType::HYPER_THERMIA, Language::GERMAN}] = "Temperatur ist kritisch!";
    
    // Pulse rate messages
    messages[{ConditionType::BRADYCARDIA, Language::ENGLISH}] = "Pulse Rate is critical!";
    messages[{ConditionType::BRADYCARDIA, Language::GERMAN}] = "Pulsfrequenz ist kritisch!";
    messages[{ConditionType::NEAR_BRADY, Language::ENGLISH}] = "Warning: Approaching bradycardia";
    messages[{ConditionType::NEAR_BRADY, Language::GERMAN}] = "Warnung: Annäherung an Bradykardie";
    messages[{ConditionType::NEAR_TACHY, Language::ENGLISH}] = "Warning: Approaching tachycardia";
    messages[{ConditionType::NEAR_TACHY, Language::GERMAN}] = "Warnung: Annäherung an Tachykardie";
    messages[{ConditionType::TACHYCARDIA, Language::ENGLISH}] = "Pulse Rate is critical!";
    messages[{ConditionType::TACHYCARDIA, Language::GERMAN}] = "Pulsfrequenz ist kritisch!";
    
    // SPO2 messages
    messages[{ConditionType::HYPOXEMIA, Language::ENGLISH}] = "Oxygen Saturation is critical!";
    messages[{ConditionType::HYPOXEMIA, Language::GERMAN}] = "Sauerstoffsättigung ist kritisch!";
    messages[{ConditionType::NEAR_HYPOXEMIA, Language::ENGLISH}] = "Warning: Approaching hypoxemia";
    messages[{ConditionType::NEAR_HYPOXEMIA, Language::GERMAN}] = "Warnung: Annäherung an Hypoxämie";
    messages[{ConditionType::HYPEROXEMIA, Language::ENGLISH}] = "Oxygen Saturation is critical!";
    messages[{ConditionType::HYPEROXEMIA, Language::GERMAN}] = "Sauerstoffsättigung ist kritisch!";
}

std::string MessageTranslator::getMessage(ConditionType condition, Language lang) const {
    auto key = std::make_pair(condition, lang);
    auto it = messages.find(key);
    return (it != messages.end()) ? it->second : "Unknown condition";
}
