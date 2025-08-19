#include "LanguageManager.h"

Language LanguageManager::currentLanguage = Language::ENGLISH;

void LanguageManager::setLanguage(Language lang) {
    currentLanguage = lang;
}

Language LanguageManager::getCurrentLanguage() {
    return currentLanguage;
}
