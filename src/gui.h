/*
        gui.h
1.	This file contains versatile gui classes.
2.	Box is the parent class and other classes like button, MessageBox, window etc are derived from it.
3.	This file can be used in any other program development.

*/
#include <stdio.h>
#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>

#define WINBG LIGHTGRAY
#define LIGHT WHITE 
#define DARK DARKGRAY



#define CHAR_WD 5
#define ST_FILL MAGENTA
#define TB_HEIGHT 15
#define MsgB_HEIGHT 80
#define MsgB_TEXTCOL BLACK


enum{CANCLE=10,OK};
enum {MSG,ALERT,OPTION,INPUT,OPTION_ALERT};
//Button ID
enum{TEMP=1000,DEF};
///////////////////GUI
//////////////////////////////////////////////////////////////
	int p[10];

class Box;
Box* const ORIGIN=(Box*)0;
class Box
{
protected:
	int X;
	int Y;
	int Width;
	int Height;
	
	Box* ptrOwner;
public:
	int LightCol;
	int DarkCol;
	Box(Box* ptr,int x,int y,int w,int h,int Lcol,int Dcol);
	void display();
	int getx(){return X;};
	int gety(){return Y;};
	int getw(){return Width;};
	int geth(){return Height;};
};


class NamedBox:public Box
{
protected:
	char title[30];
	int Font;
	int Size;
public:
	NamedBox(Box* ptr,int x,int y,int w,int h,char* tt,int Lcol,int Dcol,int font,int size);
	~NamedBox(){delete &title;};
	void display();
};

class TextBox:public NamedBox
{
	
	int FillCol,TextCol;

public:
	TextBox(Box* ptr,int x,int y,int w,int h,char* ,int Textcol,int Fillcol,int font,int size);
	void display(int styl,int offsetx,int offsety);
};


class Button:public Box
{
protected:
	
	int ID;
	int TextCol,FillCol;
	char Name[20];
	char Status[60];
public:
	Button(Box* ptr,int x,int y,int w,int h,int id,char* nm,char* status,int TextCol,int FillCol);
	void display(int push);
	int over(int& last);
	int click();
};

class stkyButton:public Button
{
	int State;
public:
	stkyButton(Box* ptr,int x,int y,int w,int h,int id,char* nm,char* status,int TextCol,int FillCol);
	int click();
	void setState(int state);
	int getState(){return State;};
};

class Window:public Box
{
protected:
/*	int X;
int Y;
int Width;
int Height;
int LightCol;
int DarkCol;
	*/
	char* title;
	int FillCol;
	int TextCol;
	int p[10];
	Box* Border;
	TextBox* t;
	TextBox* body;
	
public:
	Window(Box* ptr,int x,int y,int w,int h,char* tt,int Lcol,int dcol);
	~Window(){delete Border;delete t;delete body;};
	void display();
	void setTextCol(int col);
};

class StatusBar:Box
{
	int TextCol;
	char Msg[100];
public:
	StatusBar(int Text);
	void setDisp(char* msg);
}st(WHITE);

class MessageBox:Box
{

	TextBox* bb;
	Window *child;
public:
	MessageBox(Window* ptr);
	int evoke(char* Text,char* Caption,int type,Window* pt);
}	;//global();

/////////////Definations/////////////

Box::Box(Box* ptr,int x,int y,int w,int h,int Lcol=LIGHT,int Dcol=DARK)
{
	ptrOwner=ptr;
	X=x;Y=y;Width=w;Height=h;LightCol=Lcol;DarkCol=Dcol;
	if(ptrOwner !=ORIGIN)
	{
		X+=ptrOwner->X;
		Y+=ptrOwner->Y;
	}
};



void Box::display()
{
	//
	setcolor(LightCol);
	moveto(X,Y+Height);
	lineto(X,Y);
	lineto(X+Width,Y);

	setcolor(DarkCol);
	lineto(X+Width,Y+Height);
	lineto(X,Y+Height);
};

