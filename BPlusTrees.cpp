#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
    Node* parent;
    bool leaf;
    bool root;
    vector<int> data;
    vector<Node*> children;
    int order;
    
    Node(){};
    
    Node(int order, Node* parent){
        this->order = order;
        this->children.push_back(NULL);
        this->parent = parent;
        this->leaf = false;
        this->root = false;
    };
    
    Node* search(int value){
        vector<int>::iterator it;
        vector<Node*>::iterator node_it = this->children.begin();
        for(it = this->data.begin(); it != this->data.end(); it++){
            if(*it > value)
                break;
            node_it++;
        }
        return *node_it;
    }
    
    void insert(int value, Node* ptr){
        vector<int>::iterator it;
        vector<Node*>::iterator node_it = this->children.begin();
        bool flag = false;
        for(it = this->data.begin(); it != this->data.end(); it++){
            node_it++;
            if(*it > value){
                flag = true;
                break;
            }
        }
        if(!flag){
            this->data.push_back(value);
            if(this->leaf)
                this->children.insert(node_it, ptr);
            else
                this->children.push_back(ptr);
        }
        else{
            this->data.insert(it, value);
            this->children.insert(node_it, ptr);
        }
        return;
    }
    
};

class BPTrees{
public:
    Node* root;
    int order;
    int node_count;
    
    BPTrees(int order){
        this->order = order;
        this->root = new Node(order, NULL);
        this->root->leaf = true;
        this->root->root = true;
        this->node_count = 0;
    }
    
    Node* split(Node* node){
        Node* split_node = new Node(order, NULL);
        int mid = (node->order + 1)/2;
        int split_key = node->data[mid];
        vector<int> temp = node->data;
        vector<Node*> temp_ptr = node->children;
        if(node->leaf){
            split_node->leaf = true;
            node->data = vector<int>(temp.begin(), temp.begin() + mid);
            split_node->data = vector<int>(temp.begin() + mid, temp.end());
            node->children = vector<Node*>(temp_ptr.begin(), temp_ptr.begin() + mid);
            split_node->children = vector<Node*>(temp_ptr.begin() + mid, temp_ptr.end());
            node->children.push_back(split_node);
        }
        else{
            node->data = vector<int>(temp.begin(), temp.begin() + mid);
            split_node->data = vector<int>(temp.begin() + mid + 1, temp.end());
            node->children = vector<Node*>(temp_ptr.begin(), temp_ptr.begin() + mid + 1);
            split_node->children = vector<Node*>(temp_ptr.begin() + mid + 1, temp_ptr.end());
        }
        for(int i = 0; i < node->children.size(); i++)
            if(node->children[i] != NULL)
                node->children[i]->parent = node;
        for(int i = 0; i < split_node->children.size(); i++)
            if(split_node->children[i] != NULL)
                split_node->children[i]->parent = split_node;
        if(node->root){
            node->root = false;
            this->root = new Node(order, NULL);
            this->root->root = true;
            this->root->data.push_back(split_key);
            this->root->children[0] = node;
            this->root->children.push_back(split_node);
            node->parent = split_node->parent = this->root;
        }
        else{
            split_node->parent = node->parent;
            node->parent->insert(split_key, split_node);
            if(node->parent->data.size() == (this->order + 1))
                node->parent = split_node->parent = this->split(node->parent);
        }
        return split_node;
    }

    bool insert(int value){
        Node* node = this->root;
        while(!node->leaf)
            node = node->search(value);
        vector<int>::iterator it;
        for(it = node->data.begin(); it != node->data.end(); it++)
            if(*it == value)
                return false;
        node->insert(value, NULL);
        if(node->data.size() == (this->order + 1))
            this->split(node);
        return true;
    }
    
    void print(){
        return;
    }
};

int main(int argc, const char * argv[]) {
    /*cout << "Help:\n----\n[i]nsert\n[p]rint tree\n[h]elp\n[q]uit\n" << endl;
    cout << "Input Tree Order: ";
    int order;
    cin >> order;
    BPTrees* tree = new BPTrees(order);
    char command;
    int value;
    while(true){
        cout << "Input a command: ";
        cin >> command;
        switch(command){
            case 'i':
                cout << "<value>: ";
                cin >> value;
                tree->insert(value);
                break;
            case 'p':
                cout << tree << endl;
                break;
            case 'h':
                cout << "Help:\n----\n[i]nsert\n[p]rint tree\n[h]elp\n[q]uit\n" << std::endl;
                break;
            case 'q':
                return 0;
                break;
            default:
                std::cout << "Invalid Command" << std::endl;
        }
    }*/
    BPTrees* tree = new BPTrees(2);
    tree->insert(3);
    tree->insert(8);
    tree->insert(6);
    tree->insert(13);
    tree->insert(18);
    tree->insert(16);
    tree->insert(7);
    tree->insert(2);
    tree->insert(12);
    tree->insert(11);
    tree->insert(17);
    tree->insert(1);
    tree->insert(5);
    return 0;
}
