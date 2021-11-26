#include"BinaryTree.h"
/*
* 
* Binary Tree
*/
void BinaryTree::initialize(TreeNode*& root) {
	/*
	* ����ݹ��ʼ����
	* ���룺 root   ����
	*/
	Type c;
	if (root == tree) std::cout <<
		"Enter preorder traversal sequence('\\' represent nullptr):"<<std::endl;
	std::cin >> c;
	if (c == '\\') root = nullptr;
	else {
		root = new TreeNode;
		root->data = c;
		initialize(root->left);
		initialize(root->right);
	}
}

int Find(Type root_data, Type* In, int start, int end) {
	/*
	* ��ѰIn������ root_data���ֵ�λ������
	*/
	for (int i = start; i <= end; i++)
		if (In[i] == root_data) return i;
}
TreeNode* BinaryTree::pre_in_creat(Type* Pre, int start1, int end1, Type* In, int start2, int end2) {
	/*
	* ��������������������������
	* ���룺 Pre      �����������
	*       start1   Pre��ʼ������
	*        end1     Pre��ֹ������
	* *      In      �����������
	*       start2   Pre��ʼ������
	*        end2     Pre��ֹ������
	* ����� �������
	*/      
	TreeNode* root = new TreeNode{ Pre[start1] };
	if (!tree) tree = root;
	int root_index = Find(Pre[start1],In, start2, end2);
	int left_size = root_index - start2;
	int right_size = end2 - root_index;
	if (left_size <= 0) //������Ϊ��
		root->left = nullptr;
	else
		root->left = pre_in_creat(Pre, start1 + 1, start1 + left_size, In, start2, start2 + left_size - 1);
	if (right_size <= 0) //������Ϊ��
		root->right = nullptr;
	else
		root->right = pre_in_creat(Pre, end1-right_size+1,end1, In, end2-right_size+1, end2);
	return root;
}
TreeNode* BinaryTree::PreInCreat(Type*Pre, Type*In, int size) {
	int start = 0, end = start + size - 1;
	TreeNode* ret = pre_in_creat(Pre, start, end, In, start, end);
	return ret;
}


void BinaryTree::pre2post_fulltree(Type* Pre, int start1, int end1,Type* Post,int start2,int end2) {
	/*
	* ��������������ǰ�����У��ó���������У�
	* ���룺 Pre      �����������
	*       start1   Pre��ʼ������
	*        end1     Pre��ֹ������
	* *      Post      ����������У���Ž��
	*       start2    Post��ʼ������
	*        end2     Post��ֹ������
	*/
	Type root = Pre[start1];
	int t_size = (end1-start1) / 2;
	Post[end2] = root;
	if (t_size != 0) {

		int left_start1 = start1 + 1, left_end1 = left_start1 + t_size - 1;
		int right_start1 = left_end1 + 1, right_end1 = right_start1 + t_size - 1;

		int left_start2 = start2, left_end2 = left_start2 + t_size - 1;
		int right_start2 = left_end2 + 1, right_end2 = right_start2 + t_size - 1;

		pre2post_fulltree(Pre, left_start1, left_end1, Post, left_start2, left_end2);
		pre2post_fulltree(Pre, right_start1, right_end1, Post, right_start2, right_end2);
	}
}
void BinaryTree::Pre2Post_FullTree(Type* Pre, Type* Post,int size) {
	int start = 0, end = start + size - 1;
	pre2post_fulltree(Pre, start, end, Post, start, end);
}


TreeNode* BinaryTree::LeafLink() {
	/*
	* ��Ҷ�ڵ���������ʽ��������
	*/
	LStack<TreeNode*> stack;
	TreeNode* head = new TreeNode{0,nullptr,nullptr};
	TreeNode* p = tree,*tail=head;
	while (p || !stack.IsEmpty()) {
		if (p) {
			if (!p->left && !p->right) {//Ҷ�ڵ�
				p->right=tail->right;
				tail->right = p;
				tail = p;
			}
			stack.Push(p);
			p = p->left;
		}
		else {
			stack.Pop(p);
			p = p->right;
		}
	}
	tail->right = nullptr;
	return head;
}

