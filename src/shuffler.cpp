/*
 * Google blacklist mapping
 * Marshall Whittaker / oxagast
 */

//    __ _  _  __   ___  __  ____ ____
//   /  ( \/ )/ _\ / __)/ _\/ ___(_  _)
//  (  O )  (/    ( (_ /    \___ \ )(
//   \__(_/\_\_/\_/\___\_/\_(____/(__)

// g++ src/shuffler.cpp src/googet.cpp -o shuffler -lcurl --std=gnu++11

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <ctime>
#include <stdexcept>
#include <iterator>
#include <random>

std::vector<std::string> googet(std::string sub_query);

int rand_int(int i) { return std::rand()%i;}

std::vector<std::string> search_for(std::string query, int letters) {
  int current_suggestion;
  std::vector<std::string> suggestions;
  suggestions.clear();
  suggestions = googet(query.substr(0, letters));
  for (current_suggestion = 0; current_suggestion < suggestions.size();
       current_suggestion++) {
      if (suggestions.size() > 0) {
    std::cout << "Chars: " << letters << " : " << query.substr(0, letters)
              << " : " << suggestions[current_suggestion] << std::endl;
      }
  }
  return (suggestions);
}

int rand_range(int rand_from, int rand_to) {
  std::random_device rd;
  std::default_random_engine generator(rd()); // seed random
  std::uniform_int_distribution<int> distribution(rand_from,
                                                  rand_to); // get a random
  auto roll = std::bind(distribution,
                        generator); // bind it so we can do it multiple times
  return (roll());
}

int main ( int argc, char *argv[]) {
  if (argc == 2) {
  std::srand ( unsigned ( std::time(0) ) );
  std::vector<std::string> list;
  std::ifstream qfile(argv[1]);
  std::copy(std::istream_iterator<std::string> (qfile),
  std::istream_iterator<std::string>(),
    back_inserter(list));
  while (42) {
  std::random_shuffle (list.begin(), list.end());
  std::string query = list[0] + " " + list[1] + " " + list[2];
      std::cout << "Query is to be: " << query.length() << " : " <<
    query << std::endl << std::endl;
    std::vector<std::string> sub_query_result;
    /* loop around each letter */
    for (int letters = 1; letters <= query.length(); letters++) {
      search_for(query, letters);
    }

 }
 std::cerr << "This shouldn't happen." << std::endl;
     return (1);
}
std::cerr << "Provide a file with a list of words or phrases." <<
std::endl << argv[0] << " wordlist" << std::endl;
return (1);
}
