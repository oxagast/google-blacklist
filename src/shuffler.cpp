/*
 * Google blacklist mapping
 * Marshall Whittaker / oxagast
 */

//    __ _  _  __   ___  __  ____ ____
//   /  ( \/ )/ _\ / __)/ _\/ ___(_  _)
//  (  O )  (/    ( (_ /    \___ \ )(
//   \__(_/\_\_/\_/\___\_/\_(____/(__)

// g++ src/frontend.cpp src/googet.cpp -o googet -lcurl --std=gnu++11

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
#include<stdexcept>
#include <iterator>

int rand_int(int i) { return std::rand()%i;}

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
  std::srand ( unsigned ( std::time(0) ) );
  std::vector<std::string> list;
  std::ifstream qfile(argv[1]);
  std::copy(std::istream_iterator<std::string> (qfile),
    std::istream_iterator<std::string>(),
    back_inserter(list));
 while (true) {
  std::random_shuffle (list.begin(), list.end());
  std::string part_one = list[0];
  std::string part_two = list[1];
  std::string part_three = list[2];
  std::string whole = "./googet \"" + part_one + " " + part_two + " " + part_three + "\"";
  system(whole.c_str());
 }
}