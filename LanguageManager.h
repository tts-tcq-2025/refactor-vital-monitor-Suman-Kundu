#pragma once
#include "VitalTypes.h"

class LanguageManager {
private:
    static Language currentLanguage;

public:
    static void setLanguage(Language lang);
    static Language getCurrentLanguage();
};
