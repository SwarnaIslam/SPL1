#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<iostream>
#include<math.h>
using namespace std;
vector<int>data_index;
vector<int>text_index;
long long getHashValue(string operation){
    int p = 37;
    long long mod = 10009;
    long long power_of_p = 1;
    long long hashValue = 0;
    for (int i = 0;operation[i]!='\0'; i++) {
        hashValue= (hashValue+ (operation[i] - '$' + 1) * power_of_p)% mod;
        power_of_p= (power_of_p * p) % mod;
    }
    return (hashValue%mod + mod) % mod;
}
struct dataHashTableItem{
    string key="";
    int size=0;
    int *array;
};
struct textHashTableItem{
    string key;
    int line;
};
struct dataLinkedList{
    dataHashTableItem *dataItem;
    dataLinkedList *next;
};

struct textLinkedList{
    textHashTableItem *textItem;
    textLinkedList *next;
};

struct dataHashTable{
    dataHashTableItem **dataItems;
    dataLinkedList **dataOverflowBuckets;
    int dataTableSize;
};

struct textHashTable{
    textHashTableItem **textItems;
    textLinkedList **textOverflowBuckets;
    int textTableSize;
};

dataLinkedList* allocateDataList(){
    dataLinkedList *list=(dataLinkedList*)malloc(sizeof(dataLinkedList));
    return list;
}

textLinkedList* allocateTextList(){
    textLinkedList *list=(textLinkedList*)malloc(sizeof(textLinkedList));
    return list;
}

dataLinkedList* dataLinkedListInsert(dataLinkedList* list, dataHashTableItem* item){
    dataLinkedList *node=allocateDataList();
    node->dataItem=item;
    node->next=NULL;
    if(!list){
        list=node;
        return list;
    }
    dataLinkedList* temp=list;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=node;
    return list;
}

textLinkedList* textLinkedListInsert(textLinkedList* list, textHashTableItem* item){
    textLinkedList *node=allocateTextList();
    node->textItem=item;
    node->next=NULL;
    if(!list){
        list=node;
        return list;
    }
    textLinkedList* temp=list;
    while(1){
        if(temp->next!=NULL)
            temp=temp->next;
        if(temp->textItem->key==item->key){
            temp->textItem->line=item->line;
        }

        if(temp->next==NULL)break;
    }
    temp->next=node;
    return list;
}

dataLinkedList** create_dataOverflowBuckets(dataHashTable* table){
    dataLinkedList** buckets=(dataLinkedList**)calloc(table->dataTableSize, sizeof(dataLinkedList*));
    return buckets;
}

textLinkedList** create_textOverflowBuckets(textHashTable* table){
    textLinkedList** buckets=(textLinkedList**)calloc(table->textTableSize, sizeof(textLinkedList*));
    return buckets;
}

dataHashTable* createDataHashTable(int size){
    dataHashTable *table=(dataHashTable*)malloc(sizeof(dataHashTable));

    table->dataTableSize=size;
    table->dataItems=(dataHashTableItem**) calloc(table->dataTableSize,sizeof(dataHashTableItem*));

    for(int i=0;i<table->dataTableSize;i++){
        table->dataItems[i]=NULL;
    }
    table->dataOverflowBuckets=create_dataOverflowBuckets(table);
    return table;
}

textHashTable* createtextHashTable(int size){
    textHashTable *table=(textHashTable*)malloc(sizeof(textHashTable));

    table->textTableSize=size;
    table->textItems=(textHashTableItem**) calloc(table->textTableSize,sizeof(textHashTableItem*));

    for(int i=0;i<table->textTableSize;i++){
        table->textItems[i]=NULL;
    }
    table->textOverflowBuckets=create_textOverflowBuckets(table);
    return table;
}

void handle_dataCollison(dataHashTable* table, long long index, dataHashTableItem* item){
    dataLinkedList* node=table->dataOverflowBuckets[index];

    if(node==NULL){
        node=allocateDataList();
        node->dataItem=item;
        table->dataOverflowBuckets[index]=node;
    }
    else{
        table->dataOverflowBuckets[index]=dataLinkedListInsert(node, item);
    }
}

