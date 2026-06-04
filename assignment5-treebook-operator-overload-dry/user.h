/*
 * Assignment 4: TreeBook
 * Adapted by Tinkercademy from Stanford CS106L Assignment 5
 * (originally by Fabio Ibanez, with modifications by Jacob Roberts-Baca).
 */

#include <iostream>
#include <string>
#include "friend_list.h" 
class User
{
public:
  User(const std::string& name);
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);
  User& operator+=(User& user);
  bool operator<(const User& user) const;
  User(User&& other) = delete;
  User& operator=(User&& other) = delete;
  User(const User& other) = default;
  User& operator=(const User& other) = default;
  /** 
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */

private:
  std::string _name;
  FriendList  _friends;


  friend std::ostream& operator<<(std::ostream &os, User user);
  
};
