/*
(Cube_App.cpp)
1.	It consists of only CUBE_APP  class definition.
2.	All enumeration for Message ID and Button ID are done in this file.
3.	All the solving algorithm and main loop of application is in this file.
4.	Objects like main cube, buttons, windows, box, etc are initialise.
5.	MainLoop() method enters the main event loop.
6.	KeyMsg() and MouseMsg() methods translates the keyboard input and mouse input and tag it with appropriate Message ID, i.e. assign GlobalMsg.
7.	DispatchMsg( ) method filters the message assigned to GlobalMsg variable virtually dispatches the messages or perform the required task.
8.	SolveIt() method starts the solving algorithm which is equipped with different mini-methodes.

*/
//Cube_App.h
#include <stdio.h>
#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
#include "mouse.h"
#include "bigCube.h"
#include "gui.h"

#define INTROTEXT LIGHTCYAN
#define TEXTCOL BLUE
#define FILL CYAN

#define CHAR_H 20
#define CHAR_W 60
#define CHAR_W2 9
#define CHARWIDTH 7
#define RAND 20
#define WINBG LIGHTGRAY
#define LIGHT WHITE 
#define DARK DARKGRAY
#define BHEIGHT 15
#define MOVEX 5
#define MOVEY 205
#define PLAY_Y 300
#define STRING1 "3D Cube"
#define STRING2 "dhilung@hotpop.com"
#define STRING4 "R -> Rotation toggle | UP,DOWN -> Speed | LEFT,RIGHT -> Pespective Index | Esc -> EXIT"
#define STRING5 "Use your mouse as in AUTOCAD or in 3DsMax"
#define STR_CREDIT "                                 ])>---->        CREDIT        <----<(["




#define ST_FILL MAGENTA
#define BUT_W 55
#define BUT_H 15
#define BUT_DS 4
#define BUT_DL	15
#define BUT_TXTCOL BLUE
#define BUT_FILLCOL CYAN

enum {ta3=1,ta2,ta1,sb3,sb2,sb1,fb3,fb2,fb1,tb3,tb2,tb1,sa3,sa2,sa1,fa3,fa2,fa1};
char DEF_MSG[]="Esc -> Back | R -> Rotation toggle | UP,DOWN -> Speed | LEFT,RIGHT -> Pespective Index";

enum{DEFAULT=100,CREDIT,EXIT,PAUSE,SAVE,RESET,RESTORE,MOVE,SOLVE,NAVIGATE,SET_ROT,SHOW_NUM,SPEED_UP,SPEED_DWN,SCALE_UP,SCALE_DWN,PER_INDEX_UP,PER_INDEX_DWN,START,START_NO,DELAY_UP,DELAY_DWN,RXX,RYY,RZZ,TOG_STEP};
enum{X_R,Y_G,Z_B};
enum{X_ROT=10,Y_ROT,Z_ROT};
//Buttom IDs
enum {DEFLT=1,ID_VPORT,ID_SAVE,ID_RESTORE,ID_RANDOM,ID_SOLVE,ID_EXIT,ID_RESET,ID_ROT_BUT,ID_STEPED,ID_SP1,ID_SP2,ID_INDEX1,ID_INDEX2,ID_SCALE1,ID_SCALE2,ID_DISPATCH,ID_CREDIT};
enum{NO_REV,REV,MIRROR};	//Move type
///////////////////CUBE_APP
	int GlobalMsg='a';







void DisplayLogo() {
	
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
	
	if(!fp) {setcolor(RED);outtextxy(BitmapX+80,BitmapY+20,"logo.bmp not found.");}
}

class CUBE_APP{
	
	int running,b,x,y,_x,_y,count;
	char rx,ry,rz;
//Current
	int topaxis,sideaxis,frontaxis;

	int key,i,n,arot,a,lastover,solve_running,delay,step;
	float speed,cuberot;
	int midx,midy,maxcol;
	char CUBE_APPbuffer[30];
	char buff[30];	
	float dist;
	
	//NamedBox Moves;
	Button* top[7];
	Button* side[7];
	Button* front[7];
//	button save,restore,random,reset;

	Button *save,*restore,*random,*reset;
	Button *inc_delay,*dec_delay,*speed_up,*speed_dwn,*index_up,*index_dwn,*scale_up,*scale_dwn;
	stkyButton *rxx,*ryy,*rzz;
	stkyButton *rot_but,*steped;
	
	//
	Window* MainWin;
	MessageBox* Common;
	Button* close;
	stkyButton solve;
	
	
	bcube back;
	//	bcube restore_cube;
	bcube bc;	//MAIN CUBE
	///Utility funcions
	void setRot(int flag);
	void trace(int,int,float *);
	void trace(int,int,char *);
	void trace(char *);
	void trace(Box* b,int x,int y,int w,int h,char* v);


	void draw();
	void KeyMsg();
	void MouseOverMsg();
	void TransMsgRotation();
	void findOrientation();
	void MouseMsg();
	void MouseMsgSolve();
	void animate();
	void DispatchMsg(int msg_flag);
	void credit();

	
	//For solving;
	void move(int);
	int chk(int cb,int xyz)
	{
		return bc.c[cb].xyzcolor[xyz];
	};

	void solveIt(int);
	void corner1();
	void corner2();
	void corner3();
	void topinsert();
	//some moves
	void move1(int flag);
	void move2(int flag);
	void move3(int flag);
	void move_Nammy(int flag);
	void bottom_corner();
	void bottom_insert();
	void bottom_last();
	void pushit(int flag);
	void pullit(int flag);
	void lastMove();
	int solve_check();

public:
	CUBE_APP();
	~CUBE_APP();
	void intro();
	void ini();
	void MainEventLoop();
	
};
void CUBE_APP::~CUBE_APP()
{

	delete []CUBE_APPbuffer;
	delete []buff;	
	delete restore;
	delete []top;
	delete []side;
	delete []front;
	delete save;
	delete random;
	delete reset;
	delete inc_delay;
	delete dec_delay;
	delete steped;
	delete rot_but;
	delete MainWin;
	delete Common;
	delete close;
	delete &solve;
	delete &bc;
	delete &back;
	
//	cout<<"Destroyed";
}


