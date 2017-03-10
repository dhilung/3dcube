/*
(cube.cpp)
1.	It consists of basic classes.
·	qtrnion 	(for manipulation 3D rotations)
·	matrix		(for getting the rotation matrix)
·	vpoint		(basic point in space)
·	cube		(a single cube (there are 27 such cubes in main program))
2.  qtrnion, matrix and vpoint classes can be manipulated as in mathematics. 
    (operators  are overloaded).


*/

#include <stdio.h>
#include<graphics.h>
#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<process.h>
#include <stdlib.h>

#define PI  3.141592
#define CP 10
#define SIDE 15
#define BORDER 5
#define AXIS 100
#define VP_WIDTH 430
#define VP_HEIGHT 200
#define CC 28
#define SPACE 32


#define DEB 0
//////////////  GLOBAL VARIABLES//////////////////////
float perIndex=600;	//Perspective Index
float scale=1;		//Scale
int shownum=0;		//Show number point
int faceColors[]={WHITE,YELLOW,GREEN,RED,CYAN,MAGENTA};	//base,top,mid1,mid2,mid3,mid4
///////////////////////////////////////////
class qtrnion{
public:
	float l,m,n;
	qtrnion(){l=0;m=0;n=0;};
	void normalize(){
		float d;
		d=sqrt(l*l+m*m+n*n);
		l/=d;m/=d;n/=d;
	};
	void setValue(float a,float b,float c){
		l=a;m=b;n=c;
		normalize();
	};
};
class matrix{
public:
	float mat[4][4];
	matrix(){ reset();};  //Constructor
	void reset();
	void disp();
	matrix operator *(matrix &);
	matrix getMatX(float);
	matrix getMatY(float);
	matrix getMatZ(float);
	matrix* setMatTot(float theta,float x,float y,float z);
	matrix getMatTot(float theta,float x,float y,float z);
	matrix getMatTot(float phi,float theta,float shi);

} globalMat;


void matrix::reset(){
	int i,j;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			if(i==j) mat[i][i]=1;
			else mat[i][j]=0;
		};
	} ;
}; //reset


void matrix::disp(){
	int i,j;
	cout<<"\n\n"<<endl;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			cout<<mat[i][j]<<"\t\t";
		};
		cout<<"\b\n";
	} ;
}; //reset

matrix matrix::operator *(matrix& m)
{
	int i,j,k;
	float tp=0.0;
	matrix temp;
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			for(k=0;k<4;k++){
				tp+=(temp.mat[i][k])*(m.mat[k][j]);  //Addition
			};
			temp.mat[i][j]=tp;
			tp=0.0;
		};
	} ;
	return temp;
};    // oper
matrix matrix::getMatX(float phi)
{
	phi*=PI/180;
	reset();
	mat[1][1]=cos(phi);
	mat[1][2]=(-sin(phi));
	mat[2][1]=sin(phi);
	mat[2][2]=cos(phi);
	return *this;
}  ;
matrix matrix::getMatY(float theta)
{
	theta*=PI/180;
	reset();
	mat[0][0]=cos(theta);
	mat[2][0]=sin(theta);
	mat[0][2]=(-sin(theta));
	mat[2][2]=cos(theta);
	return *this;
}  ;
matrix matrix::getMatZ(float shi)
{
	shi*=PI/180;
	reset();
	mat[0][0]=cos(shi);
	mat[0][1]=(-sin(shi));
	mat[1][0]=sin(shi);
	mat[1][1]=cos(shi);
	return *this;
}  ;
//Getting Tot Rotation
//Using X,Yand Z axis rotation
matrix matrix::getMatTot(float phi,float theta,float shi)       
{
	matrix mat,matTot;
	matTot=mat.getMatX(phi)*mat.getMatY(theta)*mat.getMatZ(shi);
	return matTot;
}  ;
//Getting Tot Rotation
//Using quaternion axis rotation
matrix* matrix::setMatTot(float theta,float x,float y,float z)
{
	//matrix matTot;
	float w;
	theta*=PI/(2*180);             // angle/2
	w=cos(theta);
	x*=sin(theta);
	y*=sin(theta);
	z*=sin(theta);
	
	this->mat[0][0]=1.0-2*y*y-2*z*z;
	this->mat[0][1]=2*x*y-2*w*z;
	this->mat[0][2]=2*x*z+2*w*y;
	this->mat[1][0]=2*x*y+2*w*z;
	this->mat[1][1]=1.0-2*x*x-2*z*z;
	this->mat[1][2]=2*y*z-2*w*x;
	this->mat[2][0]=2*x*z-2*w*y;
	this->mat[2][1]=2*y*z+2*w*x;
	this->mat[2][2]=1-2*x*x-2*y*y;
	return this;
}  ;             

