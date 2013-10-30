/*
навигация:

ctrl+i - вверх
ctrl+k - вниз
ctrl+j - влево
ctrl+l - вправо

управление:

1-выделение(наощупь-пометил начало,пометил конец)
2-вставка выделенного,т.е копирование
*/
#include <iostream>
#include <fstream>
using namespace std;
#include <conio.h>
#include <windows.h>
#include "Text Editor.h"
#include "Spisok.h"

class Console_Text_Editor:public TextEditor
{
public:
    Spisok *get_text()
    {
        return TextEditor::get_text();
    }
};

void redraw(Spisok *buf, int selection_begin, int selection_end);
void gotoxy(short x, short y);

int main()
{
    Console_Text_Editor editor;

    Spisok *text;
    unsigned char key=0;
    int x=0,y=0, x_select=0, y_select=0;

    editor.load_text("temp.txt");
    text=editor.get_text();
    if(text)
        redraw(text, x_select, y_select);
    gotoxy(x,y);

    while(true)
    {
//-----------------ВВОД ТЕКСТА------------------------------------------//
        if(kbhit())
        {
            key=getch();

            if((175>=key && key>=52)||(key<=48 && key>=32) || (key>=224 && key<=241) || key==13)//исключаем управляющие кнопки
            {
                editor.add_symbol(key);
                redraw(text, 0, 0);
                x=editor.get_x();
                y=editor.get_y();
                gotoxy(x,y);
            }
        }
//---------------------------------------------------------------------//

        switch(key)
        {
            //--------------навигация по тексту---------------------//
        case 10:                                //ctrl+j
            editor.go_left();
            x=editor.get_x();
            y=editor.get_y();
            gotoxy(x, y);
            break;
        case 12:        //ctrl+l
            editor.go_right();
            x=editor.get_x();
            y=editor.get_y();
            gotoxy(x,y);
            break;
        case 11:        //ctrl+k
            editor.go_down();
            x=editor.get_x();
            y=editor.get_y();
            gotoxy(x, y);
            break;
        case 9:          //ctrl+i
            editor.go_up();
            x=editor.get_x();
            y=editor.get_y();
            gotoxy(x, y);
            break;



            //-------------управление---------------
        case 8:                                             //backspace
            {
                if(editor.text_empty())
                    editor.delete_selection();
                else
                    editor.backspace();
                x=editor.get_x();
                y=editor.get_y();
                redraw(text, 0, 0);
                gotoxy(x, y);
                break;
            }

        case '1':
            {
                editor.selection();
                break;
            }

        case '2':                                       //вставка
            {
                editor.insert_selection();
                redraw(text, 0, 0);
                gotoxy(x, y);
                break;
            }
        }

        if(key==27)
            break;

        key=0;
        Sleep(1);
    }

    editor.save_text("temp.txt");
    return 0;
}

void redraw(Spisok *buf, int selection_begin, int selection_end)
{
    system("cls");
    gotoxy(0,0);
    for(int i=0; i<buf->get_size(); i++)
    {
        if(buf->find(i)==13)
            cout<<endl;
        else
        {
            if(i<=selection_end && i>selection_begin)
            {
                //SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_RED);
                cout<<buf->find(i);
            }
            else
            {
                //SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | FOREGROUND_RED);
                cout<<buf->find(i);
            }
        }
    }
}

void gotoxy(short x, short y)
{
    COORD position= {x,y};
    SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), position);
}