void CUBE_APP::credit()
{
	cube cc(30,0,0,0);
	int i=0;
	char col_flag=2;
	float t=1.5,dx=.9,dy=.5,dz=1.3,ini_scale;
	viewporttype cur;
	ini_scale=scale;
	getviewsettings(&cur);	
	setviewport(5,20,10+VP_WIDTH,10+VP_HEIGHT,1);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
	//
				cc.faceColor[0]=BROWN;	///RED
				cc.faceColor[1]=YELLOW;
				cc.faceColor[2]=LIGHTRED;
				cc.faceColor[3]=RED;
				cc.faceColor[4]=LIGHTRED;
				cc.faceColor[5]=RED;
//
	do{

		scale=sin(i*3.41/180*1.5)+.50;
		if(fabs(cc.getCenterX())>90) dx=-dx;
		if(fabs(cc.getCenterY())>20) dy=-dy;
		if(fabs(cc.getCenterZ())>100) dz=-dz;
		if(i>9999) i=0;

		cc.move(dx,dy,dz);
		globalMat.setMatTot(t,.2,.3,.4);
		cc.rotate(&globalMat);
	//	globalMat.setMatTot(t,0,1,0);
	//	cc.rotate(&globalMat);
		globalMat.setMatTot(t,0.4,0.3,.9);
		cc.rotate(&globalMat);
		if(scale>0&&scale<.05)
		{
			
			col_flag=rand()%7;
		//	col_flag=5;
			switch(col_flag)
			{
			case 0:
				cc.faceColor[0]=DARKGRAY;
				cc.faceColor[1]=LIGHTCYAN    ;
				cc.faceColor[2]=LIGHTBLUE    ;
				cc.faceColor[3]=BLUE    ;
				cc.faceColor[4]=LIGHTBLUE    ;
				cc.faceColor[5]=BLUE    ;
				break;
			case 1:
				cc.faceColor[0]=YELLOW;
				cc.faceColor[1]=DARKGRAY;
				cc.faceColor[2]=LIGHTGREEN        ;
				cc.faceColor[3]=GREEN        ;
				cc.faceColor[4]=LIGHTGREEN        ;
				cc.faceColor[5]=GREEN        ;
				break;
			case 2:
				cc.faceColor[0]=BROWN;	///RED
				cc.faceColor[1]=YELLOW;
				cc.faceColor[2]=LIGHTRED;
				cc.faceColor[3]=RED;
				cc.faceColor[4]=LIGHTRED;
				cc.faceColor[5]=RED;
				break;
			case 3:
				cc.faceColor[0]=BLACK;
				cc.faceColor[1]=WHITE;
				cc.faceColor[2]=LIGHTGRAY;
				cc.faceColor[3]=DARKGRAY;
				cc.faceColor[4]=LIGHTGRAY;
				cc.faceColor[5]=DARKGRAY;
				break;
			case 4:
				cc.faceColor[0]=BROWN;
				cc.faceColor[1]=WHITE;
				cc.faceColor[2]=LIGHTMAGENTA;
				cc.faceColor[3]=MAGENTA;
				cc.faceColor[4]=LIGHTMAGENTA;
				cc.faceColor[5]=MAGENTA;
				break;
			case 5:
				cc.faceColor[0]=DARKGRAY;
				cc.faceColor[1]=WHITE;
				cc.faceColor[2]=CYAN;
				cc.faceColor[3]=LIGHTCYAN;
				cc.faceColor[4]=CYAN;
				cc.faceColor[5]=LIGHTCYAN;
				break;
			case 6:
				cc.faceColor[0]=LIGHTBLUE;
				cc.faceColor[1]=LIGHTRED;
				cc.faceColor[2]=GREEN;
				cc.faceColor[3]=LIGHTGREEN;
				cc.faceColor[4]=BLUE;
				cc.faceColor[5]=RED;
				break;
			}
		
		}




	setactivepage(1);

		clearviewport();
		  cc.disp(BLACK);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
		outtextxy(40,30,"Every problem has its solution.*");
		outtextxy(10,30+CHAR_H+3,"What does it take to solve trillions of problems?");
		outtextxy(10,30+2*CHAR_H,"Rigorous thinking and sticking to one smart idea.");
		outtextxy(10,30+4*CHAR_H,"Programmer : Dhilung H. Kirat");
		settextstyle(SMALL_FONT,HORIZ_DIR,4);
		setcolor(BLUE);
		outtextxy(10,30+6*CHAR_H,"*But it doesn't mean 'Every question can be answered.'");
		outtextxy(10,30+7*CHAR_H-5,"'coz answer is for the questioner (a human)");
	    outtextxy(10,30+8*CHAR_H-10,"but solution is for the problem (a abstract entity).             2004.3.30");

		//	delay(10);
	setvisualpage(1);	// 2 page display system (age flipping)
	setactivepage(0);
		if(fabs(cc.getCenterX())>50) dx=-dx;
		if(fabs(cc.getCenterY())>20) dy=-dy;
		if(fabs(cc.getCenterZ())>60) dz=-dz;
	

		cc.move(dx,dy,dz);
		globalMat.setMatTot(t,.2,.3,.4);
		cc.rotate(&globalMat);
		globalMat.setMatTot(t,0.4,0.3,.9);
		cc.rotate(&globalMat);
		
		clearviewport();
		  cc.disp(BLACK);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
		outtextxy(40,30,"Every problem has its solution.*");
		outtextxy(10,30+CHAR_H+3,"What does it take to solve trillions of problems?");
		outtextxy(10,30+2*CHAR_H,"Rigorous thinking and sticking to one smart idea.");
		outtextxy(10,30+4*CHAR_H,"Programmer : Dhilung H. Kirat");
		settextstyle(SMALL_FONT,HORIZ_DIR,4);
		setcolor(BLUE);
		outtextxy(10,30+6*CHAR_H,"*But it doesn't mean 'Every question can be answered.'");
		outtextxy(10,30+7*CHAR_H-5,"'coz answer is for the questioner (a human)");
	    outtextxy(10,30+8*CHAR_H-10,"but solution is for the problem (a abstract entity).             2004.3.30");

	setvisualpage(0);

		i++;
	if(kbhit()) key=getch();
	}while(key!=27&&key!=32&&key!=13&&!getmouse());
	key='a';
	scale=ini_scale;
	setviewport(cur.left,cur.top,cur.right,cur.bottom,cur.clip);
	settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	
}
void CUBE_APP::trace(Box* b,int x,int y,int w,int h,char* v="")
{

	if(v=="") v=CUBE_APPbuffer;
	TextBox temp(b,x,y,w,h,v);
	setactivepage(1);
	temp.display();
	setactivepage(0);
	temp.display();
}
void CUBE_APP::setRot(int flag=2)
{
	switch(flag)
	{
	case 2:
		if(arot) {arot=0;rot_but->setState(0);}
		else {arot=1;rot_but->setState(1);}
		break;
	case 0:
		arot=0;rot_but->setState(0);break;
	case 1:
		arot=1;rot_but->setState(1);break;
	case X_ROT:
		if(rx) {rx=0;rxx->setState(0);}
		else {rx=1;rxx->setState(1);}
		break;
	case Y_ROT:
		if(ry) {ry=0;ryy->setState(0);}
		else {ry=1;ryy->setState(1);}
		break;
	case Z_ROT:
		if(rz) {rz=0;rzz->setState(0);}
		else {rz=1;rzz->setState(1);}
		break;
	}

}
void CUBE_APP::move(int move_flag)
{

	if(solve_running)
	{
		int i;
	a=move_flag;
	cuberot=speed; running=1;
	while(cuberot&&solve_running){
		animate();
		if(!step) MouseMsgSolve();
		//	mouseovermsg();
	};
	for (i=0;i<=delay&&solve_running;i++)
	{
		if(solve_running) animate();
		
		if(step) 
		{
			if(kbhit()) {key=getch();i=delay;}
				else i--;
			if(lastover!=ID_STEPED)st.setDisp("Step-wise ON    Press any key for next move || Press step bottom again for Step-wise OFF.");
			lastover=ID_STEPED;
		}
		MouseMsgSolve();
		//mousemsg();
	}
	
	count++;
	}
	
};
void CUBE_APP::corner1()
{
	int ref1,ref2,c1,c2,c3;
	if(chk(26,1)!=ref1)
	{
		if(chk(8,0)==ref1){move(sb2);move(sb2);}else
			if(chk(16,5)==ref1){move(sa2);}else
				if(chk(12,3)==ref1){move(sb2);}else
					if(chk(10,2)==ref1){move(fa2);}else
						if(chk(14,4)==ref1){move(fb2);}
	}
	//cor1;
	
	if(ref1==chk(24,1)&&ref2==chk(24,5)){move(fa1); move(fa1); move(sb3); move(sb3);}
	if(ref1==chk(24,5)&&ref2==chk(24,4)){move(fb1); move(sa3);}
	if(ref1==chk(24,4)&&ref2==chk(24,1)){move(fb1); move(fb1); move(tb3); move(sb3);}
	
	//cor 2
	
	if(ref1==chk(18,1)&&ref2==chk(18,2)){move(fb1); move(tb3); move(sb3);}
	if(ref1==chk(18,5)&&ref2==chk(18,1)){move(sa3);}
	if(ref1==chk(18,2)&&ref2==chk(18,5)){move(fb1); move(sb3); move(sb3);}
	
	//cor3
	
	if(ref1==chk(6,4)&&ref2==chk(6,5)){move(fb1); move(tb3); move(sb3);}
	if(ref1==chk(6,5)&&ref2==chk(6,0)){move(sa3);}
	if(ref1==chk(6,0)&&ref2==chk(6,4)){move(fb1); move(sb3); move(sb3);}
	//c4
	
	c1=chk(0,2);c2=chk(0,5);c3=chk(0,0);
	if( ref1 == c1 && ref2 == c3 ) { move(tb3); move(sb3); } 
	if( ref1 == c2 && ref2 == c1 ) { move(fb3); move(tb3); move(fa3); } 
	if( ref1 == c3 && ref2 == c2 ) { move(sb3); move(sb3); } 
	//corner 5
	c1 = chk(2,2);c2= chk(2,3);c3=chk(2,0);
	if( ref1 == c1 && ref2 == c2 ) { move(sb1); move(fa3); move(sa1); } 
	if( ref1 == c2 && ref2 == c3 ) { move(sb3); } 
	if( ref1 == c3 && ref2 == c1 ) { move(ta3); move(sb3); move(sb3); } 
	//corner 6
	c1 = chk(4,4);c2=chk(4,3);c3=chk(4,0);
	
	if( ref1 == c1 && ref2 == c3 ) { move(ta3); move(sb3); } 
	if( ref1 == c2 && ref2 == c1 ) { move(ta3); move(sb1); move(fa3); move(sa1); } 
	if( ref1 == c3 && ref2 == c2 ) { move(ta3); move(ta3); move(sb3); move(sb3); }
	//corner 7
	
	c1 = chk(20,1);c2=chk(20,3);c3=chk(20,2);
	if( ref1 == c2 && ref2 == c3 ) { move(sa3); move(ta3); move(sa3); move(sa3); } 
	if( ref1 == c3 && ref2 == c1 ) { move(sa3); move(ta3); move(fb3); move(tb3); move(fa3); } 
};

void CUBE_APP::corner2()
{
	int ref1,ref2,c1,c2,c3;
	ref1=chk(22,1);ref2=chk(22,4);	
	// corner 1
	
	c1 = chk(24,1);c2 = chk(24,5);  c3 = chk(24,4);
	
    if( ref1 == c2 && ref2 == c1 ) { move(fa1); move(tb3); move(sb1); move(ta3); move(sa1); } 
    if( ref1 == c3 && ref2 == c2 ) { move(fa1); move(tb3); move(fa1); move(fa1); } 
	// corner 2
	
	c1 = chk(18,1); c2 = chk(18,5); c3 = chk(18,2);
	
    if( ref1 == c1 && ref2 == c2 ) { move(sb3); move(ta3); move(sa3); move(fb1); } 
    if( ref1 == c2 && ref2 == c3 ) { move(fb1); move(ta3); move(fb1); } 
    if( ref1 == c3 && ref2 == c1 ) { move(fa1); } 
	// corner 3
	
	c1 = chk(6,4); c2 = chk(6,5);  c3 = chk(6,0);
	
    if( ref1 == c1 && ref2 == c3 ) { move(fb1); } 
    if( ref1 == c2 && ref2 == c1 ) { move(fb3); move(sa1); move(fa3); } 
    if( ref1 == c3 && ref2 == c2 ) { move(tb3); move(fa1); move(fa1); } 
	// corner 4
	
	c1=chk(0,2);c2=chk(0,5);c3=chk(0,0);
	
    if( ref1 == c1 && ref2 == c2 ) { move(sb1); move(ta3); move(sa1); } 
    if( ref1 == c2 && ref2 == c3 ) { move(ta3); move(fb1); } 
    if( ref1 == c3 && ref2 == c1 ) { move(fa1); move(fa1); } 
	// corner 5
	
	c1 = chk(4,4);c2=chk(4,3);c3=chk(4,0);
	
    if( ref1 == c1 && ref2 == c2 ) { move(tb3); move(fb3); move(sa1); move(fa3); } 
    if( ref1 == c2 && ref2 == c3 ) { move(tb3); move(fb1); } 
    if( ref1 == c3 && ref2 == c1 ) { move(tb3); move(tb3); move(fa1); move(fa1); } 
	// corner 6
	c1 = chk(2,2);c2= chk(2,3);c3=chk(2,0);
	
    if( ref1 == c1 && ref2 == c3 ) { move(ta3); move(ta3); move(fb1); } 
    if( ref1 == c2 && ref2 == c1 ) { move(sb1); move(ta3); move(ta3); move(sa1); } 
    if( ref1 == c3 && ref2 == c2 ) { move(ta3); move(fa1); move(fa1); } 
};

