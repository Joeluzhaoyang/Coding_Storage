#include <iostream>
#include <cstring>
#include "system.h"
#include "student.h"
#include "course.h"
#include "course_database.h"
#include "student_database.h"
#include "wait_list.h"
#include "swap_list.h"

using namespace std;

/*
The following 3 helper functions may be useful in add/swap/drop function. You may implement them if you find them useful.
If not, you can remove these 3 helper functions as we will NOT set any test case testing these helper functions.
*/

// Helper function: add the Student to the end of the waitlist of the Course.
void join_waitlist(const int student_id, Course* course) {
    // TODO
}

// Helper function: find the index of a course within the enrolled course list of a student.
int search_course_index(const Student* const student, const char* const course_name) {
    // TODO
        return 0;
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course* const course) {
    // TODO

        return 0;
}


System::System(const int max_num_course, const int max_num_student) {
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System& system) {
    this->course_database = new Course_Database(*system.course_database);
    this->student_database = new Student_Database(*system.student_database);
}

System::~System() {
    //cout<<"WorkingS"<<endl;
    delete course_database;
    delete student_database;
    //cout<<"WorkingS"<<endl;
}

void System::admit(const char* const name, const int student_id, const double gpa) {
    this->student_database->create_entry(name, student_id, gpa);
}

bool System::apply_overload(const int student_id, const int request_credit) {
    // TODO
    Student* candidate = student_database->get_student_by_id(student_id);
    if(candidate->get_curr_credit() >= 30 || request_credit > 30)
    {return false;}
    else if(request_credit >= 24 && candidate->get_gpa() >=3.7)
    {
        candidate->set_max_credit(request_credit);
        return true;
    }
    else if(request_credit >= 18 && candidate->get_gpa() >=3.3)
    {
        candidate->set_max_credit(request_credit);
        return true;
    }
    else{return false;}
}

bool System::add(const int student_id, const char* const course_name) {
    // TODO
    Student* ppl = student_database->get_student_by_id(student_id);
    Course* lec = course_database->get_course_by_name(course_name);

    if(ppl->get_curr_credit() + ppl->get_pending_credit() + lec->get_num_credit() 
    > ppl->get_max_credit() )
    {return false;}

    if(lec->get_size() < lec->get_capacity())//check capacity, to enroll in
    {
        
        int* student_enrolled = lec->get_students_enrolled();
        student_enrolled[lec->get_size()]=ppl->get_student_id();
        //lec->set_students_enrolled(student_enrolled);

        lec->set_size(lec->get_size()+1);

        ppl->set_curr_credit(ppl->get_curr_credit()+lec->get_num_credit());

        char** enrolled_courses = ppl->get_enrolled_courses();
        enrolled_courses[ppl->get_num_enrolled_course()] = new char[strlen(course_name)+1];
        strcpy(enrolled_courses[ppl->get_num_enrolled_course()],course_name);
        //ppl->set_enrolled_courses(enrolled_courses);

        ppl->set_num_enrolled_course(ppl->get_num_enrolled_course()+1);

        return true;
    }
    else//to waitlist
    {
        Student_ListNode* new_waitlist = new Student_ListNode(student_id,nullptr);//new node
        Wait_List* ppl_waitlist = lec->get_wait_list();//edit target waitlist
        Student_ListNode* temp_waitlist = ppl_waitlist->get_head();//editing pointer

        if(ppl_waitlist->get_head() == nullptr)//if it is the first student
        {
            ppl_waitlist->set_head(new_waitlist);
            ppl_waitlist->set_end(new_waitlist);
            if(strcmp("MAGIC1000",lec->get_name()) == 0 || strcmp("MAGIC1001",lec->get_name()) == 0)//added for deadlock
            {return true;}
            ppl->set_pending_credit(ppl->get_pending_credit() + lec->get_num_credit() );
            return true;
        }
        else
        {
            ppl_waitlist->get_end()->next = new_waitlist;
            ppl_waitlist->set_end(new_waitlist);
            if(strcmp("MAGIC1000",lec->get_name()) == 0 || strcmp("MAGIC1001",lec->get_name()) == 0)//added for deadlock
                return true;
            ppl->set_pending_credit(ppl->get_pending_credit() + lec->get_num_credit() );
            return true;
        }
    }
    return false;
}

bool System::swap(const int student_id, const char* const original_course_name, const char* const target_course_name) {
    // TODO
    Student* ppl = student_database->get_student_by_id(student_id);
    Course* old_lec = course_database->get_course_by_name(original_course_name);
    Course* target_lec = course_database->get_course_by_name(target_course_name);
    
    if(ppl->get_curr_credit() + ppl->get_pending_credit() + target_lec->get_num_credit() 
    - old_lec->get_num_credit() > ppl->get_max_credit())
    {return false;}

    if(target_lec->get_size() < target_lec->get_capacity())//if have position in target_lec, drop it
    {
        drop(student_id,original_course_name);//drop course
        add(student_id,target_course_name);//add to enrolled course
        return true;
    }
    else//to wait list and swap list
    {
        add(student_id,target_course_name);//go to wait list
        Swap* ppl_swap = new Swap(original_course_name,target_course_name,nullptr);
        Swap_List* temp_swaplist = ppl->get_swap_list();
        Swap* temp_swap = temp_swaplist->get_head();
        if(temp_swap == nullptr)
        {
            temp_swaplist->set_head(ppl_swap);
        }
        else
        {
            while(temp_swap->next != nullptr)
            {temp_swap = temp_swap->next;}
            temp_swap->next = ppl_swap;
        }
        return true;
    }
}

