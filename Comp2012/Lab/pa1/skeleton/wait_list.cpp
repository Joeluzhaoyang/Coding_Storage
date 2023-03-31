#include <iostream>
#include "wait_list.h"

using namespace std;

Student_ListNode::Student_ListNode(const int student_id, Student_ListNode* const next)
:student_id(student_id) {
    // TODO
    this->next = next;
}

Wait_List::Wait_List() {
    // TODO
    this->head = nullptr;
    this->end = nullptr;
}

Wait_List::Wait_List(const Wait_List& wait_list) {
    // TODO
    this->set_head(nullptr);
    this->set_end(nullptr);
    Student_ListNode* old_ptr = wait_list.get_head();
    Student_ListNode* new_ptr = this->get_head();

    if(old_ptr != nullptr)
    {
        Student_ListNode* copy_ptr = new Student_ListNode(old_ptr->student_id,nullptr);
        this->set_head(copy_ptr);
        this->set_end(copy_ptr);
    }
    if(this->get_head() != nullptr)
    {
        new_ptr = this->get_head();

        while(old_ptr->next != nullptr)
        {
            Student_ListNode* copy_ptr = new Student_ListNode(old_ptr->next->student_id,nullptr);
            new_ptr->next = copy_ptr;
            old_ptr = old_ptr->next;
            new_ptr = new_ptr->next;
        }
        this->set_end(new_ptr);
    }
}

Wait_List::~Wait_List() {
    // TODO
    for(Student_ListNode* i = this->head ; i != nullptr;)
    {
        Student_ListNode* j = i->next;
        delete i;
        i=j;
    }
}

void Wait_List::print_list() const {
    Student_ListNode* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Waitlist Number: " << index++ << endl;
        cout << temp->student_id << endl;
        temp = temp->next;
    }
}

Student_ListNode* Wait_List::get_head() const {
    return head;
}

Student_ListNode* Wait_List::get_end() const {
    return end;
}

void Wait_List::set_head(Student_ListNode* const head) {
    this->head = head;
}

void Wait_List::set_end(Student_ListNode* const end) {
    this->end = end;
}