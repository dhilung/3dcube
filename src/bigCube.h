/*
		This heder file is for two classes "bcube" and "GUI"
		"bcube" (BigCUbe) is main object and "GUI" (Graphic User Interface) is main playground.
		Main parts of programming is in this module.
*/		



#include <stdio.h>
#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
#include "cube.h"



#define WIREFRAME LIGHTCYAN



////////////////  GLOBAL FUNCTIONS  //////////////////////////
void sort(int n,int *list,cube *x){
	int item,i,temp;
	for(i=0;i<n;i++){
		list[i]=i;	//initialize  tag;
		
	};
	for(item=0;item<(n-1);++item){
		for(i=item+1;i<n;++i)
		{
			if((x+list[i])->getCenterZ()<(x+list[item])->getCenterZ()){
				temp=*(list+item);
				*(list+item)=*(list+i);;
				*(list+i)=temp;
			};
			
		};
	};
};	// sort

char waitKey()
{
	while(!kbhit()){};
	return getch();
};

//class solver;

class bcube{

	
	char BCbuffer[20];
	int order[28];
	public:
	vpoint axis[3];
	cube c[28];
	cube cr[28];
	qtrnion qaxis[3];
	bcube(){
	
		inibcube();
	};
	void inibcube() {
		int i;
		axis[0].setxyz(AXIS,0,0);
		axis[1].setxyz(0,AXIS,0);
		axis[2].setxyz(0,0,AXIS);

		c[0].setCenter(-(SIDE*2+BORDER),(SIDE*2+BORDER),(SIDE*2+BORDER));
		c[1].setCenter(0,(SIDE*2+BORDER),(SIDE*2+BORDER));
		c[2].setCenter((SIDE*2+BORDER),(SIDE*2+BORDER),(SIDE*2+BORDER));
		c[3].setCenter((SIDE*2+BORDER),(SIDE*2+BORDER),0);
		c[4].setCenter((SIDE*2+BORDER),(SIDE*2+BORDER),-(SIDE*2+BORDER));
		c[5].setCenter(0,(SIDE*2+BORDER),-(SIDE*2+BORDER));
		c[6].setCenter(-(SIDE*2+BORDER),(SIDE*2+BORDER),-(SIDE*2+BORDER));
		c[7].setCenter(-(SIDE*2+BORDER),(SIDE*2+BORDER),0);
		c[8].setCenter(0,(SIDE*2+BORDER),0);
//
		c[9].setCenter(-(SIDE*2+BORDER),0,(SIDE*2+BORDER));
		c[10].setCenter(0,0,(SIDE*2+BORDER));
		c[11].setCenter((SIDE*2+BORDER),0,(SIDE*2+BORDER));
		c[12].setCenter((SIDE*2+BORDER),0,0);
		c[13].setCenter((SIDE*2+BORDER),0,-(SIDE*2+BORDER));
		c[14].setCenter(0,0,-(SIDE*2+BORDER));
		c[15].setCenter(-(SIDE*2+BORDER),0,-(SIDE*2+BORDER));
		c[16].setCenter(-(SIDE*2+BORDER),0,0);
		c[17].setCenter(0,0,0);
//
		c[18].setCenter(-(SIDE*2+BORDER),-(SIDE*2+BORDER),(SIDE*2+BORDER));
		c[19].setCenter(0,-(SIDE*2+BORDER),(SIDE*2+BORDER));
		c[20].setCenter((SIDE*2+BORDER),-(SIDE*2+BORDER),(SIDE*2+BORDER));
		c[21].setCenter((SIDE*2+BORDER),-(SIDE*2+BORDER),0);
		c[22].setCenter((SIDE*2+BORDER),-(SIDE*2+BORDER),-(SIDE*2+BORDER));
		c[23].setCenter(0,-(SIDE*2+BORDER),-(SIDE*2+BORDER));
		c[24].setCenter(-(SIDE*2+BORDER),-(SIDE*2+BORDER),-(SIDE*2+BORDER));
		c[25].setCenter(-(SIDE*2+BORDER),-(SIDE*2+BORDER),0);
		c[26].setCenter(0,-(SIDE*2+BORDER),0);
		for(i=0;i<27;i++)
		{
			c[i].inicol();
		};

		updateq();
//
	};
	void faceRot(float,int);
	void drawAxis();
	void rotAxis(float,float,float);
	void disp();
	void swapit(int *);
	void swap();
	void updateq();


};	//bcube