void BinaryTree::preprint(TreeNode* root) {
	/*
	* ���������ӡ����
	* ���룺 root      ���ڵ�
	*/
	if (root == this->tree) std::cout << "Preorder traveral :" << std::endl;
	if (!root) return;
	std::cout << root->data << " ";
	preprint(root->left);
	preprint(root->right);
	if (root == this->tree) std::cout << std::endl;
}

void BinaryTree::PrePrint_NR() {
	/*
	* ��������ǵݹ��㷨��ӡ����
	*/
	std::cout << "Preorder traveral by non-recursion :" << std::endl;
	TreeNode* p = tree;
	LStack<TreeNode*> stack;
	while (p || !stack.IsEmpty()) {
		if (p) {//��ջ
			std::cout << p->data << " ";
			stack.Push(p);
			p = p->left;
		}
		else {
			stack.Pop(p);
			p = p->right;
		}
	}
	std::cout << std::endl;
}

Type BinaryTree::preorder_k(TreeNode*root, int& k) {
	/*
	* ��ȡ����������е�k��ֵ��
	* ���룺 root      ���ڵ�
	*/
	if (!root) return -1;
	if (--k == 0) return root->data;
	Type t1=preorder_k(root->left,k);
	if (t1 != -1) return t1;
	Type t2=preorder_k(root->right, k);
	if (t2 != -1) return t2;
	return -1;
}
Type BinaryTree::Preorder_K(int k) {
	int x = k;
	return preorder_k(tree, x);
}


void BinaryTree::inprint(TreeNode* root) {
	/*
	* �б�����ӡ����
	* ���룺 root      ���ڵ�
	*/
	if (root == this->tree) std::cout << "Inorder traveral :" << std::endl;
	if (!root) return;
	inprint(root->left);
	std::cout << root->data << " ";
	inprint(root->right);
	if (root == this->tree) std::cout << std::endl;
}

void BinaryTree::InPrint_NR() {
	/*
	* ��������ǵݹ��ӡ����
	*/
	std::cout << "Inorder traveral by non-recursion :" << std::endl;
	LStack<TreeNode*> stack;
	TreeNode* p = tree;
	while (p || !stack.IsEmpty()) {
		if (p) {
			stack.Push(p);
			p = p->left;
		}
		else {
			stack.Pop(p);
			std::cout << p->data << " ";
			p = p->right;
		}
	}
	std::cout << std::endl;
}

void BinaryTree::postprint(TreeNode* root) {
	/*
	* ���������ӡ����
	* ���룺 root      ���ڵ�
	*/
	if (root == this->tree) std::cout << "Postorder traveral :" << std::endl;
	if (!root) return;
	postprint(root->left);
	postprint(root->right);
	std::cout << root->data << " ";
	if (root == this->tree) std::cout << std::endl;
}

void BinaryTree::PostPrint_NR() {
	/*
	* ��������ǵݹ��ӡ����
	*/
	std::cout << "Postorder traveral by non-recursion:" << std::endl;
	LStack<TreeNode*>s1, s2;
	TreeNode* p=tree;
	while (p || !s1.IsEmpty()) {
		if (p) {
			s2.Push(p);
			s1.Push(p);
			p = p->right;
		}
		else {
			s1.Pop(p);
			p = p->left;
		}
	}
	while (!s2.IsEmpty()) {
		s2.Pop(p);
		std::cout << p->data << " ";
	}
	std::cout << std::endl;
}

bool BinaryTree::print_x_ancestor(TreeNode*root,Type x) {
	/*
	* ��ӡֵΪx�����Ƚ�㣺
	* ���룺 root      ���ڵ�
	*        x        Ŀ��ֵ
	*/
	if (!root) return false;
	if (root->data == x) return true;
	bool find=print_x_ancestor(root->left, x) || print_x_ancestor(root->right,x);
	if(find)std::cout << root->data << " ";
	return find;
}
void BinaryTree::Print_x_Ancestor(Type x) {
	print_x_ancestor(tree, x);
}

