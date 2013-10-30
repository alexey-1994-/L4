#include "Text Editor.h"
#include <fstream>
using namespace std;

//------------------------------------------------IMPL----------------------------------//
class Text_Editor
{
public:
    void load_text(char *name);
    void save_text(char *name);

    void set_max_size_string(int size);

    void go_up();
    void go_down();
    void go_left();
    void go_right();

    void backspace();
    void selection();
    void insert_selection();
    void delete_selection();
    void add_symbol(char symbol);

    bool is_selected();
    bool text_empty();

    void set_x_select(int x);
    void set_y_select(int y);
    int get_x(){return x;};
    int get_y(){return y;};
    int get_x_select(){return x_select;};
    int get_y_select(){return y_select;};

    Spisok *get_text(){return text;};

    Text_Editor();
    ~Text_Editor();

protected:

private:
    Spisok
           *text,
           *selected;

    int
            max_size_x,
            max_y,

            x,
            y,

            x_select,
            y_select;

    bool
            select;

    int size_y_in_all_text();            //возвращает количество строк в тексте
    int size_string(int y);              //полный размер строки в позиции у
    int position_to_cursor(int x, int y);//возвращает номер елемента в списке в позиции ху
};

bool Text_Editor::text_empty()
{
    return selected->empty();
}

bool Text_Editor::is_selected()
{
    return selected;
}

void Text_Editor::delete_selection()
{
    int size=selected->get_size();

    if(position_to_cursor(x_select, y_select) < position_to_cursor(x, y))
    {
        for(int i=0; i<size; i++)
            text->delete_element(position_to_cursor(x_select, y_select));
        x=x_select; y=y_select;
    }
    else
        if(position_to_cursor(x_select, y_select) > position_to_cursor(x, y))
            for(int i=0; i<size; i++)
                text->delete_element(position_to_cursor(x, y));

    x_select=x;
    y_select=y;
    select=false;
    selected->~Spisok();
}

void Text_Editor::insert_selection()
{
    int size=selected->get_size();

    for(int i=0; i<size; i++)
        text->insert_element(selected->find(i), i+position_to_cursor(x, y));
    max_y=size_y_in_all_text();
}

void Text_Editor::selection()
{
    if(select)
    {
        int size;

        select=false;
        if(position_to_cursor(x, y) < position_to_cursor(x_select, y_select))
        {
            size=position_to_cursor(x_select, y_select);
            for(int i=position_to_cursor(x, y); i<size; i++)
                selected->add_element(text->find(i));
        }
        else
        {
            size=position_to_cursor(x ,y);
            for(int i=position_to_cursor(x_select, y_select); i<size; i++)
                selected->add_element(text->find(i));
        }

    }
    else
    {
        select=true;
        x_select=x;
        y_select=y;
        selected->~Spisok();
    }
}

void Text_Editor::backspace()
{
    if(x==0)
        if(y!=0)
        {
            y--;
            x=size_string(y)-1;
            max_y--;
        }
        else
            return;
    else
        x--;
    text->delete_element(position_to_cursor(x, y));
}

void Text_Editor::go_up()
{
    if(y>0)
    {
        y--;
        if(size_string(y)-1<x)
            x=size_string(y)-1;
    }
}

void Text_Editor::go_down()
{
    if(y<max_y)
    {
        y++;
        if(size_string(y)-1<x)
            x=size_string(y)-1;
    }
}

void Text_Editor::go_left()
{
    if(x>0)
        x--;
    else
        if(y>0)
        {
            y--;
            x=size_string(y)-1;
        }
}

void Text_Editor::go_right()
{
    if(x<size_string(y)-1)
        x++;
    else
        if(y<max_y)
        {
            x=0;
            y++;
        }
}

void Text_Editor::add_symbol(char symbol)
{
    if(x<max_size_x)
    x++;
    else
    {
        x=0;
        y++;
        max_y++;
    }
    text->insert_element(symbol, position_to_cursor(x-1, y));
    if(symbol==13)
    {
        max_y++;
        y++;
        x=0;
    }
}

