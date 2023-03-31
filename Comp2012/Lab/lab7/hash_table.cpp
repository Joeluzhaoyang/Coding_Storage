#include "hash_table.h"
#include <cmath>
#include <iostream>

int HashTable::hashFunction(const std::string &name, int base, int table_size) {
  int res = 0;
  for (unsigned int i = 0; i < name.size(); i++) {
    res = (base*res + name[i] - 'a') % table_size;
  }
  return res;
}

int HashTable::getNextHashTableSize(int now_hash_table_size) {
  int res = now_hash_table_size*2;
  bool is_prime = false;
  while (true) {
    is_prime = true;
    int sq = sqrt(res);
    for (int i = 2; i <= sq; i++) {
      if (res % i == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      break;
    res++;
  }
  return res;
}

HashTable::HashTable(int init_size, int maximum_probe_num,
                     ProbeMode probe_mode): base_1_(37),base_2_(41), hash_table_size_(init_size), maximum_probe_num_(maximum_probe_num)
                      {  // Task 1 
    probe_mode_ = probe_mode;

    table_ = new HashCell[hash_table_size_];
    for(int i = 0 ; i < hash_table_size_ ; i++){
      this->table_[i].student = nullptr;
      this->table_[i].state = HashCellState::Empty;
    }
    switch(probe_mode){
      case ProbeMode::Linear:
        this->probe_func_ = [](int hash_value1, int hash_value2, int num_probe, int hash_table_size){
          int p = (hash_value1 + num_probe) % hash_table_size;
          std::cout << "Probing for the position: " << p << std::endl;
          return p;
        };
        break;
      

      case ProbeMode::Quadratic:
        this->probe_func_ = [](int hash_value1, int hash_value2, int num_probe, int hash_table_size){
          int p = (hash_value1 + num_probe*num_probe) % hash_table_size;
          std::cout << "Probing for the position: " << p << std::endl;
          return p;
        };
        break;
      

      case ProbeMode::DoubleHash:
        this->probe_func_ = [](int hash_value1, int hash_value2, int num_probe, int hash_table_size){
          int p = (hash_value1 + num_probe * hash_value2) % hash_table_size;
          std::cout << "Probing for the position: " << p << std::endl;
          return p;
        };
        break;
        default:
        break;
      
    }
}

HashTable::~HashTable() {  // Task 1
  delete[ ]table_;

}

bool HashTable::add(const std::string &name, int score) {  // Task 2 & 5
  int hash_value1 = hashFunction(name,base_1_,hash_table_size_);
  int hash_value2 = 0;
  if(probe_mode_ == ProbeMode::DoubleHash){
     hash_value2 = hashFunction(name,base_2_,hash_table_size_);
    if(hash_value2 == 0){
      hash_value2 = 1;
    }
  }
  
  for(int num_probe = 0 ; num_probe < maximum_probe_num_ ; num_probe++)
  {
    int pos = probe_func_(hash_value1,hash_value2,num_probe,hash_table_size_);
    if (table_[pos].state == HashCellState::Active){
      if(table_[pos].student->name() == name){
        return false;
      }
    }
    else{
      table_[pos].state = HashCellState::Active;
      table_[pos].student = new Student(name,score);
      return true;
    }
  }
  reHashUntilSuccess();
  return add(name, score);
}

int HashTable::search(const std::string &name) const {  // Task 3
  int hash_value1 = hashFunction(name,base_1_,hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash){
    hash_value2 = hashFunction(name, base_2_, hash_table_size_);
    if (hash_value2 == 0){
      hash_value2 = 1;
    }
  }

  int i = 0;
  while( i < hash_table_size_){//testing
    int pos = probe_func_(hash_value1, hash_value2, i, hash_table_size_);
    i++;
    if (table_[pos].state == HashCellState::Deleted){
      continue;
    }
    else if (table_[pos].state == HashCellState::Active){
      if(table_[pos].student->name() == name){
        return table_[pos].student->score();
      }
    }
    else if (table_[pos].state == HashCellState::Empty){
      return -1;
    }
  }
  return -1;
}

bool HashTable::remove(const std::string &name) {  // Task 4
  int hash_value1 = hashFunction(name,base_1_,hash_table_size_);
  int hash_value2 = 0;
  if (probe_mode_ == ProbeMode::DoubleHash)
  {
    hash_value2 = hashFunction(name, base_2_,hash_table_size_);
    if (hash_value2 == 0)
    {
      hash_value2 = 1;
    }
  }

  for(int i = 0; i < hash_table_size_; i++){
    int pos = probe_func_(hash_value1, hash_value2, i, hash_table_size_);
    
    if (table_[pos].state == HashCellState::Deleted){
      continue;
    }
    else if(table_[pos].state == HashCellState::Active)
    {
      if(table_[pos].student->name() == name){
        delete table_[pos].student;
        table_[pos].student = nullptr;
        table_[pos].state = HashCellState::Deleted;
        return true;
      }
    }
    else if (table_[pos].state == HashCellState::Empty){
      return false;
    }
  }
  return false;
}

void HashTable::reHashUntilSuccess() {
  int next_hash_table_size = getNextHashTableSize(hash_table_size_);
  while (true) {
    if (reHash(next_hash_table_size)) {
      return;
    }
    next_hash_table_size = getNextHashTableSize(next_hash_table_size);
  }
}

bool HashTable::reHash(int rehash_table_size) {  // Task 5
  HashCell* newTable= new HashCell[rehash_table_size];
  for(int i = 0; i < rehash_table_size; i++){
    newTable[i].state = HashCellState::Empty;
    newTable[i].student = nullptr;
  }//init

  for(int i = 0; i < hash_table_size_; i++){
    if(table_[i].state == HashCellState::Active){
      int hash_value1 = hashFunction(table_[i].student->name(),base_1_,rehash_table_size);
      int hash_value2 = 0;
      bool tof = false;
      if (probe_mode_ == ProbeMode::DoubleHash)
      {
        hash_value2 = hashFunction(table_[i].student->name(), base_2_, rehash_table_size);
        if (hash_value2 == 0)
        {
          hash_value2 = 1;
        }
      }

      for(int j = 0; j<maximum_probe_num_; j++){//insert to new table
        int pos = probe_func_(hash_value1,hash_value2,j,rehash_table_size);
        if(newTable[pos].state == HashCellState::Empty){
          newTable[pos].state = HashCellState::Active;
          newTable[pos].student = new Student(*table_[i].student);
          tof = true;
          break;
        }
      }
      if(tof == false){
        delete[] newTable;
        return false;
      }
    
    }
    else if (table_[i].state == HashCellState::Deleted){
      continue;
    }
  }
  this->hash_table_size_ = rehash_table_size;
  delete[] table_;
  table_ = newTable;
  return true;
}

void HashTable::print() const {
  std::cout << "hash_table_size:" << hash_table_size_ << std::endl;
  for (int i = 0; i < hash_table_size_; i++) {
    std::cout << i << ": state = ";
    if (table_[i].state == HashCellState::Empty) {
      std::cout << "Empty" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Deleted) {
      std::cout << "Deleted" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Active) {
      std::cout << "Active ";
      std::cout << "Student = (" << table_[i].student->name() << ", "
                << table_[i].student->score() << ")" << std::endl;
    }
  }
}