void CUBE_APP::corner3()
{
	
	int ref1,ref2,c1,c2,c3;
	ref1=chk(22,1);ref2=chk(24,5);	
	// corner 1
	
	c1 = chk(18,1); c2 = chk(18,5); c3 = chk(18,2);
	
    if( ref1 == c2 && ref2 == c3 ) { move(sb3); move(tb3); move(sa3); move(fb1); move(tb3); move(fa1); } 
    if( ref1 == c3 && ref2 == c1 ) { move(fb1); move(ta3); move(fa1); move(sb3); move(ta3); move(sa3); } 
	// corner 2
	
	c1 = chk(6,4); c2 = chk(6,5);  c3 = chk(6,0);
	
    if( ref1 == c1 && ref2 == c3 ) { move(sb3); move(tb3); move(sa3); } 
    if( ref1 == c2 && ref2 == c1 ) { move(tb3); move(sb3); move(ta3); move(sa3); } 
    if( ref1 == c3 && ref2 == c2 ) { move(sb3); move(ta3); move(ta3); move(sa3); move(sa3); move(fa1); move(sb3); move(fb1); } 
	// corner 3
	
	c1=chk(0,2);c2=chk(0,5);c3=chk(0,0);
	
    if( ref1 == c1 && ref2 == c2 ) { move(sb3); move(ta3); move(sa3); } 
    if( ref1 == c2 && ref2 == c3 ) { move(sa3); move(fa1); move(sb3); move(fb1); } 
    if( ref1 == c3 && ref2 == c1 ) { move(fb1); move(ta3); move(fa1); move(sb3); move(tb3); move(tb3); move(sa3); } 
	// corner 4
	
	c1 = chk(4,4);c2=chk(4,3);c3=chk(4,0);
	
    if( ref1 == c1 && ref2 == c2 ) { move(fb1); move(tb3); move(tb3); move(fa1); } 
    if( ref1 == c2 && ref2 == c3 ) { move(sb3); move(tb3); move(tb3); move(sa3); }
    if( ref1 == c3 && ref2 == c1 ) { move(sb3); move(ta3); move(sa3); move(fb1); move(tb3); move(fa1); } 
	// corner 5
	
	c1 = chk(2,2);c2= chk(2,3);c3=chk(2,0);
	
    if( ref1 == c1 && ref2 == c3 ) { move(ta3); move(fb1); move(tb3); move(fa1); } 
    if( ref1 == c2 && ref2 == c1 ) { move(fb1); move(ta3); move(fa1); } 
    if( ref1 == c3 && ref2 == c2 ) { move(fb1); move(tb3); move(tb3); move(fa1); move(sb3); move(ta3); move(sa3); } 
};

void CUBE_APP::topinsert()
{
	int ref1,ref2,c1,c2,c3;
	ref1=chk(22,1);ref2=chk(24,3);

	///Same place (cube 21) 1
	c1=chk(21,1);c2=chk(21,3);
	if(ref1==c2&&ref2==c1){move(sa2); move(tb3); move(tb3); move(sb2); 
	//insertion
	move(fa3); move(tb2); move(fb3);
	}
	//2
	c1=chk(19,1);c2=chk(19,2);
	if(ref1==c1&&ref2==c2){move(fb2);move(tb3);move(fa2);
	//insertion
	move(fa3); move(tb2); move(fb3);}
	if(ref1==c2&&ref2==c1){move(fb2);move(tb3);move(tb3);move(fa2);move(tb3);
	//insertion
	move(fa3); move(tb2); move(fb3);
	}

	///////3
	c1=chk(23,1);c2=chk(23,4);
	if(ref1==c1&&ref2==c2){move(fa2);move(ta3);move(fb2);
	//insertion
	move(fa3); move(tb2); move(fb3);}

	if(ref1==c2&&ref2==c1){move(fa2);move(tb3);move(tb3);move(fb2);move(ta3);
	//insertion
	move(fa3); move(tb2); move(fb3);
	}
	//////4
	c1=chk(25,1);c2=chk(25,5);
	if(ref1==c1&&ref2==c2){move(fa2);move(ta3);move(fb2);
	//insertion
	move(fa3); move(tb2); move(fb3);}
	if(ref1==c2&&ref2==c1){move(fa2);move(tb3);move(tb3);move(fb2);move(ta3);
	//insertion
	move(fa3); move(tb2); move(fb3);
	}



	///Bottom band 1
	c1=chk(3,3);c2=chk(3,0);
	if(ref1==c1&&ref2==c2){
		//insertion
		move(fa3); move(tb2); move(fb3);}
	if(ref1==c2&&ref2==c1){
		//insertion 2
		move(sa2); move(tb3); move(tb3);move(sb2);
	}	
	////2

	c1=chk(1,2);c2=chk(1,0);
	if(ref1==c1&&ref2==c2){
		move(tb3);
		//insertion
		move(fa3); move(tb2); move(fb3);}
	
	if(ref1==c2&&ref2==c1){move(tb3);
	//insertion 2
	move(sa2); move(tb3); move(tb3);move(sb2);
	}


	////3

	c1=chk(7,5);c2=chk(7,0);
	if(ref1==c1&&ref2==c2){move(tb3);move(tb3);
	//insertion
	move(fa3); move(tb2); move(fb3);};
	if(ref1==c2&&ref2==c1){move(tb3);move(tb3);
	//insertion 2
	move(sa2); move(tb3); move(tb3);move(sb2);
	}


///4
	c1=chk(5,4);c2=chk(5,0);
	if(ref1==c1&&ref2==c2){move(ta3);
	//insertion
	move(fa3); move(tb2); move(fb3);}
	if(ref1==c2&&ref2==c1){move(ta3);
	//insertion 2
	move(sa2); move(tb3); move(tb3);move(sb2);
	}

////Look at middle band;


	c1=chk(13,4);c2=chk(13,3);
	if(ref1==c1&&ref2==c2){move(tb2);
	//insertion
	move(fa3); move(ta2); move(fb3);}
	if(ref1==c2&&ref2==c1){move(tb2);
	//insertion 2
	move(fb3); move(ta2); move(ta2);move(fa3);
	}

	////2
	c1=chk(11,2);c2=chk(11,3);
	if(ref1==c1&&ref2==c2){move(ta2);
	//insertion
	move(fb3); move(tb2); move(fa3);}
	if(ref1==c2&&ref2==c1){move(ta2);
	//insertion 2
	move(fa3); move(ta2); move(ta2);move(fb3);
	}

//3
	c1=chk(15,5);c2=chk(15,4);
	if(ref1==c1&&ref2==c2){
	//insertion
	move(fa3); move(ta2); move(fb3);}
	if(ref1==c2&&ref2==c1){
	//insertion 2
	move(fb3); move(ta2); move(ta2);move(fa3);
	}

	////4
	c1=chk(9,5);c2=chk(9,2);
	if(ref1==c1&&ref2==c2){
	//insertion
	move(fb3); move(tb2); move(fa3);}
	if(ref1==c2&&ref2==c1){
	//insertion 2
	move(fa3); move(ta2); move(ta2);move(fb3);
	}



};


void CUBE_APP::move1(int flag=NO_REV)
{
	if(flag==NO_REV){
		move(sb3);move(ta3);move(sa3);move(tb3);
		//last part;
		move(sa3);move(fa1);move(sb3);move(fb1);
	};

	if(flag==REV){
	// Reverse last part;
		move(fa1);move(sa3);move(fb1);move(sb3);

		move(ta3);move(sb3);move(tb3);move(sa3);
	};
}


void CUBE_APP::move2(int flag=NO_REV)
{
	if(flag==NO_REV){
		move(sb3);move(ta3);move(ta3);move(sa3);move(tb3);move(tb3);
		//last part;
		move(sa3);move(fa1);move(sb3);move(fb1);
	};

	if(flag==REV){
	// Reverse last part;
		move(fa1);move(sa3);move(fb1);move(sb3);

		move(ta3);move(ta3);move(sb3);move(tb3);move(tb3);move(sa3);
	};

	if(flag==MIRROR){

		move(sb1);move(ta3);move(ta3);move(sa1);move(tb3);move(tb3);
		//last part;
		move(sa1);move(fb1);move(sb1);move(fa1);
	};
};

void CUBE_APP::move3(int flag=NO_REV)
{
	if(flag==NO_REV)
	{
		move(sb3); move(ta3); move(sa3); move(tb3); move(sa3); 
		move(fa1); move(sb3); move(fb1); move(sa1); move(ta3); 
		move(sb1); move(ta3); move(sa1); move(tb3); move(tb3); move(sb1);
	}
}





void CUBE_APP::move_Nammy(int flag=NO_REV)
{
	if(flag==NO_REV){
		//Nammy's move
		move(sb3);move(fb3);move(tb3);move(fa3);move(sa3);move(fb1);move(ta3);move(fa1);
	};

	if(flag==REV){
	// Reverse last part;
		move(fb1);move(tb3);move(fa1);move(sb3);move(fb3);move(ta3);move(fa3);move(sa3);
	};
};

