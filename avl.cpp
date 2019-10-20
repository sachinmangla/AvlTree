#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct node {
    node* lchild;
    int data;
    int height;
    node* rchild;

    node(int data) : lchild{ nullptr }, data{ data }, height{ 1 }, rchild{ nullptr } {
        //node
    } 
} *Root = nullptr;

class AVL {

private:
    
    node* LLRotation(node* root) {
        node* rootL = root->lchild;
        node* rootLR = rootL->rchild;

        rootL->rchild = root;
        root->lchild = rootLR;
        root->height = node_height(root);
        rootL->height = node_height(rootL);

        if(Root == root) {
            Root = rootL;
        }

        return rootL;
    }

    node* RRRotation(node* root) {
        node* rootR = root->rchild;
        node* rootRL = rootR->lchild;

        rootR->lchild = root;
        root->rchild = rootRL;
        root->height = node_height(root);
        rootR->height = node_height(rootR);

        if(Root == root) {
            Root = rootR;
        }

        return rootR;
    }

    node* LRRotation(node* root) {
        node* rootL = root->lchild;
        node* rootLR = rootL->rchild;

        rootL->rchild = rootLR->lchild;
        root->lchild = rootLR->rchild;
        rootLR->lchild = rootL;
        rootLR->rchild = root;

        rootL->height = node_height(rootL);
        root->height = node_height(root);
        rootLR->height = node_height(rootLR);

        if(root == Root)
            Root = rootLR;

        return rootLR;
    }

    node* RLRotation(node* root) {
        node* rootR = root->rchild;
        node* rootRL = rootR->lchild;

        rootR->lchild = rootRL->rchild;
        root->rchild = rootRL->lchild;
        rootRL->rchild = rootR;
        rootRL->lchild = root;
        
        rootR->height = node_height(rootR);
        root->height = node_height(root);
        rootRL->height = node_height(rootRL);

        if(root == Root)
            Root = rootRL;

        return rootRL;
    }

    int BalanceFactor(node* root) {
        int hL, hR;
        hL = root && root->lchild ? root->lchild->height : 0;
        hR = root && root->rchild ? root->rchild->height : 0; 
        return hL - hR;
    } 

    int node_height(node* root) {
        int hL, hR;
        hL = root && root->lchild ? root->lchild->height : 0;
        hR = root && root->rchild ? root->rchild->height : 0; 
        return hL > hR ? hL + 1 : hR + 1;
    }

public:

    node* RInsert(node* root, int Key) {
        if(root == nullptr) {
            node* new_node = new node(Key);
            return new_node;
        }
        if(root->data > Key) {
            root->lchild = RInsert(root->lchild, Key);
        }
        else {
            root->rchild = RInsert(root->rchild, Key);
        }
        root->height = node_height(root);

        if(BalanceFactor(root) == 2 && BalanceFactor(root->lchild) == 1) {
            return LLRotation(root);
        }
        else if(BalanceFactor(root) == 2 && BalanceFactor(root->lchild) == -1) {
            return LRRotation(root);
        }
        else if(BalanceFactor(root) == -2 && BalanceFactor(root->rchild) == -1) {
            return RRRotation(root);
        }
        else if(BalanceFactor(root) == -2 && BalanceFactor(root->rchild) == 1) {
            return RLRotation(root);
        }

        return root;
    }

    void LevelOrder(node* root) {
        node* temp = nullptr;
        if(root == nullptr) {
            return;
        }
        queue<node*> q;
        q.push(root);

        while(!q.empty()) {
            temp = q.front();
            cout << temp->data << " ";
            if(temp->lchild != nullptr) {
                q.push(temp->lchild);
            }
            if(temp->rchild != nullptr) {
                q.push(temp->rchild);
            }
            
            q.pop();
        }
    }

    void preorder(node* root) {
        if(root != nullptr) {
            cout << root->data << " ";
            preorder(root->lchild);
            preorder(root->rchild);
        }
    }

    void inorder(node* root) {
        if(root != nullptr) {
            inorder(root->lchild);
            cout << root->data << " ";
            inorder(root->rchild);
        }
    }

     void postorder(node* root) {
        if(root != nullptr) {
            postorder(root->lchild);
            postorder(root->rchild);
            cout << root->data << " ";
        }
    }
};

int main() 
{
    AVL tree;

    int size;
    cout << "\nEnter num of node :- "; cin >> size;

    vector<int> vec;
    vec.reserve(size);

    cout << "\nEnter values :- ";
    for(int i = 0; i < size; i++) {
        int x; cin >> x;
        vec.push_back(x);

    }

    Root = tree.RInsert(Root, vec[0]);
    for(int i = 1; i < size; i++) {
        tree.RInsert(Root, vec[i]);
    }
    
    cout << "\nLevelOrder Traversal is:- " << '['; tree.LevelOrder(Root); cout <<']';
    cout << "\nInOrder Traversal is:- " << '['; tree.inorder(Root); cout <<']';
    cout << "\nPostOrder Traversal is:- " << '['; tree.postorder(Root); cout <<']';
    cout << "\nPreOrder Traversal is:- " << '['; tree.preorder(Root); cout <<']';
    cout << "\n\nRoot node is :- " << Root->data;

    return 0;

}