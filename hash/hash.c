#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct for links
typedef struct value{
    char link[256];
    struct value *next;
}Value;

// struct for keys
typedef struct key{
	char key[255];
	int key_count;
	struct key *next;
}Key;

// struct for hash table
typedef struct hash_table{
	Value *links;
	char key[50];
} HashTable;

// struct for hash cell
typedef struct hash_cells{
    char link[256];
    char key[256];
    struct hash_cells* next;
}HashCells;



int hash_function(int ,int ,HashTable *,int ,char *);
// Find hash 
int find_hash(int ,int ,HashTable *,int ,char *);

int find_cell_index(HashTable *,char*,int);

int find_prime(int minSize);

void print_table(HashTable *,int );

Key *add_key(char *, Key *);

Value* add_link(HashTable *,char *,int );

Key *delimeter(HashCells *, Key *);
// delimeter for keys in hash table 
HashTable *delimeter_cells(HashCells *,HashTable *,int );

void create_array(HashTable *,int ,Key *);

void create_hash_table(HashTable *,int );
// get the keys and links from text file
HashCells *get_key_links(FILE *);

int main(){
    FILE *fp;
    Key *keys;
	char *texts[2];
	int choice,stop=0;


    keys = (Key*)malloc(sizeof(Key));
    keys->next = NULL;
    keys->key_count = 0;

    strcpy(keys->key,"#");
    HashTable *table;
    int i,load_factor;
    //get load factor
    printf("Set the load factor in percent : ");scanf("%d",&load_factor);

    fp=fopen("Sample.txt","r");
    
    if(fp != NULL){
        HashCells *head;
        head = get_key_links(fp);
        fclose(fp);
        keys = delimeter(head,keys);   
        int size = find_prime(((float)100 / load_factor) * keys->key_count);
        table = (HashTable*)malloc(size * sizeof(HashTable));
        create_hash_table(table,size);
        create_array(table,size,keys);
        table = delimeter_cells(head,table,size);
		printf("size: %d",size);
		// Menu for program
		while(!stop){ // stop flag
			printf("\n\n------------------ Menu --------------\n\n");
			printf("1-Normal Search\n2-Print HAsh Table\n3-Exit\n");
			scanf("%d",&choice);
			if(choice == 1){// first choice is to search for any keyword
				char keyword[20];
				int parsed;
				printf("What are you searching: ");
				scanf("%s",keyword);

				int index = find_cell_index(table,keyword,size);
				printf("index: ");
				Value *current_links = table[index].links;
				if(current_links != NULL){
					while(current_links != NULL){
						printf("%s\n",current_links->link);
						current_links = current_links->next;
					}
				}else{
					printf("Key not found\n");
				}
				
			}else if(choice == 2){
				print_table(table,size);
			}else if(choice == 3)
				stop = 1;
			else
				printf("Wrong choice please try again\n");
		}	

    }else{
        printf("Can not open file\nExit");
    }
	fclose(fp);
}

/* ---------------- Links functions ----------------- */

// add links string to linked list
Value* add_link(HashTable *table,char *link,int index){
	// add links to linked list
	// add to end
	// return the links of wanted category

    Value *new_link = (Value*)malloc(sizeof(Value));

    strcpy(new_link->link,link);
    new_link->next = NULL;
    HashTable tab = table[index];

    if(tab.links == NULL){
        tab.links = new_link;
        tab.links->next = NULL;
    }else{
        Value *current = tab.links;
        while(current->next != NULL)
            current = current->next;
        current->next = new_link;
    }
    return tab.links;
}

/* -------------- Reading from text file ----------------*/
HashCells *get_key_links(FILE *fp){
	// read txt file and assign the links to cell's link
	// assign keys to cell's keys
	// return the cell

    HashCells *current,*head,*temp;
    int i;
    head = (HashCells*)malloc(sizeof(HashCells));
    current = head;
    while(fscanf(fp,"%[^\n]\n%[^\n]\n",current->link,current->key) == 2){
        current->next = (HashCells*)malloc(sizeof(HashCells));
        temp = current;
        current = temp->next;
    }

    temp->next = NULL;
    return head;
}

/* -------------- General Operations of Hashing --------------- */

