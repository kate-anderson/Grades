///////////////////////////////////////////////////////////////////////////////
//
// Programmer: Kate Anderson
// Date: 04/24/2015
// Name: grade.c
// Description: Calculate the grades of over 400 students.
//
/////////////////////////////////////////////
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(void)
{
    FILE *quizPtr;      //quiz_scores.txt file pointer
    FILE *examPtr;      //exam_scores.txt file pointer
    FILE *homeworkPtr;  //homework_scores.txt file pointer
    FILE *gradePtr;     //final_grades.txt file pointer
    int snum,i,j;
    float hgrade,min;
    int student;        //student ID
    float quiz[500]={0};
    float exam[500]={0};
    float score[500]={0};
    float average[500]={0};
    float homework[500][10]={{0}};
    float caverage[10]={0};
    float qgrade;       //quiz grade
    float egrade;       //exam grade

    //open the quiz file
    if((quizPtr= fopen("quiz_scores.txt","r"))== NULL)
    {
        puts("Quiz file could not be opened");
    }
    else
    {
        //read the values from the quiz file and print them to the screen
        fscanf(quizPtr,"%d",&snum);
        for(i=0;i<snum;i++)
        {
            fscanf(quizPtr,"%d%f",&student, &qgrade);
            quiz[student]=qgrade;   //store the quiz scores into an array
        }
    }
    fclose(quizPtr);    //close the quiz file

    //open the exam file
    if((examPtr= fopen("exam_scores.txt","r"))== NULL)
    {
        puts("Exam file could not be opened");
    }
    else
    {
        //read the values from the exam file and print them to the screen
        fscanf(examPtr,"%d",&snum);
        for(i=0;i<snum;i++)
        {
            fscanf(examPtr,"%d%f",&student, &egrade);
            exam[student]=egrade;   //store the exam scores into an array
        }
    }
    fclose(examPtr);    //close the exam file

    //open the homework file
    if((homeworkPtr= fopen("homework_scores.txt","r"))== NULL)
    {
        puts("Homework file could not be opened");
    }
    else
    {
        fscanf(homeworkPtr,"%d",&snum);
        for(i=0;i<snum;i++)
        {
            fscanf(homeworkPtr,"%d",&student);
            min=100;
            for(j=0;j<10;j++)
            {
                fscanf(homeworkPtr,"%f",&hgrade);
                homework[student][j]=hgrade;   //store the homework scores into an array
                caverage[j]=caverage[j]+hgrade; //store the class average into an array(adding of the homework score)
                //add the homework grades
                average[student]=average[student]+homework[student][j];
                //drop the lowest homework grade
                if(homework[student] [j]<min)
                {
                    min=homework[student][j];
                }
            }
            //average the homework scores
            average[student]=(average[student]-min)/9;
        }
        //class average for each homework assignment
        for(i=0;i<10;i++)
        {
            caverage[i]=caverage[i]/snum;
        }
    }
    fclose(homeworkPtr);    //close the homework file

    //compute the students final grades
    for(i=0;i<500;i++)
    {
        score[i]=(0.15*quiz[i])+(0.35*exam[i])+(0.5*average[i]);
        if(score[i]!=0)
        {
            snum=snum+1;
        }
    }

    //output the grades to the final grade file
    if((gradePtr= fopen("final_grades.txt","w"))== NULL)
    {
        puts("Final Grade file could not be opened");
    }
    else
    {
        fprintf(gradePtr,"%d\n",snum);
        for(i=0;i<500;i++)
        {
            if(score[i]!=0)
            {
            fprintf(gradePtr,"%d  %f\n",i,score[i]);
            }
        }
    }
    fclose(gradePtr);    //close the final grade file

    //print the class average for the homework assignments
    printf("Class average:\n");
    for(j=0;j<10;j++)
    {
        printf("Homework %d=   %f\n",j+1,caverage[j]);
    }
    return 0;
}
