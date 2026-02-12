#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct pateint {
    char name[50];
    int  age ;
    int prty;
} ptnt;

typedef struct emergency_room {
    ptnt *patients;
    int pcount;
} emgrm;

int capacity=10;

void add(emgrm *a);
void list(emgrm *a);
void sort(emgrm *a);
void serve(emgrm *a);

int main()
{
    printf("------ENTER TODAYS PAITENTS STATUS :D-------\n\n");

    emgrm hsp;
    hsp.pcount=0;
    hsp.patients=(ptnt*)calloc(capacity,sizeof(ptnt));
    if (hsp.patients == NULL) {
        fprintf(stderr, "Failed to allocate memory for patients\n");
        return 1;
    }
    
    int opt;
    do {
        printf("  enter choice to get in \n");
        printf("1)Add patient\n");
        printf("2)serve patient\n");
        printf("3)waiting list\n");
        printf("4)exit\n");
        scanf("%d",&opt);
        switch(opt)
        {

        case 1: {
            printf("hello welcome\n");
            add(&hsp);
            break;
        }

        case 2: {
            serve(&hsp);
            break;
        }

        case 3:
        {   list(&hsp);
            break;
        }

        case 4: {
            printf("exiting.....\n");
            break;
        }
        


        default: {
            printf("invalid input\n");
        }
        }
    } while(opt!=4);

    free(hsp.patients);
    return 0;
}

void add(emgrm *a) {
    /* ensure there is space for a new patient */
    if (a->pcount >= capacity) {
        int new_capacity = capacity * 2;
        ptnt *tmp = realloc(a->patients, new_capacity * sizeof(ptnt));
        if (tmp == NULL) {
            fprintf(stderr, "Memory allocation failed while growing patients array\n");
            return;
        }
        a->patients = tmp;
        capacity = new_capacity;
    }
    printf("enter name: ");
    /* read up to 49 chars and allow spaces until newline */
    scanf(" %49[^\n]", a->patients[a->pcount].name);
    printf("enter age: ");
    scanf("%d",&a->patients[a->pcount].age);
    printf("emergency index: ");
    scanf("%d",&a->patients[a->pcount].prty);
    printf("\n");
    printf("Patient added: %s | %d | %d\n",
           a->patients[a->pcount].name,
           a->patients[a->pcount].age,
           a->patients[a->pcount].prty);
    printf("\n");
    a->pcount = a->pcount + 1;
}


void list(emgrm *a) {

    sort(a);
    printf("current waiting list\n");
    if(a->pcount==0) {
        printf("no patents waiting\n");
    }
    for(int i=0; i<a->pcount; i++) {
        printf("[%s | ",a->patients[i].name);
        printf(" %d |",a->patients[i].age);
        printf(" %d ]",a->patients[i].prty);
        printf("\n");
    }

}

void sort(emgrm *a) {
    ptnt temp;
    int i;
    int flag=0;
    for(int j=0; j<a->pcount; j++) {
        flag=0;
        for( i=0; i<a->pcount-1; i++) {
            if(a->patients[i].prty>a->patients[i+1].prty)
            {
                temp=a->patients[i];
                a->patients[i]=a->patients[i+1];
                a->patients[i+1]=temp;
                flag++;
            }
        }
        if(flag==0) {
            break;
        }
    }
}


void serve(emgrm *a) {
    sort(a);
    if(a->pcount==0){printf("all the patients are served\n");
    return;}
    printf("Serving patient: %s | %d | %d\n",
           a->patients[0].name, a->patients[0].age, a->patients[0].prty);
    for(int i=0; i<=a->pcount-2; i++) {

        a->patients[i]=a->patients[i+1];

    }
    a->pcount=a->pcount-1;


}