#include <bits/stdc++.h>
#include <graphics.h>





struct Sbox
{
    POINT info;
    POINT next;
    int color;
};
int Sindex = 0;
Sbox Sboxes[100];



struct nodeS
{
    int info;
    nodeS *next;
};
struct Stack
{
    int nr_elem;
    nodeS *peak;
};
void initializationS (Stack &S)
{
    S.nr_elem=0;
    S.peak=NULL;
}
int VidS (Stack S)
{
    return S.nr_elem==0;
}
void push (Stack &S, int e)
{
    nodeS *node_newS;
    node_newS= new nodeS;
    S.nr_elem++;
    node_newS->info=e;
    node_newS->next=S.peak;
    S.peak=node_newS;
    for(int i = 0; i <= Sindex; i++)
        Sboxes[i].color = WHITE;
    Sboxes[Sindex+1].color = RED;
}
int top (Stack S)
{
    for(int i = 0; i <= Sindex; i++)
        Sboxes[i].color = WHITE;
    Sboxes[Sindex].color = RED;
    return S.peak->info;
}
void pop (Stack &S)
{
    if (!VidS(S))
    {
        nodeS *node_newS;
        node_newS=S.peak;
        S.peak=S.peak->next;
        delete node_newS;
        S.nr_elem--;
    }
}

void randomS (Stack &S)
{
    initializationS(S);
    int k,x;
    k = rand() % 20 + 1;

    for(int i = 0; i < k; i++)
    {
        x = rand() % 100;
        push(S,x);
    }
    for(int i = 0; i <= 100; i++)
        Sboxes[i].color = WHITE;

}
void empty_S (Stack &S)
{
    while (!VidS(S))
        pop(S);
}


void write_stdata(nodeS *start)
{
    FILE *pFile;
    pFile = fopen("stdata", "wb");

    if(pFile != NULL)
    {
        nodeS *currentS = start;

        nodeS *holdNext = NULL;

        while(currentS != NULL)
        {
            holdNext = currentS->next;

            currentS->next = NULL;

            fseek(pFile, 0, SEEK_END);
            fwrite(currentS, sizeof(nodeS), 1, pFile);


            currentS->next = holdNext;

            holdNext = NULL;

            currentS = currentS->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
    else
    {
        printf("FILE OPEN ERROR IN ST\n");
    }

}

nodeS *ReadNextFromFile(nodeS *start, FILE *pFile)
{
    size_t returnValue;
    if(start == NULL)
    {
        start = new nodeS;
        returnValue = fread(start, sizeof(nodeS), 1, pFile);
        start->next = NULL;
    }
    else
    {
        nodeS *indexS = start;
        nodeS *newS = new nodeS;
        while(indexS->next != NULL)
        {
            indexS = indexS->next;
        }
        returnValue = fread(newS, sizeof(nodeS), 1, pFile);
        indexS->next = newS;
        newS->next = NULL;
    }
    return start;
}


nodeS *read_stdata(nodeS *start)
{

    FILE *pFile;
    pFile = fopen("stdata", "rb");
    if(pFile != NULL)
    {
        start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(nodeS)));

        int loop = 0;
        for(loop = 0; loop < numEntries; ++loop)
        {
            fseek(pFile, (sizeof(nodeS) * loop), SEEK_SET);
            start = ReadNextFromFile(start, pFile);
        }
    }
    else
    {
        printf("FILE OPEN ERROR FOR READ IN ST\n");
    }

    return start;
}




void draw_box_Stack (nodeS *p, POINT box_info, POINT box_next, Sbox b)
{
    rectangle(box_info.x, box_info.y, box_info.x + 50, box_info.y + 50);
    rectangle(box_next.x, box_next.y, box_next.x + 50, box_next.y + 50);

    setfillstyle(LTSLASH_FILL,b.color);
    floodfill(box_info.x + 10, box_info.y + 10, BLACK);

    int middle_next_x = (box_next.x + box_next.x + 50) / 2;
    int middle_next_y = (box_next.y + box_next.y + 50) / 2;
    fillellipse(middle_next_x,middle_next_y, 5, 5);
    char c[10];
    itoa(p->info,c,10);
    int width = textwidth(c);
    int height = textheight(c);
    int spacex = (50 - width) / 2;
    int spacey = (50 - height) / 2;
    outtextxy(box_info.x + spacex,box_info.y + spacey,c);
}

void draw_arrow_Stack (POINT box_next)
{
    line (box_next.x+25,box_next.y+20,box_next.x+25,box_next.y-50);
    line (box_next.x+25,box_next.y-50,box_next.x+15,box_next.y-40);
    line (box_next.x+25,box_next.y-50,box_next.x+35,box_next.y-40);
}

void draw_line_end_Stack (POINT box_info, POINT box_next)
{
    line (box_next.x+30,box_next.y+25,box_next.x+75,box_next.y+25);
    line(box_next.x+75,box_next.y+25,box_info.x-25,box_info.y+25);
    line (box_info.x-25,box_info.y+25,box_info.x,box_info.y+25);
    line(box_info.x,box_info.y+25,box_info.x-10,box_info.y+15);
    line(box_info.x,box_info.y+25,box_info.x-10,box_info.y+35);

}

void draw_rec (nodeS *p, section S, POINT &box_info, POINT &box_next, Stack St, int contor)
{
    if (p!=NULL)
    {
        draw_rec(p->next,S,box_info,box_next, St,contor-1);

        Sindex++;
        Sboxes[Sindex].info = box_info;
        Sboxes[Sindex].next = box_next;

        if (St.nr_elem==1 || contor == St.nr_elem)
            draw_box_Stack(p,box_info,box_next,Sboxes[Sindex]);
        else
        {
            draw_box_Stack(p,box_info,box_next,Sboxes[Sindex]);
            if(box_next.y -100 > S.corner_up.y)
                draw_arrow_Stack(box_next);
        }

        if(box_next.y -100 <= S.corner_up.y)
        {
            box_info.y= S.corner_up.y + S.l - 175;
            box_info.x += 150;
            if (contor != St.nr_elem)
            draw_line_end_Stack(box_info,box_next);
            box_next.y = S.corner_up.y + S.l - 175;
            box_next.x +=150;

        }
        else
        {
            box_info.y -= 100;
            box_next.y -= 100;
        }
    }

}
void draw_Stack (Stack St, section S)
{
    setviewport(S.corner_up.x, S.corner_up.y, S.corner_down.x, S.corner_down.y, 1);
    setcolor(BLACK);
    setbkcolor(WHITE);
    setfillstyle(0, S.color);
    setlinestyle(0,0,2);
    POINT box_info;
    POINT box_next;
    box_info.x=S.corner_up.x -20;
    box_next.x=box_info.x+50;
    box_info.y=box_next.y= S.corner_up.y + S.l - 175;

    int contor=St.nr_elem;
    Sindex = -1;
    draw_rec(St.peak,S,box_info,box_next,St,contor);
}



