#include <bits/stdc++.h>
#include <windows.h>
#include <graphics.h>

#include "draw_elem.h"

FILE *lldata;
FILE *qudata;
FILE *stdata;


int mX;
int mY;


section navbar;
section work;
section opt;
section show_opt;
section calculator;

button nav_buttons[4];

#include "linked_list.h"
#include "double_list.h"
#include "stack.h"
#include "queue.h"

void ll();
void ld ();
void st();
void qu();

void draw_essentials()
{
    draw_section(navbar);
    draw_section(work);
    draw_section(opt);

    {
        strcpy(nav_buttons[0].content, "L. SIMPLA");
        strcpy(nav_buttons[1].content, "L. DUBLA");
        strcpy(nav_buttons[2].content, "STIVA");
        strcpy(nav_buttons[3].content, "COADA");

        nav_buttons[0].corner.x = 3;
        nav_buttons[0].corner.y = 0;
        nav_buttons[0].L = textwidth("L. SIMPLA");
        nav_buttons[0].l = navbar.l;
        nav_buttons[0].textcolor = YELLOW;
        nav_buttons[0].color = MAGENTA;

        for(int i = 1; i < 4 ; i++)
        {
            nav_buttons[i].corner.x = nav_buttons[i - 1].corner.x + nav_buttons[i - 1].L +  3;
            nav_buttons[i].corner.y = 0;
            nav_buttons[i].L = textwidth("L. SIMPLA");
            nav_buttons[i].l = navbar.l;
            nav_buttons[i].textcolor = YELLOW;
            nav_buttons[i].color = MAGENTA;
        }

    }

    for(int i = 0; i < 4; i++)
        if(BisHovered(mX, mY,nav_buttons[i]))
        {
            nav_buttons[i].color++;
            if(i == 0)
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    nav_buttons[i].textcolor++;
                    ll();
                }
            if( i == 1)
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    nav_buttons[i].textcolor++;
                    ld();
                }
            if(i == 2)
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    nav_buttons[i].textcolor++;
                    st();
                }
            if(i == 3)
            {
                if(GetAsyncKeyState(VK_LBUTTON))
                {
                    nav_buttons[i].textcolor++;
                    qu();
                }

            }
        }
    for(int i = 0 ; i < 4 ; i++)
        draw_button(nav_buttons[i], navbar);
}



int main()
{
    //::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    initwindow(width, height, "BIB_LIS", screenWidth * 10 / 100, screenHeight * 10 / 100);


    navbar.corner_up.x = 0;
    navbar.corner_up.y = 0;
    navbar.L = width;
    navbar.l = 40;
    navbar.corner_down.x = navbar.corner_up.x + navbar.L;
    navbar.corner_down.y = navbar.corner_up.y + navbar.l;
    navbar.color = YELLOW;

    work.L = width * 95 / 100;
    work.l = height * 90 / 100;
    work.corner_up.x = width * 2.5 / 100;
    work.corner_up.y = navbar.corner_down.y + 10;
    work.corner_down.x = work.corner_up.x + work.L;
    work.corner_down.y = work.corner_up.y + work.l;
    work.color = WHITE;

    opt.L = work.corner_up.x;
    opt.l = 200;
    opt.corner_down.x = work.corner_up.x;
    opt.corner_down.y = work.corner_down.y;
    opt.corner_up.x = 0;
    opt.corner_up.y = opt.corner_down.y - opt.l;
    opt.color = GREEN;

    int space = 5;

    show_opt.L = 200;
    show_opt.l = opt.l;
    show_opt.corner_up.x = opt.corner_down.x + space;
    show_opt.corner_up.y = opt.corner_up.y;
    show_opt.corner_down.x = opt.corner_down.x + space + show_opt.L;
    show_opt.corner_down.y = opt.corner_down.y;
    show_opt.color = opt.color;

    calculator.L = 350;
    calculator.l = show_opt.l;
    calculator.corner_up.x = show_opt.corner_down.x + space;
    calculator.corner_up.y = show_opt.corner_up.y;
    calculator.corner_down.x = show_opt.corner_down.x + space + calculator.L;
    calculator.corner_down.y = show_opt.corner_down.y;
    calculator.color = show_opt.color;



    int showed = 0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {

        setbkcolor(9);
        cleardevice();

        draw_essentials();

        mX = mousex();
        mY = mousey();


        swapbuffers();
        delay(100);
    }


    getch();
    return 0;
}

