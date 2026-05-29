/*
 * Assignment 1: Marriage Pact
 * Adapted by Tinkercademy from Stanford CS106L
 * (originally by Haven Whitney, with modifications by Fabio Ibanez
 * & Jacob Roberts-Baca).
 *
 * Complete each STUDENT TODO below. Read the README carefully — the
 * requirements there (ranges, projections, sample, reserve, no raw
 * for-loops in find_matches, iterator-safe erase in run_mixer) are
 * part of the assignment, not optional polish.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

/**
 * Reads `filename` line by line and returns the applicants.
 *
 * Requirements:
 *   - Take `filename` as `const std::string&`.
 *   - Call `reserve()` before populating, with a sensible capacity.
 *     Justify your choice in short_answer.txt.
 */
std::vector<std::string> get_applicants(const std::string& filename) {
  // STUDENT TODO: Implement this function.
  std::vector<std::string> results;
  results.reserve(100000);
  std::ifstream filestream(filename, std::ios::in);
  if(!filestream.is_open()){
    throw std::runtime_error("File not opened");
    return results;
  }

  std::string current_line;
  while(std::getline(filestream, current_line)){
    results.push_back(current_line);
  }
  return results;


}

/**
 * Returns the initials of `name`, uppercased.
 *   e.g. initials("Marceline McMillan") == "MM"
 *
 * Requirements:
 *   - Parameter must be `std::string_view` (no allocation).
 */
std::string initials(std::string_view name) {
 
  std::string initial{""};
  const auto first_char = name.find_first_not_of(" ");
  if(first_char!=std::string_view::npos){
    initial+=std::toupper(name.at(first_char));
  const auto last_char = name.find(" ", first_char);
  if(last_char!=std::string_view::npos){
    initial+=std::toupper(name.at(last_char+1));
  }    


  }
 
  return initial;
}

/**
 * Returns every applicant in `students` who shares initials with `name`.
 *
 * Requirements:
 *   - No raw `for` loops. Use std::ranges::copy_if (or views::filter
 *     piped into a vector). Use a projection where it makes the call
 *     clearer.
 *   - Take `students` as `const std::vector<std::string>&`.
 */
std::vector<std::string> find_matches(std::string_view name, const std::vector<std::string>& students) {
    std::vector<std::string> results;
    results.reserve(10000);
    std::string user_initial = initials(name);
    std::ranges::copy_if(students, std::back_inserter(results),[user_initial](std::string student_initials){return student_initials == user_initial;} , initials);
    return results;
}

/**
 * Returns one randomly-chosen match, or "NO MATCHES FOUND." if empty.
 *
 * Requirements:
 *   - Use std::sample with a seeded std::mt19937.
 *   - Do NOT use pop_back() or rand() % size.
 */
std::string get_match(const std::vector<std::string>& matches) {
  if(matches.begin()==matches.end()){
    return "NO MATCHES FOUND.";
  }
  std::vector<std::string> result;
  std::sample(matches.begin(), matches.end(), std::back_inserter(result), 1, std::mt19937 {std::random_device{}()});
  return result.at(0);
}

/**
 * Runs a multi-round mixer. In each round, scan the remaining
 * applicants left-to-right; for each applicant, look for another
 * applicant with the same initials still in the pool. If found,
 * pair them, remove both from `applicants`, and record the pair.
 * Continue rounds until a full pass yields no new pairs.
 *
 * `applicants` is mutated: paired names are removed. Whatever is
 * left over at the end is unpaired.
 *
 * Requirements:
 *   - The naive "iterate and erase as you go" approach WILL invalidate
 *     your iterator. You must handle this — see the README for the
 *     three acceptable strategies — and document your choice in
 *     short_answer.txt.
 */
std::vector<std::pair<std::string, std::string>>
run_mixer(std::vector<std::string>& applicants) {
  std::vector<std::pair<std::string, std::string>> result;
  for(auto it = applicants.begin(); it!=applicants.end();){
    auto pair = std::find_if(it+1, applicants.end(), [it](std::string name){return initials(*it)==initials(name);});
    if(pair!=applicants.end()){
      result.push_back({*it, *pair});
      applicants.erase(pair);
      it = applicants.erase(it);
    }
    else{
      it++;
    }
  }
  return result;
}

/* #### Please don't remove this line! #### */
#include "tests/utils.hpp"
