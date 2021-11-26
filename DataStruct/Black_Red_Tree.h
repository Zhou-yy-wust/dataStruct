#pragma once
#ifndef BLACK_RED_TREE_H
#define BLACK_RED_TREE_H
/*��ĿҪ��
 ��1������һ��������������
 ��2�����������������ʾ��
 ��3���ֱ����ɹ���ʧ�ܵ�ƽ�����ҳ��ȡ�
 ��4������ֵ�ݼ�����������ݡ�
 ��5�����ܣ�������������αȽϵ����ݣ������롢ɾ����
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#define RED    0  //��ɫ�ڵ�
#define BLACK  1  //��ɫ�ڵ�
typedef int Elemtype;
//������Ľڵ�
typedef struct RBNode {
    char color;
    Elemtype data;
    struct RBNode* left, * right, * parent;
}RBNode, * RBTree;
//������ĸ�
typedef struct RBRoot {
    RBNode* node;
}RBRoot;

//������������
void Create_rand(Elemtype a[]);//����һ������������
RBRoot* Create_RB();//������
RBNode* Create_RBNode(RBNode* parent, RBNode* left, RBNode* right, Elemtype data);//�������
//���ٺ����
void destroy_rbtree(RBTree tree);
void rbtree_destroy(RBRoot* root);

int Get_node_num(RBTree root);//��ڵ�����
int Get_node_level(RBTree root, int level);//����ǿս��Ĳ�����
int Get_leaf_level(RBTree root, int level);//����Ȳ�Ϊ2�Ľڵ�Ĳ�����
double Get_Success_ASL(RBTree tree);//����ASL�ɹ�
double Get_unsuccess_ASL(RBTree tree);//����ASLʧ��

void Get_max_index(RBTree root, int index, int* maxIndex);//�������ڵ�������
int Get_level(RBTree root);//�������

void RBTree_Inprint(RBTree tree);//�������
void RBtree_Prprint(RBTree tree);//ǰ�����
//��ӡ�����
void RBTree_print(RBTree tree);
void Print_RBTree(RBRoot* root);

//�������ݹ�ʵ�֣�
RBNode* Search(RBTree node, Elemtype data);
int RBTree_Search(RBRoot* root, Elemtype data);

//�������ǵݹ�ʵ�֣�
RBNode* Iterative_Search(RBTree node, Elemtype data);
int Iterative_RB_Search(RBRoot* root, Elemtype data);

void Left_rotate(RBRoot* tree, RBNode* node);//�Խڵ�x��������
void Right_rotate(RBRoot* tree, RBNode* node);//�Խڵ�x��������
//������غ���
void RBTree_Insert_Fixup(RBRoot* root, RBNode* node);//������������
void RBTree_Insert(RBRoot* root, RBNode* node);//����ڵ�
Elemtype Insert_Node(RBRoot* root, Elemtype data);//�½��ڵ㣬����������������
//ɾ����غ���
void RBTree_Delete_Fixup(RBRoot* root, RBNode* node, RBNode* parent);//ɾ����������
void RBTree_Delete(RBRoot* root, RBNode* node);//ɾ���ڵ�
bool Delete_RBTree(RBRoot* root, Elemtype data);//ɾ��ֵΪdata�Ľڵ�

void Print_Detree(RBTree root);// ����ֵ�ݼ������������

//�������岿��
//����һ��������������
void Create_rand(Elemtype a[])
{
    int i;
    srand((unsigned int)time(NULL));
    for (i = 0; i < 10; i++)
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
    }
    printf("\n");
}
//������
RBRoot* Create_RB()
{
    RBRoot* root = (RBRoot*)malloc(sizeof(RBRoot));
    root->node = NULL;
    return root;
}
//�������
RBNode* Create_RBNode(RBNode* parent, RBNode* left, RBNode* right, Elemtype data)
{
    RBNode* p;
    p = (RBNode*)malloc(sizeof(RBNode));
    p->data = data;
    p->left = left;
    p->right = right;
    p->color = BLACK;//Ĭ��Ϊ��ɫ
    return p;
}
//���ٺ����
void destroy_rbtree(RBTree tree)
{
    if (tree == NULL)
        return;
    destroy_rbtree(tree->left);
    destroy_rbtree(tree->right);
    free(tree);
}
void rbtree_destroy(RBRoot* root)
{
    if (root != NULL)
        destroy_rbtree(root->node);
    free(root);
}
//��ڵ�����
int Get_node_num(RBTree root)
{
    if (root == NULL)
        return 0;
    return 1 + Get_node_num(root->left) + Get_node_num(root->right);
}
//����ǿս��Ĳ�����
int Get_node_level(RBTree root, int level)
{
    if (root == NULL)
        return 0;
    return Get_node_level(root->left, level + 1) + Get_node_level(root->right, level + 1) + level;
}
//����Ȳ�Ϊ2�Ľڵ�Ĳ�����
int Get_leaf_level(RBTree root, int level)
{
    if (root == NULL)
        return level - 1;
    return Get_leaf_level(root->left, level + 1) + Get_leaf_level(root->right, level + 1);
}
//����ASL�ɹ�
double Get_Success_ASL(RBTree tree)
{
    if (tree == NULL)
        return 0;
    int node_num = Get_node_num(tree);
    int node_sum = Get_node_level(tree, 1);
    return (double)node_sum / node_num;
}
//����ASLʧ��
double Get_unsuccess_ASL(RBTree tree)
{
    if (tree == NULL)
        return 0;
    int node_num = Get_node_num(tree) + 1;//n0=n2+1
    int node_sum = Get_leaf_level(tree, 1);
    return (double)node_sum / node_num;
}

//�������ڵ�������
void Get_max_index(RBTree root, int index, int* maxIndex)
{
    if (root == NULL)
        return;
    if (index > *maxIndex)
        *maxIndex = index;
    Get_max_index(root->left, index * 2, maxIndex);
    Get_max_index(root->right, index * 2 + 1, maxIndex);
}
//���������max(���Ӹ߶ȣ��Һ��Ӹ߶�)+1(�����)��
int Get_level(RBTree root)
{
    if (root == NULL)
        return 0;
    int HL = Get_level(root->left);
    int HR = Get_level(root->right);
    return HL > HR ? HL + 1 : HR + 1;
}
//�������
void Print_Inprint(RBTree root)
{
    if (root == NULL)
        return;
    Print_Inprint(root->left);
    printf("%d", root->data);
    if (root->color == 1)
        printf("(��)  ");
    else
        printf("(��)  ");
    Print_Inprint(root->right);
}
//ǰ�����
void Print_Prprint(RBTree root)
{
    if (root == NULL)
        return;
    printf("%d", root->data);
    if (root->color == 1)
        printf("(��)  ");
    else
        printf("(��)  ");
    Print_Prprint(root->left);
    Print_Prprint(root->right);
}
/*��ӡ�����*/
void RBTree_print(RBTree tree)
{
    if (tree == NULL)
        return;

    RBTree Q[1024];
    int index = 1, point = 1, i = 0;

    for (i = 0; i < 1024; i++)
    {
        Q[i] = NULL;
    }

    Q[index] = tree; index++;//���ڵ�������

    while (point < 1024)
    {
        if (Q[point] != NULL)
        {
            Q[index] = Q[point]->left; index++;
            Q[index] = Q[point]->right; index++;
        }//������ֵΪindex�ķǿս����ӽ����������index��λ�á�
        else
        {
            index++; index++;
        }
        point++;
    }

    index = 0;
    Get_max_index(tree, 1, &index);//�����������������
    point = 1;//��ǰ�������ֵ

    int LEVEL = Get_level(tree);//�������������
    int level = 0;//��ǰ����
    int level_index = 0;//��ǰ�������������
    while (point <= index)
    {
        if (point > level_index)//�����ڵ�ǰ�����������������ǰ���������꣬������1
        {
            level_index = level_index * 2 + 1;
            level++;
            printf("\n");
        }
        int space_num = pow(2, LEVEL - level) - 1;//�ո����������ϵ����
        for (i = 0; i < space_num; i++)
        {
            printf("       ");
        }
        if (Q[point] != NULL)
        {
            printf("%2d", Q[point]->data);//�����ǰ������Ӧ�ڵ��ֵ
            if (Q[point]->color == RED) printf("(��)");
            else printf("(��)");
        }
        else
        {
            printf("       ");
        }
        for (i = 0; i < space_num; i++)//�Գ�λ��Ҳ�����ͬ�ո�
        {
            printf("       ");
        }
        printf("       ");//���ڽڵ�֮�䲹��һ����λ�Ŀո�
        point++;
    }
}
void Print_RBTree(RBRoot* root)
{
    if (root->node != NULL)
        RBTree_print(root->node);
}