void bcube::swapit(int *a){
	cube temp1,temp2;
	int i;
	int Move_g[4][9]={	{0,1,2,3,4,5,6,7,8},
				{9,10,11,12,13,14,15,16,17},
				{18,19,20,21,22,23,24,25,26}};
	int Move_b[4][9]={	{0,1,2,11,20,19,18,9,10},
				{7,8,3,12,21,26,25,16,17},
				{6,5,4,13,22,23,24,15,14}};
	int Move_r[4][9]={	{2,3,4,13,22,21,20,11,12},
				{1,8,5,14,23,26,19,10,17},
				{0,7,6,15,24,25,18,9,16}};							
//Green
	if(*a>0&&*a<4){	
	

		temp1=*(c+Move_g[*a-1][0]);
		temp2=*(c+Move_g[*a-1][1]);
		for(i=0;i<5;i+=2){		//Only 3 cycle i=0,i=2,i=4
			*(c+Move_g[*a-1][i])=*(c+Move_g[*a-1][i+2]);
			*(c+Move_g[*a-1][i+1])=*(c+Move_g[*a-1][i+3]);
		};
		*(c+Move_g[*a-1][i])=temp1;
		*(c+Move_g[*a-1][i+1])=temp2;
	//cout<<"Green +";
	//xyzColor Swaping for solving
		for(i=0;i<9;i++){
			(c+Move_g[*a-1][i])->swapCol(4);
		};		
	};
	//Oposite
	
	if(*a>9&&*a<13){			

		
		temp1=*(c+Move_g[*a-10][7]);
		temp2=*(c+Move_g[*a-10][6]);
		for(i=7;i>1;i-=2){		//Only 3 cycle i=7,i=5,i=3
			*(c+Move_g[*a-10][i])=*(c+Move_g[*a-10][i-2]);
			*(c+Move_g[*a-10][i-1])=*(c+Move_g[*a-10][i-3]);
		};
		*(c+Move_g[*a-10][i])=temp1;
		*(c+Move_g[*a-10][i-1])=temp2;

		//xyzColor Swaping for solving
		for(i=0;i<9;i++){
			(c+Move_g[*a-10][i])->swapCol(1);
		};
		
	};		



//Blue
	if(*a>3&&*a<7){

		temp1=*(c+Move_b[*a-4][7]);
		temp2=*(c+Move_b[*a-4][6]);
		for(i=7;i>1;i-=2){		//Only 3 cycle i=7,i=5,i=3
			*(c+Move_b[*a-4][i])=*(c+Move_b[*a-4][i-2]);
			*(c+Move_b[*a-4][i-1])=*(c+Move_b[*a-4][i-3]);
		};
		*(c+Move_b[*a-4][i])=temp1;
		*(c+Move_b[*a-4][i-1])=temp2;
		
		//cout<<"Blue +";
		//xyzColor Swaping for solving
		for(i=0;i<9;i++){
			(c+Move_b[*a-4][i])->swapCol(2);
		};		
		
	};

	//Oposite
	

		
	if(*a>12&&*a<16){
		//cout<<"Blue -";
			
		temp1=*(c+Move_b[*a-13][0]);
		temp2=*(c+Move_b[*a-13][1]);
		for(i=0;i<5;i+=2){		//Only 3 cycle i=0,i=2,i=4
			*(c+Move_b[*a-13][i])=*(c+Move_b[*a-13][i+2]);
			*(c+Move_b[*a-13][i+1])=*(c+Move_b[*a-13][i+3]);
		};
		*(c+Move_b[*a-13][i])=temp1;
		*(c+Move_b[*a-13][i+1])=temp2;
		
		//xyzColor Swaping for solving
		for(i=0;i<9;i++){
			(c+Move_b[*a-13][i])->swapCol(5);
		};		
	};/**/
//Red
	if(*a>6&&*a<10){
		temp1=*(c+Move_r[*a-7][7]);
		temp2=*(c+Move_r[*a-7][6]);
		for(i=7;i>1;i-=2){		//Only 3 cycle i=7,i=5,i=3
			*(c+Move_r[*a-7][i])=*(c+Move_r[*a-7][i-2]);
			*(c+Move_r[*a-7][i-1])=*(c+Move_r[*a-7][i-3]);
		};
		*(c+Move_r[*a-7][i])=temp1;
		*(c+Move_r[*a-7][i-1])=temp2;	
		
		//xyzColor Swaping for solving
		for(i=0;i<9;i++){
			(c+Move_r[*a-7][i])->swapCol(3);
		};			
					

	};
	//Oposite
	if(*a>15&&*a<19){			
		temp1=*(c+Move_r[*a-16][0]);
		temp2=*(c+Move_r[*a-16][1]);
		for(i=0;i<5;i+=2){		//Only 3 cycle i=0,i=2,i=4
			*(c+Move_r[*a-16][i])=*(c+Move_r[*a-16][i+2]);
			*(c+Move_r[*a-16][i+1])=*(c+Move_r[*a-16][i+3]);
		};
		*(c+Move_r[*a-16][i])=temp1;
		*(c+Move_r[*a-16][i+1])=temp2;
		
		//xyzColor Swaping for solving
		for(i=0;i<9;i++){
			(c+Move_r[*a-16][i])->swapCol(6);
		};		
	};	
		
	
};