NamedBox::NamedBox(Box* ptr,int x,int y,int w,int h,char* tt="",int Lcol=LIGHT,int Dcol=DARK,int font=DEFAULT_FONT,int size=0):Box(ptr,x,y,w,h,Lcol,Dcol)
{
	strcpy(title,tt);Font=font;Size=size;
};
void NamedBox::display()
{
	
	setcolor(LightCol);
	moveto(X,Y+Height);
	lineto(X,Y);
	lineto(X+4,Y);
	settextstyle(Font,0,Size);
	settextjustify(0,1);
	outtextxy(X+10,Y-2,title);

	moveto(X+2+strlen(title)*8,Y);
	lineto(X+Width,Y);
	setcolor(DarkCol);
	lineto(X+Width,Y+Height);
	lineto(X,Y+Height);
	
}
TextBox::TextBox(Box* ptr,int x,int y,int w,int h,char* tt="",int Textcol=WHITE,int Fillcol=BLUE,int font=DEFAULT_FONT,int size=0):NamedBox(ptr,x,y,w,h,tt,Fillcol,Fillcol,font,size)
{
	FillCol=Fillcol;
	TextCol=Textcol;

};
void TextBox::display(int styl=SOLID_FILL,int offsetx=0,int offsety=0)
{
	
	int p[10];
	p[0]=X+offsetx;p[1]=Y+offsety;				p[2]=X+Width-offsetx;p[3]=Y+offsety;
	p[6]=X+offsetx;p[7]=Y+Height-offsety;		p[4]=X+Width-offsetx;p[5]=Y+Height-offsety;
	p[8]=X+offsetx;p[9]=Y+offsety;
	
	setfillstyle(styl,FillCol);
	setcolor(FillCol);
	fillpoly(5,p);
	settextjustify(1,1);
	setcolor(TextCol);
	outtextxy(X+Width/2+offsetx,Y+Height/2+offsety,title);

}


Window::Window(Box* ptr,int x,int y,int w,int h,char* tt="",int Lcol=LIGHT,int Dcol=DARK):Box(ptr,x,y,w,h,Lcol,Dcol)
{
	
	title=tt;TextCol=WHITE;FillCol=BLUE;
	Border=new Box(this,0,0,Width,Height,LightCol,DarkCol);
	t=new TextBox(this,1,1,Width-2,TB_HEIGHT-2,title,WHITE,BLUE);
	body=new TextBox(this,1,TB_HEIGHT,Width-2,Height-TB_HEIGHT-1,"",WINBG,WINBG);
};
void Window::setTextCol(int col){TextCol=col;};
void Window::display()
{
	hidemouse();
	p[0]=X+1;p[1]=Y+TB_HEIGHT;				p[2]=X+Width-2;p[3]=Y+TB_HEIGHT;
	p[6]=X+1;p[7]=Y+Height;		p[4]=X+Width-2;p[5]=Y+Height;
	p[8]=X+1;p[9]=Y+TB_HEIGHT;
	setfillstyle(SOLID_FILL,WINBG);
	setcolor(WINBG);
	fillpoly(5,p);
	Border->display();
	t->display();
	showmouse();
	
};

StatusBar::StatusBar(int Text):Box(ORIGIN,0,339,640,10,LIGHTMAGENTA,DARK)
{
	TextCol=Text;
}
void StatusBar::setDisp(char* msg)
{
	strcpy(Msg,msg);
	Box::display();
	int p[10];
	p[0]=X;p[1]=Y;				p[2]=X+Width;p[3]=Y;
	p[6]=X;p[7]=Y+Height;		p[4]=X+Width;p[5]=Y+Height;
	p[8]=X;p[9]=Y;
	setfillstyle(SOLID_FILL,ST_FILL);
	setcolor(ST_FILL);
	settextjustify(0,1);

	setactivepage(1);
	fillpoly(5,p);	
	setcolor(TextCol);
	outtextxy(X+4,Y+Height/2-2,Msg);
	setactivepage(0);
	setcolor(ST_FILL);
	fillpoly(5,p);
	setcolor(TextCol);
	outtextxy(X+4,Y+Height/2-2,Msg);

};
Button::Button(Box* ptr,int x,int y,int w,int h,int id,char* nm="",char* status="",int Textcol=BLACK,int Fillcol=WINBG):Box(ptr,x,y,w,h)
{
	ID=id;
	strcpy(Name,nm);
	strcpy(Status,status);
	TextCol=Textcol;
	FillCol=Fillcol;
	if(Width<strlen(Name)*CHAR_WD) Width=strlen(Name)*CHAR_WD+8;
};


