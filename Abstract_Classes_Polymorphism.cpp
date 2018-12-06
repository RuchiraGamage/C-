#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache :public Cache{
public:
    LRUCache(int capacity)
    {
        cp = capacity;
        tail = NULL;
        head = NULL;
    }
    void set(int k, int v)override
    {
        std::map<int, Node*>::iterator it;

        it = mp.find(k);
        if (it != mp.end())
        {
            it->second->value = v;
        }
        else
        {
            if (cp > 0)//if capacity is greater than zero
            {
                if (mp.size() == cp)//if map size is equal to the capacity should remove the tail and add new node to the front
                {
                    it = mp.find(tail->key);
                    if (tail == head)//map with capacity 1
                    {
                        head = NULL;
                        tail = NULL;
                    }
                    else
                    {
                        tail = tail->prev;
                        tail->next = NULL;
                    }
                    delete it->second;
                    mp.erase(it);
                }
                Node* current_node = new Node(k,v);
                mp[k] = current_node;


                if (head==NULL && tail==NULL){
                    tail = current_node;
                }
                else{
                    head->prev = current_node;
                    current_node->next = head;
                }
                head = current_node;

            }
        }
    }
    int get(int key)override
    {
        std::map<int, Node*>::iterator it;
        it = mp.find(key);
        if (it != mp.end()){
            Node* node = it->second;
            if (node != head){
                if (node != tail){
                    node->next->prev = node->prev;
                    node->prev->next = node->next;
                }
                else{
                    tail = tail->prev;
                    tail->next = NULL;
                }
                node->next = head;
                head->prev = node;
                head = node;
            }
            return node->value;
        }
        return -1;
    }
};
int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
