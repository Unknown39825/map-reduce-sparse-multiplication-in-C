#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#define matsize 55 // max matrix will be 25 x 25
#define size1 100//taking input for Dpart where the element stored row wise
#define size2 matsize*8//size of key value pair string mapped;
#define sizenum 50 // size of integer for string conversion .
#define max_size matsize*matsize*matsize*2//size for the no of mapped string.
#define sizesparse matsize*matsize



struct pair//pair used for key value combination
{
    int key[2];
    int value[3];
};

struct term//sparse matrix
{
    int row;
    int col;
    int val;

};
int COL;//col used to store final col
int ROW;//final row
int COM;//common row

void sparsein(struct term a[])//take input in sparse form;
{


    int pos=1,cnt;
    start:
        fflush(stdin);
    printf("Enter the no of row and column: ");
    scanf("%d%d",&a[0].row,&a[0].col);
    printf("Enter the no of non zero term: ");
    scanf("%d",&cnt);
    printf("Enter in correct sparse format and sequence\n");

    if(cnt>a[0].row*a[0].col)
        {
            printf("\n\n\tinvalid input\n");
          goto start;
        }
    printf("Enter the input: \n");
    printf("row col value\n");
    while(cnt--)
    {
        scanf("%d",&a[pos].row);
        if((a[pos].row>a[0].row)||(a[pos].row<0))
        {
             printf("\n\n\t\tinvalid input\n\n");
             goto start;

        }

    scanf("%d",&a[pos].col);
    if((a[pos].col>a[0].col)||(a[pos].col<0))
        {
             printf("\n\n\t\tinvalid input\n\n");
             goto start;

        }

    scanf("%d",&a[pos].val);
    pos++;
    }

    a[0].val=pos-1;


}

void GetMat( struct term A[])//take input in normal form;
{
    int i,j;
    int val;
    int k=1;
    printf("Enter the no of row and column: ");
    scanf("%d%d",&A[0].row,&A[0].col);

    printf("Enter the input in normal matrix form\n");
    for(i=0;i<A[0].row;i++)
    {
        for(j=0;j<A[0].col;j++)
            {
                scanf("%d",&val);
                if(val!=0)
                {
                    A[k].row=i;
                    A[k].col=j;
                    A[k].val=val;
                    k++;
                }

            }

    }
    A[0].val=k-1;
}

void addstr(char str1[],char str2[])//function to add string to another string ;
{
    int i,j;
    i=strlen(str1);
    for(j=0;j<=strlen(str2);j++)
        str1[i++]=str2[j];
}

FILE *D;

void combine(struct term A[],struct term B[])//it makes the sparse form and convert it to map reducible form
{
    ROW=A[0].row;
    COL=B[0].col;
    if(A[0].col!=B[0].row)
    {
        printf("multiplication not possible");
        exit(0);
    }
    COM=A[0].col;

    int i,j;
     FILE *fp;
   fp= fopen("file1.txt","w");
   int k=1;

   for(i=0;i<A[0].row;i++)
    {
        int f=0;
        char str1[size2];
        char str2[size2];
        str1[0]='\0';
        str2[0]='\0';
        char line[2*size2];
        line[0]='\0';

        addstr(str1,"A,");
        char num[sizenum];
        itoa(i,num,10);
        addstr(str1,num);
        addstr(str1,",");


        for(j=0;j<A[0].col;j++)
        {
            if(A[k].row==i&&A[k].col==j)
            {
                char nt[sizenum],np[sizenum];
                itoa(j,nt,10);
                addstr(str1,nt);
                itoa(A[k++].val,np,10);
                addstr(str2,np);
                if(j!=A[0].col-1)
                {
                    addstr(str2,",");
                    addstr(str1,",");
                }
                f=1;


            }

        }

       addstr(line,str1);
       addstr(line,"\t");
       addstr(line,str2);
    if(f)
       fprintf(fp,"%s\n",line);


    }
    fclose(fp);


//  for matrix b
fp= fopen("file2.txt","w");


       k=1;

   for(i=0;i<B[0].row;i++)
    {
        int g=0;
        char str1[size2];
        char str2[size2];
        str1[0]='\0';
        str2[0]='\0';
        char line[2*size2];
        line[0]='\0';

        addstr(str1,"B,");
        char num[sizenum];
        itoa(i,num,10);
        addstr(str1,num);
        addstr(str1,",");


        for(j=0;j<B[0].col;j++)
        {
            if(B[k].row==i&&B[k].col==j)
            {
                char nt[sizenum],np[sizenum];
                itoa(j,nt,10);
                addstr(str1,nt);
                itoa(B[k++].val,np,10);
                addstr(str2,np);
                if(j!=B[0].col-1)
                {
                    addstr(str2,",");
                    addstr(str1,",");
                }
                g=1;


            }

        }

       addstr(line,str1);
       addstr(line,"\t");
       addstr(line,str2);
        if(g)
       fprintf(fp,"%s\n",line);


    }
    fclose(fp);

//    joining the files


    D=fopen("D.txt","w");

    char ch;
    fp=fopen("file1.txt","r+");
    while((ch=getc(fp))!=EOF)
    {
        fprintf(D,"%c",ch);

    }

    FILE *ff;
   ff=fopen("file2.txt","r+");
    while((ch=getc(ff))!=EOF)
    {
        fprintf(D,"%c",ch);

    }

    fclose(D);
    fclose(fp);
    fclose(ff);


}

