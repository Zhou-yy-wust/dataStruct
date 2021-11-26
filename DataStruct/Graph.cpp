#include"Graph.h"
/*
* Matrix Graph
*/
void MGraph::Initialize() {
	vexnum = 0;
	std::cout << "Enter the number of vexter :";
	std::cin >> vexnum;
	
	if (vexnum <= 0) return;
	
	Vex = new VertexType[vexnum];
	Edge = new EdgeType * [vexnum];
	for (int i = 0; i != vexnum; i++)
		Edge[i] = new EdgeType[vexnum];
	
	VertexType t;
	std::cout << "Enter vertices : ";
	for (int i = 0; i != vexnum; i++) {
		std::cin >> t;
		Vex[i] = t;
	}

	EdgeType t2;
	std::cout << "Enter adjacency matrix (0 means Inf) : " << std::endl;
	for (int i = 0; i != vexnum; i++) {
		std::cout << "Enter the edge adjacent to " << Vex[i] << " : ";
		for (int j = 0; j != vexnum; j++) {
			std::cin >> t2;
			if (t2 != 0)
				Edge[i][j] = t2;
			else
				Edge[i][j] = Inf;
		}
	}

	std::cout << std::endl;

}

MGraph::~MGraph() {
	delete []Vex;
	for (int i = 0; i != vexnum; i++)
		delete[]Edge[i];
	delete[]Edge;
}

int MGraph::Getpos(VertexType v) {
	for (int k = 0; k != vexnum; k++)
		if (Vex[k] == v)
			return k;
	return -1;
}

VertexType MGraph::FirstNeighbor(VertexType v) {
	int k =Getpos(v);
	if(k>=0)
	for (int i = 0; i != vexnum; i++)
		if (Edge[k][i] > 0)
			return Vex[i];
	return -1;
}

VertexType MGraph::NextNeighbor(VertexType v, VertexType w) {
	int pos_v = Getpos(v), pos_w =Getpos(w);
	for (int i = 0; i != vexnum; i++)
		if (i > pos_w && Edge[pos_v][i] > 0)
			return Vex[i];
	return -1;
}

void MGraph::BFSTraverse(const VertexType& p) {
	std::cout << "Graph BFS:" << std::endl;
	bool *visit=new bool[vexnum];
	for (int i = 0; i != vexnum; i++)
		visit[i] = false;

	int k = Getpos(p);
	BFS(p, visit);

	for (int i = 0; i != vexnum; i++)
		if (!visit[i])
			BFS(Vex[i], visit);
	std::cout << std::endl;

}
void MGraph::BFS(VertexType v, bool* visit) {
	LQueue<VertexType> queue;
	queue.EnQueue(v);
	std::cout << v << " ";
	visit[Getpos(v)] = true;
	while (!queue.IsEmpty()) {
		queue.DeQueue(v);
		for (VertexType w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) {
			int pos_w = Getpos(w);
			if (!visit[pos_w]) {
				std::cout << w << " ";
				visit[pos_w] = true;
				queue.EnQueue(w);   
			}
		}
	}
}

void MGraph::DFSTraverse(const VertexType&v) {
	bool* visit = new bool[vexnum];
	for (int i = 0; i != vexnum; i++) visit[i] = false;

	int k = Getpos(v);
	DFS(v, visit);
	for (int i = 0; i != vexnum; i++)
		if (!visit[i])
			DFS(Vex[i],visit);
}
void MGraph::DFS(VertexType v, bool* visit){
	int k = Getpos(v);
	visit[k] = true;
	for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t)) {
		int k = Getpos(t);
		if (!visit[k])
			DFS(t, visit);
	}
	  
}


bool MGraph::IsTree() {
	bool* visit = new bool[vexnum];
	for (int i = 0; i != vexnum; i++) visit[i] = false;
	
	int Vnum = 0, Enum = 0;
	DFS(Vex[0], visit, Vnum, Enum);
	if (Vnum == vexnum && Enum == 2 * (Vnum - 1))
		return true;
	return false;
}
void MGraph::DFS(VertexType v, bool*visit, int& Vnum, int& Enum) {
	int k = Getpos(v);
	Vnum++, visit[k] = true;
	for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t)) {
		Enum++;
		int k = Getpos(t);
		if (!visit[k])
			DFS(t, visit, Vnum, Enum);
	}
}

