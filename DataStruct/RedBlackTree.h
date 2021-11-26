#pragma once
#ifndef REDBLACKTREE_H
#define REDVLACKTREE_H

using KeyType = int;
using ElemType = int;

enum class RBT_Color{RED,BLACK};

class RBT_Node {
public:
	KeyType key;
	ElemType value;
	RBT_Color color;
	RBT_Node* lchild, *rchild, *parent;
};

class RBTree {
public:
	void Insert(const KeyType key,const ElemType value);
	ElemType Delete(const KeyType key);
	ElemType Find(const KeyType key);
private:
	RBT_Node* Tree;
	RBT_Node* Search(const KeyType key);
	void DelNode(RBT_Node* node);
	void LeftRotate(RBT_Node* node);
	void RightRotate(RBT_Node* node);
	void insertFixUp(RBT_Node*node);
	void deleteFixUp(RBT_Node* node);
};

void SetBlack(RBT_Node* node) { if(node)node->color = RBT_Color::BLACK; }
void SetRed(RBT_Node* node) { if(node)node->color = RBT_Color::RED; }

RBT_Color ColorOf(RBT_Node* node) { return node ? node->color : RBT_Color::BLACK; }

RBT_Node* ParentOf(RBT_Node* node) { 
	if (node)return node->parent;
	else return nullptr;}

RBT_Node* RightOf(RBT_Node* node) {
	if (node) return node->rchild;
	return nullptr;
}

RBT_Node* LeftOf(RBT_Node* node) {
	if (node) return node->lchild;
	return nullptr;
}

bool Color_Is_Red(RBT_Node* node) {return ColorOf(node) == RBT_Color::RED; }
bool Color_Is_Black(RBT_Node* node) { return ColorOf(node) == RBT_Color::BLACK; }

RBT_Node* nextNode(RBT_Node*node) { //获取后继结点
	if (!node ) return nullptr;
	else if (!node->rchild) {
		RBT_Node* p = ParentOf(node);
		while (p && p->rchild == node) node = p, p = ParentOf(p);
		return p;
	}
	else {
		RBT_Node* ret = node->rchild;
		while (ret->lchild) ret = ret->lchild;
		return ret;
	}
}
RBT_Node* preNode(RBT_Node* node) { //获取前驱结点
	if (!node ) return nullptr;
	else if (!node->lchild) {
		RBT_Node* p = ParentOf(node);
		while (p && p->lchild == node) {node = p, p = ParentOf(p);}
		return p;
	}
	else {
		RBT_Node* ret = node->lchild;
		while (ret->rchild) ret =ret->rchild;
		return ret;
	}
}

/*
* 右旋示意图:
*       parent                    parent
*      /                         /
*     x                         y
*    / \              ->       / \
*   lx  y                     x   ry
*      / \                   / \  
*     ly  ry                lx  ly
* 
*/
void RBTree::LeftRotate(RBT_Node* node) {
	RBT_Node* x = node, * parent = ParentOf(x), * y = RightOf(x);
	
	if (RightOf(y)) { //y左孩子非空，挂在x的右孩子上
		LeftOf(y)->parent = x; 
	}  
	x->rchild = y->lchild;
	y->lchild = x, x->parent = y;
	
	if (!parent) Tree = y; //x为根节点，则y直接为根节点
	else if (LeftOf(parent) == x) parent->lchild = y;
	else parent->rchild =y;
}

/*
* 左旋示意图:
*       parent                         parent
*             \                              \
*              x                              y
*             / \              ->            / \
*            y  rx                          ly  x
*           / \                                / \
*          ly  ry                             ry  rx
*
*/
void RBTree::RightRotate(RBT_Node* node) {
	RBT_Node* x = node, * y = LeftOf(x), * parent = ParentOf(x);
	if (ParentOf(y)) RightOf(x)->parent = x;  //y右孩子非空，挂在x的左孩子上
	x->lchild = y->rchild;
	y->rchild = x, x->parent = y;

	y->parent = parent;
	if (!parent) Tree = y;
	else if (LeftOf(parent) == x) parent->lchild = y;
	else parent->rchild = y;
}

//查找
RBT_Node* RBTree::Search(const KeyType key) {
	RBT_Node* p = Tree;
	while (p != nullptr && p->key != key) 
		if (p->key > key) p = LeftOf(p);
		else p = RightOf(p);
	return p;
}

ElemType RBTree::Find(const KeyType key) {
	RBT_Node* p = Search(key);
	if (!p) return -1;
	return p->value;
}

//插入关键字key
void RBTree::Insert(const KeyType key,const ElemType value) {
	RBT_Node* parent = nullptr, * p = Tree;
	while (p && p->key !=key) { //查找插入位置
		parent = p;
		if (p->key > key) p = LeftOf(p);
		else p = RightOf(p);
	}
    
	if (p) //树中已有关键字值
		return;

	RBT_Node* newnode = new RBT_Node{ key,value,RBT_Color::RED,nullptr,nullptr,parent };  //插入新结点

	if (!parent) Tree = newnode;    //树空，则直接插在根
	else if (parent->key > newnode->key) parent->lchild = newnode; //否则，插在parent的左或右
	else parent->rchild = newnode;

	insertFixUp(newnode);

}

