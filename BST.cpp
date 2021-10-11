#include<bits/stdc++.h>
using namespace std;
#define ll                  int
#define rep(i,n)            for(ll i=0;i<n;i++)
#define hell                1000000007LL
#define vi                  vector<int>
#define vii                 vector< vi >
#define pb                  push_back
#define mp                  make_pair
#define fi                  first
#define se                  second
#define pii                 pair<int,int>
#define all(c)              c.begin(),c.end()
#define sz(c)               c.size()
#define fastio              ios_base::sync_with_stdio(false)
ll treesize=0;
ll Max(ll a, ll b) { return a > b ? a : b; }
ll Min(ll a, ll b) { return a < b ? a : b; }
struct Node
{
    ll data;
    struct Node *left,*right;
};
typedef struct Node node;
node* head;
void insert(ll a)
{
    if(treesize==0)
    {
        head=new node;
        head->data=a;
        head->left=NULL;
        head->right=NULL;
    }
    else
    {
        node *cnode;
        cnode= new node;
        cnode=head;
        while(true)
        {
            if(a>=cnode->data)
            {
                if(cnode->right==NULL)
                {
                    node *knode;
                    knode= new node;
                    (cnode->right)=knode;
                    knode->data=a;
                    knode->left=NULL;
                    knode->right=NULL;
                    break;
                }
                else cnode=cnode->right;
            }
            else
            {
                if(cnode->left==NULL)
                {
                    node* knode;
                    knode= new node;
                    (cnode->left)=knode;
                    knode->data=a;
                    knode->left=NULL;
                    knode->right=NULL;
                    break;
                }
                else cnode=cnode->left;
            }
        }
    }
    return;
}
bool del(ll a)
{
    if(treesize==0) return false;
    else if(head->data==a)
    {
        bool l=head->left==NULL;
        bool r=head->right==NULL;
        if(l&&r) head=NULL;
        else if(l) head=head->right;
        else if(r) head=head->left;
        else
        {
            node *knode,*par;
            knode=new node;
            par=new node;
            knode=head;
            par=head;
            knode=knode->right;
            ll z=knode->data,flag=0;
            while(knode->left!=NULL)
            {
                flag=1;
                par=knode;
                knode=knode->left;
                z=knode->data;
            }
            knode->data=a;
            head->data=z;
            if(flag==0) head->right=NULL;
            else par->left=knode->right;
        }
        return true;
    }
    else
    {
        node *cnode,*pa;
        cnode=new node;
        pa=new node;
        cnode=head;
        pa=head;
        while(true)
        {
            if(cnode==NULL) return false;
            else if(cnode->data==a)
            {
                bool l,r;
                l=cnode->left==NULL;
                r=cnode->right==NULL;
                if(l&&r)
                {
                    if(pa->left!=NULL && pa->left->data==a) pa->left=NULL;
                    else pa->right=NULL;
                }
                else if(l)
                {
                    if(pa->left!=NULL && pa->left->data==a) pa->left=cnode->right;
                    else pa->right=cnode->right;
                }
                else if(r)
                {
                    if(pa->left!=NULL && pa->left->data==a) pa->left=cnode->left;
                    else pa->right=cnode->left;
                }
                else
                {
                    node *knode,*par;
                    knode=new node;
                    par=new node;
                    knode=cnode;
                    par=cnode;
                    knode=knode->right;
                    ll z=knode->data,flag=0;
                    while(knode->left!=NULL)
                    {
                        flag=1;
                        par=knode;
                        knode=knode->left;
                        z=knode->data;
                    }
                    knode->data=a;
                    cnode->data=z;
                    if(flag==0) par->right=knode->right;
                    else par->left=knode->right;
                }
                return true;
            }
            else if(a>=cnode->data)
            {
                pa=cnode;
                cnode=cnode->right;
            }
            else
            {
                pa=cnode;
                cnode=cnode->left;
            }
        }
        return true;
    }
}
/*void inorder(node* temp)
{
    node *cnode;
    cnode=temp;
    if(cnode!=NULL)
    {
        inorder((cnode->left));
        cout<<(cnode->data)<<" ";
        inorder((cnode->right));
    }
    return;
}*/
bool sear(ll a)
{
    if(treesize==0) return false;
    else if(head->data==a)
    {
        return true;
    }
    else
    {
        node *cnode;
        cnode=new node;
        cnode=head;
        while(true)
        {
            if(cnode==NULL) return false;
            else if(cnode->data==a)
            {
                return true;
            }
            else if(a>=cnode->data)
            {
                cnode=cnode->right;
            }
            else
            {
                cnode=cnode->left;
            }
        }
        return true;
    }
}
void inorder()
{
    node *cnode;
    cnode=head;
    stack<node*> s;
    set<node*> se;
    while(true)
    {
        while(cnode!=NULL && se.find(cnode)==se.end())
        {
            s.push(cnode);
            se.insert(cnode);
            cnode=cnode->left;
        }
        if(!s.empty())
        {
            node* temp=s.top();
            cout<<temp->data<<" ";
            cnode=temp->right;
            s.pop();
        }
        else break;
    }
}
int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    fastio;
    cin.tie(0);
    cout.tie(0);
    ll q;
    cout<<"Number of queries: "<<endl;
    cin>>q;
    rep(i,q)
    {
        ll t;
        cout<<"1.Insert new node"<<endl<<"2.Delete node"<<endl<<"3.Search node"<<endl<<"4.Inorder traversal"<<endl;
        cin>>t;
        if(t==1)
        {
            cout<<"Enter value: "<<endl;
            ll a;
            cin>>a;
            insert(a);
            treesize++;
        }
        else if(t==2)
        {
            cout<<"Enter value: "<<endl;
            ll a;
            cin>>a;
            bool c=del(a);
            if(c) treesize--;
        }
        else if(t==3)
        {
            cout<<"Enter value: "<<endl;
            ll a;
            cin>>a;
            bool c=sear(a);
            if(c) cout<<"Found"<<endl;
            else cout<<"Not Found"<<endl;
        }
        else
        {
            cout<<"Total nodes: "<<treesize<<endl;
            //inorder(head);
            inorder();
            cout<<endl;
        }

    }
    return 0;
}