void CUBE_APP::bottom_corner()
{
/////////////BUTTOMs
	char bottom,corner1,corner2,corner3,corner4;
	bottom=chk(8,0);
	///Checking postions
	if(chk(4,0)==bottom) corner1=1;
		else if(chk(4,4)==bottom) corner1=2;
			else corner1=3;
//
	if(chk(2,0)==bottom) corner2=1;
		else if(chk(2,3)==bottom) corner2=2;
			else corner2=3;
//
	if(chk(0,0)==bottom) corner3=1;
		else if(chk(0,2)==bottom) corner3=2;
			else corner3=3;
//
	if(chk(6,0)==bottom) corner4=1;
		else if(chk(6,5)==bottom) corner4=2;
			else corner4=3;

//Algorithm  Solving ;



	if((corner1+corner2+corner3+corner4)>4)
	{

		if(corner1*corner2*corner3*corner4==8)	//only one corner is  1 and other 2
		{
			//Taking reference corner as corner3
			if(corner1==1) {move(ta3);move(ta3);}
			if(corner2==1) {move(ta3);}
			if(corner4==1) {move(tb3);}
			move2();
		}
		if(corner1*corner2*corner3*corner4==27)	//1 and other 3 Ref corner is corner4
		{
			if(corner1==1) {move(tb3);}
			if(corner2==1) {move(ta3);move(ta3);}
			if(corner3==1) {move(ta3);}
			move2(REV);
		}
		// if no corner are 1
		if(corner1*corner2*corner3*corner4==36)
		{
		
			if(corner1==2&&corner2==3&&corner3==3&&corner4==2)
			{
				move3();
			}

			if(corner1==2&&corner2==2&&corner3==3&&corner4==3)
			{
				move(tb3);
				move3();
			}
			//////////
			if(corner1==3&&corner2==2&&corner3==2&&corner4==3)
			{
				move(tb3);move(tb3);
				move3();

			}
			if(corner1==3&&corner2==3&&corner3==2&&corner4==2)
			{
				move(ta3);
				move3();

			}
			///////////


			if(corner1==corner3&&corner2==corner4)
			{
				if(corner1==2&&corner2==3) move(tb3); 
				
				move(sb3); move(sb3); move(tb3); move(tb3); move(sb3);
				move(tb3); move(tb3); move(sb3); move(sb3);
			}
		
		}		
		//e.g. 1123 or 1213 only two corner is 1

		if(corner1*corner2*corner3*corner4==6)	
		{
			
			//ref corner is 4 Nammy's move
			if(corner1==corner2) 
			{
				
				if(corner3==3&&corner4==2)
				{
					move(tb3);move_Nammy();
				}else 
				{
					move(ta3);move1();
				}
			}

			if(corner2==corner3) 
			{
				
				if(corner4==3&&corner1==2)
				{
					move_Nammy(REV);
				}else 
				{
					move1();
				}
			}

			if(corner3==corner4) 
			{
				
				if(corner1==3&&corner2==2)
				{
					move(ta3);move_Nammy();
				}else 
				{
					move(tb3);move1();
				}
			}
			///
			if(corner4==corner1) 
			{
				
				if(corner2==3&&corner3==2)
				{
					move_Nammy();
				}else 
				{
					move(ta3);move(ta3);move1();
				}
			}
			///////if like 1213  
			if(corner1==corner3) 
			{
				
				if(corner2==3&&corner4==2)
				{
					move1(REV);
				}else 
				{
					move(ta3);move(ta3);move1(REV);
				}

			}
			/////////
			if(corner2==corner4) 
			{

				if(corner3==3&&corner1==2)
				{
					move(tb3);move1(REV);
				}else 
				{
					move(ta3);move1(REV);
				}

			}
		}//End of 1123 or 1213 only two corner is 1
	}//End of 1111;

	/////Sorting side
	//Redefining corners with colors
	if(chk(4,3)!=chk(2,3)||chk(2,2)!=chk(0,2)||chk(0,5)!=chk(6,5)||chk(6,4)!=chk(4,4))
	{
		if(chk(4,3)==chk(2,3)){move(tb3);}
		else if(chk(2,2)==chk(0,2)){move(tb3);move(tb3);}
		else if(chk(0,5)==chk(6,5)){move(ta3);}
	
		if(chk(6,4)==chk(4,4))
		{
			move2();
			move2(MIRROR);
		}else 
		{
			move2();
			move2(MIRROR);
			bottom_corner();
		};
	}


}

void CUBE_APP::bottom_insert()
{
	int ref1,ref2,c1,c2;
	ref1=chk(2,0);ref2=chk(2,2);

	c1=chk(19,2);c2=chk(19,1);
	if(ref1==c1&&ref2==c2)
	{
		//insertion 1
		move(sb3);move(tb2);move(sa3);
	}
	if(ref1==c2&&ref2==c1)
	{
		//insertion 2
		move(sb3);move(ta2);move(sa3);move(sa3);move(tb2);move(sb3);
	}

//It self
	c1=chk(1,0);c2=chk(1,2);
	if(ref1==c2&&ref2==c1)
	{
		//insertion 2
		move(sb3);move(tb2);move(sa3);move(sa3);move(ta2);move(ta2);move(sb3);
	}
///////////////////

	c1=chk(15,4);c2=chk(15,5);
	if(ref1==c1&&ref2==c2)
	{
		//insertion 1
		move(sa3);move(tb2);move(sb3);
	}

	if(ref1==c2&&ref2==c1)
	{
		//insertion 2
		move(sb3);move(tb2);move(tb2);move(sa3);
	}

	c1=chk(9,5);c2=chk(9,2);
	if(ref1==c1&&ref2==c2)
	{
		//insertion 1
		move(ta2);move(sa3);move(tb2);move(sb3);
	}

	if(ref1==c2&&ref2==c1)
	{
		//insertion 2
		move(ta2);move(sb3);move(tb2);move(tb2);move(sa3);
	}

///////////////////
	c1=chk(13,4);c2=chk(13,3);
	if(ref1==c1&&ref2==c2)
	{
		//insertion 1
		move(sb3);move(ta2);move(sa3);
	}

	if(ref1==c2&&ref2==c1)
	{
		//insertion 2
		move(sa3);move(tb2);move(tb2);move(sb3);
	}

	c1=chk(11,3);c2=chk(11,2);
	if(ref1==c1&&ref2==c2)
	{
		//insertion 1
		move(tb2);move(sb3);move(ta2);move(sa3);
	}

	if(ref1==c2&&ref2==c1)
	{
		//insertion 2
		move(tb2);move(sa3);move(tb2);move(tb2);move(sb3);
	}
//////////////////////BOTTom check
	c1=chk(7,0);c2=chk(7,5);
	if(ref1==c1&&ref2==c2)
	{
		//take out
		move(tb3);move(sa3);move(ta2);move(sb3);move(ta3);
		//insertion 1
		move(sa3);move(tb2);move(sb3);
	}

	if(ref1==c2&&ref2==c1)
	{
		//take out
		move(tb3);move(sa3);move(ta2);move(sb3);move(ta3);		
		//insertion 2
		move(sb3);move(tb2);move(tb2);move(sa3);
	}

	c1=chk(5,0);c2=chk(5,4);
	if(ref1==c1&&ref2==c2)
	{
		//take out
		move(tb3);move(tb3);move(sa3);move(ta2);move(sb3);move(ta3);move(ta3);
		//insertion 1
		move(sa3);move(tb2);move(sb3);
	}

	if(ref1==c2&&ref2==c1)
	{
		//take out
		move(tb3);move(tb3);move(sa3);move(ta2);move(sb3);move(ta3);move(ta3);		
		//insertion 2
		move(sb3);move(tb2);move(tb2);move(sa3);
	}


	c1=chk(3,0);c2=chk(3,3);
	if(ref1==c1&&ref2==c2)
	{
		//take out
		move(ta3);move(sa3);move(ta2);move(sb3);move(tb3);
		//insertion 1
		move(sa3);move(tb2);move(sb3);
	}

	if(ref1==c2&&ref2==c1)
	{
		//take out
		move(ta3);move(sa3);move(ta2);move(sb3);move(tb3);		
		//insertion 2
		move(sb3);move(tb2);move(tb2);move(sa3);
	}
	/////////Finished inserting
}

void CUBE_APP::bottom_last()
{
	int ref1,ref2,c1,c2;
	ref1=chk(20,1);ref2=chk(20,2);

	c1=chk(19,1);c2=chk(19,2);
	if(ref1!=c1||ref2!=c2)
	{
		if(ref1==c2&&ref2==c1)
		{
			move(sb3);move(ta2);move(sa3);move(ta2);move(sa3);move(ta2);move(sb3);
		}

		c1=chk(15,4);c2=chk(15,5);
		if(ref1==c1&&ref2==c2)
		{
			move(sb3);move(ta2);move(sa3);
			move(tb2);move(sb3);move(tb2);move(sa3);
		}
		if(ref1==c2&&ref2==c1)
		{
			move(sb3);move(ta2);move(sa3);
			move(sa3);move(ta2);move(sb3);
		}

		c1=chk(9,5);c2=chk(9,2);
		if(ref1==c1&&ref2==c2)
		{
			move(ta2);move(sb3);move(ta2);move(sa3);
			move(tb2);move(sb3);move(tb2);move(sa3);
		}
		if(ref1==c2&&ref2==c1)
		{
			move(ta2);move(sb3);move(ta2);move(sa3);
			move(sa3);move(ta2);move(sb3);
		}
		///////////
		c1=chk(13,4);c2=chk(13,3);
		if(ref1==c1&&ref2==c2)
		{
			move(sa3);move(tb2);move(sb3);
			move(ta2);move(sa3);move(ta2);move(sb3);
		}
		if(ref1==c2&&ref2==c1)
		{
			move(sa3);move(tb2);move(sb3);
			move(sb3);move(tb2);move(sa3);
		}

		c1=chk(11,3);c2=chk(11,2);
		if(ref1==c1&&ref2==c2)
		{
			move(tb2);move(sa3);move(tb2);move(sb3);
			move(ta2);move(sa3);move(ta2);move(sb3);
		}
		if(ref1==c2&&ref2==c1)
		{
			move(tb2);move(sa3);move(tb2);move(sb3);
			move(sb3);move(tb2);move(sa3);
		}
	}
	//Last twist for bottom band
	ref1=chk(0,2);
	if(ref1==chk(20,3)) {move(tb3);}
	else if(ref1==chk(22,4)) {move(tb3);move(tb3);}
	else if(ref1==chk(24,5)) {move(ta3);}
}
void CUBE_APP::pushit(int flag=2)
{
	if(flag==2)
	{move(fa1);move(fa1);move(tb2);move(fa1);move(fa1);move(ta2);}
	if(flag==1)
	{move(sa3);move(sa3);move(tb2);move(sa3);move(sa3);move(ta2);}
	if(flag==3)
	{move(sa1);move(sa1);move(tb2);move(sa1);move(sa1);move(ta2);}
	if(flag==4)
	{move(fa3);move(fa3);move(tb2);move(fa3);move(fa3);move(ta2);}
	if(flag==MIRROR)
	{move(fa1);move(fa1);move(ta2);move(fa1);move(fa1);move(tb2);}
	
}
void CUBE_APP::pullit(int flag=NO_REV)
{
	if(flag==NO_REV)
	{
		move(fa1);move(fa1);
		move(sa3);move(tb2);move(sb3);
		move(fa1);move(fa1);
		move(sa3);move(ta2);move(sb3);
	}
	if(flag==MIRROR)
	{
		move(sa1);move(sa1);
		move(fa3);move(ta2);move(fb3);
		move(sa1);move(sa1);
		move(fa3);move(tb2);move(fb3);
	}
}

