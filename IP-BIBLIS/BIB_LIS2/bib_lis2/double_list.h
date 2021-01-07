#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;


struct Dbox
{
    POINT info;
    POINT next;
    int color;
};
int Dindex = 0;
Dbox Dboxes[100];


struct nodeD
{
    int info;
    nodeD *next;
    nodeD *prev;
};
struct doubleList
{
    int nr_Elem;
    nodeD *first;
    nodeD *last;
};
int VidD (doubleList LD)
{
    return LD.nr_Elem==0;
}
void initializationD (doubleList &LD)
{
    LD.first=NULL;
    LD.last=NULL;
    LD.nr_Elem=0;
}
void add_start (doubleList &LD, int val)
{
    nodeD *node_newD;
    node_newD = new nodeD;
    node_newD->info=val;
    if (VidD(LD))
    {
        node_newD->prev=NULL;
        node_newD->next=LD.last;
        LD.first=node_newD;
        LD.last=LD.first;
        LD.nr_Elem=1;
    }
    else
    {
        node_newD->prev=NULL;
        node_newD->next=LD.first;
        LD.first->prev=node_newD;
        LD.first=node_newD;
        LD.nr_Elem++;
    }
    for(int i = 0; i <= Dindex; i++)
        Dboxes[i].color = WHITE;
    Dboxes[0].color = RED;
}
void add_end (doubleList &LD, int val)
{
    nodeD *node_newD;
    node_newD= new nodeD;
    node_newD->info=val;
    if (VidD(LD))
    {
        node_newD->prev=LD.first;
        node_newD->next=NULL;
        LD.last = node_newD;
        LD.first= LD.last;
        LD.nr_Elem=1;
    }
    else
    {
        node_newD->prev=LD.last;
        node_newD->next=NULL;
        LD.last->next=node_newD;
        LD.last=node_newD;
        LD.nr_Elem++;
    }
    for(int i = 0; i <= Dindex; i++)
        Dboxes[i].color = WHITE;
    Dboxes[Dindex+1].color = RED;
}
void add_poz (doubleList &LD, int poz, int val)
{
    if (poz>LD.nr_Elem)
        return;
    if (poz==0)
        add_start(LD,val);
    else if (poz==LD.nr_Elem)
        add_end(LD,val);
    else
    {
        if (!VidD(LD))
        {
            nodeD *node_newD;
            node_newD= new nodeD;
            node_newD->info=val;
            if (poz<(LD.nr_Elem/2))
            {
                nodeD *p=LD.first;
                int position_list=0;
                while (p!=NULL)
                {
                    if (poz==position_list)
                    {
                        node_newD->prev=p->prev;
                        node_newD->next=p;
                        nodeD *aux;
                        aux=p->prev;
                        p->prev=node_newD;
                        p=aux;
                        p->next=node_newD;
                        p=NULL;
                        LD.nr_Elem++;

                    }
                    else
                    {
                        p=p->next;
                        position_list++;
                    }
                }
            }
            else
            {
                nodeD *p=LD.last;
                int position_list=LD.nr_Elem-1;
                while (p!=NULL)
                {
                    if (poz==position_list)
                    {
                        node_newD->prev=p->prev;
                        node_newD->next=p;
                        nodeD *aux;
                        aux=p->prev;
                        p->prev=node_newD;
                        p=aux;
                        p->next=node_newD;
                        p=NULL;
                        LD.nr_Elem++;
                    }
                    else
                    {
                        p=p->prev;
                        position_list--;
                    }
                }

            }
        }
    }
    for(int i = 0; i <= Dindex; i++)
        Dboxes[i].color = WHITE;
    Dboxes[poz].color = RED;
}
void delete_start (doubleList &LD)
{
    if (!VidD(LD))
    {
        nodeD *node_newD;
        node_newD=LD.first;
        LD.first->prev=NULL;
        LD.first = LD.first->next;
        delete node_newD;
        LD.nr_Elem--;
    }
    for(int i = 0; i < Dindex; i++)
        Dboxes[i].color = WHITE;
    Dboxes[1].color = RED;
}
void delete_end (doubleList &LD)
{
    if (!VidD(LD))
    {
        nodeD *node_newD;
        node_newD = LD.last;
        LD.last=LD.last->prev;
        LD.last->next=NULL;
        delete node_newD;
        LD.nr_Elem--;
    }
    for(int i = 0; i <= Dindex; i++)
        Dboxes[i].color = WHITE;
    Dboxes[Dindex-1].color = RED;
}


