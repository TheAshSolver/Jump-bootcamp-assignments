#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>
#include<iterator>
#include<concepts>
#include<cctype>

template <std::input_iterator Iterator, std::indirect_unary_predicate<Iterator> UnaryPred>

std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  std::vector<std::string::iterator> x  = find_all(source.begin(), source.end(), [](auto &x){return std::isspace(static_cast<unsigned char >(x));});
  Corpus my_corpus;
  std::transform(x.begin(), x.end()-1, x.begin()+1, std::inserter(my_corpus, my_corpus.end()), [&source](auto& x1, auto& x2){return Token(source, x1, x2);});
  std::erase_if(my_corpus, [](const Token &token){
    return token.content.empty();
  });
  return my_corpus;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  auto view = source  | std::ranges::views::filter([&dictionary](const Token &token){return !dictionary.contains(token.content);})
                      | std::ranges::views::transform([&dictionary](const Token &token){
                      std::set<std::string> strings;
                      std::for_each(dictionary.begin(), dictionary.end(), [ &token,  &strings](const std::string &word){
                        if(levenshtein(word, token.content)==1){
                          strings.insert(word);
                        }
                      });
                     return Misspelling{token, strings};
                    })
                    | std::ranges::views::filter([](const Misspelling &mispelling){
                      return !mispelling.suggestions.empty();
                    });
  return std::set<Misspelling>(view.begin(), view.end());

};

/* Helper methods */

#include "utils.cpp"