void MGraph::DFS_NR(VertexType t) {
	bool* visit = new bool[vexnum];
	for (int i = 0; i != vexnum; i++) visit[i] = false;
	LStack<VertexType> stack;
	VertexType v = t;
	stack.Push(v);
	while (!stack.IsEmpty()) {
		stack.Pop(v);            //与BFS类似，BFS入队时访问，DFS出栈时访问;并且只有未被访问的才入栈/队，出栈/队时直接访问
		int pos = Getpos(v);
		std::cout << v << " ";
		for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t))
			if (!visit[Getpos(t)])
				stack.Push(t), visit[Getpos(t)] = true;
	}
}

EdgeType MGraph::Prim(VertexType start) {
	VertexType *MST = new VertexType[vexnum];  //顶点集，MST记录当前树中到未加入树中的那些顶点的最近顶点
	EdgeType* low_cost = new EdgeType[vexnum];   //最低权值
													 
	//数据结构初始化
	int pos = Getpos(start);
	EdgeType sum = 0;
	MST[0] = start;
	for (int i = 0; i != vexnum; i++)
		low_cost[i] = Edge[pos][i], MST[i] = start;
	low_cost[pos] = 0;

	//Prim
	std::cout << "Prim Algorithm : " << std::endl;
	for (int k = 1; k != vexnum; k++) { 
		//查找low_cost中的最小值,记录位置
		int min = Inf, ver_pos = 0;
		for (int j = 0; j != vexnum; j++)
			if (low_cost[j] != 0 && low_cost[j] < min)
				min = low_cost[j], ver_pos = j;

		//将最小代价的顶点加入顶点集中
		std::cout << MST[ver_pos] << " -> " << Vex[ver_pos] << " : " << min << std::endl;
		sum += min;
		low_cost[ver_pos] = 0;

		//更新low_cost、MST数组
		for (int j = 0; j != vexnum; j++)
			if (Edge[ver_pos][j] < low_cost[j])
				low_cost[j] = Edge[ver_pos][j], MST[j] = Vex[ver_pos];
	}

	std::cout << "Total toll : " << sum << std::endl;
	return sum;
}

EdgeType* MGraph::Dijkstra(VertexType source) {
	VertexType* path = new VertexType[vexnum];
	EdgeType* dist = new EdgeType[vexnum];
	bool* visit = new bool[vexnum];
	
	//初始化数据结构
	int pos = Getpos(source);
	for (int i = 0; i != vexnum; i++) {
		path[i] = source, visit[i] = false;
		dist[i] = Edge[pos][i];
	}
	visit[pos] = true, dist[pos] = 0, path[pos] = -1;

	//Dijkstra
	for (int k = 1; k != vexnum; k++) {
        
		//找寻visit为false的结点中到source最近的结点
		EdgeType min = Inf;
		int ver_pos = 0;
		for (int j = 0; j != vexnum; j++)
			if (!visit[j] && min > dist[j])
				min = dist[j], ver_pos = j;

		//更新visit、dist、path
		visit[ver_pos] = true;
		for (int j = 0; j != vexnum; j++)
			if (!visit[j] && dist[j] > dist[ver_pos] + Edge[ver_pos][j])
				dist[j] = dist[ver_pos] + Edge[ver_pos][j], path[j] = Vex[ver_pos];
	}

	//打印路径
	for (int k = 0; k != vexnum; k++)
		if (Vex[k] != source)
			Show_Path(dist, path, Vex[k]);

	return dist;
}

void MGraph::Show_Path(EdgeType* dist, VertexType* path, VertexType goal) {
	int pos = Getpos(goal);
	std::cout<< "The shortest distance is : " << dist[pos]<<std::endl;
	while (path[Getpos(goal)] > 0) {
		std::cout << goal << " <- ";
		pos = Getpos(goal),goal = path[pos];
	}
	std::cout << goal << std::endl;
}

void MGraph::Degree(int *degree) {
	for (int i = 0; i != vexnum; i++)
		for (int j = 0; j != vexnum; j++)
			if (Edge[i][j] < Inf)
				degree[j]++;
}

VertexType* MGraph::TopoSort() {
	int* degree = new int[vexnum];
	for (int i = 0; i != vexnum; i++) degree[i] = 0;
	Degree(degree);
	VertexType* path = new VertexType[vexnum];
	
	int i = 0;
	for (; i != vexnum; i++) {
		int j = 0;
		for (; j != vexnum; j++)
			if (degree[j] == 0)
				break;
		if (j == vexnum)
			break;
		//添加到路径
		path[i] = Vex[j], degree[j]--;
		//更改入度
		for (int k = 0; k != vexnum; k++)
			if (Edge[j][k] < Inf && degree[k]>0)
				degree[k]--;
	}

	if (i != vexnum)
		return nullptr;

	//输出路径
	std::cout << "Topological Sort :" << std::endl;
	std::cout << path[0] << "";
	for (int k = 1; k != vexnum; k++)
		std::cout << "->" << path[k];
	std::cout << std::endl;

	return path;
}