matrix matrix::getMatTot(float theta,float x,float y,float z)       //Overload  Getting Tot Rotation
{
	matrix matTot;
	float w;
	theta*=PI/(2*180);             // angle/2
	w=cos(theta);
	x*=sin(theta);
	y*=sin(theta);
	z*=sin(theta);
	
	matTot.mat[0][0]=1.0-2*y*y-2*z*z;
	matTot.mat[0][1]=2*x*y-2*w*z;
	matTot.mat[0][2]=2*x*z+2*w*y;
	matTot.mat[1][0]=2*x*y+2*w*z;
	matTot.mat[1][1]=1.0-2*x*x-2*z*z;
	matTot.mat[1][2]=2*y*z-2*w*x;
	matTot.mat[2][0]=2*x*z-2*w*y;
	matTot.mat[2][1]=2*y*z+2*w*x;
	matTot.mat[2][2]=1-2*x*x-2*y*y;
	return matTot;
}  ;             

////////////////////////////////////////////////

class vpoint{
protected:
	float x,y,z;
public:
	vpoint(){x=0.0;y=0.0;z=0.0;};
	vpoint(float _x,float _y,float _z){x=_x;y=_y;z=_z;};
	void setxyz(float _x,float _y,float _z){x=_x;y=_y;z=_z;};
	void setx(float _x){x=_x;};
	void sety(float _y){y=_y;};
	void setz(float _z){z=_z;};
	float getx(){return x;};
	float gety(){return y;};
	float getz(){return z;};
	void rotate(matrix *rotationMat);
	void rotate(float,float,float);
	void rotate(float *,float *,float *,float *);            
	void move(float dx,float dy,float dz){  x+=dx;y+=dy;z+=dz;};
	float magnitude(){return (sqrt(x*x+y*y+z*z));};
	void disp(){cout<<"\t "<<x<<",\t"<<y<<",\t"<<z<<"\t"<<endl;};
	vpoint operator * (float);
	vpoint operator * (matrix& m);
};     // vpoint

vpoint vpoint::operator * (float m)
{
	float _x,_y,_z;
	_x=x*m;
	_y=y*m;
	_z=z*m;
	return vpoint(_x,_y,_z);
};      //oper

vpoint vpoint::operator * (matrix &m)
{
	float _x,_y,_z;
	_x=x*m.mat[0][0]+y*m.mat[1][0]+z*m.mat[2][0];
	_y=x*m.mat[0][1]+y*m.mat[1][1]+z*m.mat[2][1];
	_z=x*m.mat[0][2]+y*m.mat[1][2]+z*m.mat[2][2];
	return vpoint(_x,_y,_z);
};      //oper

void vpoint::rotate(matrix *rotationMat)
{
	*this=*this*(*rotationMat);

}
void vpoint::rotate(float ax,float ay,float az){
	*this=*this*globalMat.getMatX(ax);
	*this=*this*globalMat.getMatY(ay);
	*this=*this*globalMat.getMatZ(az);
};

