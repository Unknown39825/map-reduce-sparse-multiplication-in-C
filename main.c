#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Matrix
{
    int **M;
    int r;
    int c;
};
typedef struct Matrix Matrix;
int COL;
int ROW;
void create_mat( Matrix *Mat)
{
    printf("Enter the no of row and column");
    scanf("%d%d",&Mat->r,&Mat->c);

    Mat->M = malloc(sizeof(int *)*(Mat->r));

    int i;
    for(i=0;i<Mat->r;i++)
    {
        Mat->M[i]=malloc(sizeof(int)*Mat->c);
    }
}

void GetMat( Matrix *Mat)
{
    int i,j;
    for(i=0;i<Mat->r;i++)
    {
        for(j=0;j<Mat->c;j++)
            scanf("%d",&Mat->M[i][j]);

    }
}
void PutMat(Matrix Mat)
{
    int i,j;
    for(i=0;i<Mat.r;i++)
    {
        for(j=0;j<Mat.c;j++)
            printf("%d ",Mat.M[i][j]);
        printf(" \n");
    }
}

void addstr(char str1[],char str2[])
{
    int i,j;
    i=strlen(str1);
    for(j=0;j<=strlen(str2);j++)
        str1[i++]=str2[j];
}

FILE *D;

void combine(Matrix A,Matrix B)
{
    ROW=A.r;
    COL=B.c;
    int i,j;
     FILE *fp;
   fp= fopen("file1","w");

   for(i=0;i<A.r;i++)
    {
        char str1[100];
        char str2[100];
        str1[0]='\0';
        str2[0]='\0';
        char line[100];
        line[0]='\0';

        addstr(str1,"A,");
        char num[5];
        itoa(i,num,10);
        addstr(str1,num);
        addstr(str1,",");


        for(j=0;j<A.c;j++)
        {
            if(A.M[i][j]==0)
                continue;
            else
            {
                char nt[5],np[5];
                itoa(j,nt,10);
                addstr(str1,nt);
                itoa(A.M[i][j],np,10);
                addstr(str2,np);
                if(j!=A.c-1)
                {
                    addstr(str2,",");
                    addstr(str1,",");
                }


            }

        }

       addstr(line,str1);
       addstr(line,"\t");
       addstr(line,str2);

       fprintf(fp,"%s\n",line);


    }
    fclose(fp);


//  for matrix b
fp= fopen("file2","w");


    for(i=0;i<B.r;i++)
    {
        char str1[100];
        char str2[100];
        str1[0]='\0';
        str2[0]='\0';
        char line[100];
        line[0]='\0';

        addstr(str1,"B,");
        char num[5];
        itoa(i,num,10);
        addstr(str1,num);
        addstr(str1,",");


        for(j=0;j<B.c;j++)
        {
            if(B.M[i][j]==0)
                continue;
            else
            {
                char nt[5],np[5];
                itoa(j,nt,10);
                addstr(str1,nt);
                itoa(B.M[i][j],np,10);
                addstr(str2,np);
                if(j!=B.c-1)
                {
                   addstr(str2,",");
                   addstr(str1,",") ;
                }


            }

        }

       addstr(line,str1);
       addstr(line,"\t");
       addstr(line,str2);

       fprintf(fp,"%s\n",line);


    }

    fclose(fp);

//    joining the files


    D=fopen("D","w");

    char ch;
    fp=fopen("file1","r+");
    while((ch=getc(fp))!=EOF)
    {
        fprintf(D,"%c",ch);

    }

    FILE *ff;
   ff=fopen("file2","r+");
    while((ch=getc(ff))!=EOF)
    {
        fprintf(D,"%c",ch);

    }

    fclose(D);
    fclose(fp);
    fclose(ff);


}
char** split_string(char* text, char delim) {

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

void map()
{

    int n=0;
    char ch;
    FILE *fp;
    fp=fopen("D","r");
    FILE *ff;
    ff=fopen("Dpart","w");

    while((ch=getc(fp))!=EOF)
    {
        if(ch=='\n')
            n++;
    }
    fclose(fp);
    fp=fopen("D","r");
    int i;
    for(i=0;i<n;i++)
    {
        char line[100];
        int j=0;
        while(((ch=getc(fp))!='\n'))
            line[j++]=ch;
        line[j]='\0';
        char **str;
        str=split_string(line,'\t');

//        while(str[l]!=NULL)
//            printf("%s \t",str[l++]);
//        printf("\n");

        char **str1;
        char **str2;
        str1=split_string(str[0],',');
        str2=split_string(str[1],',');
//        while(str1[l]!=NULL)
//            printf("%s \t",str1[l++]);
//        l=0;
//        while(str2[l]!=NULL)
//            printf("%s \t",str2[l++]);
//        printf("\n");

        if(strcmp(str1[0],"A")==0)
        {
           int m,n;

           for(m=0;m<COL;m++)
           {



               for(n=0;str2[n]!=NULL;n++)
               {
                    char key[100];
                    char value[100];
                    key[0]='\0';
                    value[0]='\0';

                    addstr(key,str1[1]);
                    addstr(key,",");
                    char conv[5];
                    itoa(m,conv,10);
                    addstr(key,conv);
                    addstr(value,"A");
                    addstr(value,",");

                    addstr(value,str1[n+2]);
                    addstr(value,",");
                    addstr(value,str2[n]);




                   fprintf(ff,"%s|%s\n",key,value);


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
                    char key[100];
                    char value[100];
                    key[0]='\0';
                    value[0]='\0';
                    char conv[5];

                   itoa(o,conv,10);
                   addstr(key,conv);
                   addstr(key,",");
                   addstr(key,str1[p+2]);

                   addstr(value,"B");
                    addstr(value,",");
                   addstr(value,str1[1]);
                   addstr(value,",");
                   addstr(value,str2[p]);
                   fprintf(ff,"%s|%s\n",key,value);


               }

           }

        }

    }
    fclose(ff);


}
void reduce()
{
    FILE *fp;
    fp=fopen("Dpart","r");
    char list[1000];
    fgets(list,1000,fp);
    fclose(fp);
    char **item;
    item=split_string(list,'\t');
    fp=fopen("Dpart","w");
    int i=0;
    while(item[i]!=NULL)
    {
        i++;
    }
    int lenght=i;
    int j;
    for(i=0;i<lenght-1;i++)
    {
        for(j=1+i;j<lenght;j++)
        {
            if(strncmp(item[i],item[j],6)>0)
            {
                char temp[100];
                strcpy(temp,item[i]);
                strcpy(item[i],item[j]);
                strcpy(item[j],temp);
            }
        }
    }
    i=0;
    while(item[i]!=NULL)
    {
        fprintf(fp,"%s\n",item[i]);
        i++;
    }
    fclose(fp);

    int mat[ROW][COL];
    int k=0;

    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COL;j++)
        {
            if((item[k][0]==i&&item[k][2]==j)&&(item[k+1][0]==i&&item[k+1][2]==j))
            {
                while((item[k][0]==i&&item[k][2]==j)&&(item[k+1][0]==i&&item[k+1][2]==j))
                printf(" %c*%c+ ",item[k][4],item[k+1][4]);
                k=k+2;
            }
        }
    }

}








int main()
{

    Matrix Mat1,Mat2;
    create_mat(&Mat1);
    GetMat(&Mat1);
    create_mat(&Mat2);
    GetMat(&Mat2);

    combine(Mat1,Mat2);
    map();



}
