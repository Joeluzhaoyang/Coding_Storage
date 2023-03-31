//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_PostOffice.h"

// TODO: Constructors and Destructors

//TIP: root will be nullptr at first, and we'll add a node once we try to add a mail object.
BST_PostOffice::BST_PostOffice()
{
    this->root = nullptr;
}

BST_PostOffice_Node::BST_PostOffice_Node(Mail *mail)
{
    this->left = nullptr;
    this->right = nullptr;
    this->district = mail->getDistrict();
    //this->mailman[mail->getAddressHash()].addMail(mail);
}

BST_PostOffice::~BST_PostOffice()
{
    if(root != nullptr){
        delete root;
    }
}

BST_PostOffice_Node::~BST_PostOffice_Node()
{
    if(this->getLeftBST() != nullptr){
        delete left;
    }
    if(this->getRightBST() != nullptr){
        delete right;
    }
}

// TODO: Accessor functions.
BST_PostOffice * BST_PostOffice_Node::getLeftBST() const
{
    return this->left;
}

BST_PostOffice * BST_PostOffice_Node::getRightBST() const
{
    return this->right;
}

District BST_PostOffice_Node::getDistrict() const
{
    return this->district;
}


//TODO: Given a district, id and street name, find the mail object.
Mail *BST_PostOffice::find(District dist, int id, std::string streetName)
{
    Mail* target = nullptr;
    if (root == nullptr)
    {
        return nullptr;
    }
    if (this->root->district == dist)
    {
        target = root->find(id,streetName);
    }
    else if (dist < this->root->district && root->left != nullptr)
    {
        target = this->root->left->find(dist,id,streetName);
    }
    else if (dist > this->root->district && root->right != nullptr)
    {
        target = this->root->right->find(dist, id, streetName);
    }
    return target;
}

Mail *BST_PostOffice_Node::find(int id, std::string streetName)
{
    Mail* target = nullptr;
    for(int i = 0; i<HASH_MODULO; i++){
        Mail* temp = nullptr;
        temp = mailman[i].find(id,streetName);
        if(temp != nullptr){
            target = temp;
            break;
        }
    }
    return target;
}


// TODO: Given a district, id and street name, remove the mail object from the
// system.
bool BST_PostOffice::remove(District dist, int id, std::string streetName)
{
    bool tof = false;
    if (root == nullptr)
    {
        return false;
    }
    if (this->root->district == dist)
    {
        tof = root->remove(id, streetName);
    }
    else if (dist < this->root->district && root->left != nullptr)
    {
        tof = this->root->left->remove(dist, id, streetName);
    }
    else if (dist > this->root->district && root->right != nullptr)
    {
        tof = this->root->right->remove(dist, id, streetName);
    }
    return tof;
}

bool BST_PostOffice_Node::remove(int id, std::string streetName)
{
    bool target = false;
    for (int i = 0; i < HASH_MODULO; i++)
    {
        bool temp = false;
        temp = mailman[i].remove(id, streetName);
        if (temp != false)
        {
            target = temp;
            break;
        }
    }
    return target;
}

// TODO: Add mail to the system
void BST_PostOffice::addMail(Mail *mail)
{
    if(root == nullptr){
        root = new BST_PostOffice_Node(mail);
    }
    if(mail->getDistrict() == this->root->getDistrict()){
        this->root->addMail(mail);
        //std::cout << root << std::endl;
    }
    else if (mail->getDistrict() < this->root->getDistrict()){
        if(root->getLeftBST() == nullptr){
            root->left = new BST_PostOffice();
        }
        this->root->left->addMail(mail);
    }
    else if(mail->getDistrict() > this->root->getDistrict()){
        if (root->getRightBST() == nullptr){
            root->right = new BST_PostOffice();
        }
        this->root->right->addMail(mail);
    }
    return;
}

void BST_PostOffice_Node::addMail(Mail *mail){
    // std::cout << mail->getAddressHash() << std::endl;
    mailman[mail->getAddressHash()].addMail(mail);
    return;
}

// TODO: Given a district, print all of the data in it.
// TIP: Print style depends on type.
void BST_PostOffice::printDistrict(District dist, printType type) const
{
    if(root == nullptr){
        return;
    }
    if(this->root->district == dist){
        std::cout<<"The District Mail Report for district "<<dist<<std::endl;
        this->root->print(type);
    }
    else if (dist < this->root->district && root->left != nullptr){
        this->root->left->printDistrict(dist,type);
    }
    else if (dist > this->root->district && root->right != nullptr){
        this->root->right->printDistrict(dist, type);
    }
    return;
    //     for (BST_PostOffice_Node *a = this->root; a != nullptr; a = a->getLeftBST()->root)
    //     {
    //         printDistrict(dist, type);
    //     }
    // for (BST_PostOffice_Node *a = this->root; a != nullptr; a = a->getRightBST()->root){
    //     printDistrict(dist, type);
    // }
}

void BST_PostOffice_Node::print(printType type) const
{
    for(int i = 0; i<HASH_MODULO;i++){
        std::cout <<"For Mailman "<<i<<std::endl;
        switch (type)
        {
        case printType::inorder:
            mailman[i].printInOrder();
            break;
        case printType::postorder:
            mailman[i].printPostOrder();
            break;
        case printType::preorder :
            mailman[i].printPreOrder();
            break;
        default:
            break;
        }
    }
    return;
}

// TODO: Given a district and ID of the mailman, print all mail in it
// TIP: Print style depends on type - see the header file
void BST_PostOffice::printMailman(District district, int i, printType type) const
{
    if(root == nullptr){
        return;
    }
    if(this->root->getDistrict() == district){
        root->printMailman(i,type);
    }
    else if (district < this->root->district && root->left != nullptr){
        root->left->printMailman(district,i,type);
    }
    else if (district > this->root->district && root->right != nullptr){
        root->right->printMailman(district,i,type);
    }
}

void BST_PostOffice_Node::printMailman(int i, printType type) const
{
    switch (type)
    {
    case printType::inorder:
        mailman[i].printInOrder();
        break;
    case printType::postorder:
        mailman[i].printPostOrder();
        break;
    case printType::preorder:
        mailman[i].printPreOrder();
        break;
    default:
        break;
    }
}

// TODO: Other print functions.
void BST_PostOffice::printInOrder() const
{   

    if(root->getLeftBST() != nullptr){
        root->left->printInOrder();
    }
    if (this->root != nullptr){
        std::cout << "BST Node for District: " << root->getDistrict() << std::endl;
        for(int i = 0; i<HASH_MODULO; i++){
            root->mailman[i].printInOrder();
        }
    }
    if(root->getRightBST() != nullptr){
        root->right->printInOrder();
    }
}

void BST_PostOffice::printPostOrder() const
{
    
    if (root->getLeftBST() != nullptr)
    {
        root->left->printPostOrder();
    }
    if (root->getRightBST() != nullptr)
    {
        root->right->printPostOrder();
    }
    if (this->root != nullptr)
    {
        std::cout << "BST Node for District: " << root->getDistrict() << std::endl;
        for (int i = 0; i < HASH_MODULO; i++)
        {
            root->mailman[i].printPostOrder();
        }
    }
}

void BST_PostOffice::printPreOrder() const{
    if (this->root != nullptr){
        std::cout << "BST Node for District: " << root->getDistrict() << std::endl;
        for (int i = 0; i < HASH_MODULO; i++)
        {
            root->mailman[i].printPreOrder();
        }
    }
    if (root->getLeftBST() != nullptr){
        root->left->printPreOrder();
    }
    if (root->getRightBST() != nullptr){
        root->right->printPreOrder();
    }
    return;
}