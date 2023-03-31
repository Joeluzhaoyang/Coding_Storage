#include "container.h"
#include <iostream>

void Container::addObject(Object *object)   //Task 1&3
{
        if (_num_object < MAX_OBJECT_NUM)
    {
        Pair test;
        test.x = this->getPosition().x + object->getSize().x;
        test.y = this->getPosition().y + object->getSize().y;
        if(test.x > this->getSize().x || test.y > this->getSize().y)
        {
            std::cout<<"The object "<<object->getName()<<" is too large and cannot be added to "<<this->getName()<<endl;;
            return;
        }
        
        _objects[_num_object++] = object;
        object->setParent(this);
        
    }
}

void Container::display() const //Task 1
{
    std::cout << "\nContainer";
    this->displayBasic();
    std::cout <<"\n\t\t";
    if(this->_num_object!=0)  
        {std::cout<<"#objects: "<<this->_num_object<<endl;}
    int count_display = 0;
    while(count_display != _num_object)
    {
        _objects[count_display]->display();
        count_display++;
    }
}

Container::Container() 
{
    for (int i = 0; i < MAX_OBJECT_NUM; i++)
        _objects[i] = nullptr;

    _num_object = 0;
}

Container::~Container()  //Task 1
{
    cout<<"\nDestructing Container "<< getName();
    for(int i = 0; i != _num_object;i++)
    {
        delete _objects[i];
    }

}