int MGraph::ComponentCount() {
	Union_find_sets S(vexnum);
	for(int i=0;i!=vexnum;i++)
		for (int j = i + 1; j != vexnum; j++) {
			if (Edge[i][j] > 0 && Edge[i][j]!=Inf) { //i ,j之间有边，则合并
				int iroot = S.Find(i), jroot = S.Find(j);
				if (iroot != jroot)
					S.Union(iroot, jroot);
			}
		}

	int count = 0;
	for (int i = 0; i != S.GetSize(); i++)
		if (S.GetElement(i) < 0) count++;
	S.print();
	return count;
}

bool MGraph::HasACyclic() {
	Union_find_sets S(vexnum);
	for(int i=0;i!=vexnum;i++)
		for(int j=i+1;j!=vexnum;j++)
			if (Edge[i][j]&&Edge[i][j] != Inf) { //i,j有边
				int iroot = S.Find(i), jroot = S.Find(j);
				if (iroot == jroot) return true;
				else S.Union(iroot, jroot);
			}
	return false;
}




void MGraph::Transposition() {
	for (int i = 0; i != vexnum; i++) 
		for (int j = i + 1; j != vexnum; j++) {
			EdgeType temp = Edge[i][j];
			Edge[i][j] = Edge[j][i];
			Edge[j][i] = temp;
		}
}

void MGraph::DFS_Kosaroju(VertexType v, bool* visit, LStack<VertexType>& stack) {
	int k = Getpos(v);
	visit[k] = true;
	for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t)) {
		int k = Getpos(t);
		if (!visit[k])
			DFS_Kosaroju(t, visit, stack);
	}
	stack.Push(v);   //逆后序遍历
}

void MGraph::DFS_Kosaroju_reverse(VertexType v, bool* visit, int* Colors, int color) {
	int k = Getpos(v);
	visit[k] = true;
	Colors[k] = color; //对顶点染色，统一颜色的属于统一强连通分量
	for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t)) {
		int pos = Getpos(t);
		if (!visit[pos])
			DFS_Kosaroju_reverse(t, visit, Colors, color);
	}
}

void MGraph::Putout(int *color, int count) {
	LQueue<VertexType>* q = new LQueue<VertexType>[count];
	for (int i = 0; i != count; i++)
		for (int j = 0; j != vexnum; j++)
			q[i].EnQueue(Vex[color[i - 1]]);

	VertexType t;
	std::cout << "the number of strongly connected component is " << count << std::endl;
	for (int i = 0; i != count; i++) {
		std::cout << "Part " << i + 1 << ": ";
		while (!q[i].IsEmpty()) {
			q[i].EnQueue(t);
			std::cout << t << ", ";
		}
		std::cout << std::endl;
	}
	delete[] q;
}


void inline InitializeVisit(bool * visit,int n) {
	for (int i = 0; i != n; i++) visit[i] = false;
}

int MGraph::Kosaroju() {
	bool* visit = new bool[vexnum];
	InitializeVisit(visit, vexnum);
	LStack<VertexType> stack;

	for (int i = 0; i != vexnum; i++)
		if (!visit[i])
			DFS_Kosaroju(Vex[i], visit, stack);

	Transposition(); //转置
	InitializeVisit(visit, vexnum);

	int color = 1,count=0;
	int* Colors = new int[vexnum];
	for (int i = 0; i != vexnum; i++) Colors[i] = 0;
	while (!stack.IsEmpty()) {
		VertexType v;
	    stack.Pop(v);
		for(int i=0;i!=vexnum;i++)
			if (!visit[i]) {    //一次遍历即一个连通分量
				count++;
				DFS_Kosaroju_reverse(v, visit, Colors, color++);
			}
	}

	Transposition(); //图复原

	Putout(Colors,count);

	return count;
}


/*
* Ajdacent List
* 
*/

void ALGraph::Initialize() {
	vexnum = 0;
	std::cout << "Enter the number of vexter :";
	std::cin >> vexnum;
	if (vexnum <= 0) return;

	vertices = new VNode[vexnum];

	VertexType t;
	std::cout << "Enter vertices (0 means Inf): ";
	for (int i = 0; i != vexnum; i++) {
		std::cin >> t;
		vertices[i].Vex = t;
	}

	int info = 0;
	std::cout << "Enter adjacent list (vertex:weight ,vertex = '\\' means end) :" << std::endl;
	for (int i = 0; i != vexnum; i++) {
		ArcNode* tail = vertices[i].first;
		std::cout << "Enter the edge adjacent to " << vertices[i].Vex << " : ";
		std::cin >> t;
		while (t != '\\') {
			std::cin >> info;
			info = info == 0 ? Inf : info;
			if (!tail) {
				tail = new ArcNode;
				tail->Vex = t, tail->info = info, tail->next = nullptr;
				vertices[i].first = tail;
			}
			else {
				ArcNode* node = new ArcNode;
				node->Vex = t, node->info = info;
				node->next = tail->next;
				tail->next = node, tail = node;
			}
			++arcnum;
			std::cin >> t;
		}
	}
}

