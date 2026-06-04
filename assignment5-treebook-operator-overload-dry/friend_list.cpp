#include<string>
#include<iostream>
#include "friend_list.h"


FriendList::~FriendList(){
    delete[] this->_friends;
}
void FriendList::set_friend(size_t index, const std::string& name){
    _friends[index] = name;
}
FriendList::FriendList(
          std::string* _friends,
          size_t _size,
          size_t _capacity): _friends(_friends), _size(_size),_capacity(_capacity){

          } 

FriendList::FriendList(const FriendList& friend_list){
    this->_size = friend_list._size;
    this->_capacity = friend_list._capacity;
    this->_friends = new std::string[this->_capacity];
    for(int i =0;i<friend_list._size;i++){
        this->_friends[i] = friend_list._friends[i]; 
    }
}

void swap(FriendList& friend_list1, FriendList& friend_list2) noexcept{
    std::swap(friend_list1._capacity, friend_list2._capacity);
    std::swap(friend_list1._size, friend_list2._size);
    std::swap(friend_list1._friends, friend_list2._friends);

}

FriendList& FriendList::operator=(FriendList friend_list){
    swap(*this, friend_list);
    return *this; 
}

void FriendList::add_friend(const std::string& name){
    if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

size_t FriendList::size() const{
    return _size;
}

size_t FriendList::capacity() const{
    return _capacity;
}



std::ostream& operator<<(std::ostream &os, FriendList friend_list){
    std::string s;
  for(int i =0;i<friend_list._size;i++){
      s+=friend_list._friends[i];
      if(i!=friend_list._size-1){
        s+=", ";
      }
  }
  os<< "["<<s<<"])"<<std::endl;
  return os;
 }