void vpoint::rotate(float *theta,float *ax,float *ay,float *az){	// 4 para rotate
	globalMat.setMatTot(*theta,*ax,*ay,*az);
	*this=*this*globalMat;
};
/////////////////////////////////////////CUBE
class cube{
	vpoint p[CP];
	float a;
	float centerX;
	float centerY;
	float centerZ;
	int current_side[4];
	//      int faceColor[6];
public:
	int faceColor[6];      	//Constant
	int xyzcolor[7];		//For swaping
	cube(){
		setSide(SIDE);	//constructor
		inicol();   
	};
	cube(float a1,float _x,float _y,float _z){
		setSide(a1);			//	constructor
		setCenter(_x,_y,_z);
		inicol();      	       
	};
	void move(float x,float y,float z)
	{
		int i;
		for(i=0;i<8;i++)
		{
			p[i].move(x,y,z);
		}
	}
	void inicol()
	{
		faceColor[0]=WHITE;
		faceColor[1]=YELLOW;
		faceColor[2]=GREEN;
		faceColor[3]=RED;
		faceColor[4]=CYAN;
		faceColor[5]=MAGENTA;
		//
		xyzcolor[0]=WHITE;
		xyzcolor[1]=YELLOW;
		xyzcolor[2]=GREEN;
		xyzcolor[3]=RED;
		xyzcolor[4]=CYAN;
		xyzcolor[5]=MAGENTA; 
	};
	void setSide(float side){a=side;};
	void setCurSide(int);
	void setCenter(int,int,int);
	float getCenterZ();
	float getCenterX();
	float getCenterY();
	float getMaxZ();
	void rotate(matrix *rotationMat);
	void rotate(float,float,float);
	void rotate(float *,float *,float *,float *);      
	void swapCol(int);
	void drawSide(int);
	void disp(int c);
	
};    //cube
void cube::setCurSide(int side)			//Setting working side
{
	switch(side)
	{
	case 0:
		current_side[0]=0;current_side[1]=1;current_side[2]=2;current_side[3]=3;
		break;
	case 1:
		current_side[0]=4;current_side[1]=5;current_side[2]=6;current_side[3]=7;
		break;
	case 2:
		current_side[0]=0;current_side[1]=1;current_side[2]=5;current_side[3]=4;
		break;		
	case 3:
		current_side[0]=1;current_side[1]=2;current_side[2]=6;current_side[3]=5;
		break;	
	case 4:
		current_side[0]=2;current_side[1]=3;current_side[2]=7;current_side[3]=6;
		break;	
	case 5:
		current_side[0]=3;current_side[1]=0;current_side[2]=4;current_side[3]=7;
		break;	
	};
};
void cube::setCenter(int _x,int _y,int _z){	//Overloaded
	centerX=_x;
	centerY=_y;
	centerZ=_z;
	p[0].setxyz(-a+_x,a+_y,a+_z);
	p[1].setxyz(a+_x,a+_y,a+_z);
	p[2].setxyz(a+_x,a+_y,-a+_z);
	p[3].setxyz(-a+_x,a+_y,-a+_z);
	//
	p[4].setxyz(-a+_x,-a+_y,a+_z);
	p[5].setxyz(a+_x,-a+_y,a+_z);
	p[6].setxyz(a+_x,-a+_y,-a+_z);
	p[7].setxyz(-a+_x,-a+_y,-a+_z);	
};

float cube::getCenterX(){	
	centerX=(p[0].getx()+p[6].gety())/2;
	return centerX;
};
float cube::getCenterY(){	
	centerY=(p[0].gety()+p[6].gety())/2;
	return centerY;
};

float cube::getCenterZ(){
	centerZ=(p[0].getz()+p[6].getz())/2;
	return centerZ;
};
float cube::getMaxZ(){
	int i;
	centerZ=p[0].getz();
	for(i=1;i<8;i++){
		if(centerZ>p[i].getz()) centerZ=p[i].getz();
	};
	return centerZ;
};

void cube::	rotate(matrix *rotationMat)
{
	int i;
	for (i=0;i<CP;i++){
		p[i].rotate(rotationMat);
	};
}
void cube::rotate(float ax,float ay,float az)
{
	int i;
	for (i=0;i<CP;i++){
		p[i].rotate(ax,ay,az);
	};
};

