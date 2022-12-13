#ifndef BINTREE
#define BINTREE

#include <iostream>
#include <stack>

using namespace std;


class BinTree {

protected:

    struct BiTNode {
        char data;
        BiTNode *lchild, *rchild;
    };

    BiTNode *root{};

public:

    class Iterator {
        friend class BinTree;

    protected:
        BiTNode *ptr;

        Iterator(BiTNode *t) { ptr = t; }   //Iterator的构造器

    public:
        Iterator() { ptr = nullptr; }

        char operator*() {
            if (ptr != nullptr)
                return ptr->data;
            else
                return '0';
        }

        bool operator!=(Iterator other) {
            return ptr != other.ptr;
        }
    };


    Iterator begin() { return Iterator(root); }

    Iterator end() { return Iterator(nullptr); }

    BinTree() {
        root = nullptr;
    }

    BinTree(istream &in) {
        string GList;
        in >> GList;
        for (int i = 0; i < GList.size(); ++i) {
            if (GList[i] == ',' && GList[i + 1] == ')') {
                GList = GList.insert(i + 1, 1, '0');
            }

            if (GList[i] == '(' && GList[i + 1] == ',') {
                GList = GList.insert(i + 1, 1, '0');
            }
        }

        BinTree binTree;
        binTree.root = (BiTNode*)std::malloc(sizeof(BiTNode));
        binTree.root->data = GList[0];
        std::stack<BiTNode *> NodeStack;
        NodeStack.push(binTree.root);

        for (int i = 1; i < GList.size(); ++i) {

            if (GList[i] == '(') {
                NodeStack.top()->lchild = (BiTNode*)std::malloc(sizeof(BiTNode));
                NodeStack.top()->lchild->data = GList[i + 1];
                NodeStack.push(NodeStack.top()->lchild);
            }

            if (GList[i] == ',') {
                NodeStack.pop();
                NodeStack.top()->rchild = (BiTNode*)std::malloc(sizeof(BiTNode));
                NodeStack.top()->rchild->data = GList[i + 1];
                NodeStack.push(NodeStack.top()->rchild);
            }

            if (GList[i] == ')') {
                NodeStack.pop();
            }
        }
    }


    void re_output(BiTNode *t) {

    }

    void output() {
        re_output(root);
    }


    void destroy(BiTNode *t)  //应该添加这个删除链表每一个结点
    {
        if (t != nullptr) {
            destroy(t->lchild);
            destroy(t->rchild);
            delete t;
        }
    }

    ~BinTree() {
        destroy(root);
    }

};


#endif




