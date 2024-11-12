#ifndef UTILS_H
#define UTILS_H

#include <string>

void clearScreen();
void displayLoadingBar(const std::string& message);
void displayWelcomeBanner();
void slowPrint(const std::string& text, int delay = 30);

#endif