char** split_string(char* text, char delim) //function used to split the strings.
{

    char** result = malloc(1*sizeof(char*));
    int size = 1;

    char* temp = strtok(text, &delim);
    *result = temp;

    while(temp != NULL) {
        size++;
        result = realloc(result,size*sizeof(char*));
        temp = strtok(NULL, &delim);
        result[size-1] = temp;
    }

    return result;
}

void map() //the map function
{

    long long int n=0;
    char ch;
    FILE *fp;
    fp=fopen("D.txt","r");
    FILE *ff;
    ff=fopen("Dpart.txt","w");

    while((ch=getc(fp))!=EOF)
    {
        if(ch=='\n')
            n++;
    }
    fclose(fp);
    fp=fopen("D.txt","r");
    long long int i;
    for(i=0;i<n;i++)
    {
        char line[size2*2];
        long long int j=0;
        while(((ch=getc(fp))!='\n'))
            line[j++]=ch;
        line[j]='\0';
        char **str;
        str=split_string(line,'\t');
        char **str1;
        char **str2;
        str1=split_string(str[0],',');
        str2=split_string(str[1],',');
        if(strcmp(str1[0],"A")==0)
        {
           int m,n;

           for(m=0;m<COL;m++)
           {



               for(n=0;str2[n]!=NULL;n++)
               {
                    char key[size1];
                    char value[size1];
                    key[0]='\0';
                    value[0]='\0';

                   addstr(key,str1[1]);
                   addstr(key,",");
                   char conv[sizenum];
                   itoa(m,conv,10);
                   addstr(key,conv);

                   addstr(value,"A");
                   addstr(value,",");
                   addstr(value,str1[n+2]);
                   addstr(value,",");
                   addstr(value,str2[n]);
                   addstr(key,",");
                   fprintf(ff,"%s%s\n",key,value);


               }

           }

        }

        if(strcmp(str1[0],"B")==0)
        {
           int o,p;

           for(o=0;o<ROW;o++)
           {



               for(p=0;str2[p]!=NULL;p++)
               {
                    char key[size2];
                    char value[size2];
                    key[0]='\0';
                    value[0]='\0';
                    char conv[sizenum];

                   itoa(o,conv,10);
                   addstr(key,conv);
                   addstr(key,",");
                   addstr(key,str1[p+2]);
                   addstr(value,"B");
                   addstr(value,",");
                   addstr(value,str1[1]);
                   addstr(value,",");
                   addstr(value,str2[p]);
                   addstr(key,",");
                   fprintf(ff,"%s%s\n",key,value);


               }

           }

        }

    }
    fprintf(ff,"END");
    fclose(ff);


}




int cmp(struct pair A,struct pair B)//comparison function used to compare the maped string and sort them;
{

    if(A.key[0]>B.key[0])
        return 1;
    else if( A.key[0]==B.key[0]&& A.key[1]>B.key[1])
    return 1;
    else if(A.key[0]==B.key[0]&& A.key[1]==B.key[1]&&A.value[0]>B.value[0])
        return 1;
    else if(A.key[0]==B.key[0]&& A.key[1]==B.key[1]&&A.value[0]==B.value[0]&&A.value[1]>B.value[1])
    return 1;
    return -1;


}
pairswap(struct pair *p1,struct pair *p2)
{

    struct pair temp;
    temp=*p1;
    *p1=*p2;
    *p2=temp;
}



struct pair item[max_size];