void RBTree::insertFixUp(RBT_Node*node) {
	RBT_Node* parent, * gdparent;

	while ((parent = ParentOf(node)) && Color_Is_Red(parent)) {  //插入在红节点之后,插入在黑节点之后无需调整
		gdparent = ParentOf(parent);

		if (LeftOf(gdparent) == parent) {  //父结点在爷结点左侧
			RBT_Node* uncle = RightOf(gdparent);
			
			if (Color_Is_Black(uncle)) {   //叔父结点为黑色
			/*  case1:         gdparent:b                       parent:b
			*                 /       \                         /      \
			*              parent:r    uncle:b     ->      newnode:r  gdparent:r
			*               /                                            \
			*            newnode:r                                       uncle:b
			*/
				if (LeftOf(parent) == node) {
					RightRotate(gdparent);
					SetBlack(parent);
					SetRed(gdparent);
				}
			/*  case2:         gdparent:b                       gdparent:b                       newnode:b
			*                 /         \           L            /      \            R           /       \
			*              parent:r    uncle:b     ---->      newnode:r  uncle:b  ---->    parent:r   gdparent:r
			*                     \                            /                                           \
			*                  newnode:r                   parent:r                                        uncle:b
			*/
				if (RightOf(parent) == node) {
					SetBlack(node);
					SetRed(gdparent);
					LeftRotate(parent);
					RightRotate(gdparent);
				}
			}

			if (Color_Is_Red(uncle)) {
			/*  case3:         gdparent:b                       gdparent:r
			*                 /       \                         /      \
			*              parent:r    uncle:r     ->     parent:b    uncle:b
			*               /                                  /
			*            newnode:r                       newnode:r         
			*/
				SetRed(gdparent);
				SetBlack(parent);
				SetBlack(uncle);
				node = gdparent;
				continue;
			}
		}


		else {  //父结点在爷结点右侧
			RBT_Node* uncle = LeftOf(gdparent);

			if (Color_Is_Black(uncle)) { //叔父结点为黑色
			/*  case1:         gdparent:b                           parent:b
			*                 /       \             L               /      \
			*              uncle:b    parent:r    ---->       gdparent:r  newnode:r
			*                           \                      /                      
			*                          newnode:r          uncle:b           
			*/
				if (RightOf(parent) == node) {
					LeftRotate(gdparent);
					SetBlack(parent);
					SetRed(gdparent);
				}
			/*  case2:         gdparent:b                       gdparent:b                    newnode:b
			*                 /         \           R            /      \         L           /       \
			*              uncle:b    parent:r     ---->    uncle:b  newnode:r  ---->    gdparent:r  parent:r
			*                           /                                  \                 /                         
			*                       newnode:r                            parent:r        uncle:b             
			*/
				if (LeftOf(parent) == node) {
					SetBlack(node);
					SetRed(gdparent);
					RightRotate(parent);
					LeftRotate(gdparent);
				}
			}

			if (Color_Is_Red(uncle)) {
			/*  case3:         gdparent:b                       gdparent:r
			*                 /       \                         /      \
			*              uncle:r    parent:r    ---->      uncle:b  parent:b    
			*                            \                                \
			*                           newnode:r                       newnode:r
			*/
				SetRed(gdparent);
				SetBlack(parent);
				SetBlack(uncle);
				node = gdparent;
				continue;
			}
		}
	}
	SetBlack(Tree);
}

ElemType RBTree::Delete(const KeyType key) {
	RBT_Node* delnode = Search(key);
	if (!delnode) return -1;

	ElemType oldvalue = delnode->value;

	DelNode(delnode);

	return oldvalue;
}

/*
* 3种况：
*     1、待删除结点为叶节点
*     2、待删除结点仅有左子树或右子树，则用左孩子或右孩子代替即可
*     3、待删除结点有左孩子和右孩子，找其前驱或后继覆盖待删除结点，转化为删除前驱或后继
*/
void RBTree::DelNode(RBT_Node* node) {
	if (node->lchild && node->rchild) { //删除结点有两个孩子,找前驱或后继结点代替
		RBT_Node* successor = nextNode(node);
		node->key = successor->key;
		node->value = successor->value;
		node = successor;

	   /*
	   *  前驱结点代替：
	   *  RBT_Node* precessor = preNode(node);  
	   *  node->key = precessor->key;
	   *  node->value = precessor->value;
       *  node = precessor;
	   */
	}
	//转化为1、2两种情况
    //找寻替代结点
	RBT_Node* replacement = node->lchild?node->lchild:node->rchild;

	if (replacement) { //情况1，待删除结点有子树
		//replacement挂在node的父亲结点下
		replacement->parent = node->parent;
		if (!ParentOf(node))
			Tree = replacement;
		else if (LeftOf(ParentOf(node)) == node)
			ParentOf(node)->lchild = replacement;
		else
			ParentOf(node)->rchild = replacement;

		//断开node所有指针连接
		node->lchild = node->rchild = node->parent = nullptr;
		delete node;

		if (Color_Is_Black(node)) { //待删除结点为黑色结点，则需要调整
			deleteFixUp(replacement);
		}

	}
	else if(!ParentOf(node)){ //特殊情况，红黑树为单个结点,直接删除根
		delete Tree;
		Tree = nullptr;

	}
	else {
		//情况2，待删除结点为叶节点
		//先调整，后删除；若先删除,deleteFixUp()无参数
		if(Color_Is_Black(node))
		     deleteFixUp(node);
		//删除node
		if (node->parent)
			if (node->parent->lchild == node)
				node->parent->lchild = nullptr;
			else
				node->parent->rchild = nullptr;
		else
			Tree = nullptr;

		node->parent = nullptr;
		delete node;
	}
}