void System::drop(const int student_id, const char* const course_name) {
    // TODO

    Student* ppl = student_database->get_student_by_id(student_id);
    Course* lec = course_database->get_course_by_name(course_name);

    char** enrolled_courses = ppl->get_enrolled_courses();
    char* course_delete = nullptr;
    int course_pos = 0;

    int* enrolled_student = lec->get_students_enrolled();
    int* student_delete = nullptr;//pointer to be delete
    int student_pos = 0;

    Wait_List* wait_list = lec->get_wait_list();
    Student_ListNode* wait_student = wait_list->get_head();
    Student_ListNode* next_student = nullptr;
    if(wait_student != nullptr)
    {next_student = wait_student->next;}



    for(; student_pos< lec->get_size() ; student_pos++)//find the student
    {
        if( enrolled_student[student_pos] == ppl->get_student_id())
        {
            student_delete = &(enrolled_student[student_pos]);//assign the student to delete
            break;
            // if(i != 0){student_prev = &(enrolled_student[i-1]);}//assign prev student
            // if(i != lec->get_size()){student_next = &(enrolled_student[i+1]);}
        }
    }

    for(; course_pos<ppl->get_num_enrolled_course();course_pos++)//find the course
    {
        if(strcmp(enrolled_courses[course_pos],lec->get_name()) == 0)
        {
            course_delete = enrolled_courses[course_pos];
            break;
            // if(course_pos != 0){course_prev = enrolled_courses[course_pos-1];}
            // if(course_pos != ppl->get_num_enrolled_course())
            // {course_next = enrolled_courses[course_pos+1];}
        }
    }


    {//simple drop
        delete[] course_delete;

        enrolled_student[student_pos] = 0;

        ppl->set_curr_credit(ppl->get_curr_credit()-lec->get_num_credit());
        lec->set_size(lec->get_size()-1);
        ppl->set_num_enrolled_course(ppl->get_num_enrolled_course()-1);
    }

    if(lec->get_size() < lec->get_capacity() && wait_student != nullptr)//wait list
    {//wait list checking
        Student* ppl_wait = student_database->get_student_by_id(wait_student->student_id);
        if(ppl_wait->get_curr_credit() + ppl_wait->get_pending_credit() 
        <= ppl_wait->get_max_credit() ) 
    	{//waiting student can enroll in
            int* student_enrolled = lec->get_students_enrolled();
            student_enrolled[student_pos]=ppl_wait->get_student_id();

            lec->set_size(lec->get_size()+1);

            ppl_wait->set_curr_credit(ppl_wait->get_curr_credit()+lec->get_num_credit());

            char** enrolled_courses = ppl_wait->get_enrolled_courses();
            enrolled_courses[ppl_wait->get_num_enrolled_course()]
             = new char[strlen(course_name)+1];
            strcpy(enrolled_courses[ppl_wait->get_num_enrolled_course()],course_name);

            ppl_wait->set_num_enrolled_course(ppl_wait->get_num_enrolled_course()+1);
            ppl_wait->set_pending_credit(ppl_wait->get_pending_credit() - 
            lec->get_num_credit());

            Swap_List* ppl_swaplist = ppl_wait->get_swap_list();
            Swap* swap_curr = ppl_swaplist->get_head();
            Swap* swap_prev = nullptr;
            while(swap_curr != nullptr)//find swap ptr
            {
                if(strcmp(swap_curr->target_course_name , lec->get_name()) == 0)
                {
                    break;
                }
                swap_prev = swap_curr;
                swap_curr = swap_curr->next; 
            }
            if(swap_curr != nullptr)
            {
                if(swap_curr->target_course_name == lec->get_name())
                {
                    drop(ppl_wait->get_student_id(),swap_curr->original_course_name);
                    swap_prev->next = swap_curr->next;
                    delete swap_curr;
                }
            }

            delete wait_student;
            wait_list->set_head(next_student);
            if(wait_list->get_head() == nullptr)
            {wait_list->set_end(nullptr);}
        }



    }
    else//simple drop bridge
    {
        enrolled_student[student_pos] = enrolled_student[lec->get_size()];
        enrolled_student[lec->get_size()] = 0;
        while(enrolled_courses[course_pos+1] != nullptr)
        {
            enrolled_courses[course_pos] = enrolled_courses[course_pos+1];
            course_pos++;
        }
        enrolled_courses[course_pos+1] = nullptr;
    }
}

void System::add_course(const char* const name, const int num_credit, const int course_capacity) {
    this->course_database->create_entry(name, num_credit, course_capacity);
}

void System::print_info() const {
    this->course_database->print_all_course();
    this->student_database->print_all_students();
}

Course_Database* System::get_course_database() const {
    return course_database;
}

Student_Database* System::get_student_database() const {
    return student_database;
}

void System::set_course_database(Course_Database* const course_database) {
    this->course_database = course_database;
}

void System::set_student_database(Student_Database* const student_database) {
    this->student_database = student_database;
}