void calculate(button &B, int &x)
{
    if(GetAsyncKeyState(0x30) || GetAsyncKeyState(VK_NUMPAD0))
        x = x * 10 + 0;
    if(GetAsyncKeyState(0x31) || GetAsyncKeyState(VK_NUMPAD1))
        x = x * 10 + 1;
    if(GetAsyncKeyState(0x32) || GetAsyncKeyState(VK_NUMPAD2))
        x = x * 10 + 2;
    if(GetAsyncKeyState(0x33) || GetAsyncKeyState(VK_NUMPAD3))
        x = x * 10 + 3;
    if(GetAsyncKeyState(0x34) || GetAsyncKeyState(VK_NUMPAD4))
        x = x * 10 + 4;
    if(GetAsyncKeyState(0x35) || GetAsyncKeyState(VK_NUMPAD5))
        x = x * 10 + 5;
    if(GetAsyncKeyState(0x36) || GetAsyncKeyState(VK_NUMPAD6))
        x = x * 10 + 6;
    if(GetAsyncKeyState(0x37) || GetAsyncKeyState(VK_NUMPAD7))
        x = x * 10 + 7;
    if(GetAsyncKeyState(0x38) || GetAsyncKeyState(VK_NUMPAD8))
        x = x * 10 + 8;
    if(GetAsyncKeyState(0x39) || GetAsyncKeyState(VK_NUMPAD9))
        x = x * 10 + 9;
    if(GetAsyncKeyState(VK_BACK))
        x = x / 10;

    char c[10];
    itoa(x, c, 10);
    strcpy(B.content, c);

}

