#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr, 0, 0)
{
}

// void swap(User& user1, User& user2) noexcept{
//   std::swap(user1._friends, user2._friends);
//   std::swap(user1._size, user2._size);
//   std::swap(user1._capacity, user2._capacity);
//   std::swap(user1._name, user2._name);
// } 

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  _friends.add_friend(name);
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _friends.size();
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
User& User::operator+=(User& user){
  add_friend(user.get_name());
  user.add_friend(get_name());
  return *this;
}

bool User::operator<(const User& user) const{
  return get_name()<user.get_name();
}

void User::set_friend(size_t index, const std::string& name)
{
  _friends.set_friend(index, name);
}


std::ostream& operator<<(std::ostream &os, User user){
  
  os<< "User(name="<< user._name<<", friends="<<user._friends<<")"<<std::endl;
  return os;
};


/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */
