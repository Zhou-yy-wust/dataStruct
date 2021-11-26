#pragma once
#ifndef BLACK_RED_TREE_H
#define BLACK_RED_TREE_H
/*题目要求：
 （1）生成一组随机数并输出。
 （2）建立红黑树，并显示。
 （3）分别计算成功和失败的平均查找长度。
 （4）按数值递减次序输出数据。
 （5）功能：检索（输出依次比较的数据）、插入、删除。
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#define RED    0  //红色节点
#define BLACK  1  //黑色节点
typedef int Elemtype;
//红黑树的节点
typedef struct RBNode {
    char color;
    Elemtype data;
    struct RBNode* left, * right, * parent;
}RBNode, * RBTree;
//红黑树的根
typedef struct RBRoot {
    RBNode* node;
}RBRoot;

//函数声明部分
void Create_rand(Elemtype a[]);//生成一组随机数并输出
RBRoot* Create_RB();//建立根
RBNode* Create_RBNode(RBNode* parent, RBNode* left, RBNode* right, Elemtype data);//建立结点
//销毁红黑树
void destroy_rbtree(RBTree tree);
void rbtree_destroy(RBRoot* root);

int Get_node_num(RBTree root);//求节点总数
int Get_node_level(RBTree root, int level);//计算非空结点的层数和
int Get_leaf_level(RBTree root, int level);//计算度不为2的节点的层数和
double Get_Success_ASL(RBTree tree);//计算ASL成功
double Get_unsuccess_ASL(RBTree tree);//计算ASL失败

void Get_max_index(RBTree root, int index, int* maxIndex);//计算最大节点索引数
int Get_level(RBTree root);//计算层数

void RBTree_Inprint(RBTree tree);//中序遍历
void RBtree_Prprint(RBTree tree);//前序遍历
//打印红黑树
void RBTree_print(RBTree tree);
void Print_RBTree(RBRoot* root);

//检索（递归实现）
RBNode* Search(RBTree node, Elemtype data);
int RBTree_Search(RBRoot* root, Elemtype data);

//检索（非递归实现）
RBNode* Iterative_Search(RBTree node, Elemtype data);
int Iterative_RB_Search(RBRoot* root, Elemtype data);

void Left_rotate(RBRoot* tree, RBNode* node);//对节点x进行左旋
void Right_rotate(RBRoot* tree, RBNode* node);//对节点x进行右旋
//插入相关函数
void RBTree_Insert_Fixup(RBRoot* root, RBNode* node);//插入修正函数
void RBTree_Insert(RBRoot* root, RBNode* node);//插入节点
Elemtype Insert_Node(RBRoot* root, Elemtype data);//新建节点，并将它插入红黑树中
//删除相关函数
void RBTree_Delete_Fixup(RBRoot* root, RBNode* node, RBNode* parent);//删除修正函数
void RBTree_Delete(RBRoot* root, RBNode* node);//删除节点
bool Delete_RBTree(RBRoot* root, Elemtype data);//删除值为data的节点

void Print_Detree(RBTree root);// 按数值递减次序输出数据

//函数定义部分
//生成一组随机数并输出。
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
//建立根
RBRoot* Create_RB()
{
    RBRoot* root = (RBRoot*)malloc(sizeof(RBRoot));
    root->node = NULL;
    return root;
}
//建立结点
RBNode* Create_RBNode(RBNode* parent, RBNode* left, RBNode* right, Elemtype data)
{
    RBNode* p;
    p = (RBNode*)malloc(sizeof(RBNode));
    p->data = data;
    p->left = left;
    p->right = right;
    p->color = BLACK;//默认为黑色
    return p;
}
//销毁红黑树
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
//求节点总数
int Get_node_num(RBTree root)
{
    if (root == NULL)
        return 0;
    return 1 + Get_node_num(root->left) + Get_node_num(root->right);
}
//计算非空结点的层数和
int Get_node_level(RBTree root, int level)
{
    if (root == NULL)
        return 0;
    return Get_node_level(root->left, level + 1) + Get_node_level(root->right, level + 1) + level;
}
//计算度不为2的节点的层数和
int Get_leaf_level(RBTree root, int level)
{
    if (root == NULL)
        return level - 1;
    return Get_leaf_level(root->left, level + 1) + Get_leaf_level(root->right, level + 1);
}
//计算ASL成功
double Get_Success_ASL(RBTree tree)
{
    if (tree == NULL)
        return 0;
    int node_num = Get_node_num(tree);
    int node_sum = Get_node_level(tree, 1);
    return (double)node_sum / node_num;
}
//计算ASL失败
double Get_unsuccess_ASL(RBTree tree)
{
    if (tree == NULL)
        return 0;
    int node_num = Get_node_num(tree) + 1;//n0=n2+1
    int node_sum = Get_leaf_level(tree, 1);
    return (double)node_sum / node_num;
}

//计算最大节点索引数
void Get_max_index(RBTree root, int index, int* maxIndex)
{
    if (root == NULL)
        return;
    if (index > *maxIndex)
        *maxIndex = index;
    Get_max_index(root->left, index * 2, maxIndex);
    Get_max_index(root->right, index * 2 + 1, maxIndex);
}
//计算层数（max(左孩子高度，右孩子高度)+1(根结点)）
int Get_level(RBTree root)
{
    if (root == NULL)
        return 0;
    int HL = Get_level(root->left);
    int HR = Get_level(root->right);
    return HL > HR ? HL + 1 : HR + 1;
}
//中序遍历
void Print_Inprint(RBTree root)
{
    if (root == NULL)
        return;
    Print_Inprint(root->left);
    printf("%d", root->data);
    if (root->color == 1)
        printf("(黑)  ");
    else
        printf("(红)  ");
    Print_Inprint(root->right);
}
//前序遍历
void Print_Prprint(RBTree root)
{
    if (root == NULL)
        return;
    printf("%d", root->data);
    if (root->color == 1)
        printf("(黑)  ");
    else
        printf("(红)  ");
    Print_Prprint(root->left);
    Print_Prprint(root->right);
}
/*打印红黑树*/
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

    Q[index] = tree; index++;//根节点入数组

    while (point < 1024)
    {
        if (Q[point] != NULL)
        {
            Q[index] = Q[point]->left; index++;
            Q[index] = Q[point]->right; index++;
        }//将索引值为index的非空结点的子结点存入数组第index个位置。
        else
        {
            index++; index++;
        }
        point++;
    }

    index = 0;
    Get_max_index(tree, 1, &index);//求出红黑树的最大索引
    point = 1;//当前结点索引值

    int LEVEL = Get_level(tree);//红黑树的最大层数
    int level = 0;//当前层数
    int level_index = 0;//当前层数的最大索引
    while (point <= index)
    {
        if (point > level_index)//若大于当前层数的最大索引，则当前层数遍历完，层数加1
        {
            level_index = level_index * 2 + 1;
            level++;
            printf("\n");
        }
        int space_num = pow(2, LEVEL - level) - 1;//空格数与层数关系函数
        for (i = 0; i < space_num; i++)
        {
            printf("       ");
        }
        if (Q[point] != NULL)
        {
            printf("%2d", Q[point]->data);//输出当前索引对应节点的值
            if (Q[point]->color == RED) printf("(红)");
            else printf("(黑)");
        }
        else
        {
            printf("       ");
        }
        for (i = 0; i < space_num; i++)//对称位置也输出相同空格
        {
            printf("       ");
        }
        printf("       ");//相邻节点之间补充一个单位的空格
        point++;
    }
}
void Print_RBTree(RBRoot* root)
{
    if (root->node != NULL)
        RBTree_print(root->node);
}

