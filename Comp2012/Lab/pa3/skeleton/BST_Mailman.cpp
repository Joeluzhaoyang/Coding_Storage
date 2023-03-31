//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_Mailman.h"

// TODO: Constructors and Destructors
BST_Mailman::BST_Mailman(){
    this->root = nullptr;
}

BST_Mailman_Node::BST_Mailman_Node(Mail *mail){
    if(mail != nullptr){
        this->streetName = mail->getStreetName();
        currentMailsStored = 0;
        for(int i = 0; i<MAX_NUM_MAILS;i++){
            mailPtr[i] = nullptr;
        }
        this->left = nullptr;
        this->right = nullptr;
        //std::cout << "Work" << std::endl;
    }
}

BST_Mailman::~BST_Mailman(){
    if (root != nullptr){
        delete root;
    }
}

BST_Mailman_Node::~BST_Mailman_Node(){
    for (int i = 0; i <currentMailsStored; i++){
        if(mailPtr[i] != nullptr){
            delete mailPtr[i];
        }
    }
    if(getLeftBST() != nullptr){
        delete left;
    }
    if(getRightBST() != nullptr){
        delete right;
    }
}

// TODO: Getters
std::string BST_Mailman_Node::getStreetName() const{
    return this->streetName;
}

BST_Mailman * BST_Mailman_Node::getRightBST() const{
    return this->right;
}

BST_Mailman * BST_Mailman_Node::getLeftBST() const{
    return this->left;
}


// TODO add mail to the array mailPtr[] - NOTE: WE WILL NEVER ASK YOU TO
//  PUT TOO MANY MAILS. (a max of MAX_NUM_MAILS add_mail calls)
void BST_Mailman::addMail(Mail *mail)
{
    // std::cout << root << std::endl;
    if(this->root == nullptr){
        this->root = new BST_Mailman_Node(mail);
        //std::cout << root << std::endl;
    }
    if(mail->getStreetName() == root->getStreetName()){
        root->addMail(mail);
        //std::cout << root << std::endl;
    }
    else if(mail->getStreetName() < root->getStreetName()){
        if(root->getLeftBST() == nullptr){
            root->left = new BST_Mailman();
        }
        root->getLeftBST()->addMail(mail);
    }
    else if (mail->getStreetName() > root->getStreetName()){
        if (root->getRightBST() == nullptr)
        {
            root->right = new BST_Mailman();
        }
        root->getRightBST()->addMail(mail);
    }
}

void BST_Mailman_Node::addMail(Mail *mail){
    this->mailPtr[currentMailsStored] = mail;
    currentMailsStored++;
    //std::cout<<this->currentMailsStored<<std::endl;
}

// TODO: Remove a mail, given its street name and ID
bool BST_Mailman::remove(int id, std::string streetName)
{
    bool target = false;
    if (root == nullptr)
    {
        return false;
    }
    if (root->getStreetName() == streetName)
    {
        target = root->remove(id);
    }
    else if (streetName < root->getStreetName() && root->getLeftBST() != nullptr)
    {
        target = root->left->remove(id, streetName);
    }
    else if (streetName > root->getStreetName() && root->getRightBST() != nullptr)
    {
        target = root->right->remove(id, streetName);
    }
    return target;
}

bool BST_Mailman_Node::remove(int id)
{
    bool target = false;
    for (int i = 0; i < MAX_NUM_MAILS; i++)
    {
        if (mailPtr[i] != nullptr)
        {
            if (id == mailPtr[i]->getId())
            {
                delete mailPtr[i];
                mailPtr[i] = nullptr;
                target = true;
                break;
            }
        }
    }
    return target;
}

// TODO: Find a mail item, given its street name and ID
Mail * BST_Mailman::find(int id, std::string streetName)
{
    Mail* target = nullptr;
    if(root == nullptr){
        return nullptr;
    }
    if(root->getStreetName() == streetName){
        target = root->find(id);
    }
    else if(streetName < root->getStreetName() && root->getLeftBST() != nullptr){
        target = root->left->find(id,streetName);
    }
    else if (streetName > root->getStreetName() && root->getRightBST() != nullptr){
        target = root->right->find(id, streetName);
    }
    return target;
}

Mail *BST_Mailman_Node::find(int id)
{
    Mail* target = nullptr;
    for(int i = 0; i<MAX_NUM_MAILS; i++){
        if(mailPtr[i] != nullptr){
            if(id == mailPtr[i]->getId()){
                target = mailPtr[i];
                break;
            }
        }
    }
    return target;
}


// TODO: Print functions. See example outputs for the necessary formats.
void BST_Mailman::printInOrder() const
{
    if(root == nullptr){
        return;
    }
    if(root->currentMailsStored == 0 && root->left == nullptr && root->right == nullptr){
        return;
    }
    if(root->getLeftBST() != nullptr){
        root->getLeftBST()->printInOrder();
    }
    root->print();
    if (root->getRightBST() != nullptr){
        root->getRightBST()->printInOrder();
    }
}

void BST_Mailman::printPostOrder() const
{
    if (root == nullptr)
    {
        return;
    }
    if (root->currentMailsStored == 0 && root->left == nullptr && root->right == nullptr)
    {
        return;
    }
    if (root->getLeftBST() != nullptr)
    {
        root->getLeftBST()->printPostOrder();
    }
    
    if (root->getRightBST() != nullptr)
    {
        root->getRightBST()->printPostOrder();
    }
    root->print();
}

void BST_Mailman::printPreOrder() const
{
    if (root == nullptr)
    {
        return;
    }
    if (root->currentMailsStored == 0 && root->left == nullptr && root->right == nullptr)
    {
        return;
    }

    root->print();
    if (root->getLeftBST() != nullptr)
    {
        root->getLeftBST()->printPreOrder();
    }

    if (root->getRightBST() != nullptr)
    {
        root->getRightBST()->printPreOrder();
    }
    
}

void BST_Mailman_Node::print() const
{
    std::cout << "BST Node for Street: " << streetName << std::endl;
    for (int i = 0; i < currentMailsStored; ++i) {
        if(mailPtr[i] != nullptr)
        {
            mailPtr[i]->printMail();
        }
    }
}
