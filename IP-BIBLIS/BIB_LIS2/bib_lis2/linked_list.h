#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
int width = screenWidth * 80 / 100;
int height = screenHeight * 80 / 100;

struct box
{
    POINT info;
    POINT next;
    int color;
};
int index = 0;
box boxes[100];


struct LL
{
    int info;
    LL* next;
};

void draw_box(LL *p, POINT box_info, POINT box_next, int color);
void draw_LL(LL* p, section S);
void draw_arrow(POINT box_info, POINT box_next);

void Show(LL* head)
{
    while( head != NULL)
    {
        cout << head -> info << endl;
        head = head -> next;
    }
}

void ClearUp(LL *start)
{

    LL *freeMe = start;
    LL *holdMe = NULL;
    while(freeMe != NULL)
    {
        holdMe = freeMe->next;

        free(freeMe);
        freeMe = holdMe;
    }
}

void InsertFirst(LL* &head, int x)
{
    LL* p = new LL;
    p -> info = x;
    p -> next = head;
    head = p;
    for(int i = 1; i <= index; i++)
        boxes[i].color = WHITE;
    boxes[1].color = RED;
}
void InsertLast (LL* &head, int x)
{
    LL* p = new LL;
    p -> info = x;
    p -> next = NULL;
    if( head == NULL) head = p;
    else
    {
        LL* q = head;
        while(q -> next != NULL)
            q = q -> next;
        q -> next = p;
    }
    for(int i = 1; i <= index; i++)
        boxes[i].color = WHITE;
    boxes[index + 1].color = RED;
}

LL* SearchPosition(LL* head, int position)
{
    int i = 1;
    while( head != NULL && i < position)
    {
        head = head -> next;
        i++;
    }

    if(i == position)
    {
        for(int i = 1; i <= index; i++)
            boxes[i].color = WHITE;
        boxes[i].color = RED;
        return head;
    }
    else
        return NULL;
}

bool InsertPosition(LL* &head, int pos, int x)
{
    LL *p = new LL;
    p -> info = x;
    p -> next = NULL;

    if(pos == 1)
    {
        p -> next = head;
        head = p;
        return true;
    }
    else
    {
        LL* q = SearchPosition(head, pos - 1);
        SearchPosition(head, pos);
        if(q != NULL)
        {
            p -> next = q -> next;
            q -> next = p;
            return true;
        }
        else return false;
    }
}

void DeleteInside(LL *p)
{
    LL* q = p -> next;
    p -> next = p -> next -> next;
    delete q;
    return;
}

bool DeletePosition(LL* &head, int position)
{
    if(head == NULL)
    {
        return false;
    }

    if(position == 1)
    {
        LL* p = head;
        head = head -> next;
        delete p;
        return true;
    }
    LL* p = SearchPosition(head, position - 1);
    SearchPosition(head, position);
    if(p == NULL) return false;
    else
    {
        DeleteInside(p);
        return true;
    }
}

void write_lldata(LL *start)
{
    FILE *pFile;
    pFile = fopen("lldata", "wb");

    if(pFile != NULL)
    {
        LL *currentLL = start;

        LL *holdNext = NULL;

        while(currentLL != NULL)
        {
            holdNext = currentLL->next;

            currentLL->next = NULL;

            fseek(pFile, 0, SEEK_END);
            fwrite(currentLL, sizeof(LL), 1, pFile);


            currentLL->next = holdNext;

            holdNext = NULL;

            currentLL = currentLL->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
    else
    {
        printf("FILE OPEN ERROR IN LL\n");
    }

}

LL *ReadNextFromFile(LL *start, FILE *pFile)
{
    size_t returnValue;
    if(start == NULL)
    {
        start = new LL;
        returnValue = fread(start, sizeof(LL), 1, pFile);
        start->next = NULL;
    }
    else
    {
        LL *indexLL = start;
        LL *newLL = new LL;
        while(indexLL->next != NULL)
        {
            indexLL = indexLL->next;
        }
        returnValue = fread(newLL, sizeof(LL), 1, pFile);
        indexLL->next = newLL;
        newLL->next = NULL;
    }
    return start;
}


LL *read_lldata(LL *start)
{

    FILE *pFile;
    pFile = fopen("lldata", "rb");
    if(pFile != NULL)
    {
        start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(LL)));

        int loop = 0;
        for(loop = 0; loop < numEntries; ++loop)
        {
            fseek(pFile, (sizeof(LL) * loop), SEEK_SET);
            start = ReadNextFromFile(start, pFile);
        }
    }
    else
    {
        printf("FILE OPEN ERROR FOR READ IN LL\n");
    }

    return start;
}

