#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

bool detectAndRemoveLoop(ListNode* head) {
    if (!head || !head->next) return false;

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }

    if (slow != fast) {
        return false; 
    }
    slow = head;
    if (slow == fast) { 
        while (fast->next != slow) {
            fast = fast->next;
        }
    } else {
        while (slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    fast->next = nullptr; 
    return true;
}
ListNode* reverseAndRemoveLoop(ListNode* head) {
    detectAndRemoveLoop(head);
    return reverseList(head);
}


void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "null" << endl;
}

int main() {
    int n;
    cout << "Enter the number of nodes in the linked list: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of nodes!" << endl;
        return 0;
    }

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    cout << "Enter the values of the nodes:" << endl;
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        ListNode* newNode = new ListNode(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    char createLoop;
    cout << "Do you want to create a loop? (y/n): ";
    cin >> createLoop;

    if (createLoop == 'y' || createLoop == 'Y') {
        int loopStart;
        cout << "Enter the position (1-based index) where the loop starts: ";
        cin >> loopStart;

        if (loopStart > 0 && loopStart <= n) {
            ListNode* loopNode = head;
            for (int i = 1; i < loopStart; ++i) {
                loopNode = loopNode->next;
            }
            tail->next = loopNode;
        } else {
            cout << "Invalid loop start position!" << endl;
        }
    }

    cout << "Reversing and handling loop..." << endl;
    head = reverseAndRemoveLoop(head);
    cout << "Modified linked list:" << endl;
    printList(head);

    return 0;
}