void BinaryTree::LevelPrint() {
	/*
	* ��α�����ӡ����
	*/
	std::cout << "Level traveral :" << std::endl;
	LQueue<TreeNode*> queue;
	TreeNode* p = tree;
	queue.EnQueue(p);
	while (!queue.IsEmpty()) {
		queue.DeQueue(p);
		std::cout << p->data << " ";
		if (p->left) queue.EnQueue(p->left);
		if (p->right) queue.EnQueue(p->right);
	}
	std::cout << std::endl;
}

void BinaryTree::LevelPrint_R2L() {
	/*
	* ��α����� Right->left ��ӡ
	*/
	std::cout << "Level traveral(from right to left)" << std::endl;
	LQueue<TreeNode*> queue;
	TreeNode* p = tree;
	queue.EnQueue(p);
	while (!queue.IsEmpty()) {
		queue.DeQueue(p);
		std::cout << p->data << " ";
		if (p->right) queue.EnQueue(p->right);
		if (p->left) queue.EnQueue(p->left);
	}
	std::cout << std::endl;
}

void BinaryTree::Print_Data_Equal_k(Type k) {
	/*
	* ��ӡ·���Ͻ��֮�͵���k��·������Ҷ�ڵ�
	*/
	int n = GetHight();
	Type sum = 0;
	Type* route = new Type[n];
	print_data_equal_k(tree, route, 1, sum, k);
}

void BinaryTree::print_data_equal_k(TreeNode*root, Type*route, int level, Type& sum, Type k) {
	/*
	* ��������ʼ���·���һֱ��Ҷ�ڵ㣬�����������н���γ�һ��·������ӡ����Ϊk������·��
	* ���룺
	*      root  ����
	*      route �洢·�ߵ�����
	*      level ��Σ���ʼΪ���Ĳ��1
	*      sum   ·���Ͻ��ͣ���ʼΪ0
	*      k     ����Ŀ��ֵ
	*/
	if (!root) return;
	sum += root->data, route[level-1] = root->data;
	if (!root->left && !root->right && sum == k) { //Ҷ��� �� ��Ϊk
		for (int i = 0; i != level; i++)
			std::cout << route[i] << " ";
		std::cout << std::endl;
	}
	print_data_equal_k(root->left, route, level + 1, sum, k);
	print_data_equal_k(root->right, route, level + 1, sum, k);
	sum -= root->data;
}


int BinaryTree::gethight(TreeNode* root) {
	/*
	* ��ȡ���ߣ�
	* ���룺 root      ���ڵ�
	* ����� ����
	*/
	if (!root) return 0;
	if (!root->left && !root->right) return 1;
	int hight = 1 + (gethight(root->left) > gethight(root->right)
		? gethight(root->left) : gethight(root->right));
	if (root == tree)
		std::cout << "Compute the hight of tree : hight = " << hight << std::endl;
	return hight;
}

int BinaryTree::GetHight_NR() {
	/*
	* ��ȡ���ߣ��ǵݹ��㷨
	*/
	int hight = 0, size=1,cur_count=0,next_count = 1;
	LQueue<TreeNode*> queue;
	TreeNode* p = tree;
	queue.EnQueue(p);
	while (!queue.IsEmpty()) {
		queue.DeQueue(p);
		size--,cur_count++;
		if (p->left) queue.EnQueue(p->left),size++;
		if (p->right) queue.EnQueue(p->right),size++;
		if (cur_count == next_count) {
			hight++;
			cur_count = 0;
			next_count=size;
		}
	}

	std::cout << "Compute the hight of tree by non-recursion: hight = "<<hight<<std::endl;
	return hight;
}

int BinaryTree::get_leaf_size(TreeNode* root) {
	/*
	* ��ȡҶ�ӽ������
	* ���룺 root      ���ڵ�
	*/
	if (!root) return 0;
	if (!root->left && !root->right) return 1;
	return get_leaf_size(root->left) + get_leaf_size(root->right);
}

