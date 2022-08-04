#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


int main();
void main_window();
void add_student();
void search_student();
void mod_student();
void delete_student();
int search_ID(char s_id[20]);
void display();
void writeToFile();
void load_database();
void About();
void search_google();


struct student{
	char ID[15];
    char name[25];
    char semester[15];
    char cgpa[5];
    char sec[10];
	char gen[5];
	char phone_no[15];
    char email[30];
    char add[20];
    
    struct student *next;
    struct student *prev;
    
}*start=NULL, *tail=NULL, *node, *current, *new_node, stu;

int count=0;
void t();

void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){  
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void drawRectangle(){
    int i, j;
    gotoxy(4,0);
    printf("%c",201);
    for(i = 5; i < 110; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(110,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(110, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(110, 25);
    printf("%c",188);
    for(i = 109; i > 4; i--){
        gotoxy(i,25);
        if(i == 53){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(4,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(4,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 5; i < 110; i++){
        gotoxy(i,6);
        if(i == 53){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(53,i);
        printf("%c",186);
    }

}

void clearWindow(){
	gotoxy(90,5);printf("Student:%d",count);
	int i, j;
    for(i=55; i < 109; i++)
	{
        for(j=7; j < 25; j++)
		{
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}
void get_password(char* pass)
{
    char temp_passP[25];
    int i=0;
     while(1)
    {
            temp_passP[i]=getch();
            if(temp_passP[i]==13){break;}
            else if(temp_passP[i]==8)
            {
                if(i!=0) {
                printf("\b \b");
                i--;
                } else {printf("\a");}
            }
            else
            {
                printf("*");
                *(pass+i) = temp_passP[i];
                i++;
            }
             *(pass+i)='\0';
     }
}

void use_pass_field(){
    int x = 15, y = 16;
    int use;
    char pass[10];
    SetColor(10);
    gotoxy(15,12);printf("The database is password protected.");
    gotoxy(15,13);printf(" Enter Valid username and password");
    SetColor(17);
    gotoxy(20,x);printf("USERNAME:- ");
    gotoxy(20,y);printf("PASSWORD:- ");
    gotoxy(34,x);scanf("%d",use);
    gotoxy(34,y);get_password(pass);
    if (pass!="ss")
    {

     return ;
 	}
}
void print_heading(const char st[]){
    SetColorAndBackground(14,28);
    gotoxy(70,7);printf("                    ",st);
    gotoxy(70,8);printf("%s",st);
    gotoxy(70,9);printf("                    ",st);
    SetColorAndBackground(22,00);
}


void highlight(int no,int count)
{
	t();
 if(no==7){
 	int i=10, j=13, c=14;
 	SetColor(55);

  gotoxy (i,j++);printf("   <Add the Record>  ");
  gotoxy (i,j++);printf("   <Modify Record>   ");
  gotoxy (i,j++);printf("   <Search Record>   ");
  gotoxy (i,j++);printf("   <Delete Record>   ");
  gotoxy (i,j++);printf("   <Display All>     ");
  gotoxy (i,j++);printf("   <About>           ");
  gotoxy (i,j++);printf("   <Save & Exit>     ");



  switch(count)
  {
   case 1:
    gotoxy (i,13);
    SetColor(c);
    printf("   >°Add the Record<    ");
    break;
   case 2:
   	SetColor(c);
    gotoxy (i,14);
    printf("   >°Modify Record<     ");
    break;
   case 3:
   	SetColor(c);
    gotoxy (i,15);
    printf("   >°Search Record<     ");
    break;
   case 4:
   	SetColor(c);
    gotoxy (i,16);
    printf("   >°Delete Record<     ");
    break;
   case 5:
   	SetColor(c);
    gotoxy (i,17);
    printf("   >°Display All<       ");
    break;
   case 6:
   	SetColor(c);
    gotoxy (i,18);
    printf("   >°About<             ");
    break;
   case 7:
   	SetColor(c);
    gotoxy (i,19);
    printf("   >°Save & Exit<       ");
    break;
  }
 }
 
 //
  if(no==8){
 	int i=66, j=12, c=14;
 	SetColor(55);

  gotoxy (i,j++);printf("   <Name>       ");
  gotoxy (i,j++);printf("   <Semester>   ");
  gotoxy (i,j++);printf("   <CGPA>       ");
  gotoxy (i,j++);printf("   <SEC>        ");
  gotoxy (i,j++);printf("   <SEX>        ");
  gotoxy (i,j++);printf("   <Phone No>   ");
  gotoxy (i,j++);printf("   <Email>      ");
  gotoxy (i,j++);printf("   <Address>    ");


  switch(count)
  {
   case 1:
    gotoxy (i,12);
    SetColor(c);
    printf("   >°Name<         ");
    break;
   case 2:
   	SetColor(c);
    gotoxy (i,13);
    printf("   >°Semester<     ");
    break;
   case 3:
   	SetColor(c);
    gotoxy (i,14);
    printf("   >°CGPA<         ");
    break;
   case 4:
   	SetColor(c);
    gotoxy (i,15);
    printf("   >°SEC<          ");
    break;
   case 5:
   	SetColor(c);
    gotoxy (i,16);
    printf("   >°SEX<          ");
    break;
   case 6:
   	SetColor(c);
    gotoxy (i,17);
    printf("   >°Phone No<     ");
    break;
   case 7:
   	SetColor(c);
    gotoxy (i,18);
    printf("   >°Email<        ");
    break;
   case 8:
   	SetColor(c);
    gotoxy (i,19);
    printf("   >°Address<      ");
    break;
  }
 }
 //
 if(no==2){
 	int c=14;
 	//clearWindow();
 	SetColor(55);

  gotoxy (60,15);printf("   <Google Record>  ");
  gotoxy (80,15);printf("   <Search ID>  ");


  switch(count)
  {
   case 1:
    gotoxy (60,15);
    SetColor(c);
    printf("   >°Google Record°< ");
    break;
   case 2:
   	SetColor(c);
    gotoxy (80,15);
    printf("   >°Search ID°< ");
    break;
  }
 }
 //
}

int curser(int no)

{
	t();
    int count=1,i=2,j=10;
    char ch='0';
    gotoxy(i,j);
 while(1){
  switch(ch){
   case 80:
    count++;
    if (count==no+1) count=1;
    break;
   case 72:
    count--;
    if(count==0) count=no;
    break;
  }
  highlight(no,count);
  ch=getch();
  if(ch=='\r'){
   if(no==7){
    if (count==1) add_student() ;
    else if(count==2) mod_student();
    else if(count==3) {clearWindow();curser(2);}//search_student();
    else if (count==4) delete_student();
    else if (count==5) display();
	else if (count==6) About();
    else   
		{	
		writeToFile();
		system ("cls");exit(0);
		}
   	}
   if(no==8){
   
   	 	return count;
   	
   		}
   if(no==2){
   	if (count==1) search_google();
    else if(count==2) search_student();
   }		
  	}

 }
}



void main_window(){
	t();
    int choice;
    SetColor(14);gotoxy(90,5);printf("Student:%d",count);
    SetColor(12);
    int x = 10;

 	gotoxy(x,7);printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
 	gotoxy(x,8);printf("°°°°°°°°°°°°° MAIN MENU °°°°°°°°°°°°°");
 	gotoxy(x,9);printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");

  		curser(7);

}

void t(){
	time_t t;
    time(&t);
    SetColor(11);gotoxy(5,5);printf(" %s", ctime(&t));
    return ;
}


void window(){
	system ("cls");
	ClearConsoleToColors(17,00);
    drawRectangle();
    gotoxy(44,2);
    SetColor(34);
    printf("STUDENT RECORD SYSTEM");
    gotoxy(26,3);
    printf("Daffodil International University (DIU), Dhaka, Bangladesh");
    gotoxy(44,4);
    printf("CSE : Summer 2018 [D]");
    gotoxy(25,24);

    main_window();

}


int main(){
	
	t();
    ClearConsoleToColors(17,00);
    SetConsoleTitle("||**GROUP NAME: VIROUS**||GROUP M>> Rahima Akter Munni//Sadia Afrin Rajani//Fahim Ahmed//S.M.Sohan//Moon Sakib");
    load_database();delay(600);system ("cls");
    window();

}

//


int search_ID(char s_id[20]){ //sohan

    current=start;
    	while(current!=NULL)
    {
        if(strcmp(s_id,current->ID) == 0 )
        {
        	gotoxy(60,24);SetColor(28);printf("Sory, This ID use plss try again!");
        
               return 0;
        }
        current=current->next;

    }
    return 1;

}


void add_student(){
	t();
	    clearWindow();
    print_heading("    <ADD RECORD>    ");
    
    int num,i;
    new_node =(struct student *)malloc(sizeof(struct student));

  	start:
  	SetColor(45);
  	int print = 55, y=12;
  gotoxy(print,y++);printf("°ID > ");gets(new_node->ID);
  
  	int k = search_ID(new_node->ID); if(k==0)goto start;
  	
  gotoxy(print,y++);printf("°Name > ");gets(new_node->name);
  gotoxy(print,y++);printf("°Semester > ");gets(new_node->semester);
  fflush(stdin);
  gotoxy(print,y++);printf("°CGPA > ");gets(new_node->cgpa);
  fflush(stdin);
  gotoxy(print,y++);printf("°SEC > ");gets(new_node->sec);
  gotoxy(print,y++);printf("°SEX > ");gets(new_node->gen);
  gotoxy(print,y++);printf("°Phone no > ");gets(new_node->phone_no);
  fflush(stdin);
  gotoxy(print,y++);printf("°Email > ");gets(new_node->email);
  gotoxy(print,y++);printf("°Address > ");gets(new_node->add);

  new_node->next=NULL;
   new_node->prev=NULL;
        

    if(start==NULL && tail==NULL)
    {
        start=new_node;
        tail=new_node;
        current=new_node;

    }
    else
    {
    	current=tail;
        current->next=new_node;
        new_node->prev=current;
        tail=new_node;
    }

    
    SetColor(28);
    gotoxy(60,22);SetColor(11); printf("The record is successfully added!");

        count++;
    main_window();

}


void search_student(){
	t();

	 clearWindow();
    print_heading("  <SEARCH RECORD>   ");
    SetColor(45);
    char s_id[15];
    int isFound = 0;
    int x=55,y=14;
    gotoxy(x,11);printf("Enter ID to Search: ");
	fflush(stdin);
    gets(s_id);
    struct student *current;
    current=start;
    	while(current!=NULL)
    {
        if(strcmp(s_id,current->ID) == 0 )
        {
        	isFound = 1;
        gotoxy(x,12);printf("The record is Found");
        gotoxy(x,y++);printf("°ID > %s",current->ID);
        gotoxy(x,y++);printf("°Name > %s",current->name);
        gotoxy(x,y++);printf("°Semester > %s",current->semester);
        gotoxy(x,y++);printf("°CGPA > %s",current->cgpa);
        gotoxy(x,y++);printf("°SEC > %s",current->sec);
        gotoxy(x,y++);printf("°SEX > %s",current->gen);
        gotoxy(x,y++);printf("°Phone No > %s",current->phone_no);
        gotoxy(x,y++);printf("°Email > %s",current->email);
        gotoxy(x,y++);printf("°Address > %s",current->add);

            break;
        }
        current=current->next;

    }
    if(isFound ==0){
        gotoxy(x,12);SetColor(28);printf("Sorry, No record found in the database!");
    }
    SetColor(28);
    main_window();

}


void mod_student(){
	t();

    clearWindow();
    print_heading("   <MODIFY RECORD>  ");
    SetColor(45);
    char s_id[15];
    int isFound = 0;
    int x=55,i=70,y=22;
    gotoxy(x,11);printf("Enter ID to Modify>> ");fflush(stdin);
    fflush(stdin);
    gets(s_id);
        struct student *current;
        current=start;
    	while(current!=NULL)
    {


        if(strcmp(current->ID,s_id) == 0 )
        {
        	int count=curser(8);
        	
        	
   		if     (count==1) 
			{
			gotoxy(x,y);printf("°Name°> ");fflush(stdin);gets(current->name);
			isFound = 1;break;
			}

    	else if(count==2) 
			{
			gotoxy(x,y);printf("°Semester°> ");fflush(stdin);gets(current->semester);
			isFound = 1;break;
			}
    	else if(count==3) 
			{
			gotoxy(x,y);printf("°CGPA° > ");fflush(stdin);gets(current->cgpa);
			isFound = 1;break;
			}
    	else if(count==4) 
			{
			gotoxy(x,y);printf("°SEC°> ");fflush(stdin);gets(current->sec);
			isFound = 1;break;
			}
		else if(count==5)
			{
	 	 	gotoxy(x,y);printf("°SEX°> ");fflush(stdin);gets(current->gen);
	 	 	isFound = 1;break;
	 		}
    	else if(count==6)
			{
	 		gotoxy(x,y);printf("°Phone_No°> ");fflush(stdin);gets(current->phone_no);
	 		isFound = 1;break;
	 		}
    	else if(count==7) 
			{
			gotoxy(x,y);printf("°Email°> ");fflush(stdin);gets(current->email);
			isFound = 1;break;
			}
    	else if(count==8)
			{
	  		gotoxy(x,y);printf("°Address°> ");fflush(stdin);gets(current->add);
	  		isFound = 1;break;
	 		}

   		 else   gotoxy(0,28);SetColor(28);main_window();
            
    	}
        current=current->next;

    }

    if(!isFound){
        gotoxy(60, 15);SetColor(28);printf("No Record Found!");
    }
    SetColor(28);
    main_window();
}


void delete_student(){
	t();

    clearWindow();
    print_heading("   <DELETE RECORD>  ");
    SetColor(45);
    char s_id[15];
    int isFound = 0, print = 37;
    struct student *current,*temp1,*temp2;
    current= start;

      if(start==NULL&&tail==NULL)
    {
        gotoxy(66,15);SetColor(28);printf("There is no data to delete! \n");
        gotoxy(0,28);
        main_window();
    }

    gotoxy(55,11);printf("Enter ID to Delete>> ");
    fflush(stdin);
    gets(s_id);

    while(current!=NULL)
    {
        if(stricmp(current->ID,s_id) == 0 )
        {
        	if(start==current)
    		{
      	  	start=current->next;
        	current->prev=start;
        	start=NULL;
        	tail=NULL;
    		}
    		else if(tail==current)
    		{
        	current=tail->prev;
        	current->next=NULL;
       		tail=current;
    		}
    		else
    		{
        	temp1=current->prev;
        	temp2=current->next;
        	temp1->next=temp2;
        	temp2->prev=temp1;
    		}
    		isFound =1;
           // break;
        }
        current=current->next;

    }
    if(isFound==1){
    SetColor(11);gotoxy(60,15);printf("The Record Is Successfully Deleted!");
    count--;
	}
	else {SetColor(28);gotoxy(65,15);printf("The Record Is No Found!");}
    main_window();
}



void display(){ //sohan

	t();
	 system ("cls");
	 SetColor(45);
	 SetColorAndBackground(14,28);
	gotoxy(44,2);printf("                              ");
	gotoxy(44,3);printf("    <ALL STUDENT RECORD>      ");
    gotoxy(44,4);printf("                              ");
    SetColorAndBackground(22,00);
    SetColor(45);
    
    int x=5,y=8,n=1;
    
        if(start==NULL)
        {
			SetColor(28);gotoxy(44,y++);puts("There Are No Record To Display!");
		}
    else
    {
    	SetColorAndBackground(14,17);
	    gotoxy(x,y++);printf("%15s°|°%-25s|°%-15s|°%-30s|°%-20s","ID","NAME","PHONE","EMAIL","ADDRESS");
        gotoxy(x,y++);puts("----------------+--------------------------+----------------+-------------------------------+---------------------");
        current=start;

        do
        {
        	gotoxy(x,y++);SetColorAndBackground(34,00);
                printf("%15s | %-25s| %-15s| %-30s| %-20s\n",\
                current->ID,\
                current->name,\
                current->phone_no,\
                current->email,\
                current->add);
        }

        while((current=current->next) != NULL);
    }
    
	y++;y++;
	
    SetColor(28);
    gotoxy(x,y++);printf("Enter any kye to MAIN MENU!  >>");
    getch();
	window();

}

void writeToFile() //fahim
{
    FILE * fptr;
    fptr = fopen("Student_record.txt", "w");
    struct student *current = start;

    if(fptr==NULL)
    {
        printf("Error\n");
    }

    else
    {
        while(current!= NULL)
        {
            fprintf(fptr, " %s %s %s %s %s %s %s %s %s",current->ID,current->name,current->semester,current->cgpa,current->sec,current->gen,current->phone_no,current->email,current->add);
            current= current->next;
        }
    }

    fclose(fptr);
    }

void load_database()//fahim
{
    FILE *fp;
    fp=fopen("Student_record.txt","r");
    char c;
    c = fgetc(fp);
    while (c != EOF)
   {
   	count++;
   	
    node =(struct student *)malloc(sizeof(struct student));
    fscanf(fp,"%s%s%s%s%s%s%s%s%s",&node->ID, &node->name, &node->semester, &node->cgpa, &node->sec, &node->gen, &node->phone_no, &node->email, &node->add);
    node->prev=NULL;
    node->next=NULL;
 
	if(start==NULL && tail==NULL)
    {
        start=node;
        tail=node;
        current=node;

    }
    else
    {
    	current=tail;
        current->next=node;
        node->prev=current;
        tail=node;
    }

    delay(20);
    printf("\n          Registration Completed Of %s & ID is %s",node->name,node->ID);
    c = fgetc(fp);
   }
   return ;
   main_window();
}


void search_google(){//sohan

	clearWindow();
    print_heading("  <SEARCH RECORD>   ");
    SetColor(45);
    char s_id[15];
    int isFound = 0;
    gotoxy(55,11);printf("GOOGLE SEARCH >> ");
	fflush(stdin);
    gets(s_id);
     system ("cls");
	 SetColor(45);
	 SetColorAndBackground(14,28);
	gotoxy(44,2);printf("                              ");
	gotoxy(44,3);printf("       <GOOGLE RECORD>        ");
    gotoxy(44,4);printf("                              ");
    SetColorAndBackground(22,00);
    SetColor(45);
    
    int x=5,y=8,n=0;
    
        if(start==NULL)
        {
			SetColor(28);gotoxy(44,y++);puts("There Are No Record To Display!"); 
		}
    else
    {
    	SetColorAndBackground(14,17);
	    gotoxy(x,y++);printf("%15s°|°%-25s|°%-15s|°%-30s|°%-20s","ID","NAME","PHONE","EMAIL","ADDRESS");
        gotoxy(x,y++);puts("----------------+--------------------------+----------------+-------------------------------+---------------------");
        current=start;
    	while(current!=NULL)
    	{
        	if(strcmp(s_id,current->ID) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
        	}
        	if(strcmp(s_id,current->name) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
        	}
        	if(strcmp(s_id,current->semester) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
        	}
       	 	if(strcmp(s_id,current->cgpa) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
        	}
        	if(strcmp(s_id,current->sec) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
        	}
        	if(strcmp(s_id,current->gen) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
        	}
        	if(strcmp(s_id,current->phone_no) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
    
        	}
        	if(strcmp(s_id,current->email) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
            
    		}
        	if(strcmp(s_id,current->add) == 0 )
        	{
        	isFound = 1;n++;
        	gotoxy(x,y++);SetColorAndBackground(34,00);
            printf("%15s | %-25s| %-15s| %-30s| %-20s\n",current->ID,current->name,current->phone_no,current->email,current->add);;
            
        	}
          
        	current=current->next;

    	}
    	if(isFound ==0){
    		SetColorAndBackground(45,00);y++;
       		gotoxy(x,y++);printf("Sorry, No record found in the database!");
     	}
	}
	
	SetColor(45);y++;
    gotoxy(x,y++);printf("Search %s Result >> %d !", s_id, n);
    SetColor(28);y++;y++;
    gotoxy(x,y++);printf("Enter any kye to MAIN MENU!  >>");
    getch();
	window(); 
}


void About(){   //sohan
	clearWindow();
	SetColor(45);
	SetColorAndBackground(57,46);
	int x=55, y=7, t=150, b=11;
	//
	delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
	delay(b);gotoxy(x,y++);printf("                                                      ");
    delay(b);gotoxy(x,y++);printf("                                                      ");
    //
    delay(t);y=7;
    //
	gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("          V     V                   VVV   VVV         ");
	gotoxy(x,y++);printf("        V  V   VV V   V              VVV VVV          ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V               VVVVV           ");
    //
    delay(t);y=7;
    //
	gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("          V     V                   VVV   VVV         ");
	gotoxy(x,y++);printf("        V  V   VV V   V              VVV VVV          ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V               VVVVV           ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV               VVV            ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV                V             ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV                            ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("          V     V                   VVV   VVV         ");
	gotoxy(x,y++);printf("        V  V   VV V   V              VVV VVV          ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V               VVVVV           ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV               VVV            ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV                V             ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV                            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV                           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV            III            ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV             III            ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("          V     V                   VVV   VVV         ");
	gotoxy(x,y++);printf("        V  V   VV V   V              VVV VVV          ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V               VVVVV           ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV               VVV            ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV                V             ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV                            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV                           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV            III            ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV             III            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV              III            ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV              III            ");
    gotoxy(x,y++);printf(" VVVV   o  VVVVV  o   VVVV             III            ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("          V     V                   VVV   VVV         ");
	gotoxy(x,y++);printf("        V  V   VV V   V              VVV VVV          ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V               VVVVV           ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV               VVV            ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV                V             ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV                            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV                           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV            III            ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV             III            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV              III            ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV              III            ");
    gotoxy(x,y++);printf(" VVVV   o  VVVVV  o   VVVV             III            ");
    gotoxy(x,y++);printf("  VVVVV      V      VVVVV                             ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV                                ");
    gotoxy(x,y++);printf("        VVVV   VVVV                 RRRRRRR           ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                   VVV   VVV         ");
	gotoxy(x,y++);printf("        V  V   VV V   V              VVV VVV          ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V               VVVVV           ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV               VVV            ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV                V             ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV                            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV                           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV            III            ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV             III            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV              III            ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV              III            ");
    gotoxy(x,y++);printf(" VVVV   o  VVVVV  o   VVVV             III            ");
    gotoxy(x,y++);printf("  VVVVV      V      VVVVV                             ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV                                ");
    gotoxy(x,y++);printf("        VVVV   VVVV                 RRRRRRR           ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                RRRRRRRR          ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                RRR  RRR          ");
    gotoxy(x,y++);printf("         VV VVV VV                  RRRRRR            ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                      VVV            ");
	gotoxy(x,y++);printf("        V  V   VV V   V                 V             ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V                               ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV                              ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV               III            ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV             III            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV            III            ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV            III            ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV             III            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV                             ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV                             ");
    gotoxy(x,y++);printf(" VVVV      VVVVV      VVVV          RRRRRR            ");
    gotoxy(x,y++);printf("  VVVVV o    V    o VVVVV           RRRRRRR           ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV              RRR  RR           ");
    gotoxy(x,y++);printf("        VVVV   VVVV                 RRRRRR            ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                RRR RR            ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                RRR  RR           ");
    gotoxy(x,y++);printf("         VV VVV VV                                    ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                                     ");
	gotoxy(x,y++);printf("        V  V   VV V   V                III            ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V                III            ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV               III            ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV               III            ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV             III            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV                           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV                           ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV          RRRRRR            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV           RRRRRRR           ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV           RRR  RR           ");
    gotoxy(x,y++);printf(" VVVV      VVVVV      VVVV          RRRRRR            ");
    gotoxy(x,y++);printf("  VVVVVo     V   o  VVVVV           RRR RR            ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV              RRR  RR           ");
    gotoxy(x,y++);printf("        VVVV   VVVV                                   ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                                  ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                   OOO            ");
    gotoxy(x,y++);printf("         VV VVV VV                    OO OO           ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                      III            ");
	gotoxy(x,y++);printf("        V  V   VV V   V                III            ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V                III            ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV                              ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV                              ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV          RRRRRR            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV         RRRRRRR           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV         RRR  RR           ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV          RRRRRR            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV           RRR RR            ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV           RRR  RR           ");
    gotoxy(x,y++);printf(" VVVV  o   VVVVV o    VVVV                            ");
    gotoxy(x,y++);printf("  VVVVV      V      VVVVV                             ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV                 OOO            ");
    gotoxy(x,y++);printf("        VVVV   VVVV                   OO OO           ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                  OO OO           ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                  OO OO           ");
    gotoxy(x,y++);printf("         VV VVV VV                     OOO            ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                                     ");
	gotoxy(x,y++);printf("        V  V   VV V   V                               ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V              RRRRRR           ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV             RRRRRRR          ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV             RRR  RR          ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV           RRRRRR           ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV          RRR RR           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV          RRR  RR          ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV                            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV                             ");
	gotoxy(x,y++);printf(" VV     oVVVVVVVVVo    VV              OOO            ");
    gotoxy(x,y++);printf(" VVVV      VVVVV      VVVV            OO OO           ");
    gotoxy(x,y++);printf("  VVVVV      V      VVVVV             OO OO           ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV                OO OO           ");
    gotoxy(x,y++);printf("        VVVV   VVVV                    OOO            ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                                  ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                                  ");
    gotoxy(x,y++);printf("         VV VVV VV                   UU  UU           ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                   RRR  RR           ");
	gotoxy(x,y++);printf("        V  V   VV V   V             RRRRRR            ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V             RRR RR            ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV            RRR  RR           ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV                              ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV                            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV           OOO             ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV          OO OO            ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV           OO OO            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV            OO OO            ");
	gotoxy(x,y++);printf(" VV     oVVVVVVVVV o   VV             OOO             ");
    gotoxy(x,y++);printf(" VVVV      VVVVV      VVVV                            ");
    gotoxy(x,y++);printf("  VVVVV      V      VVVVV                             ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV              UU  UU            ");
    gotoxy(x,y++);printf("        VVVV   VVVV                 UU  UU            ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                UU  UU            ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                UUUUUU            ");
    gotoxy(x,y++);printf("         VV VVV VV                   UUUU             ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                  RRR  RR            ");
	gotoxy(x,y++);printf("        V  V   VV V   V                               ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V                               ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV             OOO              ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV            OO OO             ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV          OO OO             ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV         OO OO             ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV          OOO              ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV                            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV                             ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV           UU  UU            ");
    gotoxy(x,y++);printf(" VVVV    o VVVVV    o VVVV          UU  UU            ");
    gotoxy(x,y++);printf("  VVVVV      V      VVVVV           UU  UU            ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV              UUUUUU            ");
    gotoxy(x,y++);printf("        VVVV   VVVV                  UUUU             ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                                  ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                                  ");
    gotoxy(x,y++);printf("         VV VVV VV                    SSS             ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("          V     V                    OOO              ");
	gotoxy(x,y++);printf("        V  V   VV V   V             OO OO             ");
    gotoxy(x,y++);printf("    V   V  VV VV  V   V             OO OO             ");
    gotoxy(x,y++);printf("   VV  VV  VV VV  VV  VV            OO OO             ");
	gotoxy(x,y++);printf("  VVVV VVVVV   VVVVV VVV             OOO              ");
    gotoxy(x,y++);printf(" VV VV VVVVVVVVVVVVV VV VV                            ");
    gotoxy(x,y++);printf("VV  VV VVVVVVVVVVVVV VV  VV                           ");
	gotoxy(x,y++);printf("VV VVVVVVVVVVVVVVVVVVVVV VV         UU  UU            ");
    gotoxy(x,y++);printf("VVVVVVVVVVVVVVVVVVVVVVVVVV          UU  UU            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV           UU  UU            ");
	gotoxy(x,y++);printf(" VV      VVVVVVVVV     VV           UUUUUU            ");
    gotoxy(x,y++);printf(" VVVV      VVVVV      VVVV           UUUU             ");
    gotoxy(x,y++);printf("  VVVVV   Q  V     QVVVVV                             ");
	gotoxy(x,y++);printf("     VVVVVVVV VVVVVVVV                                ");
    gotoxy(x,y++);printf("        VVVV   VVVV                   SSSS            ");
    gotoxy(x,y++);printf("       VVVVVVVVVVVVV                 SS   S           ");
	gotoxy(x,y++);printf("       V VVVVVVVVV V                  SSS             ");
    gotoxy(x,y++);printf("         VV VVV VV                  S   SS            ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                  OO OO               ");
	gotoxy(x,y++);printf("                                   OOO                ");
    gotoxy(x,y++);printf("        V  V   V  V                                   ");
    gotoxy(x,y++);printf("    V  VV  V   V  VV  V                               ");
	gotoxy(x,y++);printf("   VVV VVVVV   VVVVV VV            UU  UU             ");
    gotoxy(x,y++);printf("  V VV VVVVVVVVVVVVV VV V          UU  UU             ");
    gotoxy(x,y++);printf(" V  VV VVVVVVVVVVVVV VV  V         UU  UU             ");
	gotoxy(x,y++);printf(" V VVVVVVVVVVVVVVVVVVVVV V         UUUUUU             ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV           UUUU              ");
    gotoxy(x,y++);printf("  VVVVVVVVVVVVVVVVVVVVVV                              ");
	gotoxy(x,y++);printf("  V      VVVVVVVVV     V                              ");
    gotoxy(x,y++);printf("  VVV     QVVVVV    Q VVV            SSSS             ");
    gotoxy(x,y++);printf("   VVVV      V      VVVV            SS   S            ");
	gotoxy(x,y++);printf("      VVVVVVV VVVVVVV                SSS              ");
    gotoxy(x,y++);printf("         VVV   VVV                 S   SS             ");
    gotoxy(x,y++);printf("        VVVVVVVVVVV                 SSSS              ");
	gotoxy(x,y++);printf("         VVVVVVVVV                                    ");
    gotoxy(x,y++);printf("          V VVV V                                     ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                    UU  UU            ");
    gotoxy(x,y++);printf("                                    UU  UU            ");
    gotoxy(x,y++);printf("                                    UU  UU            ");
	gotoxy(x,y++);printf("     V   V V   V  V  V              UUUUUU            ");
    gotoxy(x,y++);printf("    VV VVVVVVVVVVVVV VV              UUUU             ");
    gotoxy(x,y++);printf("    VV VVVVVVVVVVVVV VV                               ");
	gotoxy(x,y++);printf("   VVVVVVVVVVVVVVVVVVVVV                              ");
    gotoxy(x,y++);printf("  VVVVVVVVVVVVVVVVVVVVVV              SSSS            ");
    gotoxy(x,y++);printf(" VVVVVVVVVVVVVVVVVVVVVVVV            SS   S           ");
	gotoxy(x,y++);printf("  V      VVVVVVVVV     V             SSS              ");
    gotoxy(x,y++);printf("   V     QVVVVV    Q V             S   SS             ");
    gotoxy(x,y++);printf("     VV      V      VV              SSSS              ");
	gotoxy(x,y++);printf("       VVVVVV VVVVVV                                  ");
    gotoxy(x,y++);printf("          VV   VV                                     ");
    gotoxy(x,y++);printf("          VVVVVVV                                     ");
	gotoxy(x,y++);printf("           VVVVV                                      ");
    gotoxy(x,y++);printf("            VV                                        ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                    UU  UU            ");
	gotoxy(x,y++);printf("                                    UUUUUU            ");
    gotoxy(x,y++);printf("                                     UUUU             ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("               V                                      ");
    gotoxy(x,y++);printf("     V  VVVVVVVVVVV  V                SSSS            ");
    gotoxy(x,y++);printf("    VV VVVVVVVVVVVVV VV              SS   S           ");
	gotoxy(x,y++);printf("    VVVVVVVVVVVVVVVVVVV               SSS             ");
    gotoxy(x,y++);printf("    VVVVVVVVVVVVVVVVVVV             S   SS            ");
    gotoxy(x,y++);printf("     VVVVVVVVVVVVVVVVV               SSSS             ");
	gotoxy(x,y++);printf("         QVVVVVVVVV Q                                 ");
    gotoxy(x,y++);printf("            VVVVV                                     ");
    gotoxy(x,y++);printf("              V                                       ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                     SSSS             ");
    gotoxy(x,y++);printf("                                    SS   S            ");
	gotoxy(x,y++);printf("        V V     V V                  SSS              ");
    gotoxy(x,y++);printf("       VVVVVV VVVVVV               S   SS             ");
    gotoxy(x,y++);printf("       VVVVV   VVVVV                SSSS              ");
	gotoxy(x,y++);printf("        VVV     VVV                                   ");
    gotoxy(x,y++);printf("         VVV   VVV                                    ");
    gotoxy(x,y++);printf("          VVV VVV                                     ");
	gotoxy(x,y++);printf("           VVVVV                                      ");
    gotoxy(x,y++);printf("            VVV                                       ");
    gotoxy(x,y++);printf("             V                                        ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                    SS                ");
	gotoxy(x,y++);printf("                                     SSS              ");
    gotoxy(x,y++);printf("                                   S   SS             ");
    gotoxy(x,y++);printf("                                    SSSS              ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("             V                                        ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                    SSSS              ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("             V                                        ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("      V                                               ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("V                                                     ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("___                                                   ");
    gotoxy(x,y++);printf("_/                                                    ");
	gotoxy(x,y++);printf("/                                                     ");
    gotoxy(x,y++);printf(":                                                     ");
    gotoxy(x,y++);printf("°:                                                    ");
	gotoxy(x,y++);printf("°°|                                                   ");
    gotoxy(x,y++);printf("°/                                                    ");
    gotoxy(x,y++);printf("/                                                     ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf(";                                                     ");
	gotoxy(x,y++);printf(";;                                                    ");
    gotoxy(x,y++);printf(";                                                     ");
    gotoxy(x,y++);printf("                                                      ");
	gotoxy(x,y++);printf("                                                      ");
    gotoxy(x,y++);printf("                                                      ");
    // 
    delay(t);y=7;
    //
    gotoxy(x,y++);printf(":                                                     ");
	gotoxy(x,y++);printf("_)                                                    ");
    gotoxy(x,y++);printf("_)____                                                ");
    gotoxy(x,y++);printf("_/:_/                                                 ");
	gotoxy(x,y++);printf("¤°_/                                                  ");
    gotoxy(x,y++);printf("¤|]:                                                  ");
    gotoxy(x,y++);printf("¤|]°:                                                 ");
	gotoxy(x,y++);printf("¤|]°°|                                                ");
    gotoxy(x,y++);printf("¤/°°/                                                 ");
    gotoxy(x,y++);printf("/°°/                                                  ");
	gotoxy(x,y++);printf("°°/                                                   ");
    gotoxy(x,y++);printf("°/]                                                   ");
    gotoxy(x,y++);printf("/|];                                                  ");
	gotoxy(x,y++);printf("¤|];;                                                 ");
    gotoxy(x,y++);printf("¤|];                                                  ");
    gotoxy(x,y++);printf("¤//                                                   ");
	gotoxy(x,y++);printf("|/                                                    ");
    gotoxy(x,y++);printf("V                                                     ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("-/:                                                   ");
	gotoxy(x,y++);printf("(__)                                                  ");
    gotoxy(x,y++);printf("(__)____                                              ");
    gotoxy(x,y++);printf("/:_/:_/                                               ");
	gotoxy(x,y++);printf("_°¤°_/                                                ");
    gotoxy(x,y++);printf(";;¤|]:                                                ");
    gotoxy(x,y++);printf(";;¤|]°:                                               ");
	gotoxy(x,y++);printf("[|¤|]°°|                                              ");
    gotoxy(x,y++);printf("[|¤/°°/                                               ");
    gotoxy(x,y++);printf("[|/°°/                                                ");
	gotoxy(x,y++);printf("-/°°/                                                 ");
    gotoxy(x,y++);printf("/°°/]                                                 ");
    gotoxy(x,y++);printf("°°/|];                                                ");
	gotoxy(x,y++);printf("°|¤|];;                                               ");
    gotoxy(x,y++);printf("°|¤|];                                                ");
    gotoxy(x,y++);printf(":|¤//                                                 ");
	gotoxy(x,y++);printf(" :|/                                                  ");
    gotoxy(x,y++);printf("--V                                                   ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("----/:                                                ");
	gotoxy(x,y++);printf("---(__)                                               ");
    gotoxy(x,y++);printf("---(__)____                                           ");
    gotoxy(x,y++);printf("-:_/:_/:_/                                            ");
	gotoxy(x,y++);printf("--:_°¤°_/                                             ");
    gotoxy(x,y++);printf("-;;;;¤|]:                                             ");
    gotoxy(x,y++);printf("--;;;¤|]°:                                            ");
	gotoxy(x,y++);printf("-;;[|¤|]°°|                                           ");
    gotoxy(x,y++);printf("--;[|¤/°°/                                            ");
    gotoxy(x,y++);printf("---[|/°°/                                             ");
	gotoxy(x,y++);printf("----/°°/                                              ");
    gotoxy(x,y++);printf("---/°°/]                                              ");
    gotoxy(x,y++);printf("--/°°/|];                                             ");
	gotoxy(x,y++);printf("-|°°|¤|];;                                            ");
    gotoxy(x,y++);printf("--:°|¤|];                                             ");
    gotoxy(x,y++);printf("---:|¤//                                              ");
	gotoxy(x,y++);printf("--- :|/                                               ");
    gotoxy(x,y++);printf("-----V                                                ");
    //
    delay(t);y=7;
    //
    gotoxy(x,y++);printf("----/:                                                ");
	gotoxy(x,y++);printf("---(__)                                               ");
    gotoxy(x,y++);printf("---(__)____                                           ");
    gotoxy(x,y++);printf("-:_/:_/:_/                                            ");
	gotoxy(x,y++);printf("--:_°¤°_/                                             ");
    gotoxy(x,y++);printf("-;;;;¤|]:                                             ");
    gotoxy(x,y++);printf("--;;;¤|]°:                                            ");
	gotoxy(x,y++);printf("-;;[|¤|]°°|                                           ");
    gotoxy(x,y++);printf("--;[|¤/°°/                                            ");
    gotoxy(x,y++);printf("---[|/°°/                                             ");
	gotoxy(x,y++);printf("----/°°/                                              ");
    gotoxy(x,y++);printf("---/°°/]                                              ");
    gotoxy(x,y++);printf("--/°°/|];                                             ");
	gotoxy(x,y++);printf("-|°°|¤|];;                                            ");
    gotoxy(x,y++);printf("--:°|¤|];                                             ");
    gotoxy(x,y++);printf("---:|¤//                                              ");
	gotoxy(x,y++);printf("--- :|/                                               ");
    gotoxy(x,y++);printf("-----V                                                ");
    
    //
    int s=0;
    char head[]="<STUDENT RECORD SYSTEM>";
    char munni[]="@ Rahima Akter Munni>>";
    char rajani[]="@ Sadia Afrin Rajani>>";
    char fahim[]="@ Md. Fahim Ahmed>>";
    char sohan[]="@ S. M. Sohan>>";
    char monskb[]="@ Monsakib Rahaman>>";
    
	char wmunni[]="# Project 'LRADER'!";
    char wrajani[]="# Project 'MANAGER'!";
    char wfahim[]="# Project 'PROGRAMMER'!";
    char wsohan[]="# 'EDITOR' and 'DESIGNER'!";
    char wmonskb[]="# 'PROGRAMMER'!";
    
    gotoxy(75,8);SetColorAndBackground(00,28);
    for( s=0; s<strlen(head); s++)
    {
        delay(20);
        printf("%c",head[s]);
    }
    y=10,t=50;
    gotoxy(70,y++);SetColorAndBackground(00,46);
    for( s=0; s<strlen(munni); s++)
    {
        delay(t);
        printf("%c",munni[s]);
    }
    gotoxy(80,y++);SetColorAndBackground(28,46);
    for( s=0; s<strlen(wmunni); s++)
    {
        delay(t);
        printf("%c",wmunni[s]);
    }y++;
    gotoxy(70,y++);SetColorAndBackground(00,46);
    for( s=0; s<strlen(rajani); s++)
    {
        delay(t);
        printf("%c",rajani[s]);
    }
    gotoxy(80,y++);SetColorAndBackground(28,46);
    for( s=0; s<strlen(wrajani); s++)
    {
        delay(t);
        printf("%c",wrajani[s]);
    }y++;
    gotoxy(70,y++);SetColorAndBackground(00,46);
    for( s=0; s<strlen(fahim); s++)
    {
        delay(t);
        printf("%c",fahim[s]);
    }
    gotoxy(80,y++);SetColorAndBackground(28,46);
    for( s=0; s<strlen(wfahim); s++)
    {
        delay(t);
        printf("%c",wfahim[s]);
    }y++;
    gotoxy(70,y++);SetColorAndBackground(00,46);
    for( s=0; s<strlen(sohan); s++)
    {
        delay(t);
        printf("%c",sohan[s]);
    }
    gotoxy(80,y++);SetColorAndBackground(28,46);
    for( s=0; s<strlen(wsohan); s++)
    {
        delay(t);
        printf("%c",wsohan[s]);
    }y++;
    gotoxy(70,y++);SetColorAndBackground(00,46);
    for( s=0; s<strlen(monskb); s++)
    {
        delay(t);
        printf("%c",monskb[s]);
    }
    gotoxy(80,y++);SetColorAndBackground(28,46);
    for( s=0; s<strlen(wmonskb); s++)
    {
        delay(t);
        printf("%c",wmonskb[s]);
    }
  
    SetColorAndBackground(22,00);
    SetColor(45);
		
}


