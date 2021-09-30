//
//  Vector1.h
//  Project
//
//  Created by School on 12/2/19.
//  Copyright © 2019 DiabloValleyCollege. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

template < typename  V >

class Vector

{
  
  struct Node
  {
    V value;
    int ind;
    Node* next;
  };
  
  V dummy;
  
  Node* firstNode;
  Node* lastNode;
  int siz;
  
public:
  
  Vector();  //Main Constructor
  Vector(const Vector <V>& ); //Copy Constructor
  ~Vector();
  V operator[]( const int ) const;
  V& operator[]( const int );
  Vector<V>& operator=( const Vector<V>& );
  void pushBack( const V& );  //Put new value at top of stack
  const V& back() const;

  void popBack();

  int size() const;
  bool empty() const;
  
  
};

template < typename V >
Vector<V>::Vector()
{
  firstNode = 0;
  lastNode = 0;
  siz = 0;
}

template < typename V >
Vector<V>::Vector(const Vector <V>& original )
{
  firstNode = 0;
  lastNode = 0;
  siz = original.siz;
  
  for ( Node* p = original.firstNode; p; p = p->next)
  {
    Node* temp = new Node;
    temp->value = p->value;
    temp->ind = p->ind;
    temp->next = 0;
    if ( lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
  }
  
}

template < typename V >
Vector<V>::~Vector()
{
  while ( firstNode )
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
  }
}

template < typename V >
V Vector<V>::operator[]( const int index) const
{

  for (Node* p = firstNode; p; p = p->next)
    if (p->ind == index)
      return p->value;
  return V();
}


template < typename V >
V& Vector<V>::operator[]( const int index)
{
  for (Node* p = firstNode; p; p = p->next)
    if (p->ind == index)
      return p->value;
  Node* temp = new Node;
  temp->ind = index;
  temp->value = V();
  
  if ( firstNode == 0 && lastNode ==0 )
  {
    firstNode= temp;
    temp->next = lastNode;
    lastNode = 0;
     siz++;
    return firstNode->value;
  }
  
  else if (firstNode && lastNode == 0 )
  {
   ++siz;
    firstNode->next= temp;
    temp->next=lastNode;
    lastNode = temp;
    return lastNode->value;
  }

else // (firstNode && lastNode)
{
  Node* p = firstNode;
  while ( p->next)
  {
    p = p->next;
  }
  ++siz;
  p->next = temp;
  temp->next = 0;
  lastNode=temp;
  return lastNode->value;
}

  
}

template < typename V >
Vector<V>& Vector<V>::operator=(const Vector<V>& original)
{
  if ( this != &original )
  {
    while ( firstNode )
    {
      Node* p =firstNode;
      firstNode = firstNode->next;
      delete p;
    }
    lastNode = 0;
    for ( Node* p = original.firstNode; p; p = p->next)
    {
      Node* temp = new Node;
      temp->value = p->value;
      temp->ind = p->ind;
      temp->next = 0;
      if ( lastNode) lastNode->next = temp;
      else firstNode = temp;
      lastNode = temp;
    }
    siz = original.siz;
  }
  return *this;
}

template < typename V>
void Vector<V>::pushBack(const V& value )
{
  int index = siz;
  Node* temp = new Node{ value , index};
  if ( lastNode && firstNode)
    lastNode->next = temp;
  else if ( firstNode && lastNode == 0)
    firstNode->next = temp;
  else
    firstNode= temp;
  
  lastNode= temp;
  ++siz;
}

template < typename V>
void Vector<V>::popBack()
{
  if ( firstNode == 0)
  {
    lastNode = 0;
    return;
  }
  
  Node* p = firstNode;
  Node* prev = 0;
  
  while ( p->next != 0 )
  {
    prev = p;
    p = p->next;
  }
  
  if ( p == firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    lastNode = 0;
    delete p;
    --siz;
  }

  else
  {
  prev->next = 0;
      lastNode = prev;
  --siz;
  }
  
   
}

template < typename V>
const V& Vector<V>::back() const
{
  
  if ( firstNode && lastNode == 0)
    return firstNode->value;
  else if (firstNode && lastNode)
    return lastNode->value;
  
  return dummy;
}




template < typename V >
int Vector<V>::size() const
{
  return siz;
}

template < typename V>
bool Vector<V>::empty() const
{
  if ( siz == 0 ) return true;
  return false;
}


#endif /* Vector_h */