void CUBE_APP::lastMove()
{
	char ref1,ref2,c1,cor1,cor2,cor3,cor4;
	ref1=chk(12,3);ref2=chk(16,5);

	if(chk(13,3)==ref1||chk(13,3)==ref2) cor1=0;else cor1=1;
	if(chk(11,3)==ref1||chk(11,3)==ref2) cor2=0;else cor2=1;
	if(chk(9,5)==ref1||chk(9,5)==ref2) cor3=0;else cor3=1;
	if(chk(15,5)==ref1||chk(15,5)==ref2) cor4=0;else cor4=1;

	if(cor1==1&&cor2==0&&cor3==0&&cor4==1)
	{
		move(fa1); move(fa1); move(sa3); move(tb2); move(sb3);
		move(fa1); move(fa1); move(sa3); move(ta2); move(sb3);
		
	}
	if(cor1==1&&cor2==1&&cor3==0&&cor4==0)
	{
		move(tb2); move(fa1); move(fa1); move(sa3); move(tb2); move(sb3);
		move(fa1); move(fa1); move(sa3); move(ta2); move(sb3);
	}
//////
	if(cor1==0&&cor2==1&&cor3==1&&cor4==0)
	{
		move(tb2); move(tb2); move(fa1); move(fa1); move(sa3); move(tb2);
		move(sb3); move(fa1); move(fa1); move(sa3); move(ta2); move(sb3);
	}
	if(cor1==0&&cor2==0&&cor3==1&&cor4==1)
	{
		move(ta2); move(fa1); move(fa1); move(sa3); move(tb2); move(sb3);
		move(fa1); move(fa1); move(sa3); move(ta2); move(sb3);
	}
////
	if(cor1==1&&cor2==0&&cor3==1&&cor4==0)
	{
		move(sa3); move(tb2); move(sb3); move(fa1); move(fa1); move(sa3);
		move(ta2); move(sb3); move(fa1); move(fa1);
	}
	if(cor1==0&&cor2==1&&cor3==0&&cor4==1)
	{
		move(ta2); move(sa3); move(tb2); move(sb3); move(fa1); move(fa1);
		move(sa3); move(ta2); move(sb3); move(fa1); move(fa1);
	}
	if(cor1==1&&cor2==1&&cor3==1&&cor4==1)
	{
		move(ta2); move(sa3); move(tb2); move(sb3); move(fa1); move(fa1);
		move(sa3); move(ta2); move(sb3); move(fa1); move(fa1);
	}
	
	/////////Put right
	ref1=chk(16,5);ref2=chk(10,2);
	if(chk(15,5)==ref1&&chk(15,4)==ref2)
	{
		move(sb3); move(sb3); move(tb2); move(sb3); move(sb3); move(ta2);
	}
	if(chk(13,3)==ref1&&chk(13,4)==ref2)
	{
		move(sb1); move(sb1); move(ta2); move(sb1); move(sb1); move(tb2);
	}
	if(chk(11,3)==ref1&&chk(11,2)==ref2)
	{
		move(sb3); move(sb3); move(ta2); move(sb3); move(sb3); move(tb2);
	}
	/////////
	ref2=chk(14,4);
	if(chk(13,3)==ref1&&chk(13,4)==ref2)
	{
		move(sb1); move(sb1); move(tb2); move(sb1); move(sb1); move(ta2);
	}
	if(chk(11,3)==ref1&&chk(11,2)==ref2)
	{
		move(fa3); move(fa3); move(ta2); move(fa3); move(fa3); move(tb2);
	}

	if(solve_check())
	{

	//Last twist for middle band
	ref1=chk(10,2);
	if(ref1==chk(20,3)) {move(tb2);}
	else if(ref1==chk(22,4)) {move(tb2);move(tb2);}
	else if(ref1==chk(24,5)) {move(ta2);}
	} else lastMove();

};


int CUBE_APP::solve_check()

{
	//Middle band chk
	int ref;
	ref=chk(16,5);
	if(ref==chk(15,5)&&ref==chk(9,5)&&chk(10,2)==chk(9,2)&&chk(10,2)==chk(11,2)&&chk(12,3)==chk(11,3)&&chk(12,3)==chk(13,3))
	{return 1;}
	else return 0;
}


