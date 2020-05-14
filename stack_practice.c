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
};

//Stack olusturmak icin fonksiyon, her stack pointer ilan edildiginde bir kez cagirilmalidir
//cagirilirken gereksindigi parametre: &yigin
void StackYarat(struct Stack** head){
    (*head) = (struct Stack*)malloc(sizeof(struct Stack)); //yigin1 isaretcisi icin adres
    (*head)->sonraki=NULL;
    (*head)->ogr_b=NULL;
}

//bu fonksiyon sadece OgrNo_entry tarafindan cagirilir ve main'de cagirilmamalidir
//Ogrenci Numarasini tutacak bagli listeyi olusturmak icin kullanılır
//parametreler:OgrNo_entry fonk. icindeki *head ptr'si, Main'den gelen char*OgrenciNumarasi
void set(struct Stack*stack,char* Num){
    int number[10]={0};
    for(int i=9;i>=1;i--){
        number[i]=(Num[(i-1)]-48);//inanilmaz trick
        //0 karakteri ASCII'de 48 ve 9 karakteri 57 ise 48-48=0 ve 57-48=9
    }
    for (int j=6;j<10;j++){
        number[0]=number[0]+number[j];
        number[0] = number[0]*10;//basamak arttir
    }
    number[0]=number[0]/10; //bir basamak fazla fix

    struct OgrNo* n_dgt=(struct OgrNo*)malloc(sizeof(struct OgrNo));
    n_dgt->sayi=number[9];
    n_dgt->next=NULL;
    stack->ogr_b=n_dgt;
    for(int i=8;i>=0;i--){
    struct OgrNo* n_dgt=(struct OgrNo*)malloc(sizeof(struct OgrNo));
    n_dgt->sayi=number[i];
    n_dgt->next=stack->ogr_b;
    stack->ogr_b=n_dgt;
    }
}

//cagirilirken gereksindigi parametreler:char*OgrenciNumarasi,&yigin
//Olusturulmus Stack'e yeni bir Ogrenci numarasi ekler
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

//cagirilirken gereksindigi parametreler:&yigin
//Stack'deki ogrenci numaralarini ekrana yazdirir
void printStack(struct Stack**head){
    struct Stack*temp=(*head);
    struct OgrNo*gecici;
    while(temp!=NULL){
        gecici = temp->ogr_b;
        printf("ID:%d\nOgrenci Number:",gecici->sayi);
        gecici = gecici->next;
        for(int i=0;i<9;i++){
            printf("%d",gecici->sayi);
            gecici=gecici->next;
        }
        printf("\n");
        temp=temp->sonraki;
    }
}

//cagirilirken gereksindigi parametreler:&yigin
// en kucuk ID'yi bastirir, main'e doner
int minBul(struct Stack**head){
    struct Stack*min;struct Stack*temp=(*head);min=temp;
    while(temp!=NULL){
        if((min->ogr_b->sayi)>(temp->ogr_b->sayi))
            min=temp;
        temp=temp->sonraki;
    }
    printf("En kucuk ogrenci ID'si %d\n",min->ogr_b->sayi);
    return min->ogr_b->sayi;
}

//yiginin en ust uyesini cikartir, ona ptr doner
struct Stack* pop(struct Stack **head){
    struct Stack*temp;
    temp=*head;
    (*head)=(*head)->sonraki;
    temp->sonraki=NULL;
    return temp;
}

//parametreler:&yigin,&uye
//istenen uye ptr'sini kullanarak yigina koyar
void push(struct Stack**head, struct Stack**element){
    (*element)->sonraki = (*head);
    (*head)=(*element);
}

void reversing_recursion(struct Stack**rev_head,struct Stack**norm_head){
    struct Stack*temp=NULL;
    temp=pop(norm_head);
    temp->sonraki=(*rev_head); 
    (*rev_head)=temp;
    if((*norm_head)!=NULL)
        reversing_recursion(rev_head,norm_head);
}

/*yukaridaki fonksiyonun calismasi hakkinda detay:
eger cagiran fonksiyonda *reversed=NULL olarak tanimlandigi esnada ilan edilmeseydi
temp->sonraki=(*rev_head) satiri, yiginin son elemaninin sonraki isaretcisini
reversed tanimlandiginda atanan rastgele adrese isaret ettirecekti, halbuki son eleman
bosluga isaret ediyor olmalı, böylece yazdirici fonksiyonlar nerede duracaklarini bilebilirler*/

void stackReverse(struct Stack**head){
    struct Stack*reversed=NULL;
    reversing_recursion((&reversed),head);
    (*head)=reversed;
}

//ascending_reorder tarafindan kullanilan
//alt icdongu
void reorder_entry(struct Stack**head,struct Stack**uye){
    if(((*head)==NULL)||(((*uye)->ogr_b->sayi)>((*head)->ogr_b->sayi))){
        push(head,uye);
    }
    else{
        struct Stack*temp=pop(head);
        reorder_entry(head,uye);
        push(head,&temp);
    }
}

//kendi kendisini cagirarak listeyi 
//idler kucukten buyuge olacak sekilde yeniden siralar
void ascending_reorder(struct Stack**head){
    if((*head)!=NULL){
        struct Stack* gecici=pop(head);
        ascending_reorder(head);
        reorder_entry(head,&gecici);
    }
    else
        return;
}

//gonderilen yigin uyesinin tuttugu ogrenci numarasinin
//yilini iki haneli (00-99olabilir) tamsayi doner 
int yil_hesabi(struct Stack**uye){
    int ts_gecici=0;
    struct OgrNo*isrt_gecici=(*uye)->ogr_b;
    for(int i=0;i<4;i++){
        isrt_gecici=isrt_gecici->next;
    }
    for(int i = 4;i<6;i++){
        ts_gecici=ts_gecici+(isrt_gecici->sayi);
        ts_gecici=ts_gecici*10;
        isrt_gecici=isrt_gecici->next;
    }
    ts_gecici=ts_gecici/10;
    return ts_gecici;
}

//yillara_gore tarafindan cagirilan alt icdongu
void yg_giris(struct Stack**head,struct Stack**uye){
       if(((*head)==NULL)||((yil_hesabi(uye))>(yil_hesabi(head)))){
        push(head,uye);
    }
    else{
        struct Stack*temp=pop(head);
        yg_giris(head,uye);
        push(head,&temp);
    }
}

//listenin uyelerinden ayni yilda olanlarini 
//bir araya getirerek siralar
void yillara_gore(struct Stack**head){
    if((*head)!=NULL){
        struct Stack* gecici=pop(head);
        yillara_gore(head);
        yg_giris(head,&gecici);
    }
    else
        return;
}

int main(){
    struct Stack* yigin1=NULL; 
    StackYarat(&yigin1);
    printf("1 - Enter university id number\n2 - List all numbers according to the last 4 digits, in ascending order\n");
    printf("3 - List all numbers grouped by year\n4 - Exit\n");
    int choice=0;
    while(choice!=4){
        printf("Enter choice:");scanf(" %d",&choice);printf("\n");
        if(choice==1){
            char*OgrNo=malloc(9*(sizeof(char))); printf("Enter university id number:");
            scanf("%s",OgrNo);
            OgrNo_entry(OgrNo,&yigin1);
        }
        if(choice==2){
            ascending_reorder(&yigin1);
            printStack(&yigin1);
        }
        if(choice==3){
            yillara_gore(&yigin1);
            printStack(&yigin1);
        }
        /*printStack(&yigin1);
        int minID = minBul(&yigin1);

        stackReverse(&yigin1);
        printStack(&yigin1);*/
    }
}