void delete_poz (doubleList &LD, int poz)
{
    if (poz<LD.nr_Elem)
    {

        if (poz==0)
            delete_start(LD);
        else if (poz==LD.nr_Elem-1)
            delete_end(LD);
        else
        {
            if (!VidD(LD))
            {
                nodeD *node_newD;
                //if (poz<(LD.nr_Elem/2))
                // {
                nodeD *p=LD.first;
                int position_list=1;
                while (p!=NULL)
                {
                    if (poz==position_list)
                    {
                        node_newD = p;
                        p->prev->next = p->next;
                        p->next->prev = p->prev;
                        delete node_newD;
                        LD.nr_Elem--;
                        p=NULL;

                    }
                    else
                    {
                        p=p->next;
                        position_list++;
                    }
                }
                //}
                /*else
                {
                    nodeD *p=LD.last;
                    int position_list=LD.nr_Elem;
                    while (p!=NULL)
                    {
                        if (poz==position_list)
                        {
                            node_newD = p;
                            p->prev->next = p->next;
                            p->next->prev = p->prev;
                            delete node_newD;
                            LD.nr_Elem--;
                            p=NULL;
                        }
                        else
                        {
                            p=p->prev;
                            position_list--;
                        }
                    }

                }*/
            }
        }

        for(int i = 0; i <= Dindex; i++)
            Dboxes[i].color = WHITE;
        Dboxes[poz].color = RED;
    }
}


void search_poz (doubleList LD, int poz)
{
    if (poz<=LD.nr_Elem)
    {
        for(int i = 0; i <= Dindex; i++)
            Dboxes[i].color = WHITE;
        Dboxes[poz].color = RED;
        /*if (poz==0)
            return LD.first->info;
        else if (poz==LD.nr_Elem-1)
            return LD.last->info;
        else
        {
            if (!VidD(LD))
            {
                if (poz<(LD.nr_Elem/2))
                {
                    nodeD *p=LD.first;
                    int position_list=0;
                    while (p!=NULL)
                    {
                        if (position_list==poz)
                            return p->info;
                        p=p->next;
                    }
                }
                else
                {
                    nodeD *p=LD.last;
                    int position_list=LD.nr_Elem-1;
                    while (p!=NULL)
                    {
                        if (poz==position_list)
                            return p->info;
                        p=p->prev;
                    }

                }
            }
        }*/
    }
}



void write_dldata (nodeD *start)
{
    FILE *pFile;
    pFile = fopen("dldata", "wb");

    if(pFile != NULL)
    {
        nodeD *currentD = start;

        nodeD *holdNext = NULL;
        nodeD *holdprev = NULL;

        while(currentD != NULL)
        {
            holdNext = currentD->next;
            holdprev = currentD->prev;

            currentD->next = NULL;
            currentD->prev = NULL;

            fseek(pFile, 0, SEEK_END);
            fwrite(currentD, sizeof(nodeD), 1, pFile);


            currentD->next = holdNext;
            currentD->prev = holdprev;

            holdNext = NULL;
            holdprev = NULL;

            currentD = currentD->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
    else
    {
        printf("FILE OPEN ERROR\n");
    }

}

nodeD *ReadNextFromFile(nodeD *start, FILE *pFile)
{
    size_t returnValue;
    if(start == NULL)
    {
        start = new nodeD;
        returnValue = fread(start, sizeof(nodeD), 1, pFile);
        start->next = NULL;
        start->prev = NULL;
    }
    else
    {
        nodeD *indexD = start;
        nodeD *newD = new nodeD;
        while(indexD->next != NULL)
        {
            indexD = indexD->next;
        }
        returnValue = fread(newD, sizeof(nodeD), 1, pFile);
        indexD->next = newD;
        newD->next = NULL;
        newD->prev = indexD;
    }
    return start;
}

nodeD *read_dldata(nodeD *start)
{

    FILE *pFile;
    pFile = fopen("dldata", "rb");
    if(pFile != NULL)
    {

        start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(nodeD)));

        int loop = 0;
        for(loop = 0; loop < numEntries; ++loop)
        {
            fseek(pFile, (sizeof(nodeD) * loop), SEEK_SET);
            start = ReadNextFromFile(start, pFile);
        }
    }
    else
    {
        printf("FILE OPEN ERROR FOR READ\n");
    }

    return start;

}