void reduce()//the reduce function
{

    FILE *fp,*ff;
    fp=fopen("Dpart.txt","r");

    char list[size1];
    fgets(list,size1,fp);
    long long  int i=0;
    while(strcmp(list,"END"))
    {
        char **splitter;
        splitter=split_string(list,',');
        item[i].key[0]=atoi(splitter[0]);
        item[i].key[1]=atoi(splitter[1]);
        item[i].value[0]=splitter[2][0];
        item[i].value[1]=atoi(splitter[3]);
        item[i].value[2]=atoi(splitter[4]);
        i++;
        fgets(list,size1,fp);



    }
    fclose(fp);
//    printf("i is equal to %d",i);
    fp=fopen("Dpart1.txt","w");

    long long int lenght=i;

    long long int  j;



    for(i=0;i<lenght-1;i++)
    {

        for(j=0;j<lenght-i-1;j++)
        {
            if(cmp(item[j],item[j+1])>0)
            {
               pairswap(&item[j],&item[j+1]);
            }
        }
    }

    i=0;
    while(i<lenght)
    {
        fprintf(fp,"%d,%d\t%c,%d,%d\n",item[i].key[0],item[i].key[1] ,item[i].value[0] ,item[i].value[1],item[i].value[2]);
        i++;
    }
    fprintf(fp,"END");
    fclose(fp);
    char line[size1];

    ff=fopen("result.txt","w");
    int flag=0;
    char check[size1];
    char **pair;
    char **value;

    i=0;
    while(i<lenght)
    {
        int arr1[matsize]={0};
        int arr2[matsize]={0};

        int k1=item[i].key[0],k2=item[i].key[1];

        do
        {


            flag=0;


            if(item[i].value[0]=='A')
//                (strcmp(value[0],"A")==0)
                arr1[item[i].value[1]]=item[i].value[2];
            else if(item[i].value[0]=='B')
                arr2[item[i].value[1]]=item[i].value[2];
//
//            fgets(line,size1,fp);
//
//            strcpy(line1,line);
//            value1=split_string(line1,'\t');


            if(item[i+1].key[0]==k1&&item[i+1].key[1]==k2)
                flag=1;



        i++;
        }while(flag&&(i<lenght));


    if(!flag)
        {
            int xx,aij,bjk;
            long long int result=0;
            for(xx=0;xx<COM;xx++)
            {
                aij=(arr1[xx]!=0)?arr1[xx]:0;
                bjk=(arr2[xx]!=0)?arr2[xx]:0;
                result=result+aij*bjk;

            }
            if(result)
            fprintf(ff,"%d,%d,%lld\n",k1,k2,result);
        }

    int mmn;
//    for(mmn=0;mmn<COM;mmn++)
//            {
////                aij=(arr1[mmn]!=0)?arr1[mmn]:0;
////                bjk=(arr2[mmn]!=0)?arr2[mmn]:0;
//                    printf("%d  ",arr1[mmn]);
//                    printf("%d  ",arr2[mmn]);
//
//
//            }
//     printf("\n");
    }

    fprintf(ff,"END");

    fclose(ff);
    fclose(fp);

}

void filetosparse(struct term sparse[])//function to take input of result file and convert to sparse form
{

    sparse[0].row=ROW;
    sparse[0].col=COL;
    FILE *fp;
    long long int i=1;
    char line[size1];
    char **pair;
    fp=fopen("result.txt","r");
    fgets(line,size1,fp);
    while(strcasecmp(line,"END"))
    {
        pair=split_string(line,',');
        sparse[i].row=atoi(pair[0]);
        sparse[i].col=atoi(pair[1]);
        sparse[i].val=atoi(pair[2]);
        i++;


        fgets(line,size1,fp);
    }
    sparse[0].val=i-1;

    int  j;

fclose(fp);
}



void disp(struct term sparse[])//function  to display in normal form
{   printf("\n\n output in normal form \n");
    int i,j,k=1;
    for(i=0;i<sparse[0].row;i++)
    {
        for(j=0;j<sparse[0].col;j++)
        {
            if(sparse[k].row==i&&sparse[k].col==j)
            {
                printf("%4d  ",sparse[k].val);
                k++;
            }
            else
               printf("%4d  ",0);

        }
        printf("\n\n");
    }
}




void spdisp(struct term sparse[])//function to display in sparse form;
{
    int i,j;
    FILE *fp;
//    fp=fopen("result.txt","w");
    printf("\n\nrow col val");

    for(i=0;i<=sparse[0].val;i++)
    {

        printf("\n%3d %3d %3d",sparse[i].row,sparse[i].col,sparse[i].val);
//        fprintf(fp,"\n%d,%d,%3d",sparse[i].row,sparse[i].col,sparse[i].val);
        if(i==0)
            {
//                fprintf(fp,"\n");
                printf("\n");
            }

    }
//    fclose(fp);

}

int main()
{
    printf("\n\tWelcome to map reduce Sparse Multiplication in C\n\n");

    struct term sparse1[sizesparse];
    struct term sparse2[sizesparse];
    struct term sparse[sizesparse];
    int choice;
    start1:
    printf("Matrix 1\n");

    printf("Enter 1 for entering in sparse form 2 for entering in normal form");
    scanf("%d",&choice);
    if(choice==1)
    {
        sparsein(sparse1);
    }
    else if(choice==2)
    {
        GetMat(sparse1);
        disp(sparse1);
    }
     else
        {
            printf("\n\tEnter the valid option\n");
            goto start1;
        }

    start2:
    printf("\n\nMatrix 2\n");
    printf("Enter 1 for entering in sparse form 2 for entering in normal form");
    scanf("%d",&choice);
    if(choice==1)
    {
        sparsein(sparse2);
    }
    else if(choice==2)
    {
        GetMat(sparse2);
        disp(sparse2);
    }
    else
        {
            printf("\n\tEnter the valid option\n");
            goto start2;
        }


    combine(sparse1,sparse2);
    printf("\n\tCombine task completed");

    map();

    printf("\n\tMap task completed");
    reduce();
    printf("\n\treduce task completed");
    filetosparse(sparse);
    spdisp(sparse);
    disp(sparse);


    printf("\n\tpress any key to exit");
    getch();
    printf("\n\tThanks \n programmed by chetan");
}