int ALGraph::Getpos(const VertexType& v) {
	for (int i = 0; i != vexnum; i++)
		if (vertices[i].Vex == v)
			return i;
	return -1;

}
VertexType ALGraph::FirstNeighbor(const VertexType&v) {
	int k = Getpos(v);
	if (k >= 0)
		if (vertices[k].first)
			return vertices[k].first->Vex;
	return -1;
}

VertexType ALGraph::NextNeighbor(const VertexType&v, const VertexType&w) {
	int k = Getpos(v);
	if (k < 0) return -1;
	ArcNode* i = vertices[k].first;
	while (i && i->Vex != w)
		i = i->next;
	return i->next ? i->next->Vex : -1;
}

void ALGraph::BFSTraverse(const VertexType& v) {
	bool* visit = new bool[vexnum];
	for (int i = 0; i != vexnum; i++) visit[i] = false;

	int k = Getpos(v);
	if (!visit[k])
		BFS(v, visit);
	for (int i = 0; i != vexnum; i++)
		if (!visit[i])
			BFS(vertices[i].Vex, visit);

}
void ALGraph::BFS(VertexType v, bool*visit) {
	LQueue<VertexType> queue;
	queue.EnQueue(v);
	while (!queue.IsEmpty()) {
		queue.DeQueue(v);
		int k = Getpos(v);
		if (!visit[k]) {
			std::cout << v << " ";
			visit[k] = true;
		}
		for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t)) {
			int pos = Getpos(t);
			if (!visit[pos]) {
				std::cout << t << " ";
				visit[pos] = true;
				queue.EnQueue(t);
			}
		}
	}

}

void ALGraph::DFSTraverse(const VertexType& v) {
	bool* visit = new bool[vexnum];
	for (int i = 0; i != vexnum; i++) visit[i] = false;

	int k = Getpos(v);
	DFS(v, visit);

	for (int i = 0; i != vexnum; i++)
		if (!visit[i])
			DFS(vertices[i].Vex, visit);
}
void ALGraph::DFS(VertexType v, bool* visit) {
	int k = Getpos(v);
	if (!visit[k]) {
		std::cout << v << " ";
		visit[k] = true;
	}
	for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t)) {
		int k = Getpos(t);
		if (!visit[k])
			DFS(t, visit);
	}

}

void ALGraph::DFS_NR(VertexType t) {
	bool* visit = new bool[vexnum];
	for (int i = 0; i != vexnum; i++) visit[i] = false;
	LStack<VertexType> stack;
	VertexType v = t;
	stack.Push(v);
	while (!stack.IsEmpty()) {
		stack.Pop(v);            //与BFS类似，BFS入队时访问，DFS出栈时访问;并且只有未被访问的才入栈/队，出栈/队时直接访问
		int pos = Getpos(v);
		std::cout << v << " ";
		for (VertexType t = FirstNeighbor(v); t > 0; t = NextNeighbor(v, t))
			if (!visit[Getpos(t)])
				stack.Push(t), visit[Getpos(t)] = true;
	}
}

void ALGraph::FindPath(const VertexType&start, const VertexType&target) {
	bool* visit = new bool[vexnum];
	for (int i = 0; i != vexnum; i++) visit[i] = false;
	int distance = -1;
	VertexType* path = new VertexType[vexnum];
	std::cout << "All the single path from " << start << " to " << target << " : " << std::endl;
	find_path(start, target, path, visit, distance);
}

void ALGraph::find_path(const VertexType&start, const VertexType&target, VertexType* path, bool* visit, int distance) {
	path[++distance] = start;    //记录路径
	visit[Getpos(start)] = true;   
	if (start == target)
		ShowPath(path, distance);
	for (VertexType t = FirstNeighbor(start); t > 0; t = NextNeighbor(start, t))
		if (!visit[Getpos(t)])
			find_path(t, target, path, visit, distance);
	visit[Getpos(start)] = false;

}

void ALGraph::ShowPath(VertexType*path, int distance) {
	for (int i = 0; i != distance; i++)
		std::cout << path[i] << " -> ";
	std::cout << path[distance] << std::endl;
}