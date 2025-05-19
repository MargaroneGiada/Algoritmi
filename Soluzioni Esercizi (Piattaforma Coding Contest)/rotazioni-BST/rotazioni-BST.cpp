#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class Node{
    private:
        Node<T> *p, *l, *r;
        T *k;
    
    public:
        Node(T* k = NULL, Node<T> *p = NULL, Node<T> *l = NULL, Node<T> *r = NULL){
            this->p = p;
            this->l = l;
            this->r = r;
            this->k = k;
        }

        void setParent(Node<T> *p){this->p = p;}
        void setLeft(Node<T> *p){this->l = p;}
        void setRight(Node<T> *p){this->r = p;}
        void setKey(T *p){this->k = p;}

        Node<T>* getParent(){return p;}
        Node<T>* getLeft(){return l;}
        Node<T>* getRight(){return r;}
        T* getKey(){return k;}
};

template<class T>
class BST{
    private:
        Node<T> *root, *current;
        int n;

        Node<T>* _search(Node<T> *x, T k){
            if(*x->getKey()==k || !x){
                return x;
            }
            if(k<=*x->getKey()){
                return _search(x->getLeft(), k);
            }
            return _search(x->getRight(), k);
        }

        Node<T>* _min(Node<T> *x){
            if(!x || !x->getLeft())
                return x;
            return _min(x->getLeft());
        }

        void _canc(Node<T> *x, T k){
            Node<T> *tmp = _search(x, k);
            if(!tmp){
                return;
            }

            if(tmp->getLeft() && tmp->getRight()){
                Node<T> *min = _min(tmp->getRight());
                tmp->setKey(min->getKey());
                _canc(min, *min->getKey());
            }else{
                Node<T> *son = tmp->getLeft();
                if(!son){
                    son = tmp->getRight();
                }
                Node<T> *p = tmp->getParent();
                if(p){
                    if( k < *p->getKey()){
                        p->setLeft(son);
                    }
                    else{
                        p->setRight(son);
                    }
                }else{
                    root=son;
                }
                if(son){
                    son->setParent(p);
                }
                n--;
            }
        }

        void insertNodeUp(Node<T> *before, Node<T> *node){
            if(before->getParent() != NULL){
                if(before == before->getParent()->getLeft()){
                    before->getParent()->setLeft(node);
                }else if(before == before->getParent()->getRight()){
                    before->getParent()->setRight(node);
                }
            }else{
                root = node;
            }
            node->setParent(before->getParent());
            before->setParent(node);
        }

        void _leftRotate(Node<T> *node){
            if(!node->getRight()){
                return;
            }
            Node<T> *nParent = node->getRight();
            insertNodeUp(node, nParent);
            node->setRight(nParent->getLeft());
            if(nParent->getLeft() != NULL){
                nParent->getLeft()->setParent(node);
            }
            nParent->setLeft(node);
        }

        void _rightRotate(Node<T> *node){
            if(!node->getLeft()){
                return;
            }
            Node<T> *nParent = node->getLeft();
            insertNodeUp(node, nParent);
            node->setLeft(nParent->getRight());
            if(nParent->getRight() != NULL){
                nParent->getRight()->setParent(node);
            }
            nParent->setRight(node);
        }

        void _inorder(Node<T> *x, ostream &out){
                if(!x){
                    return;
                }
                _inorder(x->getLeft(), out);
                out << *x->getKey() << " ";
                _inorder(x->getRight(), out);
        }

        void _postorder(Node<T> *x, ostream &out){
                if(!x){
                    return;
                }
                _postorder(x->getLeft(), out);
                _postorder(x->getRight(), out);
                out << *x->getKey() << " ";
        }

        void _preorder(Node<T> *x, ostream &out){
                if(!x){
                    return;
                }
                out << *x->getKey() << " ";
                _preorder(x->getLeft(), out);
                _preorder(x->getRight(), out);
        }
    
    public:
        BST(){
            root = current = NULL;
            n = 0;
        }

        BST<T> *insert(T x){
            Node<T> *tmp = root;
            Node<T> *p = NULL;

            while(tmp){
                p = tmp;
                if( x <= *(tmp->getKey()))
                    tmp = tmp->getLeft();
                else
                    tmp = tmp->getRight();
            }

            Node<T> *y = new Node<T>(new T(x), p);

            if(!p)
                root = y;
            else if(x <= *(p->getKey()))
                p->setLeft(y);
            else
                p->setRight(y);
            n++;
            return this;
        }

        void LeftRotate(T x){
            Node<T> *tmp = _search(root, x);
            if(tmp)
                _leftRotate(tmp);
        }

        void RightRotate(T x){
            Node<T> *tmp = _search(root, x);
            if(tmp)
                _rightRotate(tmp);
        }

        void canc(T x){
            _canc(root, x);
        }

        void inorder(ostream &out){
            _inorder(root, out);
            out << endl;
        }

        void postorder(ostream &out){
            _postorder(root, out);
            out << endl;
        }

        void preorder(ostream &out){
            _preorder(root, out);
            out << endl;
        }

        int getSize() const {return n;}
};

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");

    string t;
    char op;
    int N = 0, R = 0;
    double x = 0.0;
    BST<double> *b;

    for(int i = 0; i < 100; i++){
        in >> t >> N >> R >> t;
        b = new BST<double>();

        for(int g = 0; g < N; g++){
            in >> op;
            if(op == 'i'){
                in >> op >> op >> op >> x;
                b->insert(x);
            }else{
                in >> op >> op >> op >> op >> x;
                b->canc(x);
            }
        }
        for(int g = 0; g < R; g++){
            in >> op;
            if( op ==  'r'){
                in >> op >> op >> op >> op >> op >> x;
                b->RightRotate(x);
            }else{
                in >> op >> op >> op >> op >> x;
                b->LeftRotate(x); 
            }
        }
        if( t == "inorder"){
            b->inorder(out);
        }else if( t == "preorder"){
            b->preorder(out);
        }else if( t == "postorder"){
            b->postorder(out);
        }

        delete b;
    }

    in.close();
    out.close();
}
