#ifndef SPISOK_H_INCLUDED
#define SPISOK_H_INCLUDED

typedef char Other;
class Spisok_impl;

class Spisok        //ןנûש
{
public:
    bool add_element(Other data);
    bool insert_element(Other data, int position);
    bool delete_element(int position);
    Other find(int position);
    int get_size();
    bool empty();

    Spisok();
    ~Spisok();

private:
    Spisok_impl *pimpl;
};

#endif // SPISOK_H_INCLUDED
