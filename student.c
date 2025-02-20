#include "hw5.h"

void StudentPrint(Student *stu, int num)
{
    printf("There are %d students\n", num);
    for (int ind = 0; ind < num; ind++)
    {
        printf("ID = %d, Name = %s\n", stu[ind].ID, stu[ind].name);
    }
}

// count the number of '\n' to determine the number of records
int countNewLine(FILE *fptr)
{
    int numline = 0;
    while (!feof(fptr))
    {
        int onechar = fgetc(fptr);
        if (onechar == '\n')
        {
            numline++;
        }
    }
    return numline;
}

/* This is the first function you need to implement */
bool StudentRead(char *filename, Student **stu, int *numelem)
{
    /* 1.1: open the file to read */
    FILE *fptr = fopen(filename, "r");
    if (!fptr)
        return false;

    int numline = countNewLine(fptr);
    fseek(fptr, 0, SEEK_SET);

    /* 1.2 allocate memory for the data */
    Student *stuptr = (Student *)malloc(numline * sizeof(Student));
    if (!stuptr)
    {
        fclose(fptr);
        return false;
    }

    /* 1.3: read data from the file */
    for (int i = 0; i < numline; i++)
    {
        fscanf(fptr, "%d %79s", &stuptr[i].ID, stuptr[i].name);
    }
    fclose(fptr);

    *numelem = numline;
    *stu = stuptr;
    return true;
}

/* This is the second function you need to implement */
bool StudentWrite(char *filename, Student *stu, int numelem)
{
    // open the file to write
    FILE *fptr = fopen(filename, "w");
    if (!fptr)
        return false;

    // write the data from array stu to the opened file
    for (int i = 0; i < numelem; i++)
    {
        fprintf(fptr, "%d %s\n", stu[i].ID, stu[i].name);
    }
    fclose(fptr);
    return true;
}

/* This is the third function you need to implement */
void sortStudents(Student *stu, int numelem, int (*compar)(const void *, const void *))
{
    /* Fill in to call qsort function to sort array stu */
    qsort(stu, numelem, sizeof(Student), compar);
}

/* This is the fourth function you need to implement */
int compareID(const void *p1, const void *p2)
{
    /* Fill in to compare p1 and p2 by id */
    const Student *st1 = (const Student *)p1;
    const Student *st2 = (const Student *)p2;
    return st1->ID - st2->ID;
}

/* This is the fifth function you need to implement */
int compareName(const void *p1, const void *p2)
{
    /* Fill in to compare p1 and p2 by name */
    const Student *st1 = (const Student *)p1;
    const Student *st2 = (const Student *)p2;
    return strcmp(st1->name, st2->name);
}

/* This is the sixth function you need to implement */
bool areStudentsSorted(Student *stu, int numelem, int (*compar)(const void *, const void *))
{
    /* Fill in to check if the stu array is sorted according to compar */
    for (int i = 0; i < numelem - 1; i++)
    {
        if (compar(&stu[i], &stu[i + 1]) > 0)
            return false;
    }
    return true;
}
