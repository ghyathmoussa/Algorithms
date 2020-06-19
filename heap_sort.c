#include<stdio.h>
int main(){
    int i,n,no,temp,c,root,j;
    int dizi[50];
    printf("Enter the number of elements: \n");
    scanf("%d \n",&no);
    printf("Enter the element: ");
    for(i=0;i<no;i++)
        scanf("%d \n",&dizi[i]);
    for(i=1;i<no;i++){
        c=i;
        while(c!=0){
            root=(c-1)/2;
            if(dizi[root]<dizi[c]){ /*to creat max array and put it in the first*/
                temp=dizi[root];
                dizi[root]=dizi[c];
                dizi[c]=temp;
            }
            c=root;
        }
    }
    printf("heap array: \n");
    for(i=0;i<no;i++)
        printf("%d \n",dizi[i]);

    for(j=no-1;j>=0;j--){
        temp=dizi[0];
        dizi[0]=dizi[j]; /*swap max elemant to the end*/
        dizi[j]=temp;
        root=0;
        do {
            c=2*root+1; /* left node of rootelemant*/
            if((dizi[c]<dizi[c+1]) && c<j-1)
                c++;
            if(dizi[root]<dizi[c] && c<j){ /* rerange to max elemant*/
                temp=dizi[root];
                dizi[root]=dizi[c];
                dizi[c]=temp;
            }
            root=c;
        }while(c<j);
    }

    printf("sorted array is: \n");
    for(i=0;i<no;i++)
        printf("%d ",dizi[i]);

    return 0;
}