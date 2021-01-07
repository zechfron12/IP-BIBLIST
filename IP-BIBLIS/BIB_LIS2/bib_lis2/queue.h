#include <bits/stdc++.h>
#include <graphics.h>

using namespace std;

struct qbox
{
    POINT info;
    POINT next;
    int color;
};
int qindex = 0;
box qboxes[100];

struct qnode
{
    int info;
    qnode * next;
};

struct QQ
{
    qnode* head;
    qnode* tail;
    int length;
};

bool QisNULL(QQ q)
{
    return q.length == 0;
}

void initQ(QQ& q)
{
    q.head = NULL;
    q.tail = NULL;
    q.length = 0;
}

int Qpeek(QQ q)
{
    if (!QisNULL(q))
    {
        for(int i = 0; i <= index; i++)
            qboxes[i].color = WHITE;

        qboxes[0].color = RED;
        return q.head->info;
    }
    else
    {
        cout<<"EROARE";
        return -1;
    }
}

int dequeue(QQ &q)
{
    if (!QisNULL(q))
    {
        int x = Qpeek(q);
        qnode* p;
        p = q.head;
        q.head = q.head -> next;
        delete p;
        q.length--;

        for(int i = 0; i <= index; i++)
            qboxes[i].color = WHITE;

        qboxes[0].color = RED;
        return x;
    }
    else
    {
        cout<< "EROARE";
        return -1;
    }
}

void deleteQ(QQ &q)
{
    int x;
    while (!QisNULL(q)) x=dequeue(q);
}

void enqueue(QQ &q, int x)

{
    qnode * qnode_nou;
    if (QisNULL(q))
    {
        q.length = 1;
        q.head = new qnode;
        q.head -> info = x;
        q.head -> next = NULL;
        q.tail = q.head;
        for(int i = 0; i <= index; i++)
            qboxes[i].color = WHITE;
    }
    else
    {
        q.length++;
        qnode_nou = new qnode;
        qnode_nou -> info = x;
        qnode_nou -> next = NULL;
        q.tail -> next = qnode_nou;
        q.tail = qnode_nou;
        for(int i = 0; i <= index; i++)
            qboxes[i].color = WHITE;
    }
}

void ShowQ(QQ q)
{
    qnode* p;
    p=q.head;
    while (p!=NULL)
    {
        cout<< p -> info <<endl;
        p = p -> next;
    }
}

void randomQ(QQ &p)
{
    initQ(p);
    int k,x;
    k = rand() % 20 + 1;

    for(int i = 0; i < k; i++)
    {
        x = rand() % 100;
        enqueue(p,x);
    }
}

void write_qudata(qnode *start)
{
    FILE *pFile;
    pFile = fopen("qudata", "wb");

    if(pFile != NULL)
    {
        qnode *currentLL = start;

        qnode *holdNext = NULL;

        while(currentLL != NULL)
        {
            holdNext = currentLL->next;

            currentLL->next = NULL;

            fseek(pFile, 0, SEEK_END);
            fwrite(currentLL, sizeof(qnode), 1, pFile);


            currentLL->next = holdNext;

            holdNext = NULL;

            currentLL = currentLL->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
    else
    {
        printf("FILE OPEN ERROR IN QU\n");
    }

}

qnode *ReadNextFromFile(qnode *start, FILE *pFile)
{
    size_t returnValue;
    if(start == NULL)
    {
        start = new qnode;
        returnValue = fread(start, sizeof(qnode), 1, pFile);
        start->next = NULL;
    }
    else
    {
        qnode *indexLL = start;
        qnode *newLL = new qnode;
        while(indexLL->next != NULL)
        {
            indexLL = indexLL->next;
        }
        returnValue = fread(newLL, sizeof(qnode), 1, pFile);
        indexLL -> next = newLL;
        newLL -> next = NULL;
    }
    return start;
}


qnode *read_qudata(qnode *start)
{

    FILE *pFile;
    pFile = fopen("qudata", "rb");
    if(pFile != NULL)
    {
        start = NULL;

        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(qnode)));

        int loop = 0;
        for(loop = 0; loop < numEntries; ++loop)
        {
            fseek(pFile, (sizeof(qnode) * loop), SEEK_SET);
            start = ReadNextFromFile(start, pFile);
        }
    }
    else
    {
        printf("FILE OPEN ERROR FOR READ IN QU\n");
    }

    return start;
}



void Qdraw_box(qnode *p, POINT box_info, POINT box_next,int color)
{
    setlinestyle(0,0,2);

    rectangle(box_info.x, box_info.y, box_info.x + 50, box_info.y + 50);
    rectangle(box_next.x, box_next.y, box_next.x + 50, box_next.y + 50);

    setfillstyle(LTSLASH_FILL,color);
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

void Qdraw_uparrow(POINT box_info, POINT box_next)
{
    setlinestyle(0,0,2);

    int x1 = box_next.x + 25 ;
    int y1 = box_next.y - 50;

    int x2 = x1;
    int y2 = box_next.y + 25;

    line(x1, y1, x2, y2);
    line(x1, y1,x1 + 10, y1 + 10);
    line(x1, y1,x1 - 10, y1 + 10);

    setlinestyle(0,0,0);

}

void Qdraw_leftarrow(POINT box_info, POINT box_next)
{
    setlinestyle(0,0,2);

    int x1 = box_info.x - 100;
    int y1 = box_info.y + 25;

    int x2 = box_info.x;
    int y2 = y1;

    line(x1,y1,x2,y2);
    line(x1, y1,x1 + 10, y1 - 10);
    line(x1, y1,x1 + 10, y1 + 10);

    setlinestyle(0,0,0);
}
void Qdraw_downarrow(POINT box_info, POINT box_next)
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

void draw_QQ(QQ q, section S)
{
    qnode* p = q.head;
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
    qindex = 0;
    int spacey = 100;

    if(p != NULL)
    {
        Qdraw_box(p, box_info, box_next,qboxes[0].color);
        p = p -> next;
        box_info.y += spacey;
        box_next.y = box_info.y;
    }

    while(p != NULL)
    {
        qindex++;
        qboxes[qindex].info = box_info;
        qboxes[qindex].next = box_next;

        if(box_info.y +  spacey > S.corner_down.y || box_info.y + spacey < S.corner_up.y)
        {
            box_info.x += 200;
            box_next.x = box_info.x + 50;
            box_info.y -= spacey;
            box_next.y = box_info.y;

            Qdraw_leftarrow(box_info, box_next);
            Qdraw_box(p, box_info, box_next, qboxes[qindex].color);

            spacey*= -1;
            box_info.y += spacey;
            box_next.y = box_info.y;
        }
        else if(spacey > 0)
        {
            Qdraw_uparrow(box_info, box_next);
            Qdraw_box(p, box_info, box_next, qboxes[qindex].color);

            box_info.y += spacey;
            box_next.y = box_info.y;
        }
        else if(spacey < 0)
        {
            Qdraw_downarrow(box_info, box_next);
            Qdraw_box(p, box_info, box_next, qboxes[qindex].color);

            box_info.y += spacey;
            box_next.y = box_info.y;
        }

        p = p -> next;
    }
    setlinestyle(0,0,0);
}
