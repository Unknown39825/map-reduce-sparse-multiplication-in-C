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
        printf("%s \n",line);





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