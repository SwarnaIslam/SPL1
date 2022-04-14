#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<iostream>
#include<math.h>
using namespace std;
vector<int>data_index;
long long getHashValue(string operation){
    int p = 37;
    long long mod = 100103;
    long long power_of_p = 1;
    long long hashValue = 0;
    for (int i = 0;operation[i]!='\0'; i++) {
        hashValue= (hashValue+ (operation[i] - '$' + 1) * power_of_p)% mod;
        power_of_p= (power_of_p * p) % mod;
    }
    return (hashValue%mod + mod) % mod;
}
struct data_ht_item{
    string key="";
    int size=0;
    int *array;
};

struct data_linkedList{
    data_ht_item *dataItem;
    data_linkedList *next;
};

struct data_hashTable{
    data_ht_item **dataItems;
    data_linkedList **dataOverflowBuckets;
    int dataTableSize;
    int dataCount;
};

data_linkedList* allocateDataList(){
    data_linkedList *list=(data_linkedList*)malloc(sizeof(data_linkedList));
    return list;
}

data_linkedList* dataLinkedListInsert(data_linkedList* list, data_ht_item* item){
    data_linkedList *node=allocateDataList();
    node->dataItem=item;
    node->next=NULL;
    if(!list){
        list=node;
        return list;
    }
    data_linkedList* temp=list;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=node;
    return list;
}

data_linkedList** create_dataOverflowBuckets(data_hashTable* table){
    data_linkedList** buckets=(data_linkedList**)calloc(table->dataTableSize, sizeof(data_linkedList*));
    return buckets;
}

data_hashTable* create_dataTable(int size){
    data_hashTable *table=(data_hashTable*)malloc(sizeof(data_hashTable));

    table->dataTableSize=size;
    table->dataCount=0;
    table->dataItems=(data_ht_item**) calloc(table->dataTableSize,sizeof(data_ht_item*));

    for(int i=0;i<table->dataTableSize;i++){
        table->dataItems[i]=NULL;
    }
    table->dataOverflowBuckets=create_dataOverflowBuckets(table);
    return table;
}


void handle_dataCollison(data_hashTable* table, long long index, data_ht_item* item){
    data_linkedList* node=table->dataOverflowBuckets[index];

    if(node==NULL){
        node=allocateDataList();
        node->dataItem=item;
        table->dataOverflowBuckets[index]=node;
    }
    else{
        table->dataOverflowBuckets[index]=dataLinkedListInsert(node, item);
    }
}

data_ht_item* create_dataItem(string key, int size, int* array){
    data_ht_item *item=new data_ht_item;
    //data_ht_item *item=(data_ht_item*)malloc(sizeof(data_ht_item));

    item->key=key;
    item->size=size;
    item->array=array;
    cout<<item->array[0]<<endl;
    return item;
}

void data_ht_insert(data_hashTable *table, string key,int size,int* array){
    data_ht_item* item=create_dataItem(key,size,array);

    long long index=getHashValue(key);
    data_index.push_back(index);
    cout<<"HashValue: "<<index<<endl;
    data_ht_item* curr_item=table->dataItems[index];
    if(curr_item==NULL){
        table->dataItems[index]=item;
        table->dataCount++;
    }
    else{
        if(curr_item->key==key){
            curr_item->size=size;
            curr_item->array=array;
        }
        else{
            handle_dataCollison(table, index,item);
        }
    }
}
void print_data_table(data_hashTable* table) {
    printf("\n-------------------\n");
    int memory=0x10010000;
    for (int i:data_index) {
        if (table->dataItems[i]) {
            double size=table->dataItems[i]->size;
            double p=ceil(size/4)*4;
            cout<<table->dataItems[i]->key<<" ";
            printf("%#x\n",memory);
            memory+=p;
            if (table->dataOverflowBuckets[i]) {
                data_linkedList* head = table->dataOverflowBuckets[i];
                while (head) {
                    size=head->dataItem->size;
                    p=ceil(size/4)*4;
                    cout<<head->dataItem->key<<" ";
                    printf("%#x\n",memory);
                    head = head->next;
                    memory+=p;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}
 
int* ht_search(data_hashTable* table, string key){
    int index=getHashValue(key);
    data_ht_item *item=table->dataItems[index];
    data_linkedList* node=table->dataOverflowBuckets[index];

    while(item!=NULL){
        if(item->key==key){
            return item->array;
        }
        if(node==NULL){
            return NULL;
        }
        item=node->dataItem;
        node=node->next;
    }
    return NULL;
}
template<typename T1, typename T2>
struct BST{
    private:
        T1 labelName;
        T2 lineNumber;
        struct BST *right, *left;
        struct BST *newNode(T1 label, T2 line) {
            struct BST *temp = new BST;
            
            temp->labelName = label;
            temp->lineNumber =line;
            temp->left = temp->right = NULL;
            return temp;
        }
    public:
        struct BST *insertBST(T1 label, T2 line, struct BST *temp){
            if(temp==NULL){
                    temp=newNode(label, line);
                    return temp;
            }
            else if(label>temp->labelName)return insertBST(label, line, temp->right);
            else if(label<temp->labelName)return insertBST(label, line, temp->left);
        }
        T2 searchBST( struct BST *temp, T1 label){
            if(temp==NULL)
                return 0;
            else if (temp->labelName == label)
                return temp->lineNumber;
            
            if (temp->labelName < label)
            return searchBST(temp->right, label);

            return searchBST(temp->left, label);
        }
};

#endif