//功能：检索（递归实现）
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
//检索（非递归实现）
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

/* 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 */
void Left_rotate(RBRoot* tree, RBNode* node)//对结点x进行左旋
{
    if (node->right == NULL)//右结点为空，不能左旋
        return;
    RBNode* p = node;
    RBNode* q = node->right;
    RBNode* parent = node->parent;
    if (parent == NULL)//如果p是根结点
    {
        tree->node = q;//则将根结点设为q
    }
    else
    {//将p分为左右结点进行讨论
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
/* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \
*        x   ry                           lx   y
*       / \                                   / \
*      lx  rx                                rx  ry
*/
void Right_rotate(RBRoot* tree, RBNode* node)
{
    if (node->left == NULL)//左结点为空，不能右旋
        return;
    RBNode* p = node;
    RBNode* q = node->left;
    RBNode* parent = node->parent;
    if (p->parent != NULL)//p不为根结点情形
    {//将p分为左右结点进行讨论
        if (parent->left == p)
            parent->left = q;
        else
            parent->right = q;
    }
    else//p为空结点情形
        tree->node = q;

    q->parent = parent;
    p->parent = q;

    p->left = q->right;
    if (p->left)//p的左结点存在
        p->left->parent = p;
    q->right = p;
}
//红黑树插入修正函数
void RBTree_Insert_Fixup(RBRoot* root, RBNode* node)
{
    RBNode* parent, * gparent;
    // 若父节点存在，并且父节点的颜色是红色
    while ((parent = node->parent) && (parent->color == RED))
    {
        gparent = parent->parent;
        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // 情形1：叔叔节点是红色
            RBNode* uncle = gparent->right;
            if (uncle && uncle->color == RED)
            {//父、叔变黑，爷变红,对爷进行判断
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
                continue;
            }
            // 情形2：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                RBNode* tmp;
                Left_rotate(root, parent);//父左旋
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // 情形3：叔叔是黑色，且当前节点是左孩子。
            parent->color = BLACK;
            gparent->color = RED;
            Right_rotate(root, gparent);
        }
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // 情形1：叔叔节点是红色
            RBNode* uncle = gparent->left;
            if (uncle && (uncle->color == RED))
            {
                uncle->color = BLACK;
                parent->color = BLACK;
                gparent->color = RED;
                node = gparent;
                continue;
            }
            // 情形2：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                RBNode* tmp;
                Right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            // 情形3：叔叔是黑色，且当前节点是右孩子。
            parent->color = BLACK;
            gparent->color = RED;
            Left_rotate(root, gparent);
        }
    }
    // 将根节点设为黑色
    root->node->color = BLACK;
}
//添加节点：将节点(node)插入到红黑树中
void RBTree_Insert(RBRoot* root, RBNode* node)
{
    RBNode* y = NULL;
    RBNode* x = root->node;
    // 1.将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;//找到合适位置，y为此位置的父节点

    if (y == NULL)
    {
        root->node = node;// 情况1：若y是空节点，则将node设为根
    }
    else
    {
        if (node->data < y->data)
            y->left = node;// 情况2：若“node->data”<“y->data”，则将node设为“y的左孩子”
        else
            y->right = node;// 情况3：(“node->data”>=“y->data”)将node设为“y的右孩子”
    }
    node->color = RED;// 2. 设置节点的颜色为红色
    // 3.将它重新修正为一颗二叉查找树
    RBTree_Insert_Fixup(root, node);
}
//新建结点，并将它插入红黑树中
Elemtype Insert_Node(RBRoot* root, Elemtype data)
{
    RBNode* node;
    node = Create_RBNode(NULL, NULL, NULL, data);
    if (node == NULL)
        return -1;
    else if (Iterative_Search(root->node, data) != NULL)//查找红黑树中有无相同元素
        return -1;
    else
        RBTree_Insert(root, node);
    return 0;
}
//红黑树删除修正函数
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
                // 情况1: x的兄弟w是红色的
                other->color = BLACK;
                parent->color = RED;
                Left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                // 情况2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || other->right->color == BLACK)
                {
                    // 情况3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    other->left->color = BLACK;
                    other->color = RED;
                    Right_rotate(root, other);
                    other = parent->right;
                }
                // 情况4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
                // 情况1: x的兄弟w是红色的
                other->color = BLACK;
                parent->color = RED;
                Right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || other->left->color == BLACK) &&
                (!other->right || other->right->color == BLACK))
            {
                // 情况2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color == BLACK)
                {
                    // 情况3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    other->right->color = BLACK;
                    other->color = RED;
                    Left_rotate(root, other);
                    other = parent->left;
                }
                // 情况4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
//删除结点
void RBTree_Delete(RBRoot* root, RBNode* node)
{
    RBNode* child = NULL, * parent = NULL;
    int color = 0;
    // 被删除节点的"左右孩子都不为空"的情况。
    if ((node->left != NULL) && (node->right != NULL))
    {
        // 被删节点的后继节点。(取代节点)
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        RBNode* replace = node;

        // 获取后继节点（最右下角）
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (node->parent)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else
            // "node节点"是根节点，更新根节点。
            root->node = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = replace->parent;
        // 保存"取代节点"的颜色
        color = replace->color;
        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            if (child)// child不为空
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
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
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
//删除值为data的结点
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
// 按数值递减次序输出数据
void Print_Detree(RBTree root)
{
    if (root == NULL)
        return;
    Print_Detree(root->right);
    printf("%d", root->data);
    if (root->color == 1)
        printf("(黑)  ");
    else
        printf("(红)  ");
    Print_Detree(root->left);
}
int main()
{
    int i, t;
    RBRoot* root = NULL;
    root = Create_RB();//建立根
    printf("操作指令如下：\n");
    printf("1.建立初始红黑树（随机数据）\n");
    printf("2.显示平均查找长度\n");
    printf("3.插入数据\n");
    printf("4.删除数据\n");
    printf("5.检索数据\n");
    printf("6.按数值递减次序输出数据\n");
    printf("7.显示红黑二叉树\n");
    printf("8.重新建立新树（随机数据）\n");
    printf("9.退出\n");
    printf("10.帮助\n");
    while (true)
    {
        printf("输入选择:");
        int command = 0;
        Elemtype data;
        int res = 0;
        std::cout << "Enter command:";
        std::cin >> command;
        switch (command)
        {
        case 1:
            printf("输入随机数个数：");
            std::cin >> t;
            srand((unsigned int)time(NULL));
            printf("产生的随机数组：");
            i = 0;
            while (i < t)
            {
                Elemtype data = rand() % 100;
                printf("%d ", data);
                Insert_Node(root, data);
                i = Get_node_num(root->node);
            }
            printf("\n红黑树建立完成，如下所示：\n");
            if (Get_node_num(root->node) >= 13)//节点过多，则利用中序和前序的方式显示红黑树
            {
                printf("数据过多，图形显示不直观，则用中序与前序遍历显示\n");
                printf("中序遍历：");
                Print_Inprint(root->node);
                printf("\n前序遍历：");
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
                printf("红黑树未建立!请先建立红黑树\n"); break;
            }
            printf("ASL成功=%d/%d=%.2f\n", Get_node_level(root->node, 1), Get_node_num(root->node), Get_Success_ASL(root->node));
            printf("ASL失败=%d/%d=%.2f\n", Get_leaf_level(root->node, 1), Get_node_num(root->node) + 1, Get_unsuccess_ASL(root->node));
            printf("\n");
            break;
        case 3:
            printf("输入待插入的数据:"); std::cin >> data;
            if (Iterative_Search(root->node, data) != NULL)
                printf("原红黑树中已有数%d,插入失败。\n", data);
            else
            {
                Insert_Node(root, data);
                printf("插入数据%d后，红黑树如下所示：\n", data);
                Print_RBTree(root);
                printf("\n新树的平均查找长度如下：\n");
                printf("ASL成功=%d/%d=%.2f\n", Get_node_level(root->node, 1), Get_node_num(root->node), Get_Success_ASL(root->node));
                printf("ASL失败=%d/%d=%.2f\n", Get_leaf_level(root->node, 1), Get_node_num(root->node) + 1, Get_unsuccess_ASL(root->node));
            }
            break;
        case 4:
            if (root->node == NULL)
            {
                printf("红黑树未建立!请先建立红黑树\n"); break;
            }
            printf("输入待删除的数据:"); std::cin >> data;
            if (Delete_RBTree(root, data))
            {
                printf("删除数据%d后，红黑树如下所示：\n", data);
                Print_RBTree(root);
                printf("\n新树的平均查找长度如下：\n");
                printf("ASL成功=%d/%d=%.2f\n", Get_node_level(root->node, 1), Get_node_num(root->node), Get_Success_ASL(root->node));
                printf("ASL失败=%d/%d=%.2f\n", Get_leaf_level(root->node, 1), Get_node_num(root->node) + 1, Get_unsuccess_ASL(root->node));
            }
            else
                printf("红黑树中无此数据,删除失败\n");
            break;
        case 5:
            if (root->node == NULL)
            {
                printf("红黑树未建立!请先建立红黑树\n"); break;
            }
            printf("输入待检索的数据:"); std::cin >> data;
            printf("依次比较的数据为：");
            res = RBTree_Search(root, data);//调用递归方法
            if (res > 0)
                printf("查询成功,查询次数为%d\n", len);
            else
                printf("红黑树中无此数据,查询次数为%d\n", len);
            len = 1;
            printf("\n");
            break;
        case 6:
            if (root->node == NULL)
            {
                printf("红黑树未建立!请先建立红黑树\n"); break;
            }
            Print_Detree(root->node);
            printf("\n");
            break;
        case 7:
            if (root->node == NULL)
            {
                printf("红黑树未建立!请先建立红黑树\n"); break;
            }
            printf("红黑树如下所示：\n");
            if (Get_node_num(root->node) >= 13)//节点过多，则利用中序和前序的方式显示红黑树
            {
                printf("数据过多，图形显示不直观，则用中序与前序遍历显示\n");
                printf("中序遍历：");
                Print_Inprint(root->node);
                printf("\n前序遍历：");
                Print_Prprint(root->node);
                printf("\n");
            }
            else
                Print_RBTree(root);
            printf("\n");
            break;
        case 8:
            if (root->node != NULL)
                rbtree_destroy(root);//销毁红黑树
            srand((unsigned int)time(NULL));
            root = Create_RB();
            printf("请输入新树节点数：");
            std::cin >> data;
            i = 0;
            while (i < t)
            {
                Elemtype data = rand() % 100;
                Insert_Node(root, data);
                i = Get_node_num(root->node);
            }
            printf("新的红黑树如下所示：\n");
            if (Get_node_num(root->node) >= 13)//节点过多，则利用中序和前序的方式显示红黑树
            {
                printf("数据过多，图形显示不直观，则用中序与前序遍历显示\n");
                printf("中序遍历：");
                Print_Inprint(root->node);
                printf("\n前序遍历：");
                Print_Prprint(root->node);
                printf("\n");
            }
            else
                Print_RBTree(root);
            printf("\n");
            break;
        case 9:
            if (root->node != NULL)
                rbtree_destroy(root);//销毁红黑树
            printf("程序已终止!\n");
            return 0;
        case 10:
            printf("操作指令如下：\n");
            printf("1.建立初始红黑树（随机数据）\n");
            printf("2.显示平均查找长度\n");
            printf("3.插入数据\n");
            printf("4.删除数据\n");
            printf("5.检索数据\n");
            printf("6.按数值递减次序输出数据\n");
            printf("7.显示红黑二叉树\n");
            printf("8.重新建立新树（随机数据）\n");
            printf("9.退出\n");
            printf("10.帮助\n");
            break;
        default:
            printf("输入指令有误，重新输入\n");
            break;
        }
    }
    return 0;
}


#endif
