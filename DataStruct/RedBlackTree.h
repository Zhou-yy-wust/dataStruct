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

RBT_Node* nextNode(RBT_Node*node) { //��ȡ��̽��
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
RBT_Node* preNode(RBT_Node* node) { //��ȡǰ�����
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
* ����ʾ��ͼ:
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
	
	if (RightOf(y)) { //y���ӷǿգ�����x���Һ�����
		LeftOf(y)->parent = x; 
	}  
	x->rchild = y->lchild;
	y->lchild = x, x->parent = y;
	
	if (!parent) Tree = y; //xΪ���ڵ㣬��yֱ��Ϊ���ڵ�
	else if (LeftOf(parent) == x) parent->lchild = y;
	else parent->rchild =y;
}

/*
* ����ʾ��ͼ:
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
	if (ParentOf(y)) RightOf(x)->parent = x;  //y�Һ��ӷǿգ�����x��������
	x->lchild = y->rchild;
	y->rchild = x, x->parent = y;

	y->parent = parent;
	if (!parent) Tree = y;
	else if (LeftOf(parent) == x) parent->lchild = y;
	else parent->rchild = y;
}

//����
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

//����ؼ���key
void RBTree::Insert(const KeyType key,const ElemType value) {
	RBT_Node* parent = nullptr, * p = Tree;
	while (p && p->key !=key) { //���Ҳ���λ��
		parent = p;
		if (p->key > key) p = LeftOf(p);
		else p = RightOf(p);
	}
    
	if (p) //�������йؼ���ֵ
		return;

	RBT_Node* newnode = new RBT_Node{ key,value,RBT_Color::RED,nullptr,nullptr,parent };  //�����½��

	if (!parent) Tree = newnode;    //���գ���ֱ�Ӳ��ڸ�
	else if (parent->key > newnode->key) parent->lchild = newnode; //���򣬲���parent�������
	else parent->rchild = newnode;

	insertFixUp(newnode);

}

void RBTree::insertFixUp(RBT_Node*node) {
	RBT_Node* parent, * gdparent;

	while ((parent = ParentOf(node)) && Color_Is_Red(parent)) {  //�����ں�ڵ�֮��,�����ںڽڵ�֮���������
		gdparent = ParentOf(parent);

		if (LeftOf(gdparent) == parent) {  //�������ү������
			RBT_Node* uncle = RightOf(gdparent);
			
			if (Color_Is_Black(uncle)) {   //�常���Ϊ��ɫ
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


		else {  //�������ү����Ҳ�
			RBT_Node* uncle = LeftOf(gdparent);

			if (Color_Is_Black(uncle)) { //�常���Ϊ��ɫ
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
* 3�ֿ���
*     1����ɾ�����ΪҶ�ڵ�
*     2����ɾ�������������������������������ӻ��Һ��Ӵ��漴��
*     3����ɾ����������Ӻ��Һ��ӣ�����ǰ�����̸��Ǵ�ɾ����㣬ת��Ϊɾ��ǰ������
*/
void RBTree::DelNode(RBT_Node* node) {
	if (node->lchild && node->rchild) { //ɾ���������������,��ǰ�����̽�����
		RBT_Node* successor = nextNode(node);
		node->key = successor->key;
		node->value = successor->value;
		node = successor;

	   /*
	   *  ǰ�������棺
	   *  RBT_Node* precessor = preNode(node);  
	   *  node->key = precessor->key;
	   *  node->value = precessor->value;
       *  node = precessor;
	   */
	}
	//ת��Ϊ1��2�������
    //��Ѱ������
	RBT_Node* replacement = node->lchild?node->lchild:node->rchild;

	if (replacement) { //���1����ɾ�����������
		//replacement����node�ĸ��׽����
		replacement->parent = node->parent;
		if (!ParentOf(node))
			Tree = replacement;
		else if (LeftOf(ParentOf(node)) == node)
			ParentOf(node)->lchild = replacement;
		else
			ParentOf(node)->rchild = replacement;

		//�Ͽ�node����ָ������
		node->lchild = node->rchild = node->parent = nullptr;
		delete node;

		if (Color_Is_Black(node)) { //��ɾ�����Ϊ��ɫ��㣬����Ҫ����
			deleteFixUp(replacement);
		}

	}
	else if(!ParentOf(node)){ //��������������Ϊ�������,ֱ��ɾ����
		delete Tree;
		Tree = nullptr;

	}
	else {
		//���2����ɾ�����ΪҶ�ڵ�
		//�ȵ�������ɾ��������ɾ��,deleteFixUp()�޲���
		if(Color_Is_Black(node))
		     deleteFixUp(node);
		//ɾ��node
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
	while (node != Tree && Color_Is_Black(node)) {  //ɾ���������Ľ��

		if (node==LeftOf(ParentOf(node))) { //nodeΪ���ӵ����
		    //��Ѱ�ֵܽ��
			/*      parent:b                                                                    r_cousin:b
			*       /     \                                                        L           /          \
			*    node:b  r_cousin:r     :r_cousin�����������ֵܽ��,rr_cousin����  --->     parent:r   lr_cousin:b 
			*             /      \                                                         /     \
	 		*       rr_cousin:b  lr_cousin:b                                           node:b  rr_cousin:b
			*/
			RBT_Node *r_cousin = RightOf(ParentOf(node));
			//�жϴ�ʱ�ֵܽ���Ƿ����������ֵܽ�㣬���ֵܽ��Ϊ�죬���������Ľ��
			if (Color_Is_Red(r_cousin)) {
				SetRed(ParentOf(r_cousin));
				SetBlack(r_cousin);
				LeftRotate(ParentOf(r_cousin));
				r_cousin = ParentOf(node)->rchild;
			}

			if (Color_Is_Black(r_cousin->lchild)&&Color_Is_Black(r_cousin->rchild)) {
			/*
			* ���1 �ֵܲ�����
			*           parent:r
			*           /      \
			*        node:b   r_cousin:b
			*
			*/
            //���ϵݹ飬���ֵܱ�죬���ڵ��ڡ�
				SetRed(r_cousin);
				node = ParentOf(node);

			} 
			else {
				//���2 �ֵܹ���
				//�����֣�һ���ֵܽ��Ϊ3��㣬�ڶ����ֵܽ��Ϊ4���
				if (Color_Is_Black(r_cousin->rchild)) { 
					/*           gdparent:b                     gdparent                          
					*             /      \                      /     \                       
					*         parent:r   xx       R          parent:r  xx        
					*         /      \         ---->        /     \              ��ͳһ��̬��Ϊ��������̵棩
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