//Group:R3A
//Assignment No.4: Simple version Control

/*
	We have used a single file to store all the versions.
	Data structure linked list containing version number(versionno),
	data,linecount(lcnt) is used to store details of each version.
	Each node represents each version.
	$ symbol is used to distinguish each version.

	copylatest(): It is used to copy the contents of latest version
	before appending a newline or deleting a line from a version.

	append():It is used to append a line at the end of file.

	displast():It is used to display the latest version.

	del():It is used to delete a line specified in the command.

	save():It is used to save the file whose filename is specified.

	disp():It is used to display the Nth version of file.
*/


#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#define MAX 20

fstream fp,fpcopy;
char filename[20];

class node
{
   int versionno;
   char data[20][10];
   int lcnt;      		//maximum number of lines

   node * next;

   public:
		node()
		{
			next=NULL;
			lcnt=0;
		}

		friend class version;
};

class version
{
   node *head;
   int newflag;     //1 when file is to be created

   public:
		version()
		{
			head=new node;
			head->versionno=-1;
			newflag=0;
		}

		void disp(int);
		void read();
		void append(char []);
		void dispall();
		void saveversion(char *);
		void copylatest();
		void del(int);
		void save();
		void displast();
};

void version::save()
{
   node *move;
   move=head;


   while(move->next!=NULL)
   {
	move=move->next;	//last node
   }

   fp.open(filename,ios::app);

   int  i=0;

   do
   {
	fp<<move->data[i]<<"\n";
	i++;
   }while(i<move->lcnt);

   cout<<"\n\nFile saved!";

   fp.close();
}

void version::copylatest()
{
   node * move,*prev;

   if(newflag==1)
   {
		head->next=new node;
		move=head->next;
		move->versionno=0;
		strcpy(move->data[move->lcnt++],"$");
		newflag=0;
   }

   else
   {
		move=head->next;          //version 0

		while(move->next!=NULL)
		{
			move=move->next;
		}
		move->next=new node;
		prev=move;               //prev latest
		move=move->next;         //new copy

		move->versionno=prev->versionno + 1;
		move->lcnt=prev->lcnt;

		char *temp=new char(MAX);
		char temp2[5];
		strcpy(temp,"$ ");

		strcpy(move->data[0],temp);

		for(int i=1;i<prev->lcnt;i++)
		{
			  strcpy(move->data[i],prev->data[i]);
		}
   }
}

void version::del(int n)   //line number to be deleted from latest version
{
    node * move;
    move=head;       //version 0

    while(move->next!=NULL)
    {
	move=move->next;		//last node in the list
    }

    if(n>=move->lcnt)
    {
	cout<<"\n\t Line doesnt exist!!";
    }

    int i=n,j=n+1;           //n=index starting from 0
    while(i<move->lcnt)
    {
      strcpy(move->data[i++],move->data[j++]);
    }

    move->lcnt--;

    cout<<"Line "<<n <<" deleted successfully!"<<endl;
}

void version::append(char arr[])
{
    node * move;
    move=head;

    while(move->next!=NULL)
    {
	move=move->next;		 //last node in the list
    }

    if(move->lcnt==20)
    {
	cout<<"\n***No Empty Space..\nData can't be appended!\n";
    }
    else
    {
      int cnt=0,i,j;
      char line[MAX];

      do
      {
			j=0;
			strcpy(line,'\0');
			for(i=cnt;i<cnt+9;i++)
			{
			    if(arr[i]=='\n')
					break;
			    line[j++]=arr[i];
			}
			line[j]='\0';
			strcpy(move->data[move->lcnt++],line);
			cnt=i;

      }while(cnt<=strlen(arr));

      cout<<"\nLine appended successfully!"<<endl;
   }
}

void version::dispall()
{
   node * move;
   move=head->next;
   int i;

   while(move!=NULL)
   {
       i=1;
       do
       {

		cout<<"\n"<<move->data[i];
		i++;
       }while(i<move->lcnt);

       move=move->next;
       cout<<"\n\n";
  }
}

void version::displast()
{
   node * move;
   move=head;
   int i;

   cout<<"\n\nThe file is:\n";

   while(move->next!=NULL)
   {
      move=move->next;
   }

   i=1;
   do
   {
	cout<<"\n"<<move->data[i];
	i++;
   }while(i<move->lcnt);
}

