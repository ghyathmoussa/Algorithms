#include <stdio.h>
//to do the circle sort steps
int circle_inner(int a[], int low, int high,int *count)
{
    int swap = 0, temp, mid;
    if (low == high)
        return swap; // to cheak the first and last items
    int l = low, h = high;
    //starting sort between the first and last item
    while (l < h)
    {
        if (a[l] > a[h])
        {
            temp = a[l];
            a[l] = a[h];
            a[h] = temp;
            swap++;
            (*count)++;
        }
        l++;
        h--;
    }
    if (l == h)
    {
        if (a[l] > a[h + 1])
        {
            temp = a[l];
            a[l] = a[h + 1];
            a[h + 1] = temp;
            swap++;
            (*count)++;
        }
    }
    mid = (high - low) / 2;
    int firstHalf = circle_inner(a, low, low + mid,count);
    int secondHalf = circle_inner(a, low + mid + 1, high,count);

    return swap | firstHalf | secondHalf;
}
//drive circle_inner untile it end
void circleSort(int a[], int n, int *count)
{
    while (circle_inner(a, 0, n - 1,count))
    {
        (*count)++;
    }
}

int main()
{
    int count = 0;
    int a[20];
    int i, n;
    //size of array
    printf("Enter the size of array:");
    scanf("%d \n", &n);
    printf("Enter the elements: \n");
    for (i = 0; i < n; i++)
        scanf("%d ", &a[i]);           // array elements
    printf("Array befor sorting: \n"); //output before sorting
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    circleSort(a, n, &count); //starting sort
    printf("\nArray after sorting :\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]); //outout after sorting
    printf("\nthe complexity %d ", count);
    return 0;
}