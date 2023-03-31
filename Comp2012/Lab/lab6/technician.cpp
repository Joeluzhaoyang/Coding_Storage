#include <iostream>
#include "technician.h"
#include "computer.h"
#include "electronics.h"

const int MAX_NUM_TECHNICIAN = 10;

// TODO: initialize the static varibles of class Technician
Technician* Technician::technician_list[MAX_NUM_TECHNICIAN] = {nullptr};
int Technician::num_technician = 0;

// TODO: Implement the constructor
Technician::Technician(std::string name, Diagnosis_Tool* diagnosis_tool){
    this->name = name;
    this->diagnosis_tool = diagnosis_tool;
    this->num_order_finished = 0;

    technician_list[num_technician] = this;
    num_technician++;
}

Technician::~Technician(){
    delete diagnosis_tool;
}

CPU* Technician::acquire_CPU(CPU_Model model) const {
    return new CPU(model);
}

MEM* Technician::acquire_MEM(MEM_Model model) const {
    return new MEM(model);
}

// TODO: implement repair function
void Technician::repair(Computer* computer){
    bool tof1 = diagnosis_tool->diagnose(computer->cpu);
    bool tof2 = diagnosis_tool->diagnose(computer->mem);
    if(tof1 == false){
        CPU* newcpu = acquire_CPU(computer->cpu->model);
        delete computer->cpu;
        computer->cpu = newcpu;
        computer->cpu->defect_count++;
    }
    if(tof2 == false){
        MEM* newmem = acquire_MEM(computer->mem->model);
        delete computer->mem;
        computer->mem = newmem;
        computer->mem->defect_count++;
    }
    this->num_order_finished++;
}

void Technician::print_report(){
    std::cout << "----------------------" << std::endl;
    std::cout << "REPORT FOR TECHNICIANS" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout.width(20);
    std::cout << std::left << "NAME" << "ORDERS_COMPLETED" << std::endl;
    for(int i = 0; i < num_technician; ++i){
        std::cout.width(20);
        std::cout << std::left << technician_list[i]->name << technician_list[i]->num_order_finished << std::endl;
    }
}
