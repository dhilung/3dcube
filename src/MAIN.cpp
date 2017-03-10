/*
Main file (main.cpp)
1.	It consists of only main() function definition.
2.	Intro-screen display function is called from this file.
3.	Cube_App.h is included.

*/
#include<process.h>
#include<graphics.h>
#include<iostream.h>
#include "Cube_App.h"
//==========================MAIN======================
void main()
{

	CUBE_APP gui;

	registerbgidriver(EGAVGA_driver);
	registerbgifont(triplex_font);
	registerbgifont(small_font);
	
	int gdriver=VGA,gmode=VGAMED;

	initgraph(&gdriver,&gmode,"");
	/////////
	if( !initmouse())  // if mouse installed
	{
		cout << "Mouse Driver Not found..." << endl;
		return;
	}
	showmouse();
	setbkcolor(LIGHTGRAY);
	gui.intro();
	
	////////
       waitKey();
	//	hidemouse();
	setmouse(VP_WIDTH/2,VP_HEIGHT/2);
	setbkcolor(BLACK);
	clearviewport();
	setactivepage(1);
	gui.ini();
	setactivepage(0);
	gui.ini();
	//



	showmouse();
	gui.MainEventLoop();
	//

       //	waitKey();
	closegraph();
	delete &gui;
	exit(0);
};   //main