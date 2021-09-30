//Grace Jung
//1610447
//Henry Kutlik
//1662812
//Anthony Perez
//1714958
//Lynn Tran
//1585079

#ifndef AssociativeArray_h
#define AssociativeArray_h

#include <queue>
using namespace std;

template < typename K, typename V >
class AssociativeArray
{
  struct Node
  {
    K key;
    V value;
    Node* next;
  };
  
  Node* firstNode;
  int siz;
  
public:
  AssociativeArray() { firstNode = 0; siz = 0; }
  AssociativeArray( const AssociativeArray< K , V >& );
  AssociativeArray<K,V>& operator=( const AssociativeArray< K , V >& );
  ~AssociativeArray();
  V operator[]( const K& ) const;
  V& operator[]( const K& );
  bool containsKey( const K& ) const;
  void deleteKey( const K& );
  queue<K> keys() const;
  int size() {return siz;}
  void clear();
};

template < typename  K , typename V >
AssociativeArray< K , V >::AssociativeArray( const AssociativeArray< K , V >& original )  //Copy Constructor (Dynamic Memory Managment)
{
  firstNode = 0;
  Node* lastNode = 0;
  siz = original.siz;
  
  for ( Node* p = original.firstNode; p; p = p->next)
  {
    Node* temp = new Node;
    temp->key = p->key;
    temp->value = p->value;
    temp->next = 0;
    if ( lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
  }
}

template < typename  K , typename V >
AssociativeArray<K,V>& AssociativeArray< K , V >::operator=( const AssociativeArray<K, V> & original )  //Assignment Operator (D.M.M)
{
  if ( this != &original )
  {
    while ( firstNode )
    {
      Node* p =firstNode;
      firstNode = firstNode->next;
      delete p;
    }
    Node* lastNode = 0;
    for ( Node* p = original.firstNode; p; p = p->next)
    {
      Node* temp = new Node;
      temp->key = p->key;
      temp->value = p->value;
      temp->next = 0;
      if ( lastNode) lastNode->next = temp;
      else firstNode = temp;
      lastNode = temp;
    }
    siz = original.siz;
  }
  return *this;
}

template < typename  K , typename V >
AssociativeArray< K , V >::~AssociativeArray()  //Destructor (D.D.M)
{
  while ( firstNode )
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
  }
}

template < typename  K , typename V >
V AssociativeArray< K , V >::operator[]( const K& key ) const //Square Bracket Getter
{
  for (Node* p = firstNode; p; p = p->next)
    if (p->key == key)
      return p->value;
  return V();
}

template < typename  K , typename V >
V& AssociativeArray< K , V >::operator[]( const K& key )  //Square Bracket Setter
{
  for (Node* p = firstNode; p; p = p->next)
    if (p->key == key)
      return p->value;
  ++siz;
  Node* temp = new Node;
  temp->key = key;
  temp->value = V( );
  temp->next = firstNode;
  firstNode = temp;
  return firstNode->value;
}

template < typename  K , typename V >
bool AssociativeArray< K , V >::containsKey( const K& key ) const //True/False Contains Key
{
  for (Node* p = firstNode; p; p = p->next)
    if (p->key == key)
      return true;
  return false;
}

template < typename  K , typename V >
void AssociativeArray< K , V >::deleteKey( const K& key ) //Delete Key Function
{
  Node* p;
  Node* prev;
  for ( p = firstNode, prev = 0; p; prev = p, p = p->next)
    if ( p->key == key )
      break;
  
  if ( p )
  {
    --siz;
    if ( prev ) prev->next = p->next;
    else firstNode = p->next;
    delete p;
  }
  
}

template < typename  K , typename V >
queue<K> AssociativeArray< K , V >::keys() const  //Display Keys
{
  queue<K> k_queue;
  for (Node* p = firstNode; p; p = p->next)
    k_queue.push(p->key);
  return k_queue;
}

template < typename  K , typename V >
void AssociativeArray< K , V >::clear() //Clear Linked List
{
  while ( firstNode )
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
}


#endif /* AssociativeArray_h */