void ll()
{
    lldata = fopen("lldata","r+");

    LL* p;
    p = NULL;

    p = read_lldata(p);

    int poz = 0;
    int info = 0;
    int showed = 0;
    int show_cal = 0;

    for(int i = 1; i <= 100; i++)
        boxes[i].color = WHITE;

    int selected[10],show_c[10];
    for(int i = 0; i< 10; i++)
        selected[i] = 0, show_c[i] = 0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        setviewport(0,0, width, height, 1);
        setbkcolor(9);
        cleardevice();
        mX = mousex();
        mY = mousey();

        draw_essentials();


        draw_LL(p, work);

        setviewport(0,0, width, height, 1);

        if(SisHovered(opt) && GetAsyncKeyState(VK_LBUTTON))
            showed = 1 - showed;

        if(showed)
        {

            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);

            setcolor(WHITE);


            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 - opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 - opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);

            set_mouse_to_S(mX, mY, show_opt);


            draw_section(show_opt);

            button buttons[5];

            for(int i = 0; i < 5; i++)
                buttons[i].l = show_opt.l / 5, buttons[i].L = show_opt.L;

            buttons[0].corner.x = 0;
            buttons[0].corner.y = 0;
            buttons[0].color = show_opt.color;
            buttons[0].textcolor = WHITE;
            for(int i = 1; i < 5; i++)
            {
                buttons[i].textcolor = WHITE;
                buttons[i].color = show_opt.color;
                buttons[i].corner.x = buttons[i - 1].corner.x;
                buttons[i].corner.y = buttons[i - 1].corner.y + buttons[i - 1].l;
            }

            strcpy(buttons[0].content,"INSERARE INCEPUT");
            strcpy(buttons[1].content,"INSERARE SFARSIT");
            strcpy(buttons[2].content,"INSERARE POZITIE");
            strcpy(buttons[3].content,"CAUTARE POZITIE");
            strcpy(buttons[4].content,"STERGERE POZITIE");

            ///BUTOANE CALCULATOR
            button bkcalcbutton[10];

            for(int i = 0; i < 10; i++)
            {
                bkcalcbutton[i].L = 150;
                bkcalcbutton[i].l = calculator.l / 5;
                bkcalcbutton[i].color = GREEN;
                strcpy(bkcalcbutton[i].content,"");
            }

            bkcalcbutton[0].corner.x = 0;
            bkcalcbutton[0].corner.y = 0;

            for(int i = 2; i < 10; i += 2)
            {
                bkcalcbutton[i].corner.x = bkcalcbutton[i - 2].corner.x;
                bkcalcbutton[i].corner.y = bkcalcbutton[i - 2].corner.y +bkcalcbutton[i - 2].l;
            }

            for(int i = 1; i < 10; i += 2)
            {
                bkcalcbutton[i].corner.x = bkcalcbutton[i - 1].corner.x + bkcalcbutton[i - 1].L;
                bkcalcbutton[i].corner.y = bkcalcbutton[i - 1].corner.y;
            }

            button calcbutton[10];
            button go[5];

            for(int i = 0; i < 10; i++)
            {
                if( i% 2 == 0)
                {
                    if(poz == 0)
                        strcpy(calcbutton[i].content, "POZITITE");
                    else
                    {
                        char c[10];
                        itoa(poz, c, 10);
                        strcpy(calcbutton[i].content, c);
                    }
                }
                else
                {
                    if(info == 0)
                        strcpy(calcbutton[i].content, "NUMAR");
                    else
                    {
                        char c[10];
                        itoa(info, c, 10);
                        strcpy(calcbutton[i].content, c);
                    }

                }
                calcbutton[i].L = bkcalcbutton[i].L - 10;
                calcbutton[i].l = bkcalcbutton[i].l - 10;
                calcbutton[i].color = WHITE;
                calcbutton[i].textcolor = LIGHTGRAY;
                calcbutton[i].corner.x = bkcalcbutton[i].corner.x + 5;
                calcbutton[i].corner.y = bkcalcbutton[i].corner.y + 5;
            }

            for(int i = 0; i < 5; i++)
            {
                strcpy(go[i].content, "GO");
                go[i].corner.x = bkcalcbutton[2 * i + 1].corner.x + bkcalcbutton[2 * i + 1].L + 3;
                go[i].corner.y = bkcalcbutton[2 * i + 1].corner.y;
                go[i].color = RED;
                go[i].textcolor = WHITE;
                go[i].L =  bkcalcbutton[2 * i + 1].l;
                go[i].l =  bkcalcbutton[2 * i + 1].l;

            }
            for(int i = 0; i < 5; i++)
                if(BisHovered(mX, mY,buttons[i]))
                {
                    buttons[i].textcolor++;
                    if(GetAsyncKeyState(VK_LBUTTON))
                    {
                        poz = 0;
                        info = 0;
                        show_c[2 * i] = 1 - show_c[2 * i];
                        show_c[2 * i + 1] = 1 - show_c[2 * i + 1];
                        for(int j = 0; j < 10; j++)
                            if(j != 2* i && j != 2* i + 1)
                                show_c[j] = 0;
                    }
                }

            for(int i = 0; i < 5; i++)
                draw_button(buttons[i], show_opt);

            set_mouse_to_S(mX, mY, calculator);

            bkcalcbutton[0].color = LIGHTGRAY;
            bkcalcbutton[2].color = LIGHTGRAY;
            bkcalcbutton[7].color = LIGHTGRAY;
            bkcalcbutton[9].color = LIGHTGRAY;


            for(int i = 0; i < 10; i++)
                if(show_c[i])
                {
                    if(BisHovered(mX, mY,bkcalcbutton[i]) && GetAsyncKeyState(VK_LBUTTON) && i != 0 && i != 2 && i != 7 && i != 9)
                    {
                        selected[i] = 1 - selected[i];
                        for(int j = 0; j < 10; j++)
                            if(j != i) selected [j] = 0;
                    }

                    if(selected[i])
                    {
                        bkcalcbutton[i].color++;
                        calcbutton[i].textcolor = BLACK;

                        if(i % 2) calculate(calcbutton[i],info);
                        else calculate(calcbutton[i],poz);
                    }

                    draw_button(bkcalcbutton[i], calculator);
                    draw_button(calcbutton[i], calculator);
                    if(i % 2)
                    {

                        int i_go = (i - 1) / 2;

                        if((BisHovered(mX, mY,go[i_go]) && GetAsyncKeyState(VK_LBUTTON)) || GetAsyncKeyState(VK_RETURN))
                        {
                            go[i_go].textcolor = BLACK;
                            go[i_go].color++;

                            switch (i_go)
                            {
                            case 0:
                                InsertFirst(p, info);
                                break;
                            case 1:
                                InsertLast(p, info);
                                break;
                            case 2:
                                InsertPosition(p, poz + 1, info);
                                break;
                            case 3:
                                SearchPosition(p, poz + 1);
                                break;
                            case 4:
                                DeletePosition(p, poz + 1);
                                break;
                            default:
                                break;
                            }
                        }

                        draw_button(go[i_go], calculator);
                    }
                }

        }
        else
        {
            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);

            setcolor(WHITE);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 + opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 + opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);

            setviewport(0,0, width, height, 1);

        }

        write_lldata(p);

        swapbuffers();
        delay(100);
    }
    delay(100);
}