void CUBE_APP::solveIt(int d)
{
	delay=d;
	setRot(1);
	count=0;


	char comment[60];

	solve_running=1;

	//Linear Solution
	corner1();
	if(solve_running) corner2();
	if(solve_running) corner3();

	if(solve_running) 	topinsert();//1
	if(chk(19,1)!=chk(20,1)||chk(19,2)!=chk(20,2))
	{	move(tb1);
		topinsert();//2
		if(chk(19,1)!=chk(20,1)||chk(19,2)!=chk(20,2))
		{
			move(tb1);
			topinsert();
			if(chk(19,1)!=chk(20,1)||chk(19,2)!=chk(20,2))
				{
					move(tb1);
					topinsert();
			}
		}else //for cube 19 wrong,25 correct and 23 wrong
		if(chk(25,1)!=chk(24,1)||chk(25,5)!=chk(24,5))
		{
			move(tb1);move(tb1);
			topinsert();
		}

	}else
	if(chk(23,1)!=chk(22,1)||chk(23,4)!=chk(22,4))
	{
		move(ta1);
		topinsert();
		if(chk(23,1)!=chk(22,1)||chk(23,4)!=chk(22,4))
		{
			move(ta1);
			topinsert();
		}
	}else
	if(chk(25,1)!=chk(24,1)||chk(25,5)!=chk(24,5))
	{
		move(ta1);move(ta1);
		topinsert();
	}


	if(solve_running) bottom_corner();
	if(chk(3,3)!=chk(2,3)||chk(1,2)!=chk(0,2)||chk(7,5)!=chk(6,5)||chk(5,4)!=chk(4,4)&&solve_running)
	{
		bottom_insert();
		move(tb3);
		bottom_insert();
		move(tb3);
		bottom_insert();
		move(tb3);
		bottom_insert();
	}

	if(solve_running) bottom_last();
	if(count&&solve_running) Common->evoke("The LAST PART of The Solution.","Info",ALERT);
	if(solve_running) lastMove();

	if(solve_running) 


	//

	if(solve_running&&count)
	{
		sprintf(comment,"SOLVED -> Every problem has its solution.:-)  %d Moves",count);
		st.setDisp(comment);
		Common->evoke("Every problem has its solution. ","Solved",MSG);
	}else 
		if(count) {st.setDisp("Unbalenced Equation was detected by AI");}else
			st.setDisp("Already Solved.");

	solve.setState(0);
	while(!kbhit()&&!getmouse()&&solve_running){
		if((arot+cuberot)!=0)animate();
	};
	while(kbhit()){ getch();}
	setRot(0);
	solve_running=0;	
};
void CUBE_APP::CUBE_APP():solve(ORIGIN,560,295,60,30,ID_SOLVE," SOLVE ","Don't you believe this?, Try a click",YELLOW,RED)
{
	
	a=1;key=56;speed=12;arot=1;cuberot=0;running=0;delay=0;count=0;step=0;GlobalMsg='a';
	rx=1,ry=1,rz=1;

	top[3]=new Button(ORIGIN,MOVEX+3,MOVEY+CHAR_H,BUT_W,BUT_H,500,"TOP1 <-","Top Left <-",BUT_TXTCOL,BUT_FILLCOL);
	top[4]=new Button(top[3],0,BUT_H+BUT_DS,BUT_W,BUT_H,501,"TOP2 <-","Middle Left <-",BUT_TXTCOL,BUT_FILLCOL);
	top[5]=new Button(top[4],0,BUT_H+BUT_DS,BUT_W,BUT_H,502,"TOP3 <-","Bottom Left <-",BUT_TXTCOL,BUT_FILLCOL);

	top[0]=new Button(top[3],BUT_W+BUT_DS,0,BUT_W,BUT_H,504,"TOP1 ->","Top Right ->",BUT_TXTCOL,BUT_FILLCOL);
	top[1]=new Button(top[4],BUT_W+BUT_DS,0,BUT_W,BUT_H,505,"TOP2 ->","Middle Right ->",BUT_TXTCOL,BUT_FILLCOL);
	top[2]=new Button(top[5],BUT_W+BUT_DS,0,BUT_W,BUT_H,506,"TOP3 ->","Bottom Right ->",BUT_TXTCOL,BUT_FILLCOL);

	front[3]=new Button(top[0],BUT_W+BUT_DL,0,BUT_W,BUT_H,507,"FRNT1 ('","Front Clockwise ('",BUT_TXTCOL,BUT_FILLCOL);
	front[4]=new Button(front[3],0,BUT_H+BUT_DS,BUT_W,BUT_H,508,"FRNT2 ('","Middle Clockwise ('",BUT_TXTCOL,BUT_FILLCOL);
	front[5]=new Button(front[4],0,BUT_H+BUT_DS,BUT_W,BUT_H,509,"FRNT3 ('","Back Clockwise ('",BUT_TXTCOL,BUT_FILLCOL);

	front[0]=new Button(front[3],BUT_W+BUT_DS,0,BUT_W,BUT_H,510,"FRNT1 ')","Front ani-Clockwise ')",BUT_TXTCOL,BUT_FILLCOL);
	front[1]=new Button(front[4],BUT_W+BUT_DS,0,BUT_W,BUT_H,511,"FRNT2 ')","Midle ani-Clockwise ')",BUT_TXTCOL,BUT_FILLCOL);
	front[2]=new Button(front[5],BUT_W+BUT_DS,0,BUT_W,BUT_H,512,"FRNT3 ')","Front ani-Clockwise ')",BUT_TXTCOL,BUT_FILLCOL);


	side[5]=new Button(front[0],BUT_W+BUT_DL,0,BUT_W,BUT_H,515,"SIDE1 /\\","Side-left Up",BUT_TXTCOL,BUT_FILLCOL);
	side[4]=new Button(side[5],BUT_W+BUT_DS,0,BUT_W,BUT_H,514,"SIDE2 /\\","Side-middle Up",BUT_TXTCOL,BUT_FILLCOL);
	side[3]=new Button(side[4],BUT_W+BUT_DS,0,BUT_W,BUT_H,513,"SIDE3 /\\","Side-right Up",BUT_TXTCOL,BUT_FILLCOL);

	side[0]=new Button(side[3],0,BUT_H+BUT_DS,BUT_W,BUT_H,516,"SIDE3 \\/","Side-right Down",BUT_TXTCOL,BUT_FILLCOL);
	side[1]=new Button(side[4],0,BUT_H+BUT_DS,BUT_W,BUT_H,517,"SIDE2 \\/","Side-middle Down",BUT_TXTCOL,BUT_FILLCOL);
	side[2]=new Button(side[5],0,BUT_H+BUT_DS,BUT_W,BUT_H,518,"SIDE1 \\/","Side-left Down",BUT_TXTCOL,BUT_FILLCOL);


	random=new Button(top[3],0,CHAR_H*3+BUT_DL,BUT_W+10,BUT_H+10,ID_RANDOM,"NEW GAME","New game.-> Radomize.        ->  F2 or Ctrl+F2",WHITE,BLUE);
	save=new Button(random,190,0,BUT_W+10,BUT_H+10,ID_SAVE," SAVE  ","Save current state. || F5",LIGHTCYAN,BLUE);
	restore=new Button(save,BUT_W+BUT_DL,0,BUT_W+10,BUT_H+10,ID_RESTORE,"RESTORE","Restore last saved state.       ->  F9",LIGHTCYAN,BLUE);

	reset=new stkyButton(restore,BUT_W+50,0,BUT_W+10,BUT_H+10,ID_RESET,"  RESET  ","Reset Cube       ->  SPACE BAR",YELLOW,BLUE);

	rot_but=new stkyButton(ORIGIN,500,110,BUT_W,BUT_H,ID_ROT_BUT,"  Rotation  ","Axis rotaion toggle        ->   R");

	rxx=new stkyButton((Box*)rot_but,-5,BUT_H+10,18,12,ID_ROT_BUT,"x","X rotaion toggle");
	ryy=new stkyButton((Box*)rxx,30,0,18,12,ID_ROT_BUT,"y","Y rotaion toggle");
	rzz=new stkyButton((Box*)ryy,30,0,18,12,ID_ROT_BUT,"z","Z rotaion toggle");

	
	speed_up=new Button((Box*)rot_but,0,2*BUT_H+20,70,BUT_H,ID_SP1," Speed up ","Increase speed of rotaion        ->  UP");
	speed_dwn=new Button((Box*)speed_up,0,18,70,BUT_H,ID_SP2," Speed Down ","Decrease speed of rotaion        ->  DOWN");

	index_up=new Button((Box*)speed_dwn,0,BUT_H+BUT_DL,70,BUT_H,ID_INDEX1,"Index up","Increase Perspective Index        ->  RIGHT");
	index_dwn=new Button((Box*)index_up,0,18,70,BUT_H,ID_INDEX1,"Index down","Decrease Perspective Index        ->   LEFT");

	scale_up=new Button((Box*)index_dwn,0,BUT_H+BUT_DL,18,BUT_H,ID_SCALE1,"+","Increase Scale        ->   +");
	scale_dwn=new Button((Box*)scale_up,BUT_W-2,0,18,BUT_H,ID_SCALE1,"-","Decrease Scale        ->   -");

	inc_delay=new Button((Box*)&solve,-95,15,20,12,111," + ","Increase delay between moves during solution.",RED);
	dec_delay=new Button((Box*)inc_delay,25,0,20,12,112," - ","Decrease delay between moves during solution.",RED);
	steped=new stkyButton((Box*)&solve,-45,3,40,25,ID_STEPED,"STEPS","Step wise solution ON/OFF .  Best way to track the moves",RED);


	
	
};
void CUBE_APP::trace(int ix,int iy,float *v){
	viewporttype cur;
	getviewsettings(&cur);
	rectangle(ix-1,iy-1,ix+81,iy+31);
	setviewport(ix,iy,ix+80,iy+30,1);
	clearviewport();
	sprintf(CUBE_APPbuffer," %.4f ",*v);
	outtextxy(5,10,CUBE_APPbuffer);
	setviewport(cur.left,cur.top,cur.right,cur.bottom,cur.clip);
	
};
void CUBE_APP::trace(int ix,int iy,char v[]){
	viewporttype cur;
	getviewsettings(&cur);
	setviewport(ix,iy,ix+500,iy+12,1);
	clearviewport();
	//setlinestyle(1,1,1);
	rectangle(0,0,500,12);
	outtextxy(5,6,v);
	setviewport(cur.left,cur.top,cur.right,cur.bottom,cur.clip);
	
};
void CUBE_APP::trace(char v[]){
//	setactivepage(1);
//	trace(5,335,v);
//	setactivepage(0);
//	trace(5,335,v);
	
};

void CUBE_APP::intro(){
	midx=getmaxx()/2;
	midy=getmaxy()/2;
	maxcol=getmaxcolor();	
	setcolor(YELLOW);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 6);
	settextjustify(1,1);
	outtextxy(midx,midy-120,"3D CUBE 1.0");
	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	setcolor(BLUE);
	outtextxy(midx,midy-70,"Trillions of Problems Single Solution.");
//	outtextxy(midx,midy-40,"This Programme is Heavily UNDERCONSTRUCTION.....");
//	outtextxy(midx,midy-20,"2004  2nd March");
	outtextxy(midx,midy-20,"2004  29th March");
	settextjustify(0,1);
	
	setcolor(INTROTEXT);
	

	outtextxy(midx-80,midy+15+30,"1. UP and DOWN keys for speed");
	outtextxy(midx-80,midy+15+50,"2.<- & -> for PerspectiveIndex(My Terminology :-) )");
	outtextxy(midx-80,midy+15+70,"3. + & - for Zoooooming");
	outtextxy(midx-80,midy+15+90,"4.'r' for Axis rotation toggle");
	outtextxy(midx-80,midy+15+110,"5.SPACE for Reset");
	outtextxy(midx-80,midy+15+130,"6.'p' for pause and Esc for exit");	
	outtextxy(90,midy*2-15,"And Use ur mouse, as u do in AutoCAD or 3DsMax.");
	setcolor(LIGHTBLUE);
	outtextxy(midx*2-160,midy*2-15,"dhilung@hotmail.com");
	setlinestyle(1,1,4);
	///////MS enviroment
	
	
	
};

