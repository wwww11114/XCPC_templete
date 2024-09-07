#include <iostream>
using namespace std;
struct ListNode {
    int value;
    ListNode *next;
};
ListNode *createList(int n) {
    ListNode *head = new ListNode();
    ListNode *temp = head;
    for (int i = 1; i <= n; i++) {
        cin >> temp->value;
        if (i < n) {
            temp->next = new ListNode();
            temp = temp->next;
        } else
            temp->next = NULL;
    }
    return head;
}
void ClearList(ListNode *head) {
    while (head != NULL) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}
void Initlist(ListNode *head, int x) {
    while (head != NULL) {
        head->value = x;
        head = head->next;
    }
}
void PrintList(ListNode *head) {
    while (head != NULL) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}
bool FindList(ListNode *head, int x) {
    while (head != NULL) {
        if (head->value == x)
            return true;
        head = head->next;
    }
    return false;
}
void InsertList(ListNode **head, int x, int pos) {
    ListNode *temp = new ListNode();
    temp->value = x;
    if (pos == 1) {
        temp->next = *head;
        *head = temp;
    } else {
        ListNode *temp1 = *head;
        for (int i = 1; i < pos - 1 && temp1 != nullptr; i++) {
            temp1 = temp1->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1->next;
            temp1->next = temp;
        }
    }
}
ListNode *DeleteList(ListNode *head, int pos) {
    ListNode *temp = head;
    if (pos == 1) {
        head = head->next;
        delete temp;
        return head;
    }
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    ListNode *temp1 = temp->next;
    temp->next = temp1->next;
    delete temp1;
    return head;
}
int main() {
    int n;
    cin >> n;
    ListNode *head = createList(n);
    PrintList(head);
    int x;
    cin >> x;
    cout << FindList(head, x) << endl;
    int pos;
    cin >> x >> pos;
    InsertList(&head, x, pos);
    PrintList(head);
    return 0;
}