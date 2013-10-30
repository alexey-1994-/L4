#include "Spisok.h"

class Spisok_impl
{
public:
    bool add_element(Other data);
    bool insert_element(Other data, int position);
    bool delete_element(int position);
    bool empty(){return begin;};

    Other find(int position);

    int get_size()
    {
        return size;
    };

    Spisok_impl():begin(0),size(0) {};
    ~Spisok_impl();
private:
    struct Spis
    {
        Other data;
        Spis *next;
    };
    Spis *begin;
    int size;
};

bool Spisok::empty()
{
    return pimpl->empty();
}

bool Spisok::add_element(Other data)
{
    return pimpl->add_element(data);
}

bool Spisok::insert_element(Other data, int position)
{
    return pimpl->insert_element(data, position);
}

bool Spisok::delete_element(int position)
{
    return pimpl->delete_element(position);
}

Other Spisok::find(int position)
{
    return pimpl->find(position);
}

int Spisok::get_size()
{
    return pimpl->get_size();
}

Spisok::Spisok()
{
    pimpl=new Spisok_impl;
}

Spisok::~Spisok()
{
    pimpl->~Spisok_impl();
    delete pimpl;
}

bool Spisok_impl::add_element(Other data)
{
    Spis *temp=new Spis, *ptr;
    if(temp==0)
        return false;

    temp->data=data;
    temp->next=0;

    if(begin)
        ptr=begin;
    else
    {
        begin=temp;
        size++;
        return true;
    }

    for(int i=0; i<size-1; i++)
        ptr=ptr->next;

    ptr->next=temp;

    size++;
    return true;
}

bool Spisok_impl::insert_element(Other data, int position)
{
    if(position>size || position<0)
        return false;

    Spis *temp=new Spis, *tmp=new Spis;
    if(temp==0)
        return false;

    temp->data=data;

    if(position==0)
    {
        temp->next=begin;                 //перестановка с begin
        begin=temp;
        size++;
        return true;
    }

    if(position==size-1)
    {
        return true;
    }

    tmp=begin;                            //переходим к заданной позиции
    for(int i=0; i<position-1; i++)
        tmp=tmp->next;

    temp->next=tmp->next;                 //перестановка
    tmp->next=temp;

    size++;
    return true;
}

bool Spisok_impl::delete_element(int position)
{
    if(position>size || position<0)
        return false;
    Spis *tmp_1=new Spis, *tmp_2=new Spis;

    if(position==0)
    {
        tmp_1=begin->next;
        delete begin;
        begin=tmp_1;
        if(size>0)
            size--;
        return true;
    }

    if(position==size-1)
    {
        Spis *tmp=begin, *del_ptr;

        for(int i=0; i<size-2; i++)
            tmp=tmp->next;
        del_ptr=tmp->next;
        tmp->next=0;

        delete del_ptr;
        size--;
        return true;
    }

    tmp_1=begin;                            //переходим к заданной позиции
    for(int i=0; i<position-1; i++)
        tmp_1=tmp_1->next;

    tmp_2=tmp_1->next;
    tmp_1->next=tmp_2->next;
    delete tmp_2;
    size--;
    return true;
}

Other Spisok_impl::find(int position)
{
    Spis *temp=new Spis;

    if(position>size)
        return '\0';

    temp=begin;
    for(int i=0; i<position; i++)
        temp=temp->next;

    return temp->data;
}

Spisok_impl::~Spisok_impl()
{
    int tmp=size;

    for(int i=0; i<tmp; i++)
        delete_element(0);
    begin=0;
}