void RBTree::deleteFixUp(RBT_Node* node) { 
	while (node != Tree && Color_Is_Black(node)) {  //删除无子树的结点

		if (node==LeftOf(ParentOf(node))) { //node为左孩子的情况
		    //找寻兄弟结点
			/*      parent:b                                                                    r_cousin:b
			*       /     \                                                        L           /          \
			*    node:b  r_cousin:r     :r_cousin不是真正的兄弟结点,rr_cousin才是  --->     parent:r   lr_cousin:b 
			*             /      \                                                         /     \
	 		*       rr_cousin:b  lr_cousin:b                                           node:b  rr_cousin:b
			*/
			RBT_Node *r_cousin = RightOf(ParentOf(node));
			//判断此时兄弟结点是否是真正的兄弟结点，若兄弟结点为红，则不是真正的结点
			if (Color_Is_Red(r_cousin)) {
				SetRed(ParentOf(r_cousin));
				SetBlack(r_cousin);
				LeftRotate(ParentOf(r_cousin));
				r_cousin = ParentOf(node)->rchild;
			}

			if (Color_Is_Black(r_cousin->lchild)&&Color_Is_Black(r_cousin->rchild)) {
			/*
			* 情况1 兄弟不够借
			*           parent:r
			*           /      \
			*        node:b   r_cousin:b
			*
			*/
            //向上递归，有兄弟变红，父节点变黑。
				SetRed(r_cousin);
				node = ParentOf(node);

			} 
			else {
				//情况2 兄弟够借
				//分两种，一种兄弟结点为3结点，第二种兄弟结点为4结点
				if (Color_Is_Black(r_cousin->rchild)) { 
					/*           gdparent:b                     gdparent                          
					*             /      \                      /     \                       
					*         parent:r   xx       R          parent:r  xx        
					*         /      \         ---->        /     \              （统一形态，为后序操作铺垫）
					*     node:b   r_cousin:b            node:b  lr_cousin:b          
					*                /                              \                   /
					*          lr_cousin:r                         r_cousin:r        
					*/
					SetRed(r_cousin);
					SetBlack(r_cousin->lchild);
					RightRotate(r_cousin);
					r_cousin = ParentOf(node)->rchild;
				}
				/*           gdparent:b                    gdparent:b                  gdparent:b               gdparent
				*             /      \                      /     \                     /     \                  /     \
				*         parent:r   xx                parent:r   xx       L       r_cousin:r  xx          r_cousin:r  xx
				*         /      \                      /     \          ---->      /     \                 /      \ 
				*     node:b   r_cousin:b           node:b  r_cousin:b        parent:b   rr_cousin:b   parent:b  rr_cousin:b
				*                /     \                         \             /    \                     /
				*          lr_cousin:r  rr_cousin:r           rr_cousin:r   node:b  lr_cousin:r       node:b
				*/
				Color_Is_Black(ParentOf(node))?SetBlack(r_cousin) :SetRed(r_cousin);
				SetBlack(ParentOf(node));
				SetBlack(r_cousin->rchild);
				LeftRotate(ParentOf(node));
				node = Tree;
			}

			
		}
		else {
			RBT_Node* l_cousin = LeftOf(ParentOf(node));
			if (Color_Is_Red(l_cousin)) {
				SetRed(ParentOf(l_cousin));
				SetBlack(l_cousin);
				RightRotate(ParentOf(l_cousin));
				l_cousin = ParentOf(node)->lchild;
			}

			if (Color_Is_Black(RightOf(l_cousin)) && Color_Is_Black(LeftOf(l_cousin))) {
				SetRed(l_cousin);
				node = ParentOf(node);

			}
			else {
				if (Color_Is_Black(l_cousin->lchild)) {
					SetRed(l_cousin);
					SetBlack(l_cousin->rchild);
					LeftRotate(l_cousin);
					l_cousin = LeftOf(ParentOf(node));
				}
				Color_Is_Black(ParentOf(node)) ? SetBlack(l_cousin) : SetRed(l_cousin);
				SetBlack(ParentOf(node));
				SetBlack(l_cousin->lchild);
				RightRotate(ParentOf(node));
				node = Tree;
			}
		}
	}
		SetBlack(node);
}
#endif