void draw_box_double (nodeD *p, POINT box_prev, POINT box_info, POINT box_next, Dbox b)
{
    rectangle(box_prev.x, box_prev.y, box_prev.x + 50, box_prev.y + 50);
    rectangle(box_info.x, box_info.y, box_info.x + 50, box_info.y + 50);
    rectangle(box_next.x, box_next.y, box_next.x + 50, box_next.y + 50);

    setfillstyle(LTSLASH_FILL,b.color);
    floodfill(box_info.x + 10, box_info.y + 10, BLACK);


    int middle_prev_x = (box_prev.x + box_prev.x + 50) / 2;
    int middle_prev_y = (box_prev.y + box_prev.y + 50) / 2;
    int middle_next_x = (box_next.x + box_next.x + 50) / 2;
    int middle_next_y = (box_next.y + box_next.y + 50) / 2;
    fillellipse(middle_prev_x,middle_prev_y, 5, 5);
    fillellipse(middle_next_x,middle_next_y, 5, 5);
    char c[10];
    itoa(p->info,c,10);
    int width = textwidth(c);
    int height = textheight(c);
    int spacex = (50 - width) / 2;
    int spacey = (50 - height) / 2;
    outtextxy(box_info.x + spacex,box_info.y + spacey,c);
}

void draw_arrows (POINT box_next)
{
    setcolor(BLUE);
    line(box_next.x+50,box_next.y+10, box_next.x+100,box_next.y+10);
    line (box_next.x+100,box_next.y+10, box_next.x +90, box_next.y+20);
    line (box_next.x+100,box_next.y+10, box_next.x +90, box_next.y);
    setcolor(RED);
    line(box_next.x+50,box_next.y+40, box_next.x+100,box_next.y+40);
    line (box_next.x+50,box_next.y+40,box_next.x+60,box_next.y+50);
    line (box_next.x+50,box_next.y+40,box_next.x+60,box_next.y+30);
    setcolor(BLACK);

}

void draw_arrows_end_dList (POINT box_next , POINT box_prev)
{

    setcolor(BLUE);
    line(box_next.x+10,box_next.y+50, box_next.x+10,box_next.y+70);
    line(box_next.x+10,box_next.y+70,box_prev.x+10,box_prev.y-40);
    line(box_prev.x+10,box_prev.y-40,box_prev.x+10,box_prev.y);
    line(box_prev.x+10,box_prev.y,box_prev.x,box_prev.y-10);
    line(box_prev.x+10,box_prev.y,box_prev.x+20,box_prev.y-10);
    setcolor(RED);
    line(box_next.x+40,box_next.y+50, box_next.x+40,box_next.y+90);
    line (box_next.x+40,box_next.y+90,box_prev.x+40, box_prev.y-20);
    line (box_prev.x+40, box_prev.y-20,box_prev.x+40, box_prev.y);
    line(box_prev.x+40, box_prev.y,box_prev.x+30,box_prev.y-10);
    line(box_prev.x+40, box_prev.y,box_prev.x+50,box_prev.y-10);
    setcolor(BLACK);
}
void draw_LD (doubleList LD, section S)
{
    setviewport(S.corner_up.x, S.corner_up.y, S.corner_down.x, S.corner_down.y, 1);
    setcolor(BLACK);
    setbkcolor(WHITE);
    setfillstyle(0, S.color);
    setlinestyle(0,0,2);
    POINT box_prev;
    POINT box_info;
    POINT box_next;
    box_prev.x = 50;
    box_info.x= box_prev.x+50;
    box_next.x=box_prev.x+100;
    box_prev.y =box_info.y=box_next.y= 50;

    Dindex = -1;

    int contor=0;

    nodeD *p;
    p=LD.first;
    while (p!=NULL)
    {
        contor++;

        Dindex++;
        Dboxes[index].info = box_info;
        Dboxes[index].next = box_next;

        if (p->next == NULL)
        {
            //outtextxy(100, 20 , "FIRST");
            draw_box_double(p,box_prev,box_info,box_next,Dboxes[Dindex]);
        }
        else
        {
            draw_box_double(p,box_prev,box_info,box_next,Dboxes[Dindex]);
            if(box_next.x +275< S.corner_down.x )
            draw_arrows(box_next);
        }

        if(box_next.x +275 >=S.corner_down.x)
        {
            box_prev.x = 50;
            box_info.x= box_prev.x+50;
            box_prev.y += 110;
            box_info.y=box_prev.y;
            if (contor != LD.nr_Elem)
            draw_arrows_end_dList(box_next,box_prev);
            box_next.x=box_prev.x+100;
            box_next.y=box_prev.y;
        }
        else
        {
            box_prev.x = box_next.x+100;
        box_info.x= box_prev.x+50;
        box_next.x=box_prev.x+100;
        }
        p=p->next;
    }
    setlinestyle(0,0,0);
}
