#ifndef TEXT_EDITOR_H_INCLUDED
#define TEXT_EDITOR_H_INCLUDED

#include "Spisok.h"

class Text_Editor;

class TextEditor
{
public:
    void load_text(char *name);
    void save_text(char *name);

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

    int get_x();
    int get_y();
    int get_x_select();
    int get_y_select();

    TextEditor();
    ~TextEditor();

protected:
    Spisok *get_text();
    void set_x_select(int x);
    void set_y_select(int y);
    void set_max_size_string(int size);

private:
    Text_Editor *pimpl;
};

#endif // TEXT_EDITOR_H_INCLUDED
