/*
    Back tracking Algorithms
    Problem: NxN game table that each column should contain one color
             the number of color is equal to N
    Method:  you should set the color string and each color get it's id from index
             the color will be represented by its id 
*/


#include <stdio.h>
#include <stdlib.h>

// function to check if the current configuration is valid
int isValid(int **table,int* color_int,int N) {
	int i,j,k,indexes[N];
    for(i=0;i<N;i++)
        indexes[i] = 0;
    // check if there is only 1 of each color in each column
    for (i = 0; i < N; i++) {
        for(k=0;k<N;k++)
            indexes[k] = 0;
        for (j = 0; j < N; j++) {
            for(k=0;k<N;k++){
                if (table[j][i] == color_int[k]) 
                    indexes[color_int[k]-1]++;
            }
        }
        for(k=0;k<N;k++)
            if(indexes[k] > 1){
                return 0;
            }
    }
    return 1;
}

// recursive function to solve table
int solve(int **table,int *color_int,int N,int visited[][N]) {
	int i,j,k,l,m;
    int original[N];

    // base case: if the current configuration is valid, return true
    if (isValid(table,color_int,N))
		  return 1;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
	
    // try shifting each row and recursively calling solve
    for (i = 0; i < N; i++) {
        for (l = 0; l < N; l++) 
            original[l] = table[i][l];

        for (j = 1; j <= N; j++) {
            // check if the current cell has already been visited
            if (visited[i][0] == 1){
                return 0;
            }

            // shift row i to the right j times
            int temp = table[i][N-1];
            for (k = N-1; k > 0; k--) 
                table[i][k] = table[i][k-1];
            table[i][0] = temp;

            // mark cell as visited
            visited[i][0] = 1;
            // if the function returns true, return true
            if (solve(table,color_int,N,visited)){
                return 1;
            } 

            // mark cell as unvisited
            visited[i][0] = 0;
        }

        // reset row to its original position
        for (l = 0; l < N; l++) 
            table[i][l] = original[l];
        for (l = 0; l < N; l++) 
            visited[i][l] = 0;
    }

    return 0;
}

int solve_normal(int **table,int *color_int,int N,int visited[][N]) {
	int i,j,k,l,m;
    int original[N];

    // base case: if the current configuration is valid, return true
    if (isValid(table,color_int,N))
		  return 1;
	
    // try shifting each row and recursively calling solve
    for (i = 0; i < N; i++) {
        for (l = 0; l < N; l++) 
            original[l] = table[i][l];

        for (j = 1; j <= N; j++) {
            // check if the current cell has already been visited
            if (visited[i][0] == 1){
                return 0;
            }

            // shift row i to the right j times
            int temp = table[i][N-1];
            for (k = N-1; k > 0; k--) 
                table[i][k] = table[i][k-1];
            table[i][0] = temp;

            // mark cell as visited
            visited[i][0] = 1;
            // if the function returns true, return true
            if (solve_normal(table,color_int,N,visited)){
                return 1;
            } 

            // mark cell as unvisited
            visited[i][0] = 0;
        }

        // reset row to its original position
        for (l = 0; l < N; l++) 
            table[i][l] = original[l];
        for (l = 0; l < N; l++) 
            visited[i][l] = 0;
    }

    return 0;
}

// to reset table
// because we used tha table matrix as pointer :)

void reset_table(int **table,int N,int temp_table[][N],int visited[][N]){
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++){
            table[i][j] = temp_table[i][j];
            visited[i][j] = 0;
        }
        
}

// print table
void print_table(int **table,int N,char **color_str){
  int i,j;
  for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
          printf("%s ", color_str[table[i][j]-1]);
      }
      printf("\n");
    }
}

int main(){

    int i,j,N,flag=0,*color_int;
    char **color_str;
    int **table;

    
    // take the dimension of table
    while(!flag){
        printf("Set the dimension of table-> N:");scanf("%d",&N);
        if(N<3)
            printf("Too small!, set a bigger number\n");
        else if(N>8)
            printf("Too big, set a smaller number\n");
        else
            flag = 1;
    }
    int temp_table[N][N]; // to save the first shape of table
    int visited[N][N];
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            visited[i][j] = 0;
    

    /* Taking color */

    // 1- init arrays
    color_int = (int*)malloc(N*sizeof(int));
    color_str = (char**)malloc(N*sizeof(char*));
    for(i=0;i<N;i++)
        color_str[i] = (char*)malloc(10*sizeof(char));
    
    printf("Color:\n");
    for(i=0;i<N;i++){
        printf("%d.color: ",i+1);scanf("%s",color_str[i]);
        color_int[i] = i+1;
    }
    
    /// 2- Table
    for(i=0;i<N;i++)
        printf("%d -> %s\n",color_int[i],color_str[i]);

    table = (int**)malloc(N*sizeof(int*));
    for(i=0;i<N;i++)
        table[i] = (int*)malloc(N*sizeof(int));

    printf("Please set the number of color based on the information above\n");
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            scanf("%d",&table[i][j]);

    for(i=0;i<N;i++)
        for(j=0;j<N;j++){
            temp_table[i][j] = table[i][j];
        }
    
    
    // Menu
    int choice,stop=0;
    while(!stop){
        reset_table(table,N,temp_table,visited);
        printf("\n\n---------------- Menu ---------------\n\n");
        printf("\n1-normal\n2-detailed\n3-exit\n");
        scanf("%d",&choice);
        if(choice == 1){
            solve_normal(table,color_int,N,visited);
            print_table(table,N,color_str);
            // reset_table(table,temp_table,N);
        }else if(choice == 2){
            solve(table,color_int,N,visited);
            print_table(table,N,color_str);
        }else if(choice == 3)
            stop = 1;
        else
            printf("Enter valid number\n");
    }
    return 0;
}