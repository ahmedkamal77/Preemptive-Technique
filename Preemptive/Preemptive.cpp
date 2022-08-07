// Preemptive.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

struct task
{
    int priority;
    double r;
    double p;
    double e;
    double d;
    double from;
    double to;
    int x;
    int y;

};

bool r_comp(task& a, task& b)
{
    return a.r < b.r;
}

bool priority_comp(task& a, task& b)
{
    return a.priority > b.priority;
}
int main()
{
    //preemptive

    int n, j = 6;
    cout << "Enter number of tasks: ";
    cin >> n;
    vector<task> tasks(n);
    deque<task> active;
    deque<task> waiting;
    for (int i = 0; i < n; ++i)
    {
        cout << "Enter release time of T" << i + 1 << ": ";
        cin >> tasks[i].r;
        cout << "Enter period of T" << i + 1 << ": ";
        cin >> tasks[i].p;
        cout << "Enter execution time of T" << i + 1 << ": ";
        cin >> tasks[i].e;
        cout << "Enter deadline of T" << i + 1 << ": ";
        cin >> tasks[i].d;
        cout << "Enter priority of T" << i + 1 << ": ";
        cin >> tasks[i].priority;
        cout << endl;
        tasks[i].x = i + 1;
        tasks[i].y = 1;
        tasks[i].from = tasks[i].r;
    }
    sort(tasks.begin(), tasks.end(), r_comp);
    for (int i = 1; i < n; ++i)
    {
        if (tasks[0].r == tasks[i].r)
        {
            if (tasks[0].priority < tasks[i].priority)
                swap(tasks[0], tasks[i]);
        }
    }
    active.push_back(tasks[0]);
    tasks[0].r += tasks[0].p;
    tasks[0].y++;
    sort(tasks.begin(), tasks.end(), r_comp);
    for (int i = 1; i < n; ++i)
    {
        if (tasks[0].r == tasks[i].r)
        {
            if (tasks[0].priority < tasks[i].priority)
                swap(tasks[0], tasks[i]);
        }
    }
    while (j--)
    {
        /* if(tasks[0].from+tasks[0].e > tasks[1].s)
         {
             if(tasks[0].priority<tasks[1].priority)
             {
                tasks[0].to=tasks[1].r;
                cout<<"from"<<tasks[0].from<<"to"<<tasks[0].to<<": j"<<tasks[0].x<<tasks[0].y<<endl;
                task[0].e-=tasks[0].to-tasks[0].from;

             }
         }*/
        if (active[0].from + active[0].e > tasks[0].r)
        {
            if (active[0].priority < tasks[0].priority)
            {
                active[0].to = tasks[0].r;
                cout << "from" << active[0].from << "to" << active[0].to << ": j" << active[0].x << active[0].y << endl;
                if (active[0].d * active[0].y < active[0].to)
                {
                    cout << "j" << active[0].x << active[0].y << "has exceeded deadline" << endl;
                    break;
                }
                active[0].e -= active[0].to - active[0].from;
                waiting.push_back(active[0]);
                sort(waiting.begin(), waiting.end(), priority_comp);
                active.pop_front();
                active.push_back(tasks[0]);
                tasks[0].r += tasks[0].p;
                tasks[0].y++;
                sort(tasks.begin(), tasks.end(), r_comp);
                for (int i = 1; i < n; ++i)
                {
                    if (tasks[0].r == tasks[i].r)
                    {
                        if (tasks[0].priority < tasks[i].priority)
                            swap(tasks[0], tasks[i]);
                    }
                }
            }
            else
            {
                active[0].to = active[0].from + active[0].e;
                cout << "from" << active[0].from << "to" << active[0].to << ": j" << active[0].x << active[0].y << endl;
                if (active[0].d * active[0].y < active[0].to)
                {
                    cout << "j" << active[0].x << active[0].y << "has exceeded deadline" << endl;
                    break;
                }
                if (!waiting.empty())
                {
                    if (tasks[0].r <= active[0].to)
                    {
                        if (tasks[0].priority > waiting[0].priority)
                        {
                            tasks[0].from = active[0].to;
                            active.push_back(tasks[0]);
                            tasks[0].r += tasks[0].p;
                            tasks[0].y++;
                            sort(tasks.begin(), tasks.end(), r_comp);
                            for (int i = 1; i < n; ++i)
                            {
                                if (tasks[0].r == tasks[i].r)
                                {
                                    if (tasks[0].priority < tasks[i].priority)
                                        swap(tasks[0], tasks[i]);
                                }
                            }
                        }

                    }
                    else
                    {
                        waiting[0].from = active[0].to;
                        active.push_back(waiting[0]);
                        waiting.pop_front();
                    }
                    active.pop_front();
                }
                else
                {
                    if (tasks[0].r <= active[0].to)
                        tasks[0].from = active[0].to;
                    else
                        tasks[0].from = tasks[0].r;
                    active.push_back(tasks[0]);
                    tasks[0].r += tasks[0].p;
                    tasks[0].y++;
                    sort(tasks.begin(), tasks.end(), r_comp);
                    for (int i = 1; i < n; ++i)
                    {
                        if (tasks[0].r == tasks[i].r)
                        {
                            if (tasks[0].priority < tasks[i].priority)
                                swap(tasks[0], tasks[i]);
                        }
                    }
                    active.pop_front();
                }
            }
        }
        else
        {
            active[0].to = active[0].from + active[0].e;
            cout << "from" << active[0].from << "to" << active[0].to << ": j" << active[0].x << active[0].y << endl;
            if (active[0].d * active[0].y < active[0].to)
            {
                cout << "j" << active[0].x << active[0].y << "has exceeded deadline" << endl;
                break;
            }
            if (!waiting.empty())
            {
                if (tasks[0].r <= active[0].to)
                {
                    if (tasks[0].priority > waiting[0].priority)
                    {
                        tasks[0].from = active[0].to;
                        active.push_back(tasks[0]);
                        tasks[0].r += tasks[0].p;
                        tasks[0].y++;
                        sort(tasks.begin(), tasks.end(), r_comp);
                        for (int i = 1; i < n; ++i)
                        {
                            if (tasks[0].r == tasks[i].r)
                            {
                                if (tasks[0].priority < tasks[i].priority)
                                    swap(tasks[0], tasks[i]);
                            }
                        }
                    }

                }
                else
                {
                    waiting[0].from = active[0].to;
                    active.push_back(waiting[0]);
                    waiting.pop_front();
                }
                active.pop_front();
            }
            else
            {
                if (tasks[0].r <= active[0].to)
                    tasks[0].from = active[0].to;
                else
                    tasks[0].from = tasks[0].r;
                active.push_back(tasks[0]);
                tasks[0].r += tasks[0].p;
                tasks[0].y++;
                sort(tasks.begin(), tasks.end(), r_comp);
                for (int i = 1; i < n; ++i)
                {
                    if (tasks[0].r == tasks[i].r)
                    {
                        if (tasks[0].priority < tasks[i].priority)
                            swap(tasks[0], tasks[i]);
                    }
                }
                active.pop_front();
            }
        }

    }
    return 0;
}


