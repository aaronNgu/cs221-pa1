#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){ 
    /*your code here*/
    cout << "destructor is called" << endl;
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
    // creates new node
    Node * newNode = new Node(ndata);
    Node * prevNode = tail_-> prev;
    newNode->next = tail_;
    tail_->prev = newNode;
    newNode->prev = prevNode;
    prevNode->next = newNode;
    length_++;
}

/**
 * Modifies the Chain by moving a contiguous subset of len Nodes
 * dist nodes toward the end of the chain beginning from startPos
 * (maintaining the sentinel at the end). Their order is
 * not changed in the move. You may assume that the startPos and
 * len parameters are kind: startPos + len -1 <= length. If there
 * are not enough nodes to shift by dist, just shift as many as
 * possible.
 */
void Chain::moveBack(int startPos, int len, int dist){
    /*your code here*/
    Node* frontStart = walk(head_, startPos);
    Node* frontEnd = walk(frontStart, len-1);
    Node* backStart = frontEnd->next;
    Node* before = frontStart->prev;

        backStart->prev = before;
        before->next = backStart;
    if(startPos + len + dist - 1 < length_){
        Node* backEnd = walk(frontEnd, dist);
        Node* after = backEnd->next;

        backEnd->next = frontStart;
        frontStart->prev = backEnd;
        frontEnd->next = after;
        after->prev = frontEnd;
    } else {
        //if startPos+len+dist => length_, connects to tail  
        Node* backEnd = tail_->prev;
        backEnd->next = frontStart;
        frontStart->prev = backEnd;
        frontEnd->next = tail_;
        tail_->prev = frontEnd;
    }
}

/**
 * Rolls the current Chain by k nodes: removes the last
 * k nodes from the Chain and attaches them, in order, at
 * the start of the chain (maintaining the sentinel at the front).
 */
void Chain::roll(int k){
    /*your code here*/
    Node * backStart = walk(head_, size()- k + 1);
    Node * backEnd = tail_->prev;


    Node * temp = backStart->prev;

    backEnd->next = head_->next;
    head_->next->prev = backEnd;
    head_->next = backStart;
    backStart->prev->next = tail_;
    backStart->prev=head_;
    tail_->prev= temp;
    delete temp;
    temp = NULL;
}

/**
 * Modifies the current chain by reversing the subchain
 * between pos1 and pos2, inclusive. The positions are
 * 1-based. You may assume that pos1 and pos2 are valid
 * locations in the Chain, and that pos2 >= pos1.
 */
void Chain::reverseSub(int pos1, int pos2){
    /*your code here */
}

/*
* Modifies both the current and input chains by removing
* nodes from other, and interleaving them between the Nodes
* from the current Chain. The nodes from the other Chain
* should occupy the even locations in the result. length
* of the resulting chain should be the sums of the lengths
* of current and the other. The other chain should have only
* two sentinels and no data nodes at the end of the operation.
* the weave fails and the original
* chains should be unchanged if block sizes are different.
* in that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
    /*your code here */

   cout << "before seg fault inside weave" << endl;
   // Block othBlock = other.head_->next->data;
   // doesn't work yet because copy() not done
   cout << "SEG"<< endl;
   // Seg fault here
   // Block curBlock = head_->next->data;
//    Node* curr1 = head_->next;
//    Node* curr2 = other.head_->next;
//    Node* cur = curr2;
//    Node* nCurr1 = curr1->next;
//    Node* nCurr2 = cur->next;
//    //true if one and false if second list
//    bool pos = true;
//    while(cur-!=tail_ || curr2->next!=other.tail_){
//        if()
//        if(pos){
//            // runs if is first
//            cur->next = nCurr1;
//            nCurr1->prev = cur;
//            cur->prev = curr1;
//            curr1->next = cur;
//            curr1 = cur;
//            cur = nCurr1;
//            nCurr1 = nCurr1->next;
//            pos = false;
//        } else {
//            //runs if cur is second
//            cur->next = nCurr1;
//            nCurr1->prev = cur;
//            cur->prev = curr1;
//            curr1->next = cur;
//            curr1 = cur;
//            cur = nCurr1;
//            nCurr1 = nCurr1->next;
//            pos = true;
//        }
//    }
        Node* node1 = other.head_;
        Node* node2 = head_->next;
        Node* node3 = node1->next;
        Node* node4 = node2->next;
        Node* node5 = node3->next;
        Node* beforeTail = other.tail_->prev;
        
        //runs while second list isnt empty 
        
        while(node5 != other.tail_){
            if (node4 != tail_){
                node3->next=node4;
                node4->prev=node3;
                node2->next=node3;
                node3->prev=node2;
                node5->prev=node1;
                node1->next=node5;

                node3=node5;
                node2=node4;
                node4=node4->next;
                node5=node5->next; 
            } else {
                other.tail_->prev = node1;
                node1->next = other.tail_;
                beforeTail->next = tail_;
                tail_->prev = beforeTail;
                node2->next = node3;
                node3->prev = node2;
                node5 = other.tail_;
            }
        }        
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear() {
    /*your code here*/
    cout << "clear is called" << endl;
    Node* cur = head_->next;
    Node* nxt = cur->next;
    delete head_;
    while(cur != tail_){
        delete cur;
        cur = nxt;
        nxt = nxt->next;
    }
    delete tail_;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const& other) {
    /*your code here*/
    // makes current object into copy 
    // uses new 
    Node* head_ = new Node(Block());
    Node* tail_ = new Node(Block());
    head_->next = tail_;
    tail_->prev = head_;
    Node* othNode = other.head_->next;
    for(int i = 0; i < other.size() ; i ++){
        Node * newNode = new Node(othNode->data);
        Node * prevNode = tail_-> prev;
        newNode->next = tail_;
        tail_->prev = newNode;
        newNode->prev = prevNode;
        prevNode->next = newNode;
        length_++;
        othNode = othNode->next;
        // why can't I use insertBack??
    }
    
}

