#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include "stack.h"

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator()) : m_ary(m), m_comp(c)
  {}

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap(){}

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

   /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const
  {
    return m_data.empty();
  }

   /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const
  {
    return m_data.size();
  }

private:
  // Add whatever helper functions and data members you need below
  std::vector<T> m_data;
  int m_ary;
  PComparator m_comp;
};

// Add implementation of member functions here

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return m_data[0];
}


// We will start pop() for you to handle the case of 
// calling pop on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("heap is empty");
  }
  //remove top by swapping
  std::swap(m_data[0], m_data[size() - 1]);
  m_data.pop_back();

  //trickle new top node down
  std::size_t loc = 1; // remember to subtract 1 when indexing

  while (true)
  {
    bool leftExists = ( loc * 2 - 1 < size() );
    bool rightExists = ( loc * 2 < size() );

    //messy logic but it works

    //if current node is weighed better than both children, were done
    if ( !leftExists || (
      rightExists 
        && m_comp(m_data[loc - 1], m_data[loc * 2 - 1]) 
        && m_comp(m_data[loc - 1], m_data[loc * 2]) ) )
    {
      break;
    }
    //assert(leftExists);

    //if both children exist and are better
    if (rightExists && !m_comp(m_data[loc - 1], m_data[loc * 2 - 1]) && !m_comp(m_data[loc - 1], m_data[loc * 2]))
    {
      if (m_comp(m_data[loc * 2 - 1], m_data[loc * 2]))
      {
        std::swap(m_data[loc * 2 - 1], m_data[loc - 1]);
        loc = loc * 2;
      }
      else
      {
        std::swap(m_data[loc * 2], m_data[loc - 1]);
        loc = loc * 2 + 1;
      }
    }
    else if (rightExists && !m_comp(m_data[loc - 1], m_data[loc * 2]))
    {
      std::swap(m_data[loc * 2], m_data[loc - 1]);
      loc = loc * 2+ 1;
    }
    else if (leftExists && !m_comp(m_data[loc - 1], m_data[loc * 2 - 1]))
    {
      std::swap(m_data[loc * 2 - 1], m_data[loc - 1]);
      loc = loc * 2;
    }
    else
    {// both children are worse or do not exist
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  m_data.push_back(item);
  std::size_t loc = m_data.size(); // remember to subtract before indexing

  //trickle new item up
  while (loc > 1)
  {
    if (m_comp(m_data[loc - 1], m_data[(loc/2) - 1]))
    {
      std::swap(m_data[loc - 1], m_data[(loc/2) - 1]);
      loc = loc/2;

      //if another child exists and is better, swap with that child
      if (loc * 2 < size())
      {
          if (m_comp(m_data[loc * 2 - 1], m_data[loc - 1]))
          {
              std::swap(m_data[loc - 1], m_data[loc * 2 - 1]);
          }
          else if (m_comp(m_data[loc * 2], m_data[loc - 1]))
          {
              std::swap(m_data[loc - 1], m_data[loc * 2]);
          }
      }
    }
    else{ break; }
  }
}

#endif