void bcube::faceRot(float theta,int a)
{
	int i;
	int Move_g[4][9]={	{0,1,2,3,4,5,6,7,8},
				{9,10,11,12,13,14,15,16,17},
				{18,19,20,21,22,23,24,25,26}};
	int Move_b[4][9]={	{0,1,2,11,20,19,18,9,10},
				{7,8,3,12,21,26,25,16,17},
				{6,5,4,13,22,23,24,15,14}};
	int Move_r[4][9]={	{2,3,4,13,22,21,20,11,12},
				{1,8,5,14,23,26,19,10,17},
				{0,7,6,15,24,25,18,9,16}};	
	if(a>9) {theta=-theta;a-=9;}
	for(i=0;i<9;i++){
		if(a>0&&a<4){
			globalMat.setMatTot(theta,qaxis[1].l,qaxis[1].m,qaxis[1].n);
			(c+Move_g[a-1][i])->rotate(&globalMat);
		};//rotate
		if(a>3&&a<7){
			globalMat.setMatTot(theta,qaxis[2].l,qaxis[2].m,qaxis[2].n);
			(c+Move_b[a-4][i])->rotate(&globalMat);
		//	(c+Move_b[a-4][i])->rotate(&theta,&(qaxis[2].l),&(qaxis[2].m),&(qaxis[2].n));
		};//rotate
		if(a>6&&a<10){
			globalMat.setMatTot(theta,qaxis[0].l,qaxis[0].m,qaxis[0].n);
			(c+Move_r[a-7][i])->rotate(&globalMat);
		//	(c+Move_r[a-7][i])->rotate(&theta,&(qaxis[0].l),&(qaxis[0].m),&(qaxis[0].n));
		};//rotate
	}
};



void bcube::drawAxis(){
	int i,Sc_x,Sc_y,inicol;
	float depth;
	inicol=getcolor();
	for(i=0;i<3;i++){
	if(i==0) setcolor(LIGHTRED);			//RED
	else if (i==1) setcolor(LIGHTGREEN);		//GREEN
		else setcolor(LIGHTBLUE);		//BLUE
	 depth=1/(1-axis[i].getz()/perIndex);
	 Sc_x=(int)(axis[i].getx()*depth)+VP_WIDTH/2;
	 Sc_y=(int)(axis[i].gety()*depth)+VP_HEIGHT/2;
	 outtextxy(Sc_x,Sc_y,"+");
	 moveto(Sc_x,Sc_y);
	 //
	 depth=1/(1+axis[i].getz()/perIndex);
	 Sc_x=(int)(-axis[i].getx()*depth)+VP_WIDTH/2;
	 Sc_y=(int)(-axis[i].gety()*depth)+VP_HEIGHT/2;
	 lineto(Sc_x,Sc_y);
	 outtextxy(Sc_x,Sc_y,"-");
	};
	setcolor(inicol);
};
void bcube::rotAxis(float ax,float ay,float az){
	int i;
	globalMat.setMatTot(ax,1,0,0);
	for(i=0;i<3;i++){
	
	globalMat.setMatTot(ax,1,0,0);
	axis[i]=axis[i]*globalMat;

	globalMat.setMatTot(ay,0,1,0);
	axis[i]=axis[i]*globalMat;

	globalMat.setMatTot(az,0,0,1);
	axis[i]=axis[i]*globalMat;
	
	};
    for (i=0;i<CC-1;i++){
	//c[i].rotate(ax,ay,az);

	globalMat.setMatTot(ax,1,0,0);
	c[i].rotate(&globalMat);

	globalMat.setMatTot(ay,0,1,0);
	c[i].rotate(&globalMat);

	globalMat.setMatTot(az,0,0,1);
	c[i].rotate(&globalMat);

		};	
	updateq();
};

void bcube::disp(){				//DISPLAY with Z order
	int item;
	sort(CC-1,order,c); 
	for(item=0;item<(CC-1);++item){

			if(item==15)drawAxis();
			c[order[item]].disp(WIREFRAME);
			if(shownum)
			{
				float depth;
				int Screen_x,Screen_y;
				depth=1/(1-c[order[item]].getCenterZ()*scale/perIndex);
	 			Screen_x=((int)(c[order[item]].getCenterX()*depth))*scale+(VP_WIDTH/2);
	 			Screen_y=((int)(c[order[item]].getCenterY()*depth))*scale+(VP_HEIGHT/2);
				sprintf(BCbuffer,"%d",order[item]);
				outtextxy(Screen_x,Screen_y,BCbuffer);
			};
	};
};

void bcube::updateq(){
	int i;
	for(i=0;i<3;i++){
		qaxis[i].setValue(axis[i].getx(),axis[i].gety(),axis[i].getz());
	};
};