int BinaryTree::get_branch_size(TreeNode* root) {
	/*
	* ��ȡ��֧�������
	* ���룺 root      ���ڵ�
	*/
	if (!root->left && !root->right)
		return 0;
	int left = 0, right = 0;
	if (root->left)
		left = get_branch_size(root->left);
	if (root->right)
		right = get_branch_size(root->right);
	return 1 + left + right;
}

int BinaryTree::get_level_size(TreeNode* root, int k) {
	/*
	* ��ȡ��k��������
	* ���룺 root      ���ڵ�
	*        k         ����
	*/         
	if (!root || k < 1) return 0;
	if (k == 1) return 1;
	return get_level_size(root->left, k - 1) + get_level_size(root->right, k - 1);
}

int BinaryTree::GetWidth() {
	/*
	* ��ȡ��������ȣ�
	* ��α�������¼���ֵ
	*/
	LQueue<TreeNode*> queue;
	TreeNode* p=tree;
	int width = 0, size = 1, cur_nodes = 0, next_nodes = 1;
	queue.EnQueue(p);
	while (!queue.IsEmpty()) {
		queue.DeQueue(p);
		size--;
		if (p->left) queue.EnQueue(p->left), size++;
		if (p->right) queue.EnQueue(p->right), size++;
		if (++cur_nodes == next_nodes) {
			width = width < size ? size : width;
			cur_nodes = 0, next_nodes = size;
		}
	}
	std::cout << " The width of tree is : " << width << std::endl;
	return width;
}

int BinaryTree::get_wpl(TreeNode*root, int deep) {
	/*
	* ����WPL, WPL = SUM(Leaf * length)
	* deep �� ��ȣ���¼Ҷ�ڵ��·������
	*/
	if (!root) return 0;
	if (root && !root->left && !root->right)
		return (deep-1) * root->data;
	int left_wpl = 0, right_wpl = 0;
	if(root->left)
	   left_wpl = get_wpl(root->left, deep + 1);
	if(root->right)
	   right_wpl = get_wpl(root->right, deep + 1);
	return left_wpl + right_wpl;
}

bool BinaryTree::IsComplete() { //�ؼ������п�ָ��Ӧ��������
	/*
	* �ж��Ƿ�Ϊ��ȫ������
	*/
	LQueue<TreeNode*> queue;
	TreeNode* p = tree;
	queue.EnQueue(p);
	while (!queue.IsEmpty()) { //�����п�ָ����Ϊ���
		queue.DeQueue(p);
		if (p) {
			queue.EnQueue(p->left);
			queue.EnQueue(p->right);
		}
		else {  //�����ս�㣬�������Ӧȫ�ǿս��
			while (!queue.IsEmpty()) {
				queue.DeQueue(p);
				if (p)
					return false;
			}
		}
	}
	return true;
}

bool BinaryTree::ancestor(TreeNode*root, TreeNode*p, TreeNode*q,TreeNode* &ret) {
	/*
	* ������������ȣ�
	* ���룺 root      ���ڵ�
	*        p��q      Ŀ�������
	* ����� ancesrot  ���Ƚ��
	* 
	*/
	if (!root) return false;
	if (root == q && root == p) ret = root;
	if (root == p || root == q) return true;
	bool left_find = ancestor(root->left, p, q,ret);
	bool right_find = ancestor(root->right, p, q,ret);
	if (left_find && right_find)
		ret = root;
	return left_find || right_find;
}
TreeNode* BinaryTree::Ancestor(TreeNode* p, TreeNode* q) {
	TreeNode* ret = nullptr;
	ancestor(tree, p, q, ret);
	return ret;
}