void cube::rotate(float *theta,float *ax,float *ay,float *az)
{
	int i;
	for (i=0;i<CP;i++){
		p[i].rotate(theta,ax,ay,az);
	};
};
void cube::swapCol(int flag)
{
	int temp;
	switch(flag)
	{
	case 1:	// ->
		//if(DEB) cout<<"1";
		temp=xyzcolor[5];xyzcolor[5]=xyzcolor[4];xyzcolor[4]=xyzcolor[3];xyzcolor[3]=xyzcolor[2];xyzcolor[2]=temp;
		break;
	case 2: //  ')
		//if(DEB) cout<<"2";
		temp=xyzcolor[0];xyzcolor[0]=xyzcolor[5];xyzcolor[5]=xyzcolor[1];xyzcolor[1]=xyzcolor[3];xyzcolor[3]=temp;
		break;
	case 3:	// \/
		//if(DEB) cout<<"3";
		temp=xyzcolor[0];xyzcolor[0]=xyzcolor[2];xyzcolor[2]=xyzcolor[1];xyzcolor[1]=xyzcolor[4];xyzcolor[4]=temp;
		break;
		///Reverse
	case 4:	// <-
		//if(DEB) cout<<"4";
		temp=xyzcolor[2];xyzcolor[2]=xyzcolor[3];xyzcolor[3]=xyzcolor[4];xyzcolor[4]=xyzcolor[5];xyzcolor[5]=temp;
		break;
	case 5:	// ('
		//if(DEB) cout<<"5";
		temp=xyzcolor[0];xyzcolor[0]=xyzcolor[3];xyzcolor[3]=xyzcolor[1];xyzcolor[1]=xyzcolor[5];xyzcolor[5]=temp;
		break;
		case 6:// /\
			//if(DEB) cout<<"6";
			temp=xyzcolor[0];xyzcolor[0]=xyzcolor[4];xyzcolor[4]=xyzcolor[1];xyzcolor[1]=xyzcolor[2];xyzcolor[2]=temp;
			break;
	}
};


void cube::drawSide(int side)
{
	float depth;
	int i,Screen_x,Screen_y,screen_points[10];
	setCurSide(side);
	for(i=0;i<4;i++)
	{
		
		depth=1/(1-(p+current_side[i])->getz()*scale/perIndex);
		Screen_x=((int)(p[current_side[i]].getx()*depth))*scale+(VP_WIDTH/2);
		Screen_y=((int)(p[current_side[i]].gety()*depth))*scale+(VP_HEIGHT/2);
		screen_points[i*2]=Screen_x;
		screen_points[i*2+1]=Screen_y;
		if(i==0){screen_points[8]=Screen_x;screen_points[9]=Screen_y;};
		
	};
	setfillstyle(1,faceColor[side]);	//
	//drawpoly(5,screen_points);
	fillpoly(4,screen_points);	
};
void cube::disp(int c){
	int i,zo=0;
	float z;
	char buffer[30]; //for tracing
	
	/////////////////////////////////Setting Color Depth////////////////////
	// poly
	
	
	////////////////////////////////////////////////////////////////////////
	
	
	
	// Finding Z order ( we find the point that has larget z value
	z=p[0].getz();
	for(i=0;i<8;i++){
		if(p[i].getz()>z){
			z=p[i].getz();
			zo=i;}
	};
	//This is my methode of backface detection (octree methode of finding backface detection).... little problem in perspective mode
	setcolor(c);
	//sideColor[0]=WHITE;
	if(zo<4)
	{
		drawSide(0);
	}else
	{
		drawSide(1);
		zo=zo-4;
	};
	if(zo==0)
	{
		drawSide(5);
		drawSide(2);	
	}else
	{
		drawSide(zo+1);
		drawSide(zo+2);
	};
	
	
};   //disp