void ld ()
{
    doubleList LD;
    initializationD(LD);

    nodeD *q;
    q = read_dldata(q);

    while (q!=NULL)
    {
        add_end(LD,q->info);
        q=q->next;
    }


    int poz = 0;
    int info = 0;
    int showed = 0;
    int show_cal = 0;

    for(int i = 0; i < 100; i++)
        Dboxes[i].color = WHITE;

    int selected[10],show_c[10];
    for(int i = 0; i< 10; i++)
        selected[i] = 0, show_c[i] = 0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        setviewport(0,0, width, height, 1);
        setbkcolor(9);
        cleardevice();
        mX = mousex();
        mY = mousey();

        draw_essentials();


        draw_LD(LD, work);

        setviewport(0,0, width, height, 1);

        if(SisHovered(opt) && GetAsyncKeyState(VK_LBUTTON))
            showed = 1 - showed;

        if(showed)
        {

            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);

            setcolor(WHITE);


            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 - opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 - opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);

            set_mouse_to_S(mX, mY, show_opt);


            draw_section(show_opt);

            button buttons[5];

            for(int i = 0; i < 5; i++)
                buttons[i].l = show_opt.l / 5, buttons[i].L = show_opt.L;

            buttons[0].corner.x = 0;
            buttons[0].corner.y = 0;
            buttons[0].color = show_opt.color;
            buttons[0].textcolor = WHITE;
            for(int i = 1; i < 5; i++)
            {
                buttons[i].textcolor = WHITE;
                buttons[i].color = show_opt.color;
                buttons[i].corner.x = buttons[i - 1].corner.x;
                buttons[i].corner.y = buttons[i - 1].corner.y + buttons[i - 1].l;
            }

            strcpy(buttons[0].content,"INSERARE INCEPUT");
            strcpy(buttons[1].content,"INSERARE SFARSIT");
            strcpy(buttons[2].content,"INSERARE POZITIE");
            strcpy(buttons[3].content,"CAUTARE POZITIE");
            strcpy(buttons[4].content,"STERGERE POZITIE");

            ///BUTOANE CALCULATOR
            button bkcalcbutton[10];

            for(int i = 0; i < 10; i++)
            {
                bkcalcbutton[i].L = 150;
                bkcalcbutton[i].l = calculator.l / 5;
                bkcalcbutton[i].color = GREEN;
                strcpy(bkcalcbutton[i].content,"");
            }

            bkcalcbutton[0].corner.x = 0;
            bkcalcbutton[0].corner.y = 0;

            for(int i = 2; i < 10; i += 2)
            {
                bkcalcbutton[i].corner.x = bkcalcbutton[i - 2].corner.x;
                bkcalcbutton[i].corner.y = bkcalcbutton[i - 2].corner.y +bkcalcbutton[i - 2].l;
            }

            for(int i = 1; i < 10; i += 2)
            {
                bkcalcbutton[i].corner.x = bkcalcbutton[i - 1].corner.x + bkcalcbutton[i - 1].L;
                bkcalcbutton[i].corner.y = bkcalcbutton[i - 1].corner.y;
            }

            button calcbutton[10];
            button go[5];

            for(int i = 0; i < 10; i++)
            {
                if( i% 2 == 0)
                {
                    if(poz == 0)
                        strcpy(calcbutton[i].content, "POZITITE");
                    else
                    {
                        char c[10];
                        itoa(poz, c, 10);
                        strcpy(calcbutton[i].content, c);
                    }
                }
                else
                {
                    if(info == 0)
                        strcpy(calcbutton[i].content, "NUMAR");
                    else
                    {
                        char c[10];
                        itoa(info, c, 10);
                        strcpy(calcbutton[i].content, c);
                    }

                }
                calcbutton[i].L = bkcalcbutton[i].L - 10;
                calcbutton[i].l = bkcalcbutton[i].l - 10;
                calcbutton[i].color = WHITE;
                calcbutton[i].textcolor = LIGHTGRAY;
                calcbutton[i].corner.x = bkcalcbutton[i].corner.x + 5;
                calcbutton[i].corner.y = bkcalcbutton[i].corner.y + 5;
            }

            for(int i = 0; i < 5; i++)
            {
                strcpy(go[i].content, "GO");
                go[i].corner.x = bkcalcbutton[2 * i + 1].corner.x + bkcalcbutton[2 * i + 1].L + 3;
                go[i].corner.y = bkcalcbutton[2 * i + 1].corner.y;
                go[i].color = RED;
                go[i].textcolor = WHITE;
                go[i].L =  bkcalcbutton[2 * i + 1].l;
                go[i].l =  bkcalcbutton[2 * i + 1].l;

            }
            for(int i = 0; i < 5; i++)
                if(BisHovered(mX, mY,buttons[i]))
                {
                    buttons[i].textcolor++;
                    if(GetAsyncKeyState(VK_LBUTTON))
                    {
                        poz = 0;
                        info = 0;
                        show_c[2 * i] = 1 - show_c[2 * i];
                        show_c[2 * i + 1] = 1 - show_c[2 * i + 1];
                        for(int j = 0; j < 10; j++)
                            if(j != 2* i && j != 2* i + 1)
                                show_c[j] = 0;
                    }
                }

            for(int i = 0; i < 5; i++)
                draw_button(buttons[i], show_opt);

            set_mouse_to_S(mX, mY, calculator);

            bkcalcbutton[0].color = LIGHTGRAY;
            bkcalcbutton[2].color = LIGHTGRAY;
            bkcalcbutton[7].color = LIGHTGRAY;
            bkcalcbutton[9].color = LIGHTGRAY;


            for(int i = 0; i < 10; i++)
                if(show_c[i])
                {
                    if(BisHovered(mX, mY,bkcalcbutton[i]) && GetAsyncKeyState(VK_LBUTTON) && i != 0 && i != 2 && i != 7 && i != 9)
                    {
                        selected[i] = 1 - selected[i];
                        for(int j = 0; j < 10; j++)
                            if(j != i) selected [j] = 0;
                    }

                    if(selected[i])
                    {
                        bkcalcbutton[i].color++;
                        calcbutton[i].textcolor = BLACK;

                        if(i % 2) calculate(calcbutton[i],info);
                        else calculate(calcbutton[i],poz);
                    }

                    draw_button(bkcalcbutton[i], calculator);
                    draw_button(calcbutton[i], calculator);
                    if(i % 2)
                    {

                        int i_go = (i - 1) / 2;

                        if((BisHovered(mX, mY,go[i_go]) && GetAsyncKeyState(VK_LBUTTON)) || GetAsyncKeyState(VK_RETURN))
                        {
                            go[i_go].textcolor = BLACK;
                            go[i_go].color++;

                            switch (i_go)
                            {
                            case 0:
                                add_start(LD, info);
                                break;
                            case 1:
                                add_end(LD, info);
                                break;
                            case 2:
                                add_poz(LD, poz, info);
                                break;
                            case 3:
                                search_poz(LD, poz);
                                break;
                            case 4:
                                delete_poz(LD, poz);
                                break;
                            default:
                                break;
                            }
                        }

                        draw_button(go[i_go], calculator);
                    }
                }

        }
        else
        {
            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);

            setcolor(WHITE);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 + opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 + opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);

            setviewport(0,0, width, height, 1);

        }

        q=LD.first;
        write_dldata(q);

        swapbuffers();
        delay(100);
    }
    delay(100);

}

