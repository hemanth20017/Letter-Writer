#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
void Registeration();
void Registeration()
{
    char *username,*password;
    int indexreader=0;

    printf("\t\t\t\tREGISTRATION \n\n\t------------------------------------------------------------------------------\n\n");
    printf("\n\t\tPLEASE ENTER THE USERNAME   :\t");

    username=(char*)malloc(20*sizeof(char));
    scanf("%s",username);

    printf("\n\t\tPLEASE ENTER THE PASSWORD (PASSWORD MIN LENGTH SHOULD BE =8)   :\t");
    password=(char*)malloc(20*sizeof(char));

    while(1)
    {
        fflush(stdin);
        password[indexreader]=getch();
        if(password[indexreader]=='\r')//the getch() return \r value instead of \n when we give enter /r represents line break
        {
            break;
        }
        else
        {
            printf("*");
            indexreader++;
        }
    }

   password[indexreader]='\0';

   FILE *fp;

   fp=fopen("Loginfo.txt","a");
   fprintf(fp,"%s\n",username);
   fprintf(fp,"%s\n",password);
   system("cls");//Clear screen

   fclose(fp);
}

bool validateuserdetails(char *username_given,char *password_given);
bool validateuserdetails(char *username_given,char *password_given)
{
    FILE *fp;
    char *inp;
    fp=fopen("Loginfo.txt","r");
    int endoffile;
    fseek(fp,0,2);
    endoffile=ftell(fp);
    fseek(fp,0,0);
     while(ftell(fp)!=endoffile)
    {
        inp=(char*)malloc(20*sizeof(char));
        fscanf(fp, "%s",inp);
        if((strcmp(inp,username_given))==0)//check the username
        {
            fflush(stdin);
            fscanf(fp, "%s",inp);
            //inp=(char*)malloc(20*sizeof(char));
            if ((strcmp(inp,password_given))==0)//check password
            {
                printf("\n\t\tLOGIN SUCCESS\n");
                fclose(fp);
                system("cls");
                return true;
            }
        }
        free(inp);
    }
    printf("\n\t\tLOGIN UNSUCCESSFUL\n");
    fclose(fp);
    system("cls");
    return false;
}


bool  login();//Login desk

bool  login()
{
    int indexreader=0;
    char bufferchar;

    char *username,*password;

    printf("\t\t\t\tLOGIN\n\t\t------------------------------------------------");
    printf("\n\t\t\tPROVIDE USERNAME\t:\t");

    username=(char*)malloc(20*sizeof(char));
    scanf("%s",username);

    printf("\t\t\tPROVIDE YOUR REGISTERD PASSWORD\t:\t");
    password=(char*)malloc(25*sizeof(char));

    while(1)//while loop runs an infinite loop until the user hits "Enter" key
    {
        fflush(stdin);
        if((bufferchar=getch())=='\r')//the getch() return \r value instead of \n when hit "Enter" key
        {
            break;
        }
        else
        {
            password[indexreader]=bufferchar;
            printf("*");
            indexreader++;
        }
        password[indexreader]='\0';
    }
    return validateuserdetails(username,password);
}


int templateSelector();
int templateSelector()
{
    int result1;
    printf("\t\t1-LEAVE LETTER(from parent to principal of school)\n\t\t\t2-LETTER OF RECOMENDATION\n\t\t\t3-LETTER OF RESIGNATION\n\t\t\t4-INTERVIEW FOLLOWUP LETTER\n\t\t\t5-LEAVE LETTER(official like a subordinate to boss)\n\t\t\t");
    printf("YOUR CHOICE : \t");
    scanf("%d",&result1);
    system("cls");
    return result1;
}


