
#include <iostream>
#include <string>



class FriendList{
    private:
          
          std::string* _friends;
          size_t _size;
          size_t _capacity;
    friend std::ostream& operator<<(std::ostream &os, FriendList friend_list);
    friend void swap(FriendList& friend_list1, FriendList& friend_list2) noexcept;

    public:
       FriendList(
         
          std::string* _friends,
          size_t _size,
          size_t _capacity); 
       ~FriendList();
       FriendList(const FriendList& friend_list);
       FriendList& operator=(FriendList friend_list);
       FriendList(FriendList&& friend_list) = delete;
       FriendList& operator=(FriendList&& friend_list)= delete;
       void add_friend(const std::string& name);
       size_t size() const;
       size_t capacity() const;
       void set_friend(size_t index, const  std::string& name);






};