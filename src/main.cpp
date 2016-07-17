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
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

std::vector<std::string> googet(std::string sub_query);

/*
 * this routine is a wrapper for looping around the suggestions
 * one letter at a time. it calls googet to make the https
 * requests to google.
 */
std::vector<std::string> search_for(std::string query, int letters) {
  int current_suggestion;
  std::vector<std::string> suggestions;

  suggestions = googet(query.substr(0, letters));
  for (current_suggestion = 0; current_suggestion < suggestions.size();
       current_suggestion++) {
    std::cout << "Chars: " << letters << " : " << query.substr(0, letters)
              << " : " << suggestions[current_suggestion] << std::endl;
  }
  return (suggestions);
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    std::string query = argv[1];
    std::vector<std::string> sub_query_result;
    /* loop around each letter */
    for (int letters = 1; letters <= query.length(); letters++) {
      sub_query_result = (search_for(query, letters));
    }
    return (0);
  }
  return (1);
}