int Text_Editor::position_to_cursor(int x, int y)
{
    int size=x;

    for(int i=0; i<y; i++)
        size+=size_string(i);

    return size;
}

int Text_Editor::size_string(int y)
{
    int size=1, y_t=0, i=0, verify_on_end_string=0;

    while(y!=y_t)
    {
        if(text->find(i)==13 || verify_on_end_string==max_size_x)
        {
            verify_on_end_string=0;
            y_t++;
        }
        verify_on_end_string++;
        i++;
    }
    while(true)
    {
        if(i>=text->get_size() || text->find(i)==13 || size>max_size_x-1)
            break;
        i++;
        size++;
    }

    return size;
}

int Text_Editor::size_y_in_all_text()
{
    int i_tmp=0, num_sym_in_string=0, size=text->get_size();

    for(int i=0; i<size; i++)
    {
        if(text->find(i)=='\n')
        {
            i_tmp++;
            num_sym_in_string=0;
        }
        if(num_sym_in_string==max_size_x-1)
        {
            num_sym_in_string=0;
            i_tmp++;
        }
        num_sym_in_string++;
    }

    return i_tmp;
}

void Text_Editor::load_text(char *name)
{
    ifstream f;
    char ch_tmp;
    f.open(name);
    if(f==0)
        return;

    text=new Spisok;

    while(true)
    {
        ch_tmp=f.get();
        if(f.eof())
            return;
        text->add_element(ch_tmp);
    }

    max_y=size_y_in_all_text();
    f.close();
}

void Text_Editor::save_text(char *name)
{
    int size=text->get_size();

    ofstream f;
    f.open(name);

    for(int i=0; i<size; i++)
    {
        if(text->find(i)!=13)
            f<<text->find(i);
        else f<<endl;
    }
    f.close();
}

void Text_Editor::set_max_size_string(int size)
{
    max_size_x=size;
}

Text_Editor::Text_Editor()
{
    text=new Spisok;
    selected=new Spisok;
    max_size_x=80;
    select=false;
    x_select=0;
    y_select=0;
    max_y=0;
    y=0;
    x=0;
}

Text_Editor::~Text_Editor()
{
    text->~Spisok();
    selected->~Spisok();
}

//----------------------------------------------ПРЫЩ------------------------------------//

void TextEditor::load_text(char *name)
{
    pimpl->load_text(name);
}

void TextEditor::save_text(char *name)
{
    pimpl->save_text(name);
}

void TextEditor::set_max_size_string(int size)
{
    pimpl->set_max_size_string(size);
}

void TextEditor::go_up()
{
    pimpl->go_up();
}

void TextEditor::go_down()
{
    pimpl->go_down();
}

void TextEditor::go_left()
{
    pimpl->go_left();
}

void TextEditor::go_right()
{
    pimpl->go_right();
}

void TextEditor::backspace()
{
    pimpl->backspace();
}

void TextEditor::selection()
{
    pimpl->selection();
}

void TextEditor::insert_selection()
{
    pimpl->insert_selection();
}

void TextEditor::delete_selection()
{
    pimpl->delete_selection();
}

void TextEditor::add_symbol(char symbol)
{
    pimpl->add_symbol(symbol);
}

bool TextEditor::is_selected()
{
    return pimpl->is_selected();
}

bool TextEditor::text_empty()
{
    return pimpl->text_empty();
}

int TextEditor::get_x()
{
    return pimpl->get_x();
}

int TextEditor::get_y()
{
    return pimpl->get_y();
}

int TextEditor::get_x_select()
{
    return pimpl->get_x_select();
}

int TextEditor::get_y_select()
{
    return pimpl->get_y_select();
}

TextEditor::TextEditor()
{
    pimpl=new Text_Editor;
}

TextEditor::~TextEditor()
{
    pimpl->~Text_Editor();
    delete pimpl;
}

Spisok* TextEditor::get_text()
{
    return pimpl->get_text();
}
