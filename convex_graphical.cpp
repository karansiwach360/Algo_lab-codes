#include <iostream>
#include <vector>
#include <algorithm>
#include<graphics.h>
#include<windows.h>
#include <math.h>
#include <stdio.h>
using namespace std;

float area(pair<int,int> a,pair<int,int> b,pair<int,int> c);
int direction(pair<int,int> a,pair<int,int> b,pair<int,int> c);
void QuickHull(pair<int,int> a,pair<int,int> b,vector<pair<int,int> >list);
float distance(pair<int,int> a,pair<int,int> b,pair<int,int> c);

vector<pair<int,int> >answer;

bool comp(pair<int,int> a,pair<int,int> b)
{
	int x1=answer[0].first;
	int y1=answer[0].second;
	int x2=a.first;
	int y2=a.second;
	int x3=b.first;
	int y3=b.second;
	return (y2-y1)*(x3-x1)>(x2-x1)*(y3-y1);
}

float distance(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
	int x1,y1,x2,y2;
	x1=a.first;
	y1=a.second;
	x2=b.first;
	y2=b.second;
	float ar=area(a,b,c);
	ar=ar>0?ar:-ar;
	float dist=(2.0*ar)/sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	return dist;
}

int direction(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
	float ar=area(a,b,c);
	if(ar>0)
	{
		return -1;			//anti-clockwise that is right side of a line;
	}
	else
	{
		return 1;			//clockwise that is left side of line
	}
}

float area(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
	float x1,y1,x2,y2,x3,y3;
	x1=a.first;
	y1=a.second;
	x2=b.first;
	y2=b.second;
	x3=c.first;
	y3=c.second;
	float area=x1*(y2-y3)-y1*(x2-x3)+x2*y3-y2*x3;
	return area/2.0;
}

void QuickHull(pair<int,int> a,pair<int,int> b,vector<pair<int,int> >list)
{
	vector<pair<int,int> >temp;
	for (int i = 0; i < list.size(); ++i)			//remember to  add 1st element and last elementas the currect point
	{
		if(direction(a,b,list[i])==-1)
		{
			temp.push_back(list[i]);
		}
	}

	if(temp.size()==0)					//termination of function
	{
		return;
	}
	float current_distance=0,maximum_distance=0;
	int maximum_index=0;
	for (int i = 0; i < temp.size(); ++i)
	{
		current_distance=distance(a,b,temp[i]);
		if(current_distance>maximum_distance)
		{
			maximum_distance=current_distance;
			maximum_index=i;
		}
	}
	answer.push_back(temp[maximum_index]);
	QuickHull(a,temp[maximum_index],temp);
	QuickHull(temp[maximum_index],b,temp);
}

int inputg_int(int x,int y){
    char ch;
    char name[100];
    int i=0;
    int sign=1;
    do{
        ch=getch();
        if(int(ch)==8){
                if(i>0)
            name[--i]='\0';
        else
            sign=1;
        }
        if(int(ch)>=48 && int(ch)<=57){
                name[i++]=ch;
                name[i]='\0';
                if(name[0]=='0')i--;
        }
        outtextxy(x,y,"                                                   ");
        if((ch=='-' && i==0) || sign==-1){
            outtextxy(x,y,"-");
            sign=-1;
        }
        outtextxy(x+20,y,name);
    }while(int(ch)!=13);
    return atoi(name)*sign;
}
int main()
{
    int width =  GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width,height,"",-3,-3);
    settextstyle(10,0,2);
    setcolor(10);
    outtextxy(150,25, "  Enter no. of points : ");
    int n=inputg_int(450,25);
    int k,xx,yy,i=0;
    k=n;
    char cord[100];
    POINT cursor;
	vector <pair<int,int> > a(n);
    while(k){
        GetCursorPos(&cursor);
        xx=cursor.x;
        yy=cursor.y;
        if(GetAsyncKeyState(VK_LBUTTON)){
            setcolor(10);circle(xx,yy,1);
            setcolor(8);circle(xx,yy,2);
            setcolor(6);circle(xx,yy,3);
            setcolor(4);circle(xx,yy,4);
            setcolor(10);circle(xx,yy,5);
            delay(400);
            a[i]=make_pair(xx,yy);
            settextstyle(10,0,1);
            sprintf(cord,"( %d,%d )",xx,yy);
            outtextxy(xx+10,yy,cord);
            i++;k--;
        }
    }
    sort(a.begin(),a.end());
	answer.push_back(a[0]);
	answer.push_back(a[n-1]);

	vector<pair<int,int> >b;
	b.assign(a.begin()++,a.end()--);

	QuickHull(a[0],a[n-1],b);
	QuickHull(a[n-1],a[0],b);

	sort(answer.begin()++,answer.end(),comp);
	//cout<<"\n answer \n ";
	for (int i = 0; i < answer.size();i++)
	{
		cout<<answer[i].first<<" "<<answer[i].second<<endl;
        setcolor(YELLOW);line(answer[i].first,answer[i].second,answer[(i+1)%answer.size()].first,answer[(i+1)%answer.size()].second);
	}
	//cout<<answer[0].first<<" "<<answer[0].second;
	delay(150);
    getch();
    closegraph();
    return 0;
}
