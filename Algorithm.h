#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<iostream>
using namespace std;

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