void CUBE_APP::ini(){
	


	settextstyle(DEFAULT_FONT,HORIZ_DIR,0);

	//Class scope
	Common=new MessageBox(MainWin);
	MainWin=new Window(ORIGIN,0,0,midx*2,midy*2,"3D CUBE");
	close=new Button(MainWin,midx*2-20,2,16,11,EXIT,"X","Exit ||  'Alt+F4'");
	
	//Just Draw 560,290
	
	Box viewport(ORIGIN,4,19,VP_WIDTH+7,VP_HEIGHT-8,DARKGRAY,LIGHT);
	NamedBox sol((Box* )&solve,-100,-10,165,45,"Solve",WHITE,BLUE);
	NamedBox moves(ORIGIN,MOVEX,VP_HEIGHT+21,VP_WIDTH+6,CHAR_H*3+6,"Moves ",WHITE,WHITE,SMALL_FONT,4);
	NamedBox play(&moves,0,CHAR_H*3+13,VP_WIDTH+6,CHAR_H+10+3,"Play ",WHITE,WHITE,SMALL_FONT,4);

	//Mainwin must be top
	MainWin->display();

	settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	DisplayLogo();
	close->display();
	viewport.display();
	moves.display();
	play.display();

	NamedBox n((Box*) rot_but,-30,-13,130,180,"Control Panel",WHITE,DARK,SMALL_FONT,5);
	n.display();


	NamedBox n1((Box*) speed_up,-15,-5,100,40,"Speed",BLACK,BLACK,SMALL_FONT,4);
	n1.display();
	speed_up->display();
	speed_dwn->display();


	NamedBox n2((Box*) index_up,-15,-5,100,40,"Perspective",BLACK,BLACK,SMALL_FONT,4);
	n2.display();
	index_up->display();
	index_dwn->display();

	NamedBox n3((Box*) scale_up,-15,-5,100,22,"Scale",BLACK,BLACK,SMALL_FONT,4);
	n3.display();
	scale_up->display();
	scale_dwn->display();

	rxx->display();ryy->display();rzz->display();




	rot_but->display();

				sprintf(CUBE_APPbuffer,"%d",delay);
				TextBox temp((Box*)inc_delay,10,-15,20,12,CUBE_APPbuffer);
				temp.display();

	temp.display();
	inc_delay->display();
	dec_delay->display();
	steped->display();
	sol.display();

	settextstyle(SMALL_FONT, HORIZ_DIR, 4);		
	


	top[3]->display();top[0]->display();
	top[4]->display();top[1]->display();
	top[5]->display();top[2]->display();

	front[3]->display();front[0]->display();
	front[4]->display();front[1]->display();
	front[5]->display();front[2]->display();

	side[3]->display();side[0]->display();
	side[4]->display();side[1]->display();
	side[5]->display();side[2]->display();

	random->display();
	save->display();
	restore->display();
	reset->display();
	// using . operator  copy constructor
	solve.display();

	st.setDisp("     3D CUBE Reloaded");
	
	showmouse();

	setRot(1);setRot(X_ROT);setRot(Y_ROT);setRot(Z_ROT);
	bc.inibcube();
//	bc.rotAxis(0,45,0);
	back=bc;
	//restore_cube=bc;


	settextstyle(SMALL_FONT, HORIZ_DIR, 4);		
	
};
void CUBE_APP::DispatchMsg(int msg_flag)
{
	switch(msg_flag)
	{
	case DEFAULT:
		break;
	case SPEED_UP:
		if(speed<40)speed+=0.2;
		else speed=40;
		sprintf(buff,"SPEED   %.2f",speed);st.setDisp(buff);break;
	case SPEED_DWN:
		if(speed>0.4)speed-=0.2;
		else speed=.2;
		sprintf(buff,"SPEED   %.2f",speed);st.setDisp(buff);break;
	case PER_INDEX_UP:
			if(perIndex<2000)perIndex+=(perIndex/100);
			else perIndex=2000;
			sprintf(buff,"Perspective Index   %.2f",perIndex);st.setDisp(buff);break;
	case PER_INDEX_DWN:
			if(perIndex>20)perIndex-=(perIndex/50);
			else perIndex=20;
			sprintf(buff,"Perspective Index   %.2f",perIndex);st.setDisp(buff);break;

	case START:
			if(Common->evoke("New Game?","New Game",OPTION)==1)
			{
				for(i=0;i<RAND;i++){
					int r=(int)rand()%19;
					bc.faceRot(90,r);
					bc.swapit(&r);
					animate();
				}
			};
			sprintf(buff,"New Game");st.setDisp(buff);break;
	case START_NO:		//Ctr+F2
			bc.inibcube();
			for(i=0;i<RAND;i++){
				int r=(int)rand()%19;
				bc.faceRot(90,r);
				bc.swapit(&r);
				animate();
			}
			sprintf(buff,"New Game");st.setDisp(buff);break;
	case EXIT:	//Alt+F4
			key=27;
			break;
	case SHOW_NUM:
			if(shownum) shownum=0;
			else shownum=1;break;
	case SET_ROT:
			setRot();
			break;
	case SCALE_UP:
			if(scale<10) scale*=1.03;
			else scale=10;
			sprintf(buff,"SCALE   %.2f",scale*100);st.setDisp(buff);break;
	case SCALE_DWN:
			if(scale>.01) scale/=1.03;
			else scale=.01;
			sprintf(buff,"SCALE   %.2f",scale*100);st.setDisp(buff);break;
	case RXX:
		setRot(X_ROT);break;
	case RYY:
		setRot(Y_ROT);break;
	case RZZ:
		setRot(Z_ROT);break;
	case PAUSE:
			animate();
			st.setDisp("GAME Paused   .... Press any key to continue...");
			waitKey();
			st.setDisp(STRING4);
		//	Common->evoke("Game Paused","Pause",MSG);
			animate();
			break;
	case RESET:
			if(Common->evoke("Reset Every thing?","Reset",OPTION_ALERT))
			{scale=1;speed=12;shownum=0;perIndex=500;
			setRot(0);
			//bc=restore_cube;
			bc.inibcube();
			bc.rotAxis(30,-45,20);
			animate();
			sprintf(buff,"RESET");
			st.setDisp(buff);
			};break;

	case RESTORE:
		if(Common->evoke("Restore last-save?","Restore",OPTION_ALERT))
		{bc=back;animate();}
		sprintf(buff,"Restored");break;



	case DELAY_UP:
			if(delay<40)delay++;
			else delay=40;
			sprintf(CUBE_APPbuffer,"%d",delay);
			trace((Box*)inc_delay,10,-15,20,12,CUBE_APPbuffer);
			sprintf(buff,"Delay %d",delay);st.setDisp(buff);break;
	case DELAY_DWN:
			if(delay>0)delay--;
			else delay=0;
			sprintf(CUBE_APPbuffer,"%d",delay);
			trace((Box*)inc_delay,10,-15,20,12,CUBE_APPbuffer);
			sprintf(buff,"Delay %d",delay);st.setDisp(buff);break;
	case TOG_STEP:
		if(step) {step=0;st.setDisp("Step-wise OFF");}
		else {step=1;st.setDisp("Step-wise ON");}
		break;

	case SAVE:
		back=bc;break;

	case SOLVE:
		//////////////////// GREAT RECURTION //////////
		if(Common->evoke("One from trillions --> Solve?","Solve",OPTION)){
			st.setDisp("The Next version.--> a piece of Artificial Intelligence (AI)               Press solve button angain to stop.");
			solveIt(delay);
			}else solve.setState(0);break;
									
	case MOVE:
		findOrientation();
		TransMsgRotation();break;
	case CREDIT:
		credit();
		break;
	case NAVIGATE:
		_x=gmouse_x;_y=gmouse_y;
		int dx,dy,dz;
		hidemouse();
		if(gmouse_b==1)	//left button
        {
			float rr=(float)(gmouse_x-(VP_WIDTH/2))*(gmouse_x-(VP_WIDTH/2))+(float)(gmouse_y-(VP_HEIGHT/2))*(gmouse_y-(VP_HEIGHT/2));
			if(rr>13000){
				short int pos;
				
				if(gmouse_x>VP_WIDTH/2+20)pos=-1;
				else pos=1;
				while(getmouse()){
					dz=gmouse_y-_y;
					setmouse(_x,_y);
				//	_y=gmouse_y;
					bc.rotAxis(0,0,pos*dz);
					animate();
					st.setDisp("Drag mouse to rotate global Z-axis.");
				};
			}else
			{
				while(getmouse()){
					
					dx=gmouse_x-_x;
					dy=gmouse_y-_y;
					setmouse(_x,_y);
				//	_x=gmouse_x;
				//	_y=gmouse_y;
					bc.rotAxis(dy,-dx,0);
					animate();
					st.setDisp("Drag mouse to change global axis.");
				};
				
			}
		}else
		if(gmouse_b==2)	//Right mouse
		{
			
		//	float dr;	
			while(getmouse()){
					dz=gmouse_y-_y;
				//	_y=gmouse_y;
					setmouse(_x,_y);
				if(scale<=10&&scale>=0.01) scale+=(scale*.006*dz);
				if(scale>=10) scale=10;
				if(scale<=0.01) scale=0.01;
				sprintf(buff,"SCALE   %.2f",scale*100);st.setDisp(buff);
				animate();
				
				};
		}else
		if(gmouse_b==4)	//Middl3 mouse
		{
			
		//	float dr;	
			while(getmouse()){
					dz=gmouse_y-_y;
				//	_y=gmouse_y;
					setmouse(_x,_y);
				if(perIndex<=2000&&perIndex>=20) perIndex+=(perIndex*.001*dz);
				if(perIndex>=2000) perIndex=2000;
				if(perIndex<=20) perIndex=20;
				sprintf(buff,"Perspective Index   %.2f",perIndex);st.setDisp(buff);
				animate();
				};
		};

		showmouse();
		if(!gmouse_b)st.setDisp(STRING5);
		break;


	};	//End switch
	//lastover=ID_DISPATCH;
	
}