void Button::display(int push=0)
{
		hidemouse();
	if(push)
	{
		Box b1(this,0,0,Width,Height,BLACK,LightCol);
		Box b2(this,1,1,Width-2,Height-2,FillCol,WINBG);

		TextBox tb1(this,3,3,Width-5,Height-5,Name,TextCol,FillCol);

		tb1.display(SOLID_FILL);b1.display();b2.display();
	}else 
	{
	Box b1(this,0,0,Width,Height,LightCol,BLACK);
	Box b2(this,1,1,Width-2,Height-2,LightCol,DarkCol);
	TextBox tb1(this,1,1,Width-3,Height-3,Name,TextCol,FillCol);
	tb1.display();b1.display();//b2.display();
	}
		showmouse();
}
int Button::click()
{
	
	if(gmouse_b==1&&gmouse_x>X&&gmouse_x<X+Width&&gmouse_y>Y&&gmouse_y<Y+Height)
	{


		this->display(1);

		while(gmouse_b==1)
			getmouse();

		this->display(0);

		showmouse();
		if(gmouse_x>X&&gmouse_x<X+Width&&gmouse_y>Y&&gmouse_y<Y+Height) return 1;
		else return 0;
	}
	return 0;
}
int Button::over(int& last)
{
	if(gmouse_x>X&&gmouse_x<X+Width&&gmouse_y>Y&&gmouse_y<Y+Height)
	{
		if(ID!=last)	{st.setDisp(Status);last=ID;};
		return 1;
	}
	return 0;
	
};


stkyButton::stkyButton(Box* ptr,int x,int y,int w,int h,int id,char* nm="",char* status="",int TextCol=BLACK,int FillCol=WINBG):Button(ptr,x,y,w,h,id,nm,status,TextCol,FillCol)
{
	State=0;

};



int stkyButton::click()
{
	if(gmouse_b==1&&gmouse_x>X&&gmouse_x<X+Width&&gmouse_y>Y&&gmouse_y<Y+Height)
	{
		if(State==0){
			setState(1);
			
		}else
		{
			setState(0);
			
		}
		while(gmouse_b==1)
			getmouse();
		
		
		if(gmouse_x>X&&gmouse_x<X+Width&&gmouse_y>Y&&gmouse_y<Y+Height) 
		{
			
			return 1;
		}
		else
		{ 
			if(State==0){
				setState(1);
				
			}else
			{
				setState(0);
				
			}
		}
	}
	return 0;
	
};



void stkyButton::setState(int st)
	{
	hidemouse();
		if(st){
			setactivepage(1);

			this->display(1);

			setactivepage(0);

			this->display(1);

			State=1;
		}else{
			setactivepage(1);
			this->display(0);
			setactivepage(0);
			this->display(0);
			State=0;
		};
		showmouse();
};



MessageBox::MessageBox(Window *ptr=(Window*)ORIGIN):Box(ptr,200,200,80,MsgB_HEIGHT)
{

	if(ptr!=(Window*)ORIGIN)
	{
		X=ptr->getx()+ptr->getw()/2;
		Y=ptr->gety()+ptr->geth()/2;
	}

	//	X=30;Y=50;
	
}