void handle_textCollison(textHashTable* table, long long index, textHashTableItem* item){
    textLinkedList* node=table->textOverflowBuckets[index];

    if(node==NULL){
        node=allocateTextList();
        node->textItem=item;
        table->textOverflowBuckets[index]=node;
    }
    else{
        table->textOverflowBuckets[index]=textLinkedListInsert(node, item);
    }
}

dataHashTableItem* create_dataItem(string key, int size, int* array){
    dataHashTableItem *item=new dataHashTableItem;
    //data_ht_item *item=(data_ht_item*)malloc(sizeof(data_ht_item));

    item->key=key;
    item->size=size;
    item->array=array;
    //cout<<item->array[0]<<endl;
    return item;
}
textHashTableItem* create_textItem(string key, int line){
    textHashTableItem *item=new textHashTableItem;

    item->key=key;
    item->line=line;
    return item;
}

void data_ht_insert(dataHashTable *table, string key,int size,int* array){
    dataHashTableItem* item=create_dataItem(key,size,array);

    long long index=getHashValue(key);
    data_index.push_back(index);

    dataHashTableItem* curr_item=table->dataItems[index];
    if(curr_item==NULL){
        table->dataItems[index]=item;
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

void text_ht_insert(textHashTable *table, string key,int line){
    textHashTableItem* item=create_textItem(key, line);

    long long index=getHashValue(key);
    text_index.push_back(index);

    textHashTableItem* curr_item=table->textItems[index];
    if(curr_item==NULL){
        table->textItems[index]=item;
    }
    else{
        if(curr_item->key==key){
            curr_item->line=line;
        }
        else{
            handle_textCollison(table, index,item);
        }
    }
}

void print_data_table(dataHashTable* table) {
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
                dataLinkedList* head = table->dataOverflowBuckets[i];
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
void print_text_table(textHashTable* table) {
    printf("\n-------------------\n");
    int memory=0x00400000 ;
    int p=0;
    for (int i:text_index) {
        if (table->textItems[i]) {
            int line=table->textItems[i]->line;
            cout<<table->textItems[i]->key<<" ";
            printf("%#x\n",memory+p);
            p=line*4;
            if (table->textOverflowBuckets[i]) {
                textLinkedList* head = table->textOverflowBuckets[i];
                while (head) {
                    line=head->textItem->line;
                    cout<<head->textItem->key<<" ";
                    printf("%#x\n",memory+p);
                    head = head->next;
                    p=line*4;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}
 
dataHashTableItem* data_ht_search(dataHashTable* table, string key){
    int index=getHashValue(key);
    dataHashTableItem *item=table->dataItems[index];
    dataLinkedList* node=table->dataOverflowBuckets[index];

    while(item!=NULL){
        if(item->key==key){
            return item;
        }
        if(node==NULL){
            return NULL;
        }
        item=node->dataItem;
        node=node->next;
    }
    return NULL;
}

textHashTableItem* text_ht_search(textHashTable* table, string key){
    int index=getHashValue(key);
    textHashTableItem *item=table->textItems[index];
    textLinkedList* node=table->textOverflowBuckets[index];

    while(item!=NULL){
        if(item->key==key){
            return item;
        }
        if(node==NULL){
            return NULL;
        }
        item=node->textItem;
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
            else if(label>temp->labelName){
                temp->right= insertBST(label, line, temp->right);
                return temp;
            }
            else if(label<temp->labelName){
                temp->left= insertBST(label, line, temp->left);
                return temp;
            }
        }
        T2 searchBST( struct BST *temp, T1 label){
            if(temp==NULL)
                return 0;
            else if (temp->labelName == label){
                //cout<<temp->labelName<<endl;
                return temp->lineNumber;
            }
            //cout<<temp->labelName<<endl;
            
            if (temp->labelName < label)
            return searchBST(temp->right, label);

            return searchBST(temp->left, label);
        }
        void free_children(struct BST *temp){
            if(temp->left!=NULL)free_children(temp->left);
            if(temp->right!=NULL)free_children(temp->right);
            free(temp);
        }
        // void printBST(BST* temp){
        //     if(temp==NULL)return;
        //     printBST(temp->left);
        //     printBST(temp->right);
        // }
};

#endif