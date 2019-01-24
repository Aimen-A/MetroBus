#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
void graphics(void);
int security(void);
int mbus(void);
int main()
  { 
    graphics();
    //clrscr();
    fflush(stdin);
    int choice,flag1=0,flag2=0,i=0,recno=1;
    long int size;
    int gd=DETECT,gm;
    char another1,another2,another3,another4;
    char passname[20],searchname[20],delname[20];
    struct booking
    {
	char name[30];
	char dept[20];
	char arr[20];
	char date[20];
	char timedept[20];
	char timearr[20];
	char cnic[30];
	char busno[10];
	char incharge[30];
    }book;
    FILE *bus;
    FILE *temp;
   initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
   menu:
   setbkcolor(BLUE);
   setcolor(WHITE);
   moveto(150,120);
   settextstyle(1,0,2);
   outtext("1.BOOKING");
   moveto(150,145);
   outtext("2.CANCEL BOOKING");
   moveto(150,170);
   outtext("3.SHOW ALL BOOKING RECORD");
   moveto(150,195);
   outtext("4.MODIFY RECORD");
   moveto(150,220);
   outtext("5.SEARCH RECORD");
   moveto(150,245);
   outtext("6.Exit");
   moveto(250,300);
   outtext("CHOICE:");
   setfillstyle(1,WHITE);
   bar(325,305,400,320);
   gotoxy(46,20);
   scanf("%d",&choice);
   bus=fopen("RECORD.DAT","rb+");
   if(bus==NULL)
     {
	bus=fopen("RECORD.DAT","wb+");
	if(bus==NULL) { printf("ERROR IN OPENING FILE"); exit(1); }
     }
   size=sizeof(book);
   switch(choice)
	    {
	    case 1:
	       do
	       {
		clrscr();
		cleardevice();
		fflush(stdin);
		setbkcolor(DARKGRAY);
		fseek(bus,0,SEEK_END);
		setcolor(BLUE);
		settextstyle(SMALL_FONT,HORIZ_DIR,10);
		moveto(170,0);
		outtext("RECORD ENTRY");
		printf("\n\n\n\nEnter Passanger FULL Name:             ");
		gets(book.name);
		printf("\nISL\nKCH\nLAH\nMUL\nPSH \n\tEnter departure from:           ");
		gets(book.dept);
		printf("\nISL\nKCH\nLAH\nMUL\nPSH \n\tEnter Arrival to:               ");
		gets(book.arr);
		printf("Enter CNIC No:                          ");
		gets(book.cnic);
		printf("Enter date(Day:Month:Year):             ");
		gets(book.date);
		printf("Enter bus no:                           ");
		gets(book.busno);
		printf("Enter time of departure(hour:minutes):  ");
		gets(book.timedept);
		printf("Enter time of arrival(hour:minutes):    ");
		gets(book.timearr);
		printf("booking incharge FULL Name:             ");
		gets(book.incharge);
		if((strlen(book.name)!=0)&&(strlen(book.dept)!=0)&&(strlen(book.arr)!=0)&&(strlen(book.cnic)!=0)&&(strlen(book.date)!=0)&&(strlen(book.busno)!=0)&&(strlen(book.timedept)!=0)&&(strlen(book.timearr)!=0)&&(strlen(book.incharge)!=0))
		     {
		      fwrite(&book,size,1,bus);
		      setcolor(BLUE);
		      settextstyle(SMALL_FONT,HORIZ_DIR,6);
		      moveto(100,400);
		      outtext("\nRECORD ADDED SUCCESSFULLY");
		     }
		else
		     { setcolor(RED);
		       settextstyle(SMALL_FONT,HORIZ_DIR,6);
		       moveto(100,400);
		       outtext("\n!All feilds are mandatory");
		     }
		printf("\n\nEnter another record?(y/n):");
		another1=getch();
		}while(another1=='y'||another1=='Y');
		fclose(bus);
		cleardevice();
		goto menu;
	    case 2:
	       do
		{
		clrscr();
		cleardevice();
		fflush(stdin);
		setbkcolor(DARKGRAY);
		settextstyle(SMALL_FONT,HORIZ_DIR,10);
		setcolor(RED);
		moveto(55,0);
		outtext("BOOKING CANCELATION");
		printf("\n\n\n\nEnter name to Cancel Booking:  ");
		gets(delname);
		temp=fopen("newfile.DAT","w");
		rewind(bus);
		while(fread(&book,size,1,bus)==1)
		  {
		    if((strcmpi(book.name,delname))!=0)
		      fwrite(&book,size,1,temp);
		   else if((strcmpi(book.name,delname))==0)
		      flag1=1;
		  }
		if(flag1==0)
		   {
		     setcolor(RED);
		     settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
		     moveto(200,100);
		     outtext("\nNO RECORD FOUND");
		   }
		else if(flag1==1)
		   {
		    setcolor(BLUE);
		    settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
		    moveto(200,100);
		    outtext("\nRECORD DELETED");
		   }
		flag1=0;
		fclose(bus);
		fclose(temp);
		remove("RECORD.DAT");
		rename("newfile.DAT","RECORD.DAT");
		bus=fopen("RECORD.DAT","r+");
		printf("\n\n\n\nDELETE ANOTHER RECORD(Y/N)");
		fflush(stdin);
		another4=getche();
		}while(another4=='y'||another4=='Y');
		cleardevice();
		goto menu;
	    case 3:
	       clrscr();
	       cleardevice();
	       rewind(bus);
	       setbkcolor(DARKGRAY);
	       if(fread(&book,size,1,bus)==0)
		      {
		       setcolor(BLUE);
		       settextstyle(SMALL_FONT,HORIZ_DIR,6);
		       outtext("list is empty");
		       getche();
		       cleardevice();
		       goto menu;
		      }
	       rewind(bus);
	       while(fread(&book,size,1,bus)==1)
		 {  fflush(stdin);
		    setbkcolor(DARKGRAY);
		    printf("\t%d\n",recno++);
		    printf("PASSENGER NAME:        %s\nCNIC NO:               %s\nDEPARTURE FROM:        %s\nARRIVAL TO:            %s\nBUS NO:                %s",book.name,book.cnic,book.dept,book.arr,book.busno);
		    printf("\nDep TIME:              %s\nArr TIME:              %s\nDATE:                  %s\nBOOKING INCHARGE:      %s",book.timedept,book.timearr,book.date,book.incharge);
		    printf("\n\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
		    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
		    i++;
		    if(i==2)
		     { i=0;
		       setcolor(BLUE);
		       settextstyle(SMALL_FONT,HORIZ_DIR,6);
		       moveto(250,360);
		       outtext("ENTER ANY KEY TO CONTINUE......");
		       getch();
		       clrscr();
		       cleardevice();
		     }
		 }
	       setbkcolor(DARKGRAY);
	       setcolor(BLUE);
	       settextstyle(SMALL_FONT,HORIZ_DIR,7);
	       printf("\n\n\tYOU HAVE REACHED END OF RECORD");
	       recno=1;
	       i=0;
	       getch();
	       clrscr();
	       cleardevice();
	       goto menu;
	   case 4:
	      do
		{
		clrscr();
		cleardevice();
		fflush(stdin);
		setbkcolor(DARKGRAY);
		settextstyle(SMALL_FONT,HORIZ_DIR,10);
		setcolor(GREEN);
		moveto(150,0);
		outtext("RECORD UPDATING");
		printf("\n\n\n\nEnter Passenger name To Modify:    ");
		gets(passname);
		rewind(bus);
		while(fread(&book,size,1,bus)==1)
		  {
		     if(strcmpi(book.name,passname)==0)
			{
			  flag1=1;
			  settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
			  setcolor(BLUE);
			  moveto(50,80);
			  outtext("RECORD FOUND");
			  setcolor(GREEN);
			  moveto(150,120);
			  outtext("ENTER TO MODIFY RECORD");
			  printf("\n\n\n\n\nEnter Passanger FULL Name:             ");
			  gets(book.name);
			  printf("\nISL\nKCH\nLAH\nMUL\nPSH \n\tEnter departure from:           ");
			  gets(book.dept);
			  printf("\nISL\nKCH\nLAH\nMUL\nPSH \n\tEnter Arrival to:               ");
			  gets(book.arr);
			  printf("Enter CNIC No:                          ");
			  gets(book.cnic);
			  printf("Enter date(Day:Month:Year):             ");
			  gets(book.date);
			  printf("Enter bus no:                           ");
			  gets(book.busno);
			  printf("Enter time of departure(hour:minutes):  ");
			  gets(book.timedept);
			  printf("Enter time of arrival(hour:minutes):    ");
			  gets(book.timearr);
			  printf("booking incharge FULL Name:             ");
			  gets(book.incharge);
			  if((strlen(book.name)!=0)&&(strlen(book.dept)!=0)&&(strlen(book.arr)!=0)&&(strlen(book.cnic)!=0)&&(strlen(book.date)!=0)&&(strlen(book.busno)!=0)&&(strlen(book.timedept)!=0)&&(strlen(book.timearr)!=0)&&(strlen(book.incharge)!=0))
			      {
				 fseek(bus,-size,SEEK_CUR);
				 fwrite(&book,size,1,bus);
				 printf("\n");
				 settextstyle(SMALL_FONT,HORIZ_DIR,7);
				 setcolor(BLUE);
				 moveto(50,450);
				 outtext("RECORD ADDED SUCCESSFULLY");
				 break;
			      }
			  else
			      {
				printf("\n");
				setcolor(RED);
				settextstyle(SMALL_FONT,HORIZ_DIR,7);
				moveto(60,450);
				outtext("!All feilds are madatory");
			      }
			  break;
		       }

		   }

		 if(flag1==0)
		       { setcolor(RED);
			 settextstyle(SMALL_FONT,HORIZ_DIR,7);
			 moveto(50,80);
			 outtext("NO Record Found");
		       }
		 flag1=0;
		 printf("\n\nModify Another record(y/n)?\n");
		 another4=getch();
		 }while(another4=='y'||another4=='Y');
		 fclose(bus);
		clrscr();
		cleardevice();
		goto menu;
	    case 5:
	       fflush(stdin);
	       do
		{  clrscr();
		   cleardevice();
		   setbkcolor(DARKGRAY);
		   settextstyle(SMALL_FONT,HORIZ_DIR,10);
		   setcolor(YELLOW);
		   moveto(140,0);
		   outtext("RECORD SEARCHING");
		   printf("\n\n\nENTER NAME TO SEARCH RECORD:   ");
		   gets(searchname);
		   rewind(bus);
		   while(fread(&book,size,1,bus)==1)
		   if(strcmpi(book.name,searchname)==0)
		      {
			flag2=1;
			printf("\n\nPASSENGER NAME:        %s\nCNIC NO:               %s\nDEPARTURE FROM:        %s\nARRIVAL TO:            %s\nBUS NO:                %s",book.name,book.cnic,book.dept,book.arr,book.busno);
			printf("\nDep TIME:              %s\nArr TIME:              %s\nDATE:                  %s\nBOOKING INCHARGE:      %s",book.timedept,book.timearr,book.date,book.incharge);
			printf("\n\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
			printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
		      }
		   if(flag2==0)
		       { setcolor(RED);
		       printf("\n");
			 settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
			 moveto(5,75);
			 outtext("NO Record Found");
		       }
			printf("\n\n\nSearch another record?(y/n)");
		   another3=getch();
		   }while(another3=='y'||another3=='Y');
		clrscr();
		cleardevice();
		goto menu;
	    case 6:
	       closegraph();
	       exit(0);
	    default:
		 clrscr();
		 cleardevice();
		 setcolor(RED);
		 settextstyle(SMALL_FONT,HORIZ_DIR,7);
		 moveto(120,0);
		 outtext("Invalid choice option");
		 moveto(180,100);
		 outtext("SELECT AGAIN");
		 delay(2000);
		 clrscr();
		 goto menu;
	    }






    }

void graphics(void)
   {
     int gd=DETECT,gm,i,end,maxx,maxy;
clrscr();
initgraph(&gd,&gm,"C:\\turboc3\\bgi");

rectangle(20,40,560,450);
int v=12,f=0;

setbkcolor(WHITE);
delay(100);
setfillstyle(SOLID_FILL,BLUE);
bar(20,20,120,415);
delay(100);
setfillstyle(SOLID_FILL,BLUE);
bar(20,20,220,415);
delay(100);
setfillstyle(SOLID_FILL,BLUE);
bar(20,20,320,415);
delay(100);
setfillstyle(SOLID_FILL,BLUE);
bar(20,20,620,415);

do
{
delay(100);
setfillstyle(SOLID_FILL,BLUE);
bar(20,200,620,415);
delay(30);


moveto(110,10);

settextstyle(TRIPLEX_FONT,HORIZ_DIR,9);
setcolor(YELLOW);
outtext("WELCOME");
settextstyle(TRIPLEX_FONT,HORIZ_DIR,9);
setcolor(YELLOW);
moveto(115,110);
outtext("   TO  ");
settextstyle(TRIPLEX_FONT,HORIZ_DIR,9);
setcolor(YELLOW);
moveto(27,205);
outtext("  DATABSE");


f++;

moveto(12,305);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,9);
setcolor(YELLOW);
delay(150);
outtext(" METRO BUS ");
	  delay(80);
f++;

}

while(f!=v);
moveto(110,442);
settextstyle(SMALL_FONT,HORIZ_DIR,9);
setcolor( DARKGRAY);
delay(50);
outtext("***PLEASE WAIT***");
delay(100);
setfillstyle(SOLID_FILL,RED);
bar(55,430,65,430);
delay(1770);
setfillstyle(SOLID_FILL,RED);
bar(55,430,165,430);
delay(600);
setfillstyle(SOLID_FILL,RED);
bar(55,430,265,430);
delay(690);
setfillstyle(SOLID_FILL,RED);
bar(55,430,300,430);
delay(500);
setfillstyle(SOLID_FILL,RED);
bar(55,430,400,430);
delay(500);
setfillstyle(SOLID_FILL,RED);
bar(55,430,500,430);
delay(500);
setfillstyle(SOLID_FILL,RED);
bar(55,430,570,430);
delay(500);
setfillstyle(SOLID_FILL,RED);
bar(55,430,590,430);
moveto(450,450);
settextstyle(SMALL_FONT,HORIZ_DIR,5);
setcolor(WHITE);
delay(90);
outtext("PLEASE WAIT");

moveto(470,450);
settextstyle(SMALL_FONT,HORIZ_DIR,7);
setcolor(GREEN);
delay(90);
outtext("PRESS ANY KEY");

getch();
printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
delay(90);
printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
delay(90);
printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
delay(90);
printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
delay(90);
printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
fflush(stdin);
//dedicating
maxx=getmaxx();
maxy=getmaxy();
setbkcolor(LIGHTGRAY);
setcolor(LIGHTGRAY);
setfillstyle(WIDE_DOT_FILL,BLUE);
rectangle(0,0,maxx,maxy);
floodfill(319,239,LIGHTGRAY);
delay(150);
setcolor(LIGHTBLUE);
setfillstyle(SOLID_FILL,LIGHTBLUE);
arc(319,239,315,360,100);
delay(120);
arc(319,239,270,315,100);
delay(120);
arc(319,239,225,270,100);
delay(120);
arc(319,239,180,225,100);
delay(120);
arc(319,239,135,180,100);
delay(120);
arc(319,239,90,135,100);
delay(120);
arc(319,239,45,90,100);
delay(120);
arc(319,239,0,45,100);
floodfill(319,239,LIGHTBLUE);
setcolor(LIGHTGRAY);
settextstyle(SMALL_FONT,HORIZ_DIR,7);
	moveto(227,200);
	outtext("THIS DATABASE IS");
	moveto(250,220);
	outtext("DEDICATED TO");
	moveto(260,259);
	setcolor(BLUE);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	delay(120);
	outtext("SIR WASEEM");
	delay(2000);
cleardevice();

security();
fflush(stdin);
clrscr();
cleardevice();
setbkcolor(BLACK);
end=getmaxx();
for(i=0;i<end-380;i=i+5)
{
setcolor(BLUE);
setfillstyle(SOLID_FILL,BLUE);
rectangle(180,40,458,140);
floodfill(409,90,BLUE);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
setusercharsize(1,1,3,2);
setcolor(WHITE);
moveto(240,50);
outtext("MetroBus");
setcolor(BROWN);
line(0,398,639,398);
//buslower
setcolor(RED);
line(0+i,370,60+i,370);
arc(90+i,370,0,180,30);
line(120+i,370,270+i,370);
arc(300+i,370,0,180,30);
line(330+i,370,380+i,370);
//busbody
line(0+i,370,0+i,180);
line(380+i,370,380+i,180);
line(0+i,180,380+i,180);
setfillstyle(SOLID_FILL,RED);
floodfill(200+i,275,RED);
setcolor(YELLOW);
line(0+i,275,140+i,275);
line(240+i,275,380+i,275);
rectangle(140+i,265,240+i,285);
moveto(150+i,268);
settextstyle(SMALL_FONT,HORIZ_DIR,6);
outtext("LOADING....");
//buswheel
setcolor(GREEN);
setfillstyle(CLOSE_DOT_FILL,GREEN);
circle(90+i,370,25);
floodfill(90+i,370,GREEN);
circle(300+i,370,25);
floodfill(300+i,370,GREEN);
delay(100);
cleardevice();
}
delay(500);
}


int security()
    {
    int gd=DETECT,gm;
    int attempt=0;
    char allowpass[]="misbahaimen",pword[15],ch,c;
    pass:
	clrscr();
	cleardevice();
	c=0;
	memset(pword,0,strlen(pword));
	initgraph(&gd,&gm,"C:\\turboc3\\bgi");
	setbkcolor(WHITE);
	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	rectangle(170,0,478,480);
	floodfill(249,260,BLUE);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,7);
	setusercharsize(1,1,3,2);
	setcolor(WHITE);
	moveto(250,10);
	outtext("MetroBus");
	settextstyle(SMALL_FONT,HORIZ_DIR,7);
	moveto(240,250);
	outtext("Enter Password");
	setfillstyle(1,WHITE);
	bar(250,300,400,320);
	moveto(260,300);
ch=getch();
	while(ch!='\r')
	  {setcolor(BLUE);
	    outtext("*");
	    pword[c++]=ch;
	    ch=getch();

	  }
if(strcmp(allowpass,pword)==0)
	    {
	     moveto(260,350);
	     setcolor(WHITE);
	     outtext("ACCESS GRANTED");
	     delay(500);
	     return 0;
	     }
	else
	  {
	    if(attempt<2)
	      {
		attempt++;
		setcolor(WHITE);
		moveto(270,350);
		outtext("TRY AGAIN");
		delay(1000);
		goto pass;
	      }
	    else
	      { moveto(260,350);
		setcolor(WHITE);
		outtext("ACCESS DENIED");
		delay(700);
		cleardevice();
		exit(1);
	      }
	  }
    }






