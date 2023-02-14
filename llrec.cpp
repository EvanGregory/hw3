#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot_helper(Node* &curr, Node* &smaller, Node* &larger, int pivot)
{
  if (curr == nullptr){
    return;}

  if (curr->val <= pivot)
  {
    //is smaller empty or not?
    if (smaller == nullptr)
    {
      smaller = curr;
    }
    else
    {
      
    }
    
  }
  else
  {
    //is larger empty or not?
    larger = curr;

    larger->next = curr; 
  }
  
  llpivot_helper(curr->next, smaller->next, larger, pivot);
  curr->next = nullptr;


  
}

void lldeteter(Node*&currNode)
{
  if (currNode == nullptr) return;
  lldeteter(currNode->next);
  delete currNode;
}

void llpivot(Node* &head, Node* &smaller, Node* &larger, int pivot)
{
  //remove garbage from smaller and larger
    lldeteter(smaller);
    lldeteter(larger);
  

  //call helper


}