void CUBE_APP::KeyMsg(){
	sprintf(buff,"Ready ");
	GlobalMsg=DEFAULT;
	switch(key)
	{
	case 0:
		key=getch();
		switch(key){
		case 72:
			GlobalMsg=SPEED_UP;break;
		case 80:
			GlobalMsg=SPEED_DWN;break;
		case 75:
			GlobalMsg=PER_INDEX_DWN;break;
		case 77:
			GlobalMsg=PER_INDEX_UP;break;
		case 59: //F1
			GlobalMsg=CREDIT;break;
		case 60:	//F2
			GlobalMsg=START;break;
		case 63:	//F5
			GlobalMsg=SAVE;break;
		case 67:	//F9
			GlobalMsg=RESTORE;break;
		case 95:		//Ctr+F2
			GlobalMsg=START_NO;break;
		case 107:	//Alt+F4
			GlobalMsg=EXIT;break;
		default:
			GlobalMsg=DEFAULT;
			
		};break;

	case 'S':
	case 's':
		GlobalMsg=SHOW_NUM;break;
	case 'R':
	case 'r':
		GlobalMsg=SET_ROT;break;
	case '+':
		GlobalMsg=SCALE_UP;break;
	case '-':
		GlobalMsg=SCALE_DWN;break;
	case 'P':
	case 'p':
		GlobalMsg=PAUSE;break;
	case SPACE:
		GlobalMsg=RESET;break;
			
			

	case 55:
			a=1;
			cuberot=speed; running=1;break;
	case 52:
			a=2;
			cuberot=speed;running=1;break;
			//
	case 49:
			a=3;
			cuberot=speed;running=1;break;
	case 57:
			a=10;
			cuberot=speed;running=1;break;
			//
	case 54:
			a=11;
			cuberot=speed; running=1;break;
	case 51:
			a=12;
			cuberot=speed; running=1;break;
///////			
	case 56:
			a=8;
			cuberot=speed; running=1;break;
	case 50:
			a=17;
			cuberot=speed; running=1;break;

	default:
		GlobalMsg=DEFAULT;
			
		
	};	//End switch

	
};	//msg
void CUBE_APP::MouseOverMsg()
{
	
	if(restore->over(lastover)){}else
	if(reset->over(lastover)){}else
	if(close->over(lastover)){}else
	if(save->over(lastover)){}else
	if(random->over(lastover)){}else
	if(solve.over(lastover)){}else
	if(inc_delay->over(lastover)){}else
	if(dec_delay->over(lastover)){}else
	if(steped->over(lastover)){}else
	if(speed_up->over(lastover)){}else
	if(speed_dwn->over(lastover)){}else
	if(index_up->over(lastover)){}else
	if(index_dwn->over(lastover)){}else

	if(rxx->over(lastover)){}else
	if(ryy->over(lastover)){}else
	if(rzz->over(lastover)){}else

	if(scale_up->over(lastover)){}else
	if(scale_dwn->over(lastover)){}else
	if(rot_but->over(lastover)){}else
	if(gmouse_x>5&&gmouse_y>20&&gmouse_x<VP_WIDTH+5&&gmouse_y<VP_HEIGHT+20)	//Vieport
	{
		if(lastover!=ID_VPORT)st.setDisp(STRING5);
		lastover=ID_VPORT;
	}else
	if(gmouse_x>450&&gmouse_y>20&&gmouse_x<450+173&&gmouse_y<20+72)	//Vieport
	{
		if(lastover!=ID_CREDIT)st.setDisp(STR_CREDIT);
		lastover=ID_CREDIT;
	}else
	if(gmouse_x>MOVEX&&gmouse_y>MOVEY&&gmouse_x<MOVEX+VP_WIDTH+10&&gmouse_y<MOVEY+4*CHAR_H)	//Moves
	{
		int i;
		for(i=0;i<6;i++)
		{
			if(top[i]->over(lastover)){i=10;}else
				if(front[i]->over(lastover)){i=10;}else
					if(side[i]->over(lastover)){i=10;}
		};
		if(i!=11)
		{
			if(lastover!=DEFLT)st.setDisp(STRING4);
			lastover=DEFLT;
		};
	}else	
	//Default
	{
		if(lastover!=DEFLT)st.setDisp(STRING4);
		lastover=DEFLT;
	};
		
};
void CUBE_APP::MouseMsg(){
	
	if(gmouse_x>450&&gmouse_y>20&&gmouse_x<450+172&&gmouse_y<20+70)
	{
		while(getmouse()){};
		GlobalMsg=CREDIT;
	}else	
	
	if(gmouse_x>5&&gmouse_y>20&&gmouse_x<VP_WIDTH+5&&gmouse_y<VP_HEIGHT+20)	// 3D navigation
	{
		// restrictmouse(100,100,400,300);

		GlobalMsg=NAVIGATE;
		
	}else
	if(rxx->click()){
		GlobalMsg=RXX;
	}else
	if(ryy->click()){
		GlobalMsg=RYY;
	}else
	if(rzz->click()){
		GlobalMsg=RZZ;
	}else
	if(speed_up->click()){
		GlobalMsg=SPEED_UP;
	}else
	if(speed_dwn->click()){
		GlobalMsg=SPEED_DWN;
	}else
	if(index_up->click()){
		GlobalMsg=PER_INDEX_UP;
	}else
	if(index_dwn->click()){
		GlobalMsg=PER_INDEX_DWN;
	}else
	if(scale_up->click()){
		GlobalMsg=SCALE_UP;
	}else
	if(scale_dwn->click()){
		GlobalMsg=SCALE_DWN;
	}else
	if(rot_but->click()){
		GlobalMsg=SET_ROT;
	}else
	if(inc_delay->click()){
		GlobalMsg=DELAY_UP;
	}else
	if(dec_delay->click()){
		GlobalMsg=DELAY_DWN;
	}else
	if(steped->click()){
		GlobalMsg=TOG_STEP;
	}else
	if(random->click())
	{
		GlobalMsg=START;
	}else
	if(save->click())
	{
		GlobalMsg=SAVE;
	}else
	if(close->click()) 
	{
		GlobalMsg=EXIT;
	}else
	if(restore->click()) 
	{
		GlobalMsg=RESTORE;
	}else
	if(reset->click()) 
	{
		GlobalMsg=RESET;
	}else
	if(solve.click())
	{
		GlobalMsg=SOLVE;
	}else
	{
		GlobalMsg=MOVE;
	}//else GlobalMsg=DEFAULT;
							
};

void CUBE_APP::MouseMsgSolve()
{
		if(getmouse())
		{
			if( solve.click()){	solve_running=0;}else
			if( rot_but->click()){	setRot();}else
			if(inc_delay->click()){ DispatchMsg(DELAY_UP);}else
			if(dec_delay->click()){ DispatchMsg(DELAY_DWN);}else
			if(steped->click()){ DispatchMsg(TOG_STEP);}else
			if(rxx->click()){ DispatchMsg(RXX);}else
			if(ryy->click()){ DispatchMsg(RYY);}else
			if(rzz->click()){ DispatchMsg(RZZ);}else
			if(gmouse_x>5&&gmouse_y>20&&gmouse_x<VP_WIDTH+5&&gmouse_y<VP_HEIGHT+20){DispatchMsg(NAVIGATE);}

		}if(kbhit())
		{
			key=getch();
			if(key==27||key==32&&!step) solve_running=0;else
			if(key=='r'||key=='R') setRot();else
			if(key=='+') DispatchMsg(SCALE_UP);else
			if(key=='p'||key=='P') DispatchMsg(PAUSE);else
			if(key=='-') DispatchMsg(SCALE_DWN);
			key='a';//
		}
}
void CUBE_APP::findOrientation()
{
	int i;

	// Mouse message translation finding TOP FRONT and SIDE
	// Very clumzy Code but it works


	if(fabs(bc.axis[Y_G].gety())>fabs(bc.axis[X_R].gety()) && fabs(bc.axis[Y_G].gety())>fabs(bc.axis[Z_B].gety()) )//TOP check
	{
		topaxis=Y_G;	//this setting cause Rotate in 'y-axis'(->value 0) when 'top button'(->setting g) is pressed
		if(fabs(bc.axis[Z_B].getz())>fabs(bc.axis[X_R].getz()))			//FRONT check
		{
			frontaxis=Z_B;//Rotate in 'z-axis'(->value 3) when 'front button'(->setting b) is pressed
			sideaxis=X_R;//Rotate in 'x-axis'(->value 6) when 'side button'(->setting r) is pressed
		}else 
		{
			frontaxis=X_R;	//Opposite
			sideaxis=Z_B;
		};

	}else if(fabs(bc.axis[X_R].gety())>fabs(bc.axis[Z_B].gety()))	//TOP check
	{
		topaxis=X_R; 	//this setting cause Rotate in 'x-axis'(->value 6) when 'top button'(->setting g) is pressed
		if(fabs(bc.axis[Y_G].getz())>fabs(bc.axis[Z_B].getz()))	//FRONT check
		{
			frontaxis=Y_G;//Rotate in 'y-axis'(->value 0) when 'front button'(->setting b) is pressed
			sideaxis=Z_B;//Rotate in 'z-axis'(->value 3) when 'side button'(->setting r) is pressed
		}else 
		{
			frontaxis=Z_B;//Rotate in 'z-axis'(->value 3) when 'front button'(->setting b) is pressed
			sideaxis=Y_G;
		};		
	}else
	{
		topaxis=Z_B;
		if(fabs(bc.axis[X_R].getz())>fabs(bc.axis[Y_G].getz()))
		{
			frontaxis=X_R;
			sideaxis=Y_G;			
		}else 
		{			
			frontaxis=Y_G;
			sideaxis=X_R;
		};		
	};
};
void CUBE_APP::TransMsgRotation()
{
	int i,top_button,front_button,side_button,keyorder[]={1,2,3,10,11,12};
	
	switch(topaxis)
	{
	case Y_G :
			top_button=0;break;
	case Z_B :
			top_button=3;break;
	case X_R :
			top_button=6;break;
	};
	//
	switch(frontaxis)
	{
	case Y_G :
			front_button=0;break;
	case Z_B :
			front_button=3;break;
	case X_R :
			front_button=6;break;
	};
	//
	switch(sideaxis)
	{
	case Y_G :
			side_button=0;break;
	case Z_B :
			side_button=3;break;
	case X_R:
			side_button=6;break;
	};

	// Y axis TOP
	for(i=0;i<6;i++)
	{
		if(top[i]->click()){
			if(bc.axis[topaxis].gety()>0)a=top_button+keyorder[5-i];
			else a=top_button+keyorder[i];cuberot=speed; running=1;i=10;
		}else
			if(front[i]->click()){
				if(bc.axis[frontaxis].getz()<0)a=front_button+keyorder[5-i];
				else a=front_button+keyorder[i];cuberot=speed; running=1;i=10;
			}else
				if(side[i]->click()){
					if(bc.axis[sideaxis].getx()<0)a=side_button+keyorder[5-i];
					else a=side_button+keyorder[i];cuberot=speed; running=1;i=10;
				};
				
	};	
	
	
};
void CUBE_APP::draw(){
	
	clearviewport();
	if(arot)bc.rotAxis(rx*speed/8,ry*speed/8,rz*speed/8);
	//bc.drawAxis();
//	cout<<"speed "<<speed<<"  cuberot "<<cuberot;	
	circle(VP_WIDTH/2,VP_HEIGHT/2-5,115);
	if((int)cuberot!=0){
		
		bc.faceRot(speed,a);
		cuberot+=speed;
		if(cuberot>90) {cuberot=90-(cuberot-speed);
		bc.faceRot(cuberot,a);
		cuberot=0;running=0;bc.swapit(&a);
		};
		if(cuberot<(-90)) {cuberot=-90-(cuberot-speed);
		bc.faceRot(cuberot,a);
		cuberot=0;running=0;bc.swapit(&a);

		
		}
	};
	bc.disp();
	
};

void CUBE_APP::animate(){
	viewporttype cur;
	getviewsettings(&cur);	
	setviewport(5,20,10+VP_WIDTH,10+VP_HEIGHT,1);
	setactivepage(1);
	
	draw();
	
	
	setvisualpage(1);	// 2 page display system (age flipping)
	setactivepage(0);
	
	draw();
	
	setvisualpage(0);
	
	setviewport(cur.left,cur.top,cur.right,cur.bottom,cur.clip);
};

void CUBE_APP::MainEventLoop(){

	setmouse(VP_WIDTH/2,VP_HEIGHT/2);
	/////////MAIN LOOP////////////////
	do{
		
		while(!kbhit()&&!getmouse()){
			if((arot+cuberot)!=0)animate();
			MouseOverMsg();
		};
		if(gmouse_b){
			if(!running)
			{
				MouseMsg();
				DispatchMsg(GlobalMsg);
				animate();
			};
		}else {
			key=getch();
			if(running==0)
			{
				KeyMsg();
				DispatchMsg(GlobalMsg);
			}
		}
		if(key==27)
		{
			if(Common->evoke("Close Game?","Close",OPTION)==0) key='a';
		}
	} while (key!=27);
}
	/////////EXIT MAIN LOOP////////////////
	
	///Thank

