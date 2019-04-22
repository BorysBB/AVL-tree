#include <iostream>
#include <iomanip>
using namespace std;
class Iterator;
template<typename Key, typename Info>
class Dictionary
{
    struct node{
    Key key;
    Info info;
    node *left;
    node *right;
    };
    node *root;
    node* add_node_private(Key k, Info i, node *Ptr)
    {
        if(Ptr == NULL)
        {
            Ptr=new node;
            Ptr->key = k;
            Ptr->info = i;
            Ptr->left = NULL;
            Ptr->right=NULL;
        }
        else if(Ptr->key == k)
        {
//            cout<<"No duplicates allowed"<<endl;
        }
        else if(k < Ptr->key)
        {
            Ptr->left = add_node_private(k, i, Ptr->left);
            Ptr=balance(Ptr);
        }
        else if(k > Ptr->key)
        {
            Ptr->right=add_node_private(k,i,Ptr->right);
            Ptr=balance(Ptr);
        }
        return Ptr;
    }

    int height_private(node *Ptr)
    {
    int h = 0;
    if(Ptr==NULL)
    {
        return 0;
    }
    else
    {
        int left_height=0;
        int right_height=0;
        left_height = height_private(Ptr->left);
        right_height = height_private(Ptr->right);
        int max_height = max(left_height, right_height);
        h = max_height+1;
    }
    return h;
    }
    int diff(node *Ptr)
    {
        int l_height = height_private(Ptr->left);
        int r_height = height_private(Ptr->right);
        int balance_factor = l_height - r_height;   ///definition of the balance factor
        return balance_factor;
    }
    void print_in_order_private(node *Ptr)
    {
    if(root!=NULL)
    {
        if(Ptr->left != NULL)
        {
            print_in_order_private(Ptr->left);
        }
        cout<<Ptr->key<<endl;
        cout<<"The height of the subtree of this node: "<<height_private(Ptr)-1<<endl;
        cout<<"balance factor of"<<Ptr->key<<": "<<diff(Ptr);
        cout<<endl;
        if(Ptr->right != NULL)
        {
            print_in_order_private(Ptr->right);
        }
    }
    else
    {
        cout<<"Tree is empty"<<endl;
    }
    }
    void print_reverse_order_private(node *Ptr)
    {
    if(root!=NULL)
    {
        if(Ptr->right != NULL)
        {
            print_reverse_order_private(Ptr->right);
        }
        cout<<Ptr->key<<endl;
        cout<<"The height of the subtree of this node: "<<height_private(Ptr)-1<<endl;
        cout<<"balance factor of"<<Ptr->key<<": "<<diff(Ptr);
        cout<<endl;
        if(Ptr->left != NULL)
        {
            print_reverse_order_private(Ptr->left);
        }
    }
    else
    {
        cout<<"Tree is empty"<<endl;
    }
    }
    void print_private(node *root, int space)
    {
        if(root == NULL)
        {
            cout<<" * "<<endl;
        }
        else
        {
            print_private(root->right, space+15);
            cout << setw(space) << " " << root->key << " " << root->info;
            print_private(root->left, space+15);
        }
    }
    node* remove_private(Key k, node *Ptr)
    {
        node *delPtr;
        /// empty tree
        if(Ptr == NULL)
        {
            cout<<"Tree is empty"<<endl;
            return Ptr;
        }
        else if(root->key == k && root->left==NULL && root->right==NULL)
        {
            remove_tree_private(root);
            return Ptr;
        }
        /// looking for element
        else if(k<Ptr->key)
        {
            Ptr->left = remove_private(k, Ptr->left);
        }
        else if(k>Ptr->key)
        {
            Ptr->right = remove_private(k, Ptr->right);
        }
        ///element with 0 children
        else if(Ptr->left==NULL && Ptr->right==NULL)
        {
            delPtr = Ptr;
            Ptr=NULL;
            delete delPtr;
//            return NULL;
        }
        ///element with 1 child
        else if(Ptr->left==NULL && Ptr->right!=NULL)
        {
            delPtr = Ptr;
            Ptr=Ptr->right;
            delete delPtr;
//            return Ptr;
        }
        else if(Ptr->left!=NULL && Ptr->right==NULL)
        {
            delPtr = Ptr;
            Ptr=Ptr->left;
            delete delPtr;
//            return Ptr;
        }
        ///element with 2 children
        else
        {
            delPtr = find_smallest(Ptr->right);
            Ptr->key = delPtr->key;
            Ptr->info = delPtr->info;
            Ptr->right = remove_private(Ptr->key, Ptr->right);
        }
        if(Ptr==NULL)
        {
            return Ptr;
        }
        ///balancing part
        Ptr=balance(Ptr);
//        return Ptr;
    }