int MessageBox::evoke(char* Text,char* Caption,int type,Window* pt=(Window*)ORIGIN)
{
	
	char far *image;
	if(pt!=(Window*)ORIGIN)
	{
		X=pt->getx()+pt->getw()/2;
		Y=pt->gety()+pt->geth()/2;
	}

	if(Width<strlen(Text)*(CHAR_WD+2)) Width=strlen(Text)*(CHAR_WD+2)+10;
	if(Width<180) Width=260;
	if(Width>350)Width=345;  //reduce Image size
//	Width=350;
	
	//Center
	int tempX=X;
	int tempY=Y;
	X-=Width/2;
	Y-=Height/2;
	//


	hidemouse();
	char tag=65;
	image=new char[imagesize(0,0,Width,Height)];
	getimage(X,Y,X+Width,Y+Height,image);

	TextBox b1(this,0,0,Width,Height,"",BLACK,WINBG);
	b1.display();
	TextBox b2(this,0,0,Width,TB_HEIGHT,Caption);
	b2.display();
	Box bor(this,0,0,Width,Height);
	bor.display();

	setcolor(MsgB_TEXTCOL);
	outtextxy(X+Width/2,Y+MsgB_HEIGHT/2-10,Text);

	Button ok((Box*)this,Width/3-8,MsgB_HEIGHT-20,60,18,TEMP,"OK");
	Button cancle((Box*)this,Width*2/3-8,MsgB_HEIGHT-20,60,18,TEMP,"Cancel");
	Button exit((Box*)this,Width-18,2,16,12,TEMP,"X");
	exit.display();



	
	showmouse();


	switch(type){
	case ALERT:
		setcolor(RED);
		setlinestyle(0,0,3);
		circle(X+25,Y+MsgB_HEIGHT/2-10,13);
		setfillstyle(SOLID_FILL,YELLOW);
		setlinestyle(0,0,0);
		floodfill(X+25,Y+MsgB_HEIGHT/2-10,RED);
	case MSG:
		Button a((Box*)this,Width/2-30,MsgB_HEIGHT-30,60,18,TEMP,"OK");
		ok=a;
		ok.display();
		
		break;
	case OPTION_ALERT:
		setcolor(RED);
		setlinestyle(0,0,3);
		circle(X+25,Y+MsgB_HEIGHT/2-10,13);
		setfillstyle(SOLID_FILL,YELLOW);
		setlinestyle(0,0,0);
		floodfill(X+25,Y+MsgB_HEIGHT/2-10,RED);
		outtextxy(X+25,Y+MsgB_HEIGHT/2-10,"X");

	case OPTION:
		Button b((Box*)this,Width/4-30,MsgB_HEIGHT-30,60,18,TEMP,"OK");
		Button c((Box*)this,Width*3/4-30,MsgB_HEIGHT-30,60,18,TEMP,"Cancel");
		ok=b;cancle=c;
		ok.display();
		cancle.display();
		break;
	}

  
	  do{
		while(!kbhit()&&!getmouse())
		{
			delay(20);
		}
		if(gmouse_b){
			
			if(ok.click()) tag=OK;
			if((type==OPTION||type==OPTION_ALERT||type==INPUT)&&cancle.click()) tag=CANCLE;
			if(exit.click()) tag=CANCLE;
		}else 
		{tag=getch();
		if(tag==27)tag=CANCLE;
		if(tag==13||tag==32) tag=OK;
		}
		
	}while(tag!=OK&&tag!=CANCLE);
	//Restore

	hidemouse();
	putimage(X,Y,image,COPY_PUT);
	showmouse();

	X=tempX;
	Y=tempY;
	delete []image;
	delete &ok;
	delete &cancle;
	delete &exit;

	if(tag==27||tag==13||tag==32||tag==OK) return 1;
	else return 0;
}

void BitMapDisplay() {
	
	int BitmapX = 450;
	int BitmapY = 20;
	int x,y;
	const int BitmapWidth=173;//287	333
	const int BitmapHeight=72;//95	171
	int Byte;
	FILE *fp;
	fp = fopen("logo.bmp", "rb");
	fseek(fp, 1078, 0);
	for(y=BitmapY; y<BitmapY+BitmapHeight; y++) {
		for(x=BitmapX; x<BitmapX+BitmapWidth; x++) {
			Byte = getc(fp);
			
			if (Byte == 0) {
				putpixel (x,y, 8);
			}
			else {
				putpixel (x,y, Byte);
			}
		}
		fseek(fp, 3, 1);
	}
}