// hash function
int hash_function(int key,int i,HashTable *table,int size,char *str){
    int new_key = (key+i) % size;

    if(strcmp(table[new_key].key,"#") != 0 && strcmp(table[new_key].key,str) != 0) // loop until getting a empty cell if there is a collision
        return hash_function(key,i+1,table,size,str);
    else if(!strcmp(table[new_key].key,str)) // return -1 if the key is found
        return -1;
    strcpy(table[new_key].key,str);
    return new_key;
}

// Find hash 
int find_hash(int key,int i,HashTable *table,int size,char *str){
    int new_key = (key + i) % size;
	if (strcmp(table[new_key].key, str) != 0){
		return find_hash(key, i + 1, table, size, str);
	}
	if (!strcmp(table[new_key].key, str)){
		return new_key;
	}
	return -1;
}

int find_cell_index(HashTable *table,char*  key,int size){
    int new_key;
    // first convert string key to integer
    int k = 28,i,temp;
	long long int hash_key = 0;
    for(i=0;i<strlen(key);i++){
        temp = key[i];
        hash_key = k*hash_key + temp;
    }
	hash_key = abs(hash_key);
    new_key = find_hash(hash_key,0,table,size,key);
    return new_key;
}

int find_prime(int minSize){
	int i = minSize,j,flag=1;
	j = 2;
	while (j <= minSize / 2 && flag != 0){
		if (minSize % j == 0)
			flag = 0;
		j++;
		i++;
	}
	return i;
}

// create hash table 
void create_hash_table(HashTable *table,int size){
    int i;
	for (i=0;i<size;i++){
		table[i].links = NULL;
		strcpy(table[i].key, "#");
	}
}

// create cells of hash table
void create_array(HashTable *table,int size,Key *keys){
    // create linked ist for each key
    // first convert string key to integer
    int k = 28,i,temp;
	long long int hash_key = 0;
    for(i=0;i<strlen(keys->key);i++){
        temp = keys->key[i];
        hash_key = k*hash_key + temp;
    }
	hash_key = abs(hash_key);
    while(keys != NULL){
        hash_function(hash_key,0,table,size,keys->key);
        keys = keys->next;
    }
}

// print hash table 
void print_table(HashTable *table,int size){
    int i;
	printf("\n\n Table Size: %d\n\n",size);
    for (i=0;i<size;i++)
	{
		printf("Index: %d\tKEY: %s\t\n", i, table[i].key);
		Value *current = table[i].links;
		while (current != NULL)
		{
			printf("%s\n", current->link);
			current = current->next;
		}
	}
}

/* -------------- Key Operations -------------*/

Key *add_key(char *key, Key *head){
	Key *current = head;
	if (!strcmp(current->key, "?"))
	{
		strcpy(head->key, key);
		head->key_count = 1;
		return head;
	}

	while (current->next != NULL && strcmp(current->key,key) != 0)
		current = current->next;
	if (!strcmp(current->key,key))
		return head;
	current->next = (Key *)malloc(sizeof(Key));
	current->next->next = NULL;
	strcpy(current->next->key,key);
	head->key_count++;
	return head;
}


// delimeter for keys in hash table 
Key *delimeter(HashCells *head, Key *keys){
	// split categories based on spaces
	// put the keys in linked list of type Key

	char *str;
	char temp[50];
	while (head != NULL)
	{
		strcpy(str, head->key);
		int i = 0, j;
		while (i < strlen(str)){
			j = 0;
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '\r'){
				temp[j] = str[i];
				j++;
				i++;
			}
			temp[j] = '\0';
			i++;
			keys = add_key(temp, keys);
		}
		head = head->next;
	}
	return keys;
}

/* ---------- Hash Table Operations --------------------*/
HashTable *delimeter_cells(HashCells *head,HashTable *table,int size){
	// find the key and assign the link to it's key
	// some categories has more than one link
	// some links refer to many category

    char str[50];
	char temp[50];
	while (head != NULL){
		strcpy(str, head->key);
		int i = 0,j;
		while (i<strlen(str)){
			j = 0;
			while (str[i] != '\0' && str[i] != ' ' && str[i] != '\r'){
				temp[j] = str[i];
				j++;
				i++;
			}
			temp[j] = '\0';
			i++;
			int index = find_cell_index(table, temp, size);
			table[index].links = add_link(table, head->link, index);
		}
		head = head->next;
	}
	return table;
}

