/*
 * Google blacklist mapping
 * Marshall Whittaker / oxagast
 */

//    __ _  _  __   ___  __  ____ ____ 
//   /  ( \/ )/ _\ / __)/ _\/ ___(_  _)
//  (  O )  (/    ( (_ /    \___ \ )(  
//   \__(_/\_\_/\_/\___\_/\_(____/(__)

// g++ src/main.cpp src/googet.cpp -o googet -lcurl --std=gnu++11

#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <vector>

std::vector<std::string> googet(std::string sub_query);

int main (int argc, char *argv[]) {
    if (argc == 2) {
    std::string query = argv[1];
    std::vector<std::string> suggestions = googet(query);
    for (int current_suggestion = 0; current_suggestion < suggestions.size(); current_suggestion++) {
        std::cout << suggestions[current_suggestion] << std::endl;
    }
    return (0);
    }
    return (1);
}