//���ܣ��������ݹ�ʵ�֣�
int len = 1;
RBNode* Search(RBTree node, Elemtype data)
{
    if (node == NULL)
    {
        len -= 1;
        return node;
    }
    printf("%d ", node->data);
    if (node->data == data)
        return node;
    len += 1;
    if (data < node->data)
        return Search(node->left, data);
    else
        return Search(node->right, data);
}
int RBTree_Search(RBRoot* root, Elemtype data)
{
    if (root == NULL)
        return 0;
    return Search(root->node, data) ? 1 : -1;
}
//�������ǵݹ�ʵ�֣�
RBNode* Iterative_Search(RBTree node, Elemtype data)
{
    if (node == NULL)
        return node;
    while (node != NULL && node->data != data)
    {
        if (data < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}
int Iterative_RB_Search(RBRoot* root, Elemtype data)
{
    if (root == NULL)
        return 0;
    else
        return Iterative_Search(root->node, data) ? 1 : -1;
}

/* ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(����)-->           / \
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 */
void Left_rotate(RBRoot* tree, RBNode* node)//�Խ��x��������
{
    if (node->right == NULL)//�ҽ��Ϊ�գ���������
        return;
    RBNode* p = node;
    RBNode* q = node->right;
    RBNode* parent = node->parent;
    if (parent == NULL)//���p�Ǹ����
    {
        tree->node = q;//�򽫸������Ϊq
    }
    else
    {//��p��Ϊ���ҽ���������
        if (parent->left == p)
            parent->left = q;
        else
            parent->right = q;
    }
    q->parent = parent;
    p->parent = q;

    p->right = q->left;
    if (q->left)
        q->left->parent = p;
    q->left = p;
}
/* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \
*        x   ry                           lx   y
*       / \                                   / \
*      lx  rx                                rx  ry
*/
void Right_rotate(RBRoot* tree, RBNode* node)
{
    if (node->left == NULL)//����Ϊ�գ���������
        return;
    RBNode* p = node;
    RBNode* q = node->left;
    RBNode* parent = node->parent;
    if (p->parent != NULL)//p��Ϊ���������
    {//��p��Ϊ���ҽ���������
        if (parent->left == p)
            parent->left = q;
        else
            parent->right = q;
    }
    else//pΪ�ս������
        tree->node = q;

    q->parent = parent;
    p->parent = q;

    p->left = q->right;
    if (p->left)//p���������
        p->left->parent = p;
    q->right = p;
}
//�����������������
void RBTree_Insert_Fixup(RBRoot* root, RBNode* node)
{
    RBNode* parent, * gparent;
    // �����ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ
    while ((parent = node->parent) && (parent->color == RED))
    {
        gparent = parent->parent;
        //�������ڵ㡱�ǡ��游�ڵ�����ӡ�
        if (parent == gparent->left)
        {
            // ����1������ڵ��Ǻ�ɫ
            RBNode* uncle = gparent->right;
            if (uncle && uncle->color == RED)
            {//�������ڣ�ү���,��ү�����ж�
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
                continue;
            }
            // ����2�������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
            if (parent->right == node)
            {
                RBNode* tmp;
                Left_rotate(root, parent);//������
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // ����3�������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
            parent->color = BLACK;
            gparent->color = RED;
            Right_rotate(root, gparent);
        }
        else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
        {
            // ����1������ڵ��Ǻ�ɫ
            RBNode* uncle = gparent->left;
            if (uncle && (uncle->color == RED))
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
                continue;
            }
            // ����2�������Ǻ�ɫ���ҵ�ǰ�ڵ�������
            if (parent->left == node)
            {
                RBNode* tmp;
                Right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // ����3�������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
            parent->color = BLACK;
            gparent->color = RED;
            Left_rotate(root, gparent);
        }
    }
    // �����ڵ���Ϊ��ɫ
    root->node->color = BLACK;
}
//��ӽڵ㣺���ڵ�(node)���뵽�������
void RBTree_Insert(RBRoot* root, RBNode* node)
{
    RBNode* y = NULL;
    RBNode* x = root->node;
    // 1.�����������һ�Ŷ�������������ڵ���ӵ�����������С�
    while (x != NULL)
    {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;//�ҵ�����λ�ã�yΪ��λ�õĸ��ڵ�

    if (y == NULL)
    {
        root->node = node;// ���1����y�ǿսڵ㣬��node��Ϊ��
    }
    else
    {
        if (node->data < y->data)
            y->left = node;// ���2������node->data��<��y->data������node��Ϊ��y�����ӡ�
        else
            y->right = node;// ���3��(��node->data��>=��y->data��)��node��Ϊ��y���Һ��ӡ�
    }
    node->color = RED;// 2. ���ýڵ����ɫΪ��ɫ
    // 3.������������Ϊһ�Ŷ��������
    RBTree_Insert_Fixup(root, node);
}
//�½���㣬����������������
Elemtype Insert_Node(RBRoot* root, Elemtype data)
{
    RBNode* node;
    node = Create_RBNode(NULL, NULL, NULL, data);
    if (node == NULL)
        return -1;
    else if (Iterative_Search(root->node, data) != NULL)//���Һ������������ͬԪ��
        return -1;
    else
        RBTree_Insert(root, node);
    return 0;
}
//�����ɾ����������
void RBTree_Delete_Fixup(RBRoot* root, RBNode* node, RBNode* parent)
{
    RBNode* other;

    while ((!node || (node->color == BLACK)) && node != root->node)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color == RED)
            {
                // ���1: x���ֵ�w�Ǻ�ɫ��
                other->color = BLACK;
                parent->color = RED;
                Left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                // ���2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || other->right->color == BLACK)
                {
                    // ���3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��
                    other->left->color = BLACK;
                    other->color = RED;
                    Right_rotate(root, other);
                    other = parent->right;
                }
                // ���4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
                other->color = parent->color;
                parent->color = BLACK;
                other->right->color = BLACK;
                Left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (other->color == RED)
            {
                // ���1: x���ֵ�w�Ǻ�ɫ��
                other->color = BLACK;
                parent->color = RED;
                Right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                // ���2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color == BLACK)
                {
                    // ���3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��
                    other->right->color = BLACK;
                    other->color = RED;
                    Left_rotate(root, other);
                    other = parent->left;
                }
                // ���4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
                other->color = parent->color;
                parent->color = BLACK;
                other->left->color = BLACK;
                Right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        node->color = BLACK;
}
//ɾ�����
void RBTree_Delete(RBRoot* root, RBNode* node)
{
    RBNode* child = NULL, * parent = NULL;
    int color = 0;
    // ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
    if ((node->left != NULL) && (node->right != NULL))
    {
        // ��ɾ�ڵ�ĺ�̽ڵ㡣(ȡ���ڵ�)
        // ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
        RBNode* replace = node;

        // ��ȡ��̽ڵ㣨�����½ǣ�
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
        if (node->parent)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else
            // "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
            root->node = replace;

        // child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
        // "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
        child = replace->right;
        parent = replace->parent;
        // ����"ȡ���ڵ�"����ɫ
        color = replace->color;
        // "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            if (child)// child��Ϊ��
                child->parent = parent;
            parent->left = child;

            replace->right = node->right;
            node->right->parent = replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            RBTree_Delete_Fixup(root, child, parent);
        free(node);
        return;
    }

    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    // ����"ȡ���ڵ�"����ɫ
    color = node->color;

    if (child)
        child->parent = parent;

    // "node�ڵ�"���Ǹ��ڵ�
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;

    if (color == BLACK)
        RBTree_Delete_Fixup(root, child, parent);
    free(node);
}
//ɾ��ֵΪdata�Ľ��
bool Delete_RBTree(RBRoot* root, Elemtype data)
{
    RBNode* z;
    if ((z = Iterative_Search(root->node, data)) != NULL)
    {
        RBTree_Delete(root, z);
        return true;
    }
    else
        return false;
}
// ����ֵ�ݼ������������
void Print_Detree(RBTree root)
{
    if (root == NULL)
        return;
    Print_Detree(root->right);
    printf("%d", root->data);
    if (root->color == 1)
        printf("(��)  ");
    else
        printf("(��)  ");
    Print_Detree(root->left);
}
int main()
{
    int i, t;
    RBRoot* root = NULL;
    root = Create_RB();//������
    printf("����ָ�����£�\n");
    printf("1.������ʼ�������������ݣ�\n");
    printf("2.��ʾƽ�����ҳ���\n");
    printf("3.��������\n");
    printf("4.ɾ������\n");
    printf("5.��������\n");
    printf("6.����ֵ�ݼ������������\n");
    printf("7.��ʾ��ڶ�����\n");
    printf("8.���½���������������ݣ�\n");
    printf("9.�˳�\n");
    printf("10.����\n");
    while (true)
    {
        printf("����ѡ��:");
        int command = 0;
        Elemtype data;
        int res = 0;
        std::cout << "Enter command:";
        std::cin >> command;
        switch (command)
        {
        case 1:
            printf("���������������");
            std::cin >> t;
            srand((unsigned int)time(NULL));
            printf("������������飺");
            i = 0;
            while (i < t)
            {
                Elemtype data = rand() % 100;
                printf("%d ", data);
                Insert_Node(root, data);
                i = Get_node_num(root->node);
            }
            printf("\n�����������ɣ�������ʾ��\n");
            if (Get_node_num(root->node) >= 13)//�ڵ���࣬�����������ǰ��ķ�ʽ��ʾ�����
            {
                printf("���ݹ��࣬ͼ����ʾ��ֱ�ۣ�����������ǰ�������ʾ\n");
                printf("���������");
                Print_Inprint(root->node);
                printf("\nǰ�������");
                Print_Prprint(root->node);
                printf("\n");
            }
            else
                Print_RBTree(root);
            printf("\n");
            break;
        case 2:
            if (root->node == NULL)
            {
                printf("�����δ����!���Ƚ��������\n"); break;
            }
            printf("ASL�ɹ�=%d/%d=%.2f\n", Get_node_level(root->node, 1), Get_node_num(root->node), Get_Success_ASL(root->node));
            printf("ASLʧ��=%d/%d=%.2f\n", Get_leaf_level(root->node, 1), Get_node_num(root->node) + 1, Get_unsuccess_ASL(root->node));
            printf("\n");
            break;
        case 3:
            printf("��������������:"); std::cin >> data;
            if (Iterative_Search(root->node, data) != NULL)
                printf("ԭ�������������%d,����ʧ�ܡ�\n", data);
            else
            {
                Insert_Node(root, data);
                printf("��������%d�󣬺����������ʾ��\n", data);
                Print_RBTree(root);
                printf("\n������ƽ�����ҳ������£�\n");
                printf("ASL�ɹ�=%d/%d=%.2f\n", Get_node_level(root->node, 1), Get_node_num(root->node), Get_Success_ASL(root->node));
                printf("ASLʧ��=%d/%d=%.2f\n", Get_leaf_level(root->node, 1), Get_node_num(root->node) + 1, Get_unsuccess_ASL(root->node));
            }
            break;
        case 4:
            if (root->node == NULL)
            {
                printf("�����δ����!���Ƚ��������\n"); break;
            }
            printf("�����ɾ��������:"); std::cin >> data;
            if (Delete_RBTree(root, data))
            {
                printf("ɾ������%d�󣬺����������ʾ��\n", data);
                Print_RBTree(root);
                printf("\n������ƽ�����ҳ������£�\n");
                printf("ASL�ɹ�=%d/%d=%.2f\n", Get_node_level(root->node, 1), Get_node_num(root->node), Get_Success_ASL(root->node));
                printf("ASLʧ��=%d/%d=%.2f\n", Get_leaf_level(root->node, 1), Get_node_num(root->node) + 1, Get_unsuccess_ASL(root->node));
            }
            else
                printf("��������޴�����,ɾ��ʧ��\n");
            break;
        case 5:
            if (root->node == NULL)
            {
                printf("�����δ����!���Ƚ��������\n"); break;
            }
            printf("���������������:"); std::cin >> data;
            printf("���αȽϵ�����Ϊ��");
            res = RBTree_Search(root, data);//���õݹ鷽��
            if (res > 0)
                printf("��ѯ�ɹ�,��ѯ����Ϊ%d\n", len);
            else
                printf("��������޴�����,��ѯ����Ϊ%d\n", len);
            len = 1;
            printf("\n");
            break;
        case 6:
            if (root->node == NULL)
            {
                printf("�����δ����!���Ƚ��������\n"); break;
            }
            Print_Detree(root->node);
            printf("\n");
            break;
        case 7:
            if (root->node == NULL)
            {
                printf("�����δ����!���Ƚ��������\n"); break;
            }
            printf("�����������ʾ��\n");
            if (Get_node_num(root->node) >= 13)//�ڵ���࣬�����������ǰ��ķ�ʽ��ʾ�����
            {
                printf("���ݹ��࣬ͼ����ʾ��ֱ�ۣ�����������ǰ�������ʾ\n");
                printf("���������");
                Print_Inprint(root->node);
                printf("\nǰ�������");
                Print_Prprint(root->node);
                printf("\n");
            }
            else
                Print_RBTree(root);
            printf("\n");
            break;
        case 8:
            if (root->node != NULL)
                rbtree_destroy(root);//���ٺ����
            srand((unsigned int)time(NULL));
            root = Create_RB();
            printf("�����������ڵ�����");
            std::cin >> data;
            i = 0;
            while (i < t)
            {
                Elemtype data = rand() % 100;
                Insert_Node(root, data);
                i = Get_node_num(root->node);
            }
            printf("�µĺ����������ʾ��\n");
            if (Get_node_num(root->node) >= 13)//�ڵ���࣬�����������ǰ��ķ�ʽ��ʾ�����
            {
                printf("���ݹ��࣬ͼ����ʾ��ֱ�ۣ�����������ǰ�������ʾ\n");
                printf("���������");
                Print_Inprint(root->node);
                printf("\nǰ�������");
                Print_Prprint(root->node);
                printf("\n");
            }
            else
                Print_RBTree(root);
            printf("\n");
            break;
        case 9:
            if (root->node != NULL)
                rbtree_destroy(root);//���ٺ����
            printf("��������ֹ!\n");
            return 0;
        case 10:
            printf("����ָ�����£�\n");
            printf("1.������ʼ�������������ݣ�\n");
            printf("2.��ʾƽ�����ҳ���\n");
            printf("3.��������\n");
            printf("4.ɾ������\n");
            printf("5.��������\n");
            printf("6.����ֵ�ݼ������������\n");
            printf("7.��ʾ��ڶ�����\n");
            printf("8.���½���������������ݣ�\n");
            printf("9.�˳�\n");
            printf("10.����\n");
            break;
        default:
            printf("����ָ��������������\n");
            break;
        }
    }
    return 0;
}


#endif
