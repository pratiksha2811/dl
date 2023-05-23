#include<iostream>
#include<omp.h>
#include<queue>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void pBFS(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int qs = q.size();
        #pragma omp parallel for
        for(int i = 0; i < qs; i++){
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                cout << node->val << " ";
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
    }
}


int main(){
    // Construct Tree
    int temp[7];
    cout<<"Enter values : ";
    for(int i=0;i<7;i++){
        cin>>temp[i];
    }
    TreeNode* tree = new TreeNode(temp[0]);
    tree->left = new TreeNode(temp[1]);
    tree->right = new TreeNode(temp[2]); 
    tree->left->left = new TreeNode(temp[3]);
    tree->left->right = new TreeNode(temp[4]);
    tree->right->left = new TreeNode(temp[5]);
    tree->right->right = new TreeNode(temp[6]);
    

    /*
    Our Tree Looks like this:
                1
            2       3
        4     5   6    7
        
    */

    cout << "Parallel BFS: ";
    pBFS(tree);
}