    node* find_smallest(node* Ptr)
    {
        if(root == NULL)
        {
            return Ptr;
        }
        else
        {
            if(Ptr->left!=NULL)
            {
                return find_smallest(Ptr->left);
            }
            else
            {
                return Ptr;
            }
        }
    }
    void remove_tree_private(node *&Ptr)
    {
        if(Ptr != NULL)
        {
            remove_tree_private(Ptr->left);
            remove_tree_private(Ptr->right);
            delete Ptr;
            Ptr = NULL;
        }
    }
    node* copy_tree_private(node *lhs, node * const source)
    {
        if(lhs != source)   ///avoid self-copy
        {
            if(source == NULL)
            {
                return NULL;
            }
            else
            {
                lhs = add_node_private(source->key, source->info, source);
                lhs->left = copy_tree_private(lhs->left, source->left);
                lhs->right = copy_tree_private(lhs->right, source->right);
                return lhs;
            }
        }
        return lhs;
    }
    void plus_operator_helper(node * const n)
    {
        if(n == NULL)
        {
            return;
        }
        else
        {
            plus_operator_helper(n->left);
            add_node(n->key, n->info);
            plus_operator_helper(n->right);
        }
    }
    void minus_operator_helper(node * const n)
    {
        if(n==NULL)
        {
            return;
        }
        else
        {
            minus_operator_helper(n->left);
            remove(n->key);
            minus_operator_helper(n->right);
        }
    }
    node *balance(node *temp)
    {
    int bal_factor = diff(temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
        {
//            cout<<"rotation ll on: "<<temp->key<<endl;
            temp = ll_rotation (temp);
        }
        else
        {
//            cout<<"rotation lr on: "<<temp->key;
            temp = lr_rotation (temp);
        }
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
        {
//            cout<<"rotation rl on: "<<temp->key<<endl;
            temp = rl_rotation (temp);
        }
        else
        {
//            cout<<"rotation rr on: "<<temp->key<<endl;
            temp = rr_rotation (temp);
        }
    }
    return temp;
    }
node* rr_rotation(node *parent)
{
    if(parent == root)
    {
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    root=temp;
    return temp;
    }
    else
    {
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
    }
}
node *ll_rotation(node *parent)
{
    if(parent==root)
    {
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    root=temp;
    return temp;
    }
    else
    {
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
    }
}
node *lr_rotation(node *parent)
{
    node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
node *rl_rotation(node *parent)
{
    node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
void print_leaves_private(node *Ptr)
{
    if(Ptr==NULL)
    {
        return;
    }
    else
    {
    print_leaves_private(Ptr->left);
    if(Ptr->left==NULL && Ptr->right==NULL)
    {
        cout<<"-----------"<<endl;
        cout<<"Leaf: "<<endl;
        cout<<"Key: "<<Ptr->key<<endl;
        cout<<"Info: "<<Ptr->info<<endl;
        cout<<"-----------"<<endl;
    }
    print_leaves_private(Ptr->right);
    }
}
void print_by_info_private(node* Ptr, Info condition)
{
    if(Ptr==NULL)
    {
        return;
    }
    else
    {
        print_by_info_private(Ptr->left, condition);
        if(Ptr->info==condition)
        {
            cout<<"Key: "<<Ptr->key<<endl;
            cout<<"Info: "<<Ptr->info<<endl;
            cout<<" "<<endl;
        }
        print_by_info_private(Ptr->right, condition);
    }
}

public:

        class Iterator{
        node* iterator;
        public:
        Iterator()
        {
        iterator = NULL;
        }
        Iterator(node *source)// copyconstructor
        {
            iterator = source;
        }
        const Iterator &operator = (const Iterator &copyIter)
        {
            iterator = copyIter.iterator;
            return *this;
        }
        bool operator == (const Iterator &compare)const
        {
            return iterator == compare.iterator;
        }
        Iterator operator ++ ()
        {
            if(iterator->right!=NULL)
            {
                iterator = iterator->right;
            }
            return *this;
        }
        Iterator operator ++ (int)
        {
            Iterator copy_i(iterator);
            if(iterator->right != NULL)
                iterator = iterator->right;
            return copy_i;
        }
        Iterator operator -- ()
        {
            if(iterator->left!=NULL)
                iterator = iterator->left;
            return *this;
        }
        Iterator operator -- (int)
        {
            Iterator copy_i(iterator);
            if(iterator->left != NULL)
                iterator = iterator->left;
            return copy_i;
        }
        Key getKey()
        {
            return iterator->key;
        }
        Info getInfo()
        {
            return iterator->info;
        }
        bool isnull()
        {
            if(iterator)
            {
                return false;
            }
            else
            {
            return true;
            }
        }
        void print_iterator()
        {
            cout<<"Key: "<<iterator->key<<endl;
            cout<<"Value: "<<iterator->info<<endl;
        }
        bool operator != (const Iterator &compare)const
        {
            return iterator != compare.iterator;
        }
};
    Dictionary();
    ~Dictionary();
    Dictionary(const Dictionary &source);
    void add_node(const Key &k, const Info &i);
    void print_in_order();
    void print_reverse_order();
    void print();
    void print_leaves();
    void print_by_info(Info info);
    void remove(Key key);
    void remove_tree();
    Dictionary &operator = (const Dictionary &source);
    Dictionary &operator + (const Dictionary &n);
    Dictionary &operator - (const Dictionary &n);
    Iterator begin()const
    {
        return Iterator(root);
    }


};
///constructor
template<typename Key, typename Info>
Dictionary<Key, Info>::Dictionary()
{
    root = NULL;
}
///copy constructor
template<typename Key, typename Info>
Dictionary<Key, Info>::Dictionary(const Dictionary &source)
{
//    remove_tree();
    root=copy_tree_private(root, source.root);
}
///destructor
template<typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary()
{
//    root = NULL;
remove_tree_private(root);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::print_in_order()
{
    print_in_order_private(root);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::print_reverse_order()
{
    print_reverse_order_private(root);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::add_node(const Key &k, const Info &i)
{
    root=add_node_private(k, i, root);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::print()
{
    print_private(root, 0);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::remove(Key key)
{
    remove_private(key, root);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::remove_tree()
{
    remove_tree_private(root);
}
template<typename Key, typename Info>
Dictionary<Key, Info> &Dictionary<Key, Info>::operator = (const Dictionary<Key, Info> &source)
{
    remove_tree();
    root = copy_tree_private(root, source.root);
}
template<typename Key, typename Info>
Dictionary<Key, Info> &Dictionary<Key, Info>::operator + (const Dictionary<Key, Info> &n)
{
    plus_operator_helper(n.root);
}
template<typename Key, typename Info>
Dictionary<Key, Info> &Dictionary<Key, Info>::operator - (const Dictionary<Key, Info> &n)
{
    minus_operator_helper(n.root);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::print_leaves()
{
    print_leaves_private(root);
}
template<typename Key, typename Info>
void Dictionary<Key, Info>::print_by_info(Info info)
{
    cout<<"Nodes with info: "<<info<<endl;
    print_by_info_private(root, info);
}

int main()
{
    Dictionary<int, int>T1;
    T1.add_node(50,50);
    T1.add_node(40,50);
    T1.add_node(75,75);
    T1.add_node(30,50);
    T1.add_node(35,35);
    T1.add_node(60,60);
    T1.add_node(80,80);
    T1.add_node(55,55);
    T1.add_node(78,78);
    T1.add_node(90,90);
    T1.add_node(95,95);
    T1.print();
cout<<"______________"<<endl;
cout<<"Iterator"<<endl;
Dictionary<int,int>::Iterator iterator1;
iterator1=T1.begin();
iterator1.print_iterator();
iterator1--;
iterator1--;
iterator1--;
iterator1.print_iterator();
cout<<"______________"<<endl;
cout<<"Print in order:"<<endl;
T1.print_in_order();
cout<<"______________"<<endl;
cout<<"Print reverse order:"<<endl;
T1.print_reverse_order();
cout<<"______________"<<endl;
cout<<"Print leaves:"<<endl;
T1.print_leaves();
cout<<"______________"<<endl;
cout<<"removing node :"<<endl;
T1.remove(95);
T1.print();
T1.print_leaves();
cout<<"______________"<<endl;
cout<<"copy constructor :"<<endl;
Dictionary<int, int>T3(T1);
T1.print();
cout<<"______________"<<endl;
T3.print();
cout<<"______________"<<endl;
cout<<"printing all nodes with given info :"<<endl;
T1.print_by_info(50);
cout<<"______________"<<endl;
cout<<"removing nodes and the tree :"<<endl;
T3.remove(50);
T3.print();
cout<<"______________"<<endl;
T3.remove(75);
T3.print();
T3.remove_tree();
T3.remove_tree();
T3.print();
T3.print_in_order();
T3.print_reverse_order();
T3.print_leaves();



Dictionary<int, int>T2;
T2.add_node(4,4);
T2.add_node(2,2);
T2.add_node(6,6);
T2.add_node(3,3);
T2.add_node(5,5);
T2.add_node(8,8);
T2.add_node(7,7);
T2.add_node(9,9);

Dictionary<int, int>T4;
T4.add_node(40,40);
T4.add_node(22,22);
T4.add_node(60,60);
T4.add_node(30,30);
T4.add_node(50,50);
T4.add_node(80,80);

cout<<"______________"<<endl;
cout<<"overloaded operators test:"<<endl;
cout<<"______________"<<endl;
cout<<"overloaded operators +:"<<endl;
T2+T4;
T2.print();
T2-T4;
cout<<"______________"<<endl;
T2.print();
cout<<"______________"<<endl;
T4=T2;
T2.print();
cout<<"______________"<<endl;
T4.print();


    return 0;
}