char* inputgetter();//input getter function common for almost types of input
char* inputgetter()
{
	char *input;
	input=(char*)malloc(200*sizeof(char));
	gets(input);
	return input;
}
bool validatePhoneNumber(char *phoneNumber);//phone number checker
bool validatePhoneNumber(char *phoneNumber)
{
    int index=0;
    bool validPhoneNumber;

    validPhoneNumber = false;

    if(strlen(phoneNumber)==10)
    {
       while(index<(strlen(phoneNumber)-1))
       {
             if(isdigit(phoneNumber[index]))
             {
                  validPhoneNumber = true;
                  index++;
             }
             else
             {
                 validPhoneNumber = false;
                 return validPhoneNumber;
             }
       }
    }
    return validPhoneNumber;
}

char* gender_Principal();//some letters reqire special addreressing of the person incharge like principle mangager
char* gender_Principal()
{
	char *add;
	add=(char*)malloc(40*sizeof(char));
	scanf("%s",add);
	if (strcmp("male",add)==0)
	{
		return "Sir";
	}
	else
	{
		return "Mam";
	}
}
void Leave();//Leave letter compiler code
void Leave()
{
	FILE *fp1,*fp2;
	int arr1[20],arr2[20],i=0,j=0,k;
	//c is buffer char and path is the path specified for positioning the file;
	char c,path[100]="D:\\projectfile_taker\\Finalfiles_Reciever\\",filename[40];
	fflush(stdin);
	//taking the file name which the user want to save
	printf("\t\t\t\tLEAVE LETTER\n\n\t------------------------------------------------------------------------------\n\n");
    printf("\t\tPLEASE GIVE THE FILE NAME YOU WANT TO SAVE THE FINAL .TXT FILE WITH\n\t\tYOUR CHOICE :\t ");
	gets(filename);
	strcat(filename,".txt");
	strcat(path,filename);

//	printf("%s",openpath);
	fp1=fopen("LeaveLetter.txt","r");
	fp2=fopen(path,"w");
	//first getting the blank positions in the template LeaveLetter the positions of the ( and ) braces
	while((c=fgetc(fp1))!=EOF)
	{
		if (c=='(')
		{
			arr1[i]=ftell(fp1);
			i++;
		}
		if(c==')')
		{
			arr2[j]=ftell(fp1);
			j++;
		}
	}
	fseek(fp1,0,0);
	i=1;
	j=0;
	//now inputting the text read from the user and putting in the file in the correct position sequentialy
	//the inputs are taken accordingly
	while((c=fgetc(fp1))!=EOF)
	{
		int flag=0;
		if((ftell(fp1)>=arr1[i-1]) && (ftell(fp1)<=arr2[i-1]))
		{
			if (flag==0)
			{
				if(i==1)
				{
					fflush(stdin);
					printf("\n\t\tPlease give your address starting house-no\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give the locality please give ',' at the end\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give the area surrounding the locality or nearest city please give ',' at the end\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==2)
				{
					printf("\n\t\tPlease give today's date in dd/mm/yyyy format\n\t\t");
					fflush(stdin);
					fprintf(fp2,inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==3)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the school name\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give the locality of the school and please give ',' at the end\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give the address regarding the nearest city from the school please give ',' at the end\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==4)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the gender of the principal(male/female)\n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",gender_Principal());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==5)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the name of your ward\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==6)
				{
					printf("\n\t\tPlease give the section your ward studies in\n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==7)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the reason for this leave letter\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==8)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the no of leaves you intended to take\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==9)
				{
					fflush(stdin);
					printf("\n\t\tPlease mention who is writing this letter\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
			}
		}
		else
		{
			fputc(c,fp2);
		}
	}
	printf("\n\t\t\tTHIS IS THE END OF QUESTION PROMPT PART\n");

	system("cls");
	fclose(fp1);
	fclose(fp2);
	system(path);

}
//same format is followed for the different letters
void recommend();
void recommend()
{
	FILE *fp1,*fp2;
	int arr1[20],arr2[20],i=0,j=0,k;
	char *name;
	name=(char*)malloc(20*sizeof(char));
	//c is buffer char and path is the path specified for positioning the file;
	char c,path[100]="D:\\projectfile_taker\\Finalfiles_Reciever\\",filename[40];
	fflush(stdin);
	printf("\t\t\tRECOMENDATION LETTER\n\t\t\n\n\t------------------------------------------------------------------------------\n\n");
    printf("\t\t GIVE THE  FILE NAME YOU WANT TO SAVE THE FINAL .TXT FILE WITH\n\t\tYOUR CHOICE  :\t");
	gets(filename);
	strcat(filename,".txt");
	strcat(path,filename);
	fp1=fopen("recommendationletter.txt","r");
	fp2=fopen(path,"w");
	while((c=fgetc(fp1))!=EOF)
	{
		if (c=='(')
		{
			arr1[i]=ftell(fp1);
			i++;
		}
		if(c==')')
		{
			arr2[j]=ftell(fp1);
			j++;
		}
	}
	fseek(fp1,0,0);
	i=1;
	j=0;
	while((c=fgetc(fp1))!=EOF)
	{
		int flag=0;
		if((ftell(fp1)>=arr1[i-1]) && (ftell(fp1)<=arr2[i-1]))
		{
			if (flag==0)
			{
				if(i==1)
				{
					fflush(stdin);
					printf("\t\tPlease give today's date in dd/mm/yyyy format\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==2)
				{
					fflush(stdin);
					printf("\n\t\tPlease mention the name of company that you want to address\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give its location and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease mention the nearest city to that place and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==3)
				{
					fflush(stdin);
					printf("\n\t\tPlease give name of employee you want to recommend\n\t\t");
					fflush(stdin);
					name=inputgetter();
					fprintf(fp2,"%s",name);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==4)
				{
					fflush(stdin);
					printf("\n\t\tPlease mention his work period in your company\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==5)
				{
					printf("\n\t\tPlease give the current position that employee holds \n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==6)
				{
					fflush(stdin);
					//printf("\n\t\tPlease give name of the recommended employee\n\t\t");
					fprintf(fp2,"%s",name);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==7)
				{
					fflush(stdin);
					printf("\n\t\tPlease mention the name of your company\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
			}
		}
		else
		{
			fputc(c,fp2);
		}
	}
	printf("\n\t\tTHIS IS THE END OF QUESTION PROMPT PART\n");
	fclose(fp1);
	fclose(fp2);
	system("cls");
	system(path);
}
void resign();
void resign()
{
	FILE *fp1,*fp2;
	char *company;
	company=(char*)malloc(20*sizeof(char));
	int arr1[20],arr2[20],i=0,j=0,k;
	char c,path[100]="D:\\projectfile_taker\\Finalfiles_Reciever\\",filename[40];//c is buffer char and path is the path specified for positioning the file;
	fflush(stdin);
	printf("\t\t\tRESIGNATION LETTER\n\t\t\n\n\t------------------------------------------------------------------------------\n\n");
    printf("\t\tPLEASE GIVE THE FILE NAME YOU WANT TO SAVE THE FINAL .TXT FILE WITH\n\t\tYOUR CHOICE :\t ");
	gets(filename);
	strcat(filename,".txt");
	strcat(path,filename);
	fp1=fopen("resignation.txt","r");
	fp2=fopen(path,"w");
	while((c=fgetc(fp1))!=EOF)
	{
		if (c=='(')
		{
			arr1[i]=ftell(fp1);
			i++;
		}
		if(c==')')
		{
			arr2[j]=ftell(fp1);
			j++;
		}
	}
	fseek(fp1,0,0);
	i=1;
	j=0;
	while((c=fgetc(fp1))!=EOF)
	{
		int flag=0;
		if((ftell(fp1)>=arr1[i-1]) && (ftell(fp1)<=arr2[i-1]))
		{
			if (flag==0)
			{
				if(i==1)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the name of person in charge of receiving this letter\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==2)
				{
					fflush(stdin);
					printf("\n\t\tPlease mention the position of the person whoom you are addressing through this letter\n\t\t");
					fprintf(fp2,inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==3)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the name of the company you previously worked with(the company you are resigning now)\n\t\t");
					company=inputgetter();
					fprintf(fp2,"%s",company);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==4)
				{
					fflush(stdin);
					printf("\n\t\tPlease enter the date in dd/mm/yyyy format\n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==5)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the name through which you want to address the person in charge\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==6)
				{
					printf("\n\t\tPlease give the designation of the job you previously worked\n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==7)
				{
					fflush(stdin);
					//printf("\n\t\tPlease give company  name again\n\t");
					fprintf(fp2,"%s",company);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==8)
				{
					fflush(stdin);
					printf("\n\t\tPlease give tenure of work period here in the old company\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==9)
				{
					fflush(stdin);
					printf("\n\t\tPlease give your name\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==10)
				{
					fflush(stdin);
					printf("\n\t\tPlease give your mail-id\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
			}
		}
		else
		{
			fputc(c,fp2);
		}
	}
	printf("\n\t\tTHIS IS THE END OF QUESTION PROMPT PART\n");
	fclose(fp1);
	fclose(fp2);
	system("cls");
	system(path);
}
void follow();
void follow()
{
	FILE *fp1,*fp2;
	int arr1[20],arr2[20],i=0,j=0,k;
	char c,path[100]="D:\\projectfile_taker\\Finalfiles_Reciever\\",filename[40];//c is buffer char and path is the path specified for positioning the file;
	fflush(stdin);
	char *phoneno,*name,*company,*phoneno2;
	company=(char*)malloc(20*sizeof(char));
	name=(char*)malloc(20*sizeof(char));
	printf("\t\t\tINTERVIEW FOLLOWUP LETTER\n\t\t\n\n\t------------------------------------------------------------------------------\n\n");
    printf("\t\tPLEASE GIVE THE FILE NAME YOU WANT TO SAVE THE FINAL .TXT FILE WITH\n\t\tYOUR CHOICE :\t ");
	gets(filename);
	strcat(filename,".txt");
	strcat(path,filename);
	fp1=fopen("Follow.txt","r");
	fp2=fopen(path,"w");
	while((c=fgetc(fp1))!=EOF)
	{
		if (c=='(')
		{
			arr1[i]=ftell(fp1);
			i++;
		}
		if(c==')')
		{
			arr2[j]=ftell(fp1);
			j++;
		}
	}
	fseek(fp1,0,0);
	i=1;
	j=0;
	while((c=fgetc(fp1))!=EOF)
	{
		int flag=0;
		if((ftell(fp1)>=arr1[i-1]) && (ftell(fp1)<=arr2[i-1]))
		{
			if (flag==0)
			{
				if(i==1)
				{
					fflush(stdin);
					printf("\n\t\tPlease give your name\n\t\t");
					name=inputgetter();
					fprintf(fp2,"%s",name);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==2)
				{
					fflush(stdin);
					printf("\n\t\tPlease your address start with house-no\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give its location and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease mention the nearest city to that place and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==3)
				{
                        phoneno=(char*)malloc(20*sizeof(char));
                        phoneno2=(char*)malloc(20*sizeof(char));
                        fflush(stdin);
                        printf("\n\t\tPlease give your Phone number\n\t\t");
                        phoneno=inputgetter();
                        fflush(stdin);
                        if (validatePhoneNumber(phoneno))
                        {
                            fprintf(fp2,"%s",phoneno);
                            fseek(fp1,arr2[i-1]+1,0);
                            i++;
                        }
                        else
                        {
                            printf("\n\t\tTHE GIVEN PHONE NUMBER IS INVALID PLEASE TRY AGAIN AND THIS IS THE FINAL CHANCE TO GET IT RIGHT\n\t\t");
                            phoneno2=inputgetter();
                            fprintf(fp2,"%s",phoneno2);
                            fseek(fp1,arr2[i-1]+1,0);
                            i++;
                        }

				}
				else if(i==4)
				{
					fflush(stdin);
					printf("\n\t\tPlease give your gmail Id\n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==5)
				{
					fflush(stdin);
					printf("\n\t\tPlease give todays date\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==6)
				{
					printf("\n\t\tPlease give the name the reciever\n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==7)
				{
					fflush(stdin);
					printf("\n\t\tPlease mention his position\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==8)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the company's name\n\t\t");
					company=inputgetter();
					fprintf(fp2,"%s",company);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==9)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the company's address start from its exact location\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give its location and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease mention the nearest city to that place and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==10)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the recipient name in a way you want to address like Mr./Ms.lastname\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==11)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the position you applied\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==12)
				{
					fflush(stdin);
					//printf("\n\t\tPlease give the name of the company you applied\n\t\t");
					fprintf(fp2,"%s",company);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==13)
				{
					fflush(stdin);
					//printf("\n\t\tPlease give your phone number again\n\t\t");
					fprintf(fp2,"%s",phoneno2);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==14)
				{
					fflush(stdin);
					//printf("\n\t\tPlease give your name again\n\t\t");
					fprintf(fp2,"%s",name);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
			}
		}
		else
		{
			fputc(c,fp2);
		}
	}
	printf("\n\t\tTHIS IS THE END OF QUESTION PROMPT PART\n");
	fclose(fp1);
	fclose(fp2);
	system("cls");
	system(path);
}
void leave2();
void leave2()
{
	FILE *fp1,*fp2;
	char *name;
	name=(char*)malloc(20*sizeof(char));
	int arr1[20],arr2[20],i=0,j=0,k;
	char c,path[100]="D:\\projectfile_taker\\Finalfiles_Reciever\\",filename[40];//c is buffer char and path is the path specified for positioning the file;
	fflush(stdin);
	printf("\t\tLEAVE LETTER(OFFICIAL)\n\t\tPLEASE GIVE THE FILE NAME YOU WANT TO SAVE THE FINAL .TXT FILE WITH\n\t\tYOUR CHOICE :\t ");
	gets(filename);
	strcat(filename,".txt");
	strcat(path,filename);
	fp1=fopen("formalleave.txt","r");
	fp2=fopen(path,"w");
	while((c=fgetc(fp1))!=EOF)
	{
		if (c=='(')
		{
			arr1[i]=ftell(fp1);
			i++;
		}
		if(c==')')
		{
			arr2[j]=ftell(fp1);
			j++;
		}
	}
	fseek(fp1,0,0);
	i=1;
	j=0;
	while((c=fgetc(fp1))!=EOF)
	{
		int flag=0;
		if((ftell(fp1)>=arr1[i-1]) && (ftell(fp1)<=arr2[i-1]))
		{
			if (flag==0)
			{
				if(i==1)
				{
					fflush(stdin);
					printf("\n\t\tPlease give your name\n\t\t");
					name=inputgetter();
					fprintf(fp2,"%s",name);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==2)
				{
					fflush(stdin);
					printf("\n\t\tPlease your address start with house-no\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give its location and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease mention the nearest city to that place and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if (i==3)
				{
				    fflush(stdin);
					 char *phoneno2,*phoneno;
                        phoneno=(char*)malloc(20*sizeof(char));
                        phoneno2=(char*)malloc(20*sizeof(char));
                        fflush(stdin);
                        printf("\n\t\tPlease give your Phone number\n\t\t");
                        phoneno=inputgetter();
                        fflush(stdin);
                        if (validatePhoneNumber(phoneno))
                        {
                            printf("k\n");
                            fprintf(fp2,"%s",phoneno);
                            fseek(fp1,arr2[i-1]+1,0);
                            i++;
                        }
                        else
                        {
                            printf("\n\t\tTHE GIVEN PHONE NUMBER IS INVALID PLEASE TRY AGAIN AND THIS IS THE FINAL CHANCE TO GET IT RIGHT\n\t\t");
                            phoneno2=inputgetter();
                            fprintf(fp2,"%s",phoneno2);
                            fseek(fp1,arr2[i-1]+1,0);
                            i++;
                        }
				}
				else if(i==4)
				{
					fflush(stdin);
					printf("\n\t\tPlease give your gmail Id\n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==5)
				{
					fflush(stdin);
					printf("\n\t\tPlease give todays date\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==6)
				{
					printf("\n\t\tPlease give the name the of the superviser who handles this request \n\t\t");
					fflush(stdin);
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==7)
				{
					fflush(stdin);
					printf("\n\t\tPlease mention his position\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==8)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the company's name\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==9)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the company's address\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease give its location and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fflush(stdin);
					printf("\n\t\tPlease mention the nearest city to that place and give a ','at the end of this statement\n\t\t");
					fprintf(fp2,"%s\n",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==10)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the superviser's name in a way you address him/her Mr. /Ms. lastname\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==11)
				{
					fflush(stdin);
					printf("\n\t\tPlease give start date of leave you want to apply\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==12)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the end date of that leave\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==13)
				{
					fflush(stdin);
					printf("\n\t\tPlease give the reason for your leave\n\t\t");
					fprintf(fp2,"%s",inputgetter());
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
				else if(i==14)
				{
					fflush(stdin);
					//printf("\n\t\tPlease give your name again\n\t\t");
					fprintf(fp2,"%s",name);
					fseek(fp1,arr2[i-1]+1,0);
					i++;
				}
			}
		}
		else
		{
			fputc(c,fp2);
		}
	}
	printf("\n\t\tTHIS IS THE END OF QUESTION PROMPT PART\n");
	fclose(fp1);
	fclose(fp2);
	system("cls");
	system(path);
}
int main()
{
    int i,j,choice1,choice2;
    bool isloginsuccuss;

    /*
    -----------------------------------------------------------------------
    Welcome screen. Program starts here.
    User will start the execution by making a choice for Registration, or Login
    -----------------------------------------------------------------------
    */
    printf("\t\t       WELCOME TO THE LETTER WRITER PROGRAM");
    printf("\n\t\t      a solution for letter writing ");
    printf("\n\t\t ---------------------------------------------------");
    printf("\n\n\t\t Make a choice \t\t 1-REGISTER \t\t 2-LOGIN\n\n\t\tYOUR CHOICE : \t ");
    scanf("%d",&choice1);
    system("cls");
    if (choice1==1)
    {
        Registeration();
        isloginsuccuss=true;
    }
    else
    {
        isloginsuccuss=login();

    }
    if(isloginsuccuss)
    {
        printf("\n\t\tPLEASE CHOOSE A TEMPLATE\n\t");
        choice2=templateSelector();
        switch(choice2)
        {
        case 1:
            {
                Leave();
                break;
            }
        case 2:
            {
                recommend();
                break;
            }
        case 3:
            {
                resign();
                break;
            }
        case 4:
            {
                follow();
                break;
            }
        case 5:
            {
                leave2();
                break;
            }
        default:
            {
                break;
            }
        }
        printf("\t\tYOUR .TXT FILE HAVING THE COMPLETE LETTER WILL BE DISPLAYED IN | D-DRIVE | IN FOLDER |   Finalfiles_Reciever | which is in | projectfile_taker | FOLDER\n");

    }
    else{
        printf("\n\t\t\tTHE LOGIN WAS UNSUCCESSFUL SO PLEASE TRY AGAIN\n");
        printf("\t\t------------------------------------------------------------\n");
    }
     printf("\t\tIF YOU HAVE ANY COMMENTS REGARDING THE TEMPLATES USED OR THE PROCESS PLEASE ENTER 1 ELSE GIVE 0\n\t\t");
     int comment_taker;
     scanf("%d",&comment_taker);
     if (comment_taker)
     {
          FILE *fp2;
          char* comment;
          comment=(char*)malloc(100*sizeof(char));
          fp2=fopen("Comments.txt","a");
          printf("\t\t\tPLEASE GIVE YOUR COMMENTS HERE AS SINGLE LINE \n\t\t");
          fflush(stdin);
          fprintf(fp2,"%s\n",inputgetter());
     }
     printf("\t\t\tTHANKS FOR TRYING THIS SOLUTION\n");
    return 0;
}

