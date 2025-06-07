#include "informationDisplay.h"


informationDisplay::informationDisplay()
    : lcd(0x27, 16, 2)
{}

void informationDisplay::begin() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void informationDisplay::clear() {
    lcd.clear();
}

void informationDisplay::setCursor(int col, int row) {
    lcd.setCursor(col, row);
}

void informationDisplay::display(int value) {
    lcd.print(value);
}

void informationDisplay::display(const String& text) {
    lcd.print(text);
}

void informationDisplay::displayLuminosity(int luminosityValue) {
    this->display(luminosityValue);
    this->display(" lux");
}