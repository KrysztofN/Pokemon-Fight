#include "../headers/utils.h"
#include <iostream>
#include <thread>
#include <chrono>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayLoadingBar(const std::string& message) {
    std::cout << message;
    for(int i = 0; i < 20; i++) {
        std::cout << " ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Done!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void displayWelcomeBanner() {
    std::cout << R"(
    ██████╗  ██████╗ ██╗  ██╗███████╗███╗   ███╗ ██████╗ ███╗   ██╗
    ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝████╗ ████║██╔═══██╗████╗  ██║
    ██████╔╝██║   ██║█████╔╝ █████╗  ██╔████╔██║██║   ██║██╔██╗ ██║
    ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██║╚██╔╝██║██║   ██║██║╚██╗██║
    ██║     ╚██████╔╝██║  ██╗███████╗██║ ╚═╝ ██║╚██████╔╝██║ ╚████║
    ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
    )" << '\n';
    std::cout << "=================== ADVENTURE AWAITS! ===================\n\n";
}

void slowPrint(const std::string& text, int delay = 30){
    for(char c: text){
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << std::endl;
}