void st ()
{
    Stack S;
    initializationS(S);
    nodeS *q;
    doubleList LD;
    initializationD(LD);

    q = read_stdata(q);


    while(q != NULL)
    {
        add_end(LD, q -> info);
        q = q -> next;
    }

    nodeD *p;
    p=LD.last;
    while (p!=NULL)
    {
        push(S,p->info);
        p=p->prev;
    }


    for(int i = 0; i < 100; i++)
        Sboxes[i].color = WHITE;


    int poz = 0;
    int info = 0;
    int showed = 0;
    int show_cal = 0;

    int selected[1],show_c[1];
    selected[0] = 0, show_c[0] = 0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        setviewport(0,0, width, height, 1);
        setbkcolor(9);
        setcolor(BLACK);
        cleardevice();

        mX = mousex();
        mY = mousey();

        draw_essentials();

        draw_Stack(S, work);

        setviewport(0,0, width, height, 1);

        if(SisHovered(opt) && GetAsyncKeyState(VK_LBUTTON))
            showed = 1 - showed;

        if(showed)
        {
            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);

            setcolor(WHITE);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 - opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 - opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);

            set_mouse_to_S(mX, mY, show_opt);
            draw_section(show_opt);

            button buttons[5];

            for(int i = 0; i < 5; i++)
                buttons[i].l = show_opt.l / 5, buttons[i].L = show_opt.L;

            buttons[0].corner.x = 0;
            buttons[0].corner.y = 0;
            buttons[0].color = show_opt.color;
            buttons[0].textcolor = WHITE;
            for(int i = 1; i < 5; i++)
            {
                buttons[i].textcolor = WHITE;
                buttons[i].color = show_opt.color;
                buttons[i].corner.x = buttons[i - 1].corner.x;
                buttons[i].corner.y = buttons[i - 1].corner.y + buttons[i - 1].l;
            }

            strcpy(buttons[0].content,"INSERARE ELEMENT");
            strcpy(buttons[1].content,"STERGERE ELEMENT");
            strcpy(buttons[2].content,"AFISARE VARF");
            strcpy(buttons[3].content,"STERGERE STIVA");
            strcpy(buttons[4].content,"CREARE RANDOM");

            button bkcalcbutton[1];
            button calcbutton[1];
            button go[1];

            bkcalcbutton[0].corner.x = 0;
            bkcalcbutton[0].corner.y = buttons[0].corner.y;
            bkcalcbutton[0].L = 150;
            bkcalcbutton[0].l = calculator.l / 5;
            bkcalcbutton[0].color = GREEN;
            strcpy(bkcalcbutton[0].content,"");

            calcbutton[0].L = bkcalcbutton[0].L - 10;
            calcbutton[0].l = bkcalcbutton[0].l - 10;
            calcbutton[0].color = WHITE;
            calcbutton[0].textcolor = LIGHTGRAY;
            calcbutton[0].corner.x = bkcalcbutton[0].corner.x + 5;
            calcbutton[0].corner.y = bkcalcbutton[0].corner.y + 5;

            if(info == 0)
                strcpy(calcbutton[0].content, "NUMAR");

            strcpy(go[0].content, "GO");
            go[0].corner.x = bkcalcbutton[0].corner.x + bkcalcbutton[0].L + 3;
            go[0].corner.y = bkcalcbutton[0].corner.y;
            go[0].color = RED;
            go[0].textcolor = WHITE;
            go[0].L =  bkcalcbutton[0].l;
            go[0].l =  bkcalcbutton[0].l;


            for(int i = 0; i < 5; i++)
                if(BisHovered(mX, mY,buttons[i]))
                {
                    buttons[i].textcolor++;
                    if(i == 0)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            show_c[0] = 1 - show_c[0];

                    if( i == 1)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            pop(S);

                    if(i == 2)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            top(S);

                    if(i == 3)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            empty_S(S);

                    if(i == 4)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            randomS(S);
                }

            for(int i = 0; i < 5; i++)
                draw_button(buttons[i], show_opt);

            set_mouse_to_S(mX, mY, calculator);

            if(show_c[0])
            {

                if(BisHovered(mX, mY,bkcalcbutton[0]) && GetAsyncKeyState(VK_LBUTTON))
                    selected[0] = 1 - selected[0];

                if(selected[0])
                {
                    bkcalcbutton[0].color++;
                    calcbutton[0].textcolor = BLACK;
                    calculate(calcbutton[0],info);
                }

                if(BisHovered(mX, mY,go[0]) && GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RETURN))
                {
                    go[0].textcolor = BLACK;
                    go[0].color++;
                    push(S,info);
                }

                draw_button(bkcalcbutton[0],calculator);
                draw_button(calcbutton[0],calculator);
                draw_button(go[0],calculator);
            }

        }
        else
        {
            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);
            setcolor(WHITE);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 + opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 + opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);
            setviewport(0,0, width, height, 1);
        }
        q = S.peak;
        write_stdata(q);
        swapbuffers();
        delay(100);
    }
}


