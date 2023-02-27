#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot_helper1(Node* pCurr, Node** ppSmaller, Node** ppLarger, int pivot)
{
  if (pCurr == nullptr)
    return;

  if (pCurr->val <= pivot)
  {
    *ppSmaller = pCurr;
    Node* pNext = pCurr->next;
    pCurr->next = nullptr;
    llpivot_helper1(pNext, &pCurr->next, ppLarger, pivot);
  }
  else
  {
    *ppLarger = pCurr;
    Node* pNext = pCurr->next;
    pCurr->next = nullptr;
    llpivot_helper1(pNext, ppSmaller, &pCurr->next, pivot);
  }
}

/*void llpivot_helper(Node* &curr, Node* &smaller, Node* &larger, int pivot)
{
  if (curr == nullptr){
    return;}

  if (curr->val <= pivot)
  {
    //is smaller empty or not?
    smaller = curr;
    Node* next = curr->next;
    curr->next = nullptr;
    llpivot_helper(next, smaller->next, larger, pivot);
  }
  else
  {
    //is larger empty or not?
    larger = curr;
    llpivot_helper(curr->next, smaller, larger->next, pivot);
  }
  curr->next = nullptr;
}*/

/*
void lldeteter(Node*&currNode)
{
  if (currNode == nullptr) return;
  lldeteter(currNode->next);
  delete currNode;
  currNode = nullptr;
}
*/

void llpivot(Node* &head, Node* &smaller, Node* &larger, int pivot)
{
  //remove garbage from smaller and larger
  smaller = nullptr;
  larger = nullptr;

  //call helper
//  llpivot_helper(head, smaller, larger, pivot);
  llpivot_helper1(head, &smaller, &larger, pivot);

  //remove the original linked list
  head = nullptr;
}
