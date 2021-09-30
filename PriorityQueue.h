//Grace Jung
//1610447
//Henry Kutlik
//1662812
//Anthony Perez
//1714958
//Lynn Tran
//1585079

#ifndef PriorityQueue_h
#define PriorityQueue_h

//Heap Data Structure
//Two Children per One Parent
//Array Implementation

//For swap
#include <iostream>
using namespace std;

template < typename V >
class PriorityQueue
{
  
  V* values;
  int cap;
  int siz;
  void capacity ( int );  //Private so only public member functions can access
  
public:
  PriorityQueue ( int = 2);
  PriorityQueue ( const PriorityQueue<V>& );  //copy constructor
  ~PriorityQueue () { delete [] values; }
  PriorityQueue<V>& operator= ( const PriorityQueue<V>& );  //Assignment Operator
  
  void push ( const V& );
  void pop ();
  V top () const { return siz == 0 ?  V() : values[0]; }
  int size () const { return siz; }
  bool empty () const { return siz == 0 ? true : false; }
  void clear () { siz == 0; };
  
};

template < typename V > //Default Constructor
PriorityQueue<V>::PriorityQueue ( int cap )
{
  this->cap = cap;
  siz = 0;
  values = new V[cap];
}

template < typename V >//Copy Constructor
PriorityQueue<V>::PriorityQueue ( const PriorityQueue<V>& original )
{
  cap = original.cap;
  siz = original.siz;
  values = new V[cap];
  for (int i = 0; i < cap; i++)
  {
    values[i] = original.values[i];
  }
}

template < typename V >//Assignment to operator
PriorityQueue<V>& PriorityQueue<V>::operator=(const PriorityQueue<V> & original )
{
  if (this != &original)
  {
    delete[] values;
    cap = original.cap;
    siz = original.siz;
    values = new V[cap];
    for (int i = 0; i < cap; i++)
    {
      values[i] = original.values[i];
    }
  }
  return *this;
}

template < typename V >//Push
void PriorityQueue<V>::push(const V & value )
{
  if ( siz == cap )
    capacity( 2 * cap );
  
  values[siz] = value;
  
  int index = siz;
  while (true )
  {
    int p_Index = ( index + 1 ) / 2 -1;
    
    if ( index == 0)
      break;
    
    if ( values[p_Index] > values[index] )
      break;
    
    else
    {
      swap ( values[index], values[p_Index] );
      index = p_Index;
    }
  }
  
  siz++;
}

template < typename V >//Pop
void PriorityQueue<V>::pop()
{
  if ( siz == 0 ) return;
  
  values[0] = values[ siz-1 ];
  
  int index = 0;  //Parent Index
  
  while ( true )
  {
    int l_Index = 2 * index + 1;
    int r_Index = 2 * index + 2;
    
    if (  l_Index >= siz )  //No children
      break;  //End First Condtion
    
    
    if ( r_Index >= siz ) //Only has left child
    {
      swap ( values[l_Index], values[index] );
      index = l_Index;
      break;
    } //End Second Condition
    
    if ( r_Index < siz )  //We have both left and right children
    {
      if ( values[l_Index] > values[r_Index] )
      {
        swap ( values[l_Index], values[index] );
        index = l_Index;
      }
      else
      {
        swap ( values[r_Index], values[index] );
        index = r_Index;
      }
    } //End Third Condtion
    
  }//End While
  
  siz--;
  
  //Fill Hole
  values[index] = values[siz];
  
  while (true )
  {
    int p_Index = ( index + 1 ) / 2 -1;
    
    if ( index == 0)
      break;
    
    if ( values[p_Index] > values[index] )
      break;
    
    else
    {
      swap ( values[index], values[p_Index] );
      index = p_Index;
    }
  }//End While
  
  
}


template < typename V >//Cap
void PriorityQueue<V>::capacity( int cap )
{
  V* temp = new V[cap];
  for ( int i =0 ; i < this->cap; i++ )
  {
    temp[i] = values[i];
  }
  delete [] values;
  values = temp;
  this->cap = cap;
  
}







#endif /* PriorityQueue_h */
