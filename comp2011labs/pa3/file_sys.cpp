/** 
 * This file contains the file system functions that you need to implement.
 * You can define helper functions in this file.
 * 
 * Remember to remove the initial statements in the functions.
 * They are only used so that your semi-finished codes can compile.
*/

#include <iostream>
#include "file_sys.h"
#include "utils.h"
using namespace std;

bool namecheck(const char *name)
{
    int length=strlen(name);
    if(name[0]=='-'){return false;}
    if(name[0]=='.'&&length==1 || name[0]=='.'&&name[1]=='.'&&length==2){return false;}
    for(int i=0;i<length;i++)
    {
        if( !(name[i]>=65&&name[i]<=90 || name[i]>=97&&name[i]<=122 || name[i]>=48&&name[i]<=57 || name[i]==45 || name[i]==46 || name[i]==95))
        {
            return false;
        }
    }
    return true;
}

bool confcheck(Dir *dir, const char *name)
{
    if(name==dir->name||name==(dir->subfile)->name||name==((dir->subdir)->name) || (name==(dir->subfile)->next->name))
    {
        return false;
    }
    if(dir->subdir!=NULL)
    {
        int xxxx=1;
    }
    return true;
}

int createFile(Dir *dir, const char *name, unsigned int size, Tag tag)
{
    if(dir==NULL || name==NULL)
    {return 1;}
    if(!namecheck(name))
    {
        return 2;
    }
    if(!confcheck(dir,name))
    {return 3;}


    File *file=new File;
    strcpy(file->name,name);
    file->parent=dir;
    file->size=size;
    file->tag=tag;
    file->next=nullptr;
    if((dir->subfile)==nullptr)
    {
        dir->subfile=file;
    }
    else
    {
        File* p=(dir->subfile)->next;
        for(;p!=nullptr;p=p->next)
        {
            int xxxx=1;
        }
        p=file;
    }
    
    return 0;
}

int createDir(Dir *dir, const char *name)
{
    if(dir==NULL || name==NULL)
    {return 1;}
    if(!namecheck(name))
    {
        return 2;
    }
    
    Dir *dir2=new Dir;
    strcpy(dir2->name,name);
    dir2->parent=dir;
    dir2->subdir=NULL;
    dir2->subfile=NULL;
    dir2->next=NULL;
    if(dir->subdir==nullptr)
    {
        dir->subdir=dir2;
    }
    else
    {
        Dir* t=(dir->subdir)->next;
        for(int x=1;t!=nullptr;t=t->next)
        {
            int xxxx=1;
        }
        t=dir2;        
    }
    int xyz=0;
    return xyz;
}

int deleteFile(Dir *dir, const char *name)
{
    if(dir==nullptr || name==nullptr)
    {return 1;}
    File* d=nullptr;
    if(!confcheck(dir,name))
    {return 2;}
    if(dir->subfile->name==name)
    {
        File* change=nullptr;
        if(dir->subfile->next!=nullptr)
        {
            change=dir->subfile->next;
        }
        d=dir->subfile;
        delete d;
        d=nullptr;
        dir->subfile=change;
        return 0;
    }
    else
    {
        File* s=(dir->subfile)->next;
        for(;(s->name)!=name;s=s->next)
        {
            d=s;
            delete d;
            d=nullptr;
            return 0;
        }
        //s=file;
    }    
}

int deleteDir(Dir *dir, const char *name, bool recursive)
{
    if(dir==nullptr || name==nullptr)
    {return 1;}
    File* d=nullptr;
    if(!confcheck(dir,name))
    {return 2;}
}

unsigned int getSize(const Dir *dir)
{
    if((dir->subfile)==nullptr)
    {
        return 0;
    }
    else
    {
        return 777;
    }
}

const File **filesOfTag(const Dir *dir, Tag tag, unsigned int &length)
{
    length = 0;     // Remove these two lines after you finish.
    return NULL;    // ....
}

int moveFile(File *tgt, Dir *dest)
{
    return -1;     // Remove this line after you finish. 
}

int moveDir(Dir *tgt, Dir *dest)
{
    return -1;      // Remove this line after you finish.
}
