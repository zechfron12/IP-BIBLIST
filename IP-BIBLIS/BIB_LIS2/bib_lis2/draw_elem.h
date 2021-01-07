#include <bits/stdc++.h>
#include <graphics.h>


struct button
{
    POINT corner;
    int L, l;
    int color;
    int textcolor;
    char content[100];
};


struct section
{
    POINT corner_up;
    int L, l;
    int color;
    POINT corner_down;
};

bool BisHovered(int mX, int mY, button A)
{
    if(mX > A.corner.x && mX < A.corner.x + A.L && mY > A.corner.y && mY < A.corner.y + A.l)
        return true;
    return false;
}
bool SisHovered(section A)
{

    int mX = mousex();
    int mY = mousey();

    if(mX > A.corner_up.x && mX < A.corner_up.x+ A.L && mY > A.corner_up.y && mY < A.corner_up.y + A.l)
        return true;
    return false;
}

void draw_button(button B, section S)
{
    setviewport(S.corner_up.x, S.corner_up.y, S.corner_down.x, S.corner_down.y, 1);

    setbkcolor(B.color);
    setcolor(B.color);
    rectangle(B.corner.x, B.corner.y, B.corner.x + B.L, B.corner.y + B.l);

    setfillstyle(1,B.color);

    int poly[10];

    poly[0] = B.corner.x;
    poly[1] = B.corner.y;
    poly[2] = B.corner.x + B.L;
    poly[3] = B.corner.y;
    poly[4] = B.corner.x + B.L;
    poly[5] = B.corner.y + B.l;
    poly[6] = B.corner.x;
    poly[7] = B.corner.y + B.l;
    poly[8] = B.corner.x;
    poly[9] = B.corner.y;
    fillpoly(5, poly);


    int width = textwidth(B.content);
    int height = textheight(B.content);
    int spacex = (B.L - width) / 2;
    int spacey = (B.l - height) / 2;

    setcolor(B.textcolor);
    outtextxy(B.corner.x + spacex,B.corner.y + spacey, B.content);

}

void draw_section(section S)
{
    setbkcolor(S.color);
    setcolor(BLACK);
    setfillstyle(1,S.color);

    int poly[10];

    poly[0] = S.corner_up.x;
    poly[1] = S.corner_up.y;
    poly[2] = S.corner_down.x;
    poly[3] = S.corner_up.y;
    poly[4] = S.corner_down.x;
    poly[5] = S.corner_down.y;
    poly[6] = S.corner_up.x;
    poly[7] = S.corner_down.y;
    poly[8] = S.corner_up.x;
    poly[9] = S.corner_up.y;
    fillpoly(5, poly);
}

void set_mouse_to_S(int& mX,int& mY, section S)
{
    mX = mousex();
    mY = mousey();
    mX -= S.corner_up.x;
    mY -= S.corner_up.y;
}