void qu()
{
    QQ p;
    qnode* q;
    initQ(p);

    q = read_qudata(q);

    for(int i = 0; i < 100; i++)
        qboxes[i].color = WHITE;


    while(q != NULL)
    {
        enqueue(p, q -> info);
        q = q -> next;
    }

    int poz = 0;
    int info = 0;
    int showed = 0;
    int show_cal = 0;

    int selected[1],show_c[1];
    selected[0] = 0, show_c[0] = 0;

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        setviewport(0,0, width, height, 1);
        setbkcolor(9);
        setcolor(BLACK);
        cleardevice();

        mX = mousex();
        mY = mousey();

        draw_essentials();

        draw_QQ(p, work);

        setviewport(0,0, width, height, 1);

        if(SisHovered(opt) && GetAsyncKeyState(VK_LBUTTON))
            showed = 1 - showed;

        if(showed)
        {
            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);

            setcolor(WHITE);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 - opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 - opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);

            set_mouse_to_S(mX, mY, show_opt);
            draw_section(show_opt);

            button buttons[5];

            for(int i = 0; i < 5; i++)
                buttons[i].l = show_opt.l / 5, buttons[i].L = show_opt.L;

            buttons[0].corner.x = 0;
            buttons[0].corner.y = 0;
            buttons[0].color = show_opt.color;
            buttons[0].textcolor = WHITE;
            for(int i = 1; i < 5; i++)
            {
                buttons[i].textcolor = WHITE;
                buttons[i].color = show_opt.color;
                buttons[i].corner.x = buttons[i - 1].corner.x;
                buttons[i].corner.y = buttons[i - 1].corner.y + buttons[i - 1].l;
            }

            strcpy(buttons[0].content,"INSERARE ELEMENT");
            strcpy(buttons[1].content,"STERGERE ELEMENT");
            strcpy(buttons[2].content,"AFISARE VARF");
            strcpy(buttons[3].content,"STERGERE COADA");
            strcpy(buttons[4].content,"CREARE RANDOM");

            button bkcalcbutton[1];
            button calcbutton[1];
            button go[1];

            bkcalcbutton[0].corner.x = 0;
            bkcalcbutton[0].corner.y = buttons[0].corner.y;
            bkcalcbutton[0].L = 150;
            bkcalcbutton[0].l = calculator.l / 5;
            bkcalcbutton[0].color = GREEN;
            strcpy(bkcalcbutton[0].content,"");

            calcbutton[0].L = bkcalcbutton[0].L - 10;
            calcbutton[0].l = bkcalcbutton[0].l - 10;
            calcbutton[0].color = WHITE;
            calcbutton[0].textcolor = LIGHTGRAY;
            calcbutton[0].corner.x = bkcalcbutton[0].corner.x + 5;
            calcbutton[0].corner.y = bkcalcbutton[0].corner.y + 5;

            if(info == 0)
                strcpy(calcbutton[0].content, "NUMAR");

            strcpy(go[0].content, "GO");
            go[0].corner.x = bkcalcbutton[0].corner.x + bkcalcbutton[0].L + 3;
            go[0].corner.y = bkcalcbutton[0].corner.y;
            go[0].color = RED;
            go[0].textcolor = WHITE;
            go[0].L =  bkcalcbutton[0].l;
            go[0].l =  bkcalcbutton[0].l;


            for(int i = 0; i < 5; i++)
                if(BisHovered(mX, mY,buttons[i]))
                {
                    buttons[i].textcolor++;
                    if(i == 0)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            show_c[0] = 1 - show_c[0];

                    if( i == 1)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            dequeue(p);

                    if(i == 2)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            Qpeek(p);

                    if(i == 3)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            deleteQ(p);

                    if(i == 4)
                        if(GetAsyncKeyState(VK_LBUTTON))
                            randomQ(p);
                }

            for(int i = 0; i < 5; i++)
                draw_button(buttons[i], show_opt);

            set_mouse_to_S(mX, mY, calculator);

            if(show_c[0])
            {

                if(BisHovered(mX, mY,bkcalcbutton[0]) && GetAsyncKeyState(VK_LBUTTON))
                    selected[0] = 1 - selected[0];

                if(selected[0])
                {
                    bkcalcbutton[0].color++;
                    calcbutton[0].textcolor = BLACK;
                    calculate(calcbutton[0],info);
                }

                if(BisHovered(mX, mY,go[0]) && GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RETURN))
                {
                    go[0].textcolor = BLACK;
                    go[0].color++;
                    enqueue(p, info);
                }

                draw_button(bkcalcbutton[0],calculator);
                draw_button(calcbutton[0],calculator);
                draw_button(go[0],calculator);
            }

        }
        else
        {
            setviewport(opt.corner_up.x, opt.corner_up.y, opt.corner_down.x, opt.corner_down.y, 1);
            setcolor(WHITE);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2, 125);
            line(opt.corner_down.x / 2, 75,  opt.corner_down.x / 2 + opt.corner_down.x / 4, 100);
            line(opt.corner_down.x / 2 + opt.corner_down.x / 4, 100,  opt.corner_down.x / 2, 125);
            setviewport(0,0, width, height, 1);
        }

        q = p.head;
        write_qudata(q);
        swapbuffers();
        delay(100);
    }
}
