#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct OgrNo{
    int sayi;
    struct OgrNo* next;
};

struct Stack{
    struct OgrNo* ogr_b;
    struct Stack* sonraki;
   // struct Stack* sirtaki;
};

void StackYarat(struct Stack** head){
    (*head) = (struct Stack*)malloc(sizeof(struct Stack)); //yigin1 isaretcisi icin adres
    (*head)->sonraki=NULL;
    (*head)->ogr_b=NULL;
}

void set(struct Stack*stack,char* Num){
    int number[9]={0};
    for(int i=8;i>=0;i--){
        number[i]=(Num[i]-48);//inanilmaz trick
        //0 karakteri ASCII'de 48 ve 9 karakteri 57 ise 48-48=0 ve 57-48=9
    }
    /*getDigits(&number,Num);*/
    struct OgrNo* n_dgt=(struct OgrNo*)malloc(sizeof(struct OgrNo));
    n_dgt->sayi=number[8];
    n_dgt->next=NULL;
    stack->ogr_b=n_dgt;
    for(int i=7;i>=0;i--){
    struct OgrNo* n_dgt=(struct OgrNo*)malloc(sizeof(struct OgrNo));
    n_dgt->sayi=number[i];
    n_dgt->next=stack->ogr_b;
    stack->ogr_b=n_dgt;
    }
}

void OgrNo_entry(char *Number1,struct Stack**head){
    if((*head)==NULL){
        printf("Ilk once StackYarat kullanarak yigini olusturunuz.\n");
        return;
    }
    else{
        if(((*head)->ogr_b)==NULL){
            set((*head),Number1);
            return;
        }
        else if((*head)->ogr_b!=NULL){
            struct Stack*newNode = (struct Stack*)malloc(sizeof(struct Stack));
            newNode->sonraki = (*head);
            (*head) = newNode;
            set((*head),Number1);
            return;
        }
    }
}

int main(){
    struct Stack* yigin1=NULL; //cpp olmadigi icin default constructor yok
    //lutfen her Stack ptr'yi ilk basta NULL yapiniz
    StackYarat(&yigin1);
    //int OgrNo1=050102025;//we need a character array bcs int starting with 0 gets proc difft
    char*OgrNo1 = "040170111";
    OgrNo_entry(OgrNo1,&yigin1);
    char*OgrNo2 = "050102025";
    OgrNo_entry(OgrNo1,&yigin1);
    char*OgrNo3 = "050102002";
    OgrNo_entry(OgrNo1,&yigin1);
    char*OgrNo4 = "050102018";
    OgrNo_entry(OgrNo1,&yigin1);

}