bool BinaryTree::is_similar(TreeNode* tree1, TreeNode*tree2) {
	/*
	* �ж�tree1 �� tree2 �Ƿ�����
	*/
	if (!tree1 && !tree2)
		return true;
	if (!tree1 && tree2 || tree1 && !tree2)
		return false;
	bool left_tag = is_similar(tree1->left, tree2->left);
	bool right_tag = is_similar(tree1->right, tree2->right);
	return left_tag && right_tag;

}

bool BinaryTree::is_BST(TreeNode*& cur, TreeNode*& pre) {
	if (!cur) return true;
	bool left_tag = is_BST(cur->left, pre);
	bool cur_tag = true;
	if (pre && pre->data >= cur->data)
		cur_tag = false;
	pre = cur;
	bool right_tag = is_BST(pre->right, pre);
	return left_tag && right_tag && cur_tag;
}
bool BinaryTree::IsBST() {
	TreeNode* pre = nullptr;
	return is_BST(tree, pre);
}

TreeNode* BinaryTree::get_parent(TreeNode*root, TreeNode*child) {
	/*
	* ��ȡ���ڵ㣺
	* ���룺 root      ���ڵ�
	*       child     Ŀ����
	*/
	if (!root || !child) return nullptr;
	if (root->left == child || root->right == child) return root;
	TreeNode* ltree = get_parent(root->left, child);
	TreeNode* rtree = get_parent(root->right, child);
	return ltree ? ltree : rtree;
}

TreeNode* BinaryTree::find_element(TreeNode* root, const Type goal) {
	/*
	* ����ֵ��
	* ���룺 root      ���ڵ�
	*        goal     Ŀ��ֵ
	*/
	if (!root) return nullptr;
	if (root->data == goal) return root;
	TreeNode* ltree = find_element(root->left, goal);
	TreeNode* rtree = find_element(root->right, goal);
	return ltree ? ltree : rtree;
}

void BinaryTree::exchange_node(TreeNode* root) {
	/*
	* �����������ҽڵ㣺
	* ���룺 root      ���ڵ�
	*/
	if (!root) return;
	TreeNode* temp = root->left;
	root->left = root->right;
	root->right = temp;
	exchange_node(root->left);
	exchange_node(root->right);
}

void BinaryTree::get_infix_expre(TreeNode*root) {
	/*
	* ��ȡ��׺���ʽ
	*/
	if (!root) return;
	if (!root->left && !root->right)
		std::cout << root->data;
	else {
		if (root != tree)
			std::cout << "(";
		get_infix_expre(root->left);
		std::cout << root->data;
		get_infix_expre(root->right);
		if (root != tree)
			std::cout << ")";
	}
}

void BinaryTree::Get_InfixExpre_NR() {
	/*
	* ��ȡ��׺���ʽ���ǵݹ��㷨
	*/
	LStack<TreeNode*> stack;
	TreeNode* p = tree;
	int tag = 0,index=0;
	while ((p && !isalnum(p->data)) || !stack.IsEmpty()) {
		if (p && !isalnum(p->data)) {
			stack.Push(p);
			p = p->left;
		}
		else {
			stack.Pop(p);
			if (p->left && isalnum(p->left->data))
				std::cout << '(' << p->left->data;
			else if (!p->left) {
				std::cout << '(';
				tag++;
			}

			std::cout << p->data;

			if (p->right && isalnum(p->right->data)) {
				std::cout << p->right->data << ')';
				while (tag > 0) {
					std::cout << ')';
				}
			}
			p = p->right;
		}
	}
}



void BinaryTree::Destroy(TreeNode* root) {
	/*
	* ��������
	* ���룺 root      ���ڵ�
	*/
	if (!root) return;
	Destroy(root->left);
	Destroy(root->right);
	delete root;
}

void Destroy_tree(TreeNode* root) {
	/*
	* ��������
	* ���룺 root      ���ڵ�
	*/
	if (!root) return;
	Destroy_tree(root->left);
	Destroy_tree(root->right);
	delete root;
}
void BinaryTree::Destroy_x_root(TreeNode*&root, Type x) {
	/*
	* ����ɾ����ֵxΪ����������
	* ���룺 root      ���ڵ�
	*         x        Ŀ��ֵ
	*/
	if (!root) return;
	if (root->data == x) {
		Destroy_tree(root);
		root = new TreeNode{ x,nullptr,nullptr };
	}
	Destroy_x_root(root->left, x);
	Destroy_x_root(root->right, x);
}