void Ldraw_box(LL *p, POINT box_info, POINT box_next, box b)
{

    setlinestyle(0,0,2);

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

    setlinestyle(0,0,0);
    setcolor(BLACK);
}

void Ldraw_rightarrow(POINT box_info, POINT box_next)
{
    setlinestyle(0,0,2);

    int middle_next_x = (box_next.x + box_next.x + 50) / 2;
    int middle_next_y = (box_next.y + box_next.y + 50) / 2;
    fillellipse(middle_next_x,middle_next_y, 5, 5);
    line(middle_next_x,middle_next_y, middle_next_x + 75,middle_next_y);
    line(middle_next_x + 65, middle_next_y - 10,middle_next_x + 75,middle_next_y);
    line(middle_next_x + 65, middle_next_y + 10,middle_next_x + 75,middle_next_y);

    setlinestyle(0,0,0);

}

void Ldraw_downarrow(POINT box_info, POINT box_next)
{
    setlinestyle(0,0,2);

    int x1 = box_next.x + 25 ;
    int y1 = box_next.y + 25;

    int x2 = x1;
    int y2 = y1 + 75;

    line(x1,y1,x2,y2);
    line(x2, y2,x2 - 10, y2 - 10);
    line(x2, y2,x2 + 10, y2 - 10);

    setlinestyle(0,0,0);

}

void Ldraw_leftarrow(POINT box_info, POINT box_next)
{
    setlinestyle(0,0,2);

    int x1 = box_info.x - 50;
    int y1 = box_info.y + 25;

    int x2 = box_info.x;
    int y2 = y1;

    line(x1,y1,x2,y2);
    line(x1, y1,x1 + 10, y1 - 10);
    line(x1, y1,x1 + 10, y1 + 10);

    setlinestyle(0,0,0);
}

void draw_LL(LL* p, section S)
{
    setviewport(S.corner_up.x, S.corner_up.y, S.corner_down.x, S.corner_down.y, 1);
    setcolor(BLACK);
    setbkcolor(WHITE);
    setfillstyle(0, S.color);
    setlinestyle(0,0,2);
    POINT box_info;
    POINT box_next;
    box_info.x = 50;
    box_info.y = 50;
    box_next.x = box_info.x + 50;
    box_next.y = box_info.y;
    index = 0;

    int spacex = 150;
    int spacey = 100;

    while(p != NULL)
    {
        index++;
        boxes[index].info = box_info;
        boxes[index].next = box_next;


        if(p -> next == NULL)
            Ldraw_box(p, box_info, box_next, boxes[index]);

        else if(box_info.x + 2 * spacex > S.corner_down.x + 50  || box_info.x + spacex < S.corner_up.x)
        {

            Ldraw_downarrow(box_info, box_next);
            Ldraw_box(p, box_info, box_next, boxes[index]);
        }
        else if(spacex > 0)
        {
            Ldraw_rightarrow(box_info, box_next);
            Ldraw_box(p, box_info, box_next, boxes[index]);
        }
        else if( spacex < 0)
        {
            Ldraw_leftarrow(box_info, box_next);
            Ldraw_box(p, box_info, box_next, boxes[index]);
        }

        box_info.x += spacex;
        box_next.x = box_info.x + 50;
        if(box_info.x + spacex > S.corner_down.x + 50  || box_info.x  < S.corner_up.x)
        {

            spacex *= -1;

            box_info.x += spacex;
            box_next.x = box_info.x + 50;
            box_info.y += spacey;
            box_next.y = box_info.y;
        }
        p = p -> next;
    }
    setlinestyle(0,0,0);
}