void version::read()        //store versions in a linklist
{
   char line[MAX];
   node *move;
   move=head;
   int cnt=0;


   fp.open(filename,ios::in);

   if(fp==NULL)
   {
	cout<<"\nFile does not exist";
	cout<<"\nDo you want to create a new file? Enter (Yes=1/No=0):  ";
	cin>> newflag;
   }
   else
   {
	int lineindex;
	char key1[10],key2[10],key3[10],key4[10];

	while(!fp.eof())
	{
		fp.getline(line,15);
		sscanf(line,"%s%s%s%s",key1,key2,key3,key4);

		if(key1[0]=='$')
		{
			move->next=new node;
			move=move->next;
			move->versionno=cnt++;
		}

		strcpy(move->data[move->lcnt],line);
		move->lcnt++;
	}
   }
   fp.close();
}

void version::disp(int vno)
{
   int i=0,cnt=0;
   node * move,*temp;

   move=head;
   move=move->next;
   temp=head;
   temp=temp->next;

   while(temp->next!=NULL)
   {
	temp=temp->next;
	cnt++;
   }
   if(vno>cnt)
   {
	cout<<"\n\t Version "<<vno<<" doesnt exist.";
	return;
   }
   while(i<vno)
   {
	move=move->next;
	i++;
   }

   i=1;
   cout<<"\nVersion Number"<<vno<<": \n";

   do
   {
      cout<<"\n"<<move->data[i];
      i++;
   }while(i<move->lcnt);
}


int main()
{
	clrscr();
	char input[MAX],command[MAX],data[MAX],command1[MAX],data1[MAX];
	int choice=0,i=0,j=0,k=0;

	version v;

	cout<<"\nEnter the filename with extension:  ";
	cin>>filename;

	for(i=0;i<strlen(filename);i++)
	{
		filename[i]=toupper(filename[i]);
	}

	v.read();


	cout<<"\n\n\t NOTE\
		\n\t Use the command 'append' to add new line\
		\n\t Use the command 'delete' to delete a line\
		\n\t Use the command 'svc filename' to commit\
		\n\t Use the command 'svc N' to retreive Nth record\
		\n\t Use the command 'exit' to terminate";

	do
	{
		label:
		i=0;
		j=0;

		cout<<"\n\nCommand:\> ";
		fflush(stdin);
		gets(input);

		strcpy(command,'\0');
		strcpy(data,'\0');

		while(input[i]!='\0')
		{
			if(input[i]==' ')
			{
				break;
			}
			command[j]=input[i];
			i++;j++;
		}
		command[j]='\0';

		for(int z=0;z<strlen(command);z++)
		{
			command[z]=tolower(command[z]);
		}

		i++;
		k=0;

		while(input[i]!='\0' && input[i]!='\n')
		{
			data[k]=input[i];
			i++;k++;
		}
		data[k]='\0';

		//cout<<"\n\t\t**"<<command<<" "<<data;

		if(strcmp(command,"append")==0)
			choice=1;
		else if(strcmp(command,"delete")==0)
			choice=2;
		else if(strcmp(command,"svc")==0)
		{
			if((data[1])>=0 && (data[1])<=9)	//Nth record
				choice=4;
			else
				choice=3;
		}
		else if(strcmp(command,"exit")==0)
		{
			choice=0;
		}
		else
		{
			cout<<"\n\n\t Illegal command!!";
			goto label;
		}

		switch(choice)
		{

			case 0: //To terminate
			break;
			case 1://To append line in latest file version
					v.copylatest();
					v.append(data);
					v.displast();
			break;
			case 2://To delete line from latest file version
					v.copylatest();
					v.del(atoi(data));
					v.displast();
			break;
			case 3://To save the file whose filename is specified
					v.save();
			break;
			case 4://To display Nth version of file
					v.disp(atoi(data));
			break;
			default:
					cout<<"\n\n\t Illegal command!!";
		}

		strcpy(input,'\0');
		strcpy(command,'\0');
		strcpy(data,'\0');

		i=j=k=0;

	}while(choice!=0);

	getch();
	return 0;
}