void Initialize_SSBinaryTree(SSBinarytTree& tree, int n) {
	/*
	* ��ʼ��˳��洢�Ķ�����
	* ���룺  tree    ���ڵ�
	*          n      �����������
	*/
	tree = nullptr;
	if (n <= 0) return;
	tree = new Type[MAXSIZE];
	for (int i = 0; i != MAXSIZE; i++) tree[i] = nul;
	std::cout << "Initialize Sequentially Storaged Binary Tree(Max Size= "
		<< (n > MAXSIZE ? MAXSIZE : n) << " ,Enter (key,value)):" << std::endl;
	int count = 0, pos;
	Type t;
	while (count < n && count < MAXSIZE && std::cin >> pos >> t) {
		if (pos < 0 || pos >= MAXSIZE)
			std::cerr << "Position illegal" << std::endl;
		else {
			tree[pos] = t;
			++count;
		}
	}
}


/*
* Thread Binary Tree
* 
*/
void ThreadTree::Initialize(ThreadNode*& root) {
	char c;
	std::cout << "Enter q or Q to creat a null node : ";
	std::cin >> c;
	if (tolower(c) == 'q') root = nullptr;
	else {
		Type t;
		std::cout << "value : ";
		std::cin >> t;
		root = new ThreadNode{ t,nullptr,nullptr,0,0 };
		Initialize(root->left);
		Initialize(root->right);
	}
}

void ThreadTree::InThread(ThreadNode*&post, ThreadNode*&pre) {
	if (!post) return;
	InThread(post->left, pre);   //����
	if (!post->left)  //post��ָ��գ�������
		post->left = pre, post->ltag = 1;
	if (pre && !pre->right)  //pre��ָ��գ�������
		pre->right = post, pre->rtag = 1;
	pre = post;
	InThread(post->right, pre);  //����
}

void ThreadTree::CreatInThread() {
	if (!tree) return;
	ThreadNode* p = nullptr;
	InThread(tree, p);
	p->right = nullptr, p->rtag = 1;
}

ThreadNode* ThreadTree::FirstNode(ThreadNode* root) {
	while (root->ltag == 0) root = root->left; 
	return root;
}
ThreadNode* ThreadTree::In_NextNode(ThreadNode* root) {
	if (root->rtag == 1) return root->right;
	return FirstNode(root->right);
}
ThreadNode* ThreadTree::In_PreNode(ThreadNode*root) {
	if (root->ltag) return root->left;
	ThreadNode* p = root->left;
	while (p->rtag == 0) p = p->right;
	return p;
}

void ThreadTree::Inorder() {
	for (ThreadNode* p = FirstNode(tree); p != nullptr; p = In_NextNode(p))
		std::cout << p->data << " ";
	std::cout << std::endl;
}

void ThreadTree::PreThread(ThreadNode* &post,ThreadNode*& pre) {
	if (!post) return;
	if (!post->left) //post��գ�������
		post->ltag = 1, post->left = pre;
	if (pre && !pre->right) //pre�ҿգ�������
		pre->rtag = 1, pre->right = post;
	pre = post;
	if(post->ltag==0)
	PreThread(post->left, pre);
	if(post->rtag==0)
	PreThread(post->right, pre);
}

void ThreadTree::CreatPreThread() {
	if (!tree) return;
	ThreadNode* pre = nullptr;
	PreThread(tree, pre);
	pre->right = nullptr, pre->rtag = 1;
}

ThreadNode* ThreadTree::Pre_NextNode(ThreadNode* root){
	if (root->rtag) return root->right;
	else if (root->left) return root->left;
	else return root->right;
}

