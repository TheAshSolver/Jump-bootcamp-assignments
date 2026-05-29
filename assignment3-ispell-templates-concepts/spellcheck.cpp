#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>
#include<cctype>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  std::vector<std::string::iterator> x  = find_all(source.begin(), source.end(), [](auto &x){return std::isspace(static_cast<unsigned char >(x));});
  Corpus my_corpus;
  std::transform(x.begin(), x.end()-1, x.begin()+1, std::inserter(my_corpus, my_corpus.end()), [&source](auto& x1, auto& x2){return Token(source, x1+1, x2);});
  std::erase_if(my_corpus, [](const Token &token){
    return token.content.empty();
  });
  return my_corpus;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  return std::set<Misspelling>();
};

/* Helper methods */

#include "utils.cpp"