#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <iostream>
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

  void dump() const
  {
      dumpRecurse(0, 0);
  }

private: 

  int getParent(int index) const
  {
      return (index - 1) / m_ary;
  }
  
  int getChild(int index, int whichChild) const
  {
    if (whichChild >= 0 && whichChild < m_ary)
    {
      return index * m_ary + whichChild + 1;
    }
    return -1; // assert!
  }

  void dumpRecurse(int currentNode, int depth) const
  {
      if (currentNode >= size())
          return;
      for (int i = 0; i < depth; i++) std::cout << " ";
      std::cout << currentNode << ":" << m_data[currentNode] << std::endl;

      for (int i = 0; i < m_ary; i++)
      {
          std::size_t childNode = getChild(currentNode, i);
          dumpRecurse(childNode, depth + 1);
      }

      //for (int i = 1; i < (currentNode + 1) * m_ary; i++)
      //{
      //    dumpRecurse((currentNode + 1) * i);
      //}
  }

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
  std::size_t loc = 0;

  while (true)
  {
    int bestInd = -1;
    for (int i = 0; i < m_ary; i++)
    {
      int childInd = getChild(loc, i);
      int currInd = loc;
      if (childInd < size() && 
          m_comp(m_data[childInd], m_data[currInd]))
      {
        if (bestInd == -1 || (m_comp(m_data[childInd], m_data[bestInd])))
        {
          bestInd = childInd;
        }
      }
    }
    if (bestInd == -1)
    {
      break;
    }
    else
    {
      std::swap(m_data[loc], m_data[bestInd]);
      loc = bestInd;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  std::size_t currInd = m_data.size();
  m_data.push_back(item);

  //trickle new item up
  while (currInd > 0)
  {
    std::size_t parentInd = getParent(currInd);
    if (m_comp(m_data[currInd], m_data[parentInd]))
    {
      std::swap(m_data[currInd], m_data[parentInd]);
      currInd = parentInd;
    }
    else break;
  }
}

#endif