void ThreadTree::Preorder() {
	for (ThreadNode* p = tree; p != nullptr; p = Pre_NextNode(p))
		std::cout << p->data << " ";
	std::cout << std::endl;
}


/*
* BST
* 
*/
void BinarySearchTree::Initialize() {
	/*
	* BST��ʼ������
	*/
	std::cout << "Enter a sequence ('-1' to end):" << std::endl;
	T t;
	std::cin >> t;
	while (t != -1) {
		Insert(t);
		std::cin >> t;
	}
}

BST_Node* BinarySearchTree::find_element(BST_Node*root, const T& t) {
	/*
	* BST���Ҳ���
	*/
	if (!root) return nullptr;
	if (root->data == t) return root;
	if (root->data > t)
		return find_element(root->left, t);
	else
		return find_element(root->right, t);
}
BST_Node* BinarySearchTree::FindElement(const T& t) {
	/*BST���ҷ�װ����
	*/
	return find_element(root, t);
}
BST_Node* BinarySearchTree::FindElement_NR(const T& t) {
	/*
	* BST�ǵݹ�Ĳ���
	*/
	BST_Node* p = root;
	while (p && p->data != t) {
		if (p->data > t)
			p = p->left;
		else
			p = p->right;
	}
	if (!p)
		std::cout << t << " is not in binary search tree" << std::endl;
	else
		std::cout << "Find out " << t << "successfully" << std::endl;
	return p;
}

bool BinarySearchTree::insert(BST_Node*& root, const T&t) {
	/*
	* BST�������
	*/
	if (!root) {
		root = new BST_Node{ t,nullptr,nullptr };
		return true;
	}
	if (root && root->data == t)
		return false;
	if (root->data > t)  return insert(root->left, t);
	if (root->data < t) return insert(root->right, t);
}
bool BinarySearchTree::Insert(const T& t) {
	/*
	* BST���������װ����
	*/
	return insert(root, t);
}

bool BinarySearchTree::delete_element(BST_Node*& pre, BST_Node*& cur, T& t) {
	/*
	* BSTɾ������
	*/
	if (cur) {
		bool l = delete_element(pre, cur->left, t);
		if (cur->data == t) {
			BST_Node* p = cur;
			if (cur->left == nullptr) {
				cur = cur->right;
				delete p;
				return true;
			}
			else if (cur->right == nullptr) {
				cur = cur->left;
				delete p;
				return true;
			}
		}
		if (pre && pre->data == t) {
			pre->data = cur->data;
			cur->data = t;
			return l || delete_element(pre, cur, t);
		}
		else {
			pre = cur;
			return l || delete_element(pre, cur->right, t);
		}
	}
	else
		return false;
}
bool BinarySearchTree::DeleteElement(const T&t) {
	/*
	* BSTɾ��������װ����
	*/
	T value = t;
	BST_Node* pre = nullptr;
	return delete_element(pre, root,value);

}

void BinarySearchTree::print(BST_Node* root) {
	/*
	* BST��ӡ
	*/
	if (!root) return;
	print(root->left);
	std::cout << root->data << " ";
	print(root->right);
}

void BinarySearchTree::Print() {
	/*
	* BST��ӡ��װ����
	*/
	std::cout << "The content of BST : " << std::endl;
	print(root);
	std::cout<<std::endl;
}

/*
* AVL
* 
*/
int AVL_Tree::GetHight(AVL_Node* root) {
	/*
	* ��ȡ����
	*/
	if (!root) return 0;
	int left_hight = GetHight(root->left);
	int right_hight = GetHight(root->right);
	return 1 + (left_hight > right_hight ? left_hight : right_hight);
}

int AVL_Tree::BalanceFactor(AVL_Node* root) {
	/*
	* ������ƽ������
	*/
	if (!root) return 0;
	int left_hight = 0, right_hight = 0;
	if (root->left)
		left_hight = GetHight(root->left);
	if (root->right)
		right_hight = GetHight(root->right);
	return left_hight - right_hight;
}

