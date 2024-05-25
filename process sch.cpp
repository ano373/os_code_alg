struct process
{
    int num, arv, bur, pri;
};

#define SIZE 5

void FCFS(struct process *, int);
void SJF_NP(struct process *, int);
void SJF_P(struct process *, int);
void Priority_NP(struct process *, int);
void Priority_P(struct process *, int);
void RR(struct process *, int, int);

void main(void)
{
    struct process list1[SIZE] = {{1, 0, 1, 3}, {2, 3, 8, 4}, {3, 4, 5, 2}, {4, 5, 2, 2}, {5, 8, 4, 1}};
    cout << "\n FCFS\n";
    FCFS(list1, SIZE);
    cout << "\n SJF_NP\n";
    SJF_NP(list1, SIZE);
    cout << "\n SJF_P\n";
    SJF_P(list1, SIZE);
    cout << "\n Priority_NP\n";
    Priority_NP(list1, SIZE);
    cout << "\n Priority_P\n";
    Priority_P(list1, SIZE);
    cout << "\n RR\n";
    RR(list1, SIZE, 3);
    getch();
}

class queue
{
private:
    int front, rear, counter, size;
    struct process *que;

public:
    queue(int ss)
    {
        size = ss;
        que = new process[size];
        front = rear = counter = 0;
    }
    void enqueue(process temp)
    {
        //		if(counter >= size) { cout << "ERROR, Queue is full \n";  exit ; }
        que[rear] = temp;
        rear = (rear + 1) % size;
        counter++;
    }
    process dequeue(void)
    {
        process temp;
        temp = que[front];
        front = (front + 1) % size;
        counter--;
        return temp;
    }
    bool is_full(void) { return counter == size; }
    bool is_empty(void) { return counter == 0; }
};

process *sort_process(process *ptr, int n)
{
    struct process temp, *list;
    list = new process[n];
    int a, b;
    for (a = 0; a < n; a++)
        list[a] = ptr[a];

    for (a = 0; a < n; a++)
    {
        for (b = a + 1; b < n; b++)
            if (list[a].arv > list[b].arv)
            {
                temp = list[a];
                list[a] = list[b];
                list[b] = temp;
            }
        cout << list[a].num << "\t" << list[a].arv << "\t" << list[a].bur << "\t" << list[a].pri << "\n";
    }
    return list;
}
void FCFS(struct process *prs, int n)
{
    struct process *list;
    list = sort_process(prs, n);

    int t = 0;
    for (int a = 0; a < n; a++)
    {
        while (list[a].bur > 0)
        {
            if (t >= list[a].arv)
            {
                cout << t << " ~ " << t + 1 << "\t\t" << list[a].num << "\n";
                list[a].bur--;
            }
            else
                cout << t << " ~ " << t + 1 << "\t\t" << "NULL\n";
            t++;
        }
    }
}

void SJF_NP(struct process *prs, int n)
{
    struct process *list;
    list = sort_process(prs, n);

    int t = 0;
    int index_min, min_bur, still;
    still = 1;
    while (still == 1)
    {
        index_min = -1;
        min_bur = 1000;
        for (int a = 0; a < n; a++)
            if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].bur < min_bur))
            {
                min_bur = list[a].bur;
                index_min = a;
            }

        //		cout << "min_index = " << index_min << "\t burst = " << min_bur << "\n";
        if (index_min != -1)
        {
            while (list[index_min].bur > 0)
            {
                cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
                t++;
                list[index_min].bur--;
            }
        }
        else
        {
            still = 0;
            for (int a = 0; a < n; a++)
                if (list[a].bur > 0)
                {
                    still = 1;
                    cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
                    t++;
                    break;
                }
        }
    }
}

void Priority_NP(struct process *prs, int n)
{
    struct process temp, *list;
    list = sort_process(prs, n);

    int t = 0;
    int index_min, min_pri, still;
    still = 1;
    while (still == 1)
    {
        index_min = -1;
        min_pri = 1000;
        for (int a = 0; a < n; a++)
            if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].pri < min_pri))
            {
                min_pri = list[a].pri;
                index_min = a;
            }

        if (index_min != -1)
        {
            while (list[index_min].bur > 0)
            {
                cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
                t++;
                list[index_min].bur--;
            }
        }
        else
        {
            still = 0;
            for (int a = 0; a < n; a++)
                if (list[a].bur > 0)
                {
                    still = 1;
                    cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
                    t++;
                    break;
                }
        }
    }
}

void SJF_P(struct process *prs, int n)
{
    struct process temp, *list;
    list = sort_process(prs, n);
    int t = 0;
    int index_min, min_bur, still;
    still = 1;
    while (still == 1)
    {
        index_min = -1;
        min_bur = 1000;
        for (int a = 0; a < n; a++)
            if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].bur < min_bur))
            {
                min_bur = list[a].bur;
                index_min = a;
            }

        if (index_min != -1)
        {
            cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
            t++;
            list[index_min].bur--;
        }
        else
        {
            still = 0;
            for (int a = 0; a < n; a++)
                if (list[a].bur > 0)
                {
                    still = 1;
                    cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
                    t++;
                    break;
                }
        }
    }
}

void Priority_P(struct process *prs, int n)
{
    struct process temp, *list;
    list = sort_process(prs, n);
    int t = 0;
    int index_min, min_pri, still;
    still = 1;
    while (still == 1)
    {
        index_min = -1;
        min_pri = 1000;
        for (int a = 0; a < n; a++)
            if ((t >= list[a].arv) && (list[a].bur > 0) && (list[a].pri < min_pri))
            {
                min_pri = list[a].pri;
                index_min = a;
            }

        if (index_min != -1)
        {
            cout << t << " ~ " << t + 1 << "\t\t" << list[index_min].num << "\n";
            t++;
            list[index_min].bur--;
        }
        else
        {
            still = 0;
            for (int a = 0; a < n; a++)
                if (list[a].bur > 0)
                {
                    still = 1;
                    cout << t << " ~ " << t + 1 << "\t\t" << "NULL \n";
                    t++;
                    break;
                }
        }
    }
}

void RR(struct process *prs, int n, int quantum)
{
    struct process temp, *list;
    list = sort_process(prs, n);

    queue myque(n);
    int t = 0, still = 1, index = 0;
    process current;
    for (int k = index; k < n; k++)
        if (list[k].arv == 0)
        {
            myque.enqueue(list[k]);
            index++;
        }
    while ((index < n) || (myque.is_empty() == false))
    {
        if (myque.is_empty() == true)
        {
            cout << t << " ~ " << t + 1 << "\t\t" << "IDLE \n";
            t++;
        }
        else
        {
            current = myque.dequeue();
            for (int k = 1; k <= quantum; k++)
            {
                if (current.bur > 0)
                {
                    cout << t << " ~ " << t + 1 << "\t\t" << current.num << "\n";
                    t++;
                    current.bur--;
                }
            }
        }
        for (int k = index; k < n; k++)
            if (list[k].arv <= t)
            {
                myque.enqueue(list[k]);
                index++;
            }
        if (current.bur > 0)
            myque.enqueue(current);
    }
}
