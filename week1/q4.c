//AUTHOR :SAGNIK CHATTERJEE 
//DATE  : DEC 8,2020
//Usage : 

//given an input stmt we have to identifes the verbs present in them 
//and then insert the string into the hash table
//  search by key in the hash table , if already present return the hash value of the eelement 

//Hash Table Ref: https://www.journaldev.com/35238/hash-table-in-c-plus-plus
//Better Reference : https://gist.github.com/phsym/4605704

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 50000 //size of the hash table 

//Hashtable element structure 
typedef struct hash_elem_t{
    struct hash_elem_t* next; //next element in case of collision 
    void *data; //pointer to the stored eleemnt 
    char key[];//key of the stores element 
}hash_elem_t;

//  Hashtable structure 
typedef struct {
    unsigned int capacity;//the capacity for the hashtable
    unsigned int e_num; //number of elements currently stored in the hashtable
    hash_elem_t** table;//table containing elements 
}hashtable_t ;


//structure used for iterations 
typedef struct {
    hashtable_t * ht;//hashtbale in which we can iterate 
    unsigned int index; //current index in the table
    hash_elem_t* elem; //current element in the list
}hash_elem_t;

//hashtable interator initilaizor on hashable ht 
#define HT_ITERATOR(ht) {
    ht ,0 ,ht->table[0];
}

char err_ptr; 
void* HT_ERROR = &err_ptr ; /// Data pointing to HT_ERROR are returned in case of error

//hash value calcualtion on the values , key must end with '\0' character 
//DJB algo 
static unsigned int ht_calc_hash(char *key){
    unsigned int hash =5381;
    int c;
    while((c= *str++)!=0){
        hash= ((hash <<5)+hash)+c;
    }
}







int main(){
    char buffer[100];
    printf("Enter the input stmt \n");
    scanf("%s",buffer);
    
}