void AVL_Tree::Right_Rotate(AVL_Node* &root) {
	/*
	* ��������
	*/
	if (!root) return;
	AVL_Node* ltree = root->left;
	root->left = ltree->right, ltree->right = root;
	root = ltree;
}

void AVL_Tree::Left_Rotate(AVL_Node* &root) {
	/*
	* ��������
	*/
	if (!root) return;
	AVL_Node* rtree = root->right;
	root->right = rtree->left, rtree->left = root;
	root = rtree;
}

void AVL_Tree::ReBalance(AVL_Node* &root) {
	/*
	* LL��LR��RR��RL����
	*/
	int root_balance_factor = BalanceFactor(root);
	if (root_balance_factor > 1 && BalanceFactor(root->left) > 0)//LL
		Right_Rotate(root);
	else if (root_balance_factor > 1 && BalanceFactor(root->left) < 0)//LR
		Left_Rotate(root->left), Right_Rotate(root);
	else if (root_balance_factor < -1 && BalanceFactor(root->right) < 0)//RR
		Left_Rotate(root);
	else if (root_balance_factor < -1 && BalanceFactor(root->right)>0)//RL
		Right_Rotate(root->right), Left_Rotate(root);
}

void AVL_Tree::To_Balance(AVL_Node*&root) {
	/*
	* ����AVL��ʹ֮ƽ��
	*/
	if (!root) return;
	To_Balance(root->left);
	To_Balance(root->right);
	ReBalance(root);
}

void AVL_Tree::insert(AVL_Node*& root, const AVL_Type& t) {
	/*
	* AVL�ݹ���ã��������
	*/
	if (!root) {
		root = new AVL_Node;
		root->data = t, root->left = nullptr, root->right = nullptr;
		return;
	}
	if (root->data < t)
		insert(root->right, t);
	else if (root->data > t)
		insert(root->left, t);
}

void AVL_Tree::Insert(const AVL_Type& t) {
	/*
	* AVL�����װ����
	*/
	insert(tree, t);
	To_Balance(tree);
}

void AVL_Tree::Print() {
	/*
	* ��װ����
	*/
	std::cout << "The content of AVL tree :" << std::endl;
	print(tree);
	std::cout << std::endl;
}

void AVL_Tree::Print_Pre() {
	std::cout << "The content of AVL tree by preorder :" << std::endl;
	print_pre(tree);
	std::cout << std::endl;
}

void AVL_Tree::print(AVL_Node* root) {
	/*
	* �ݹ���ã���ӡAVL
	*/
	if (!root) return;
	print(root->left);
	std::cout << root->data << " ";
	print(root->right);
}

void AVL_Tree::print_pre(AVL_Node* root) {
	if (!root) return;
	std::cout << root->data << " ";
	print_pre(root->left);
	print_pre(root->right);
}

void AVL_Tree::Initialize() {
	/*
	* AVL�����г�ʼ��
	*/
	std::cout << "Enter a sequence (enter -1 to end):" << std::endl;
	AVL_Type t;
	std::cin >> t;
	while (t != -1) {
		Insert(t);
		std::cin >> t;
	}
}

AVL_Node* AVL_Tree::FindElemnt(const AVL_Type& t) {
	/*
	* AVL ���Ҳ���
	*/
	AVL_Node* root = tree;
	int count = 1;
	while (root && root->data != t) {
		if (t > root->data)
			root = root->right;
		else
			root = root->left;
		count++;
	}
	if (!root)
		std::cout << "Search " << t << " Failure. " ;
	else
		std::cout << "Search " << t << " Successfully. ";
	std::cout << "Search Times : " << count << std::endl;
	return root;
}

/*
* 
* question
* 
* 
*/
Type question_P127(SSBinarytTree tree, int pos1, int pos2) {
	if (tree[pos1] == nul || tree[pos2] == nul) return nul;
	int n1 = pos1, n2 = pos2;
	while (n1 != n2) {
		if (n1 > n2) n1 = n1 / 2;
		else n2 = n2 / 2;
	}
	return tree[n1];
}

