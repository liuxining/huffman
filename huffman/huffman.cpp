//哈夫曼树及其应用
//     2016年11月10日14:44:28

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

typedef struct {
	int weight;		//结点权值
	int parent, lchild, rchild;//双亲、左孩子、右孩子的下标
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;//动态分配数组存储哈夫曼编码表


//在HT的前n个结点中找权值最小的两个结点的下标，存储到s1,s2中
void select(HuffmanTree &HT, int n, int &s1, int &s2)
{
	/*
	s1 = 0;
	s2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			if (s1 == 0)
				s1 = i;
			else
				if (HT[i].weight < HT[s1].weight)
				{
					//		s2 = s1;
					s1 = i;
				}
		}
	}
	HT[s1].parent = 1;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			if (s2 == 0)
				s2 = i;
			else
				if (HT[i].weight < HT[s2].weight)
				{
					//		s2 = s1;
					s2 = i;
				}
		}
	}
	*/
	s1 = 0;
	s2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			if(s1 == 0)
				s1 = i;
			else if (s2 == 0)
			{
				s2 = i;
				if (HT[s1].weight > HT[s2].weight)
				{
					int p = s1;
					s1 = s2;
					s2 = p;
				}
			}
			else
			{
				if (HT[i].weight < HT[s2].weight)
					if (HT[i].weight < HT[s1].weight)
					{
						s2 = s1;
						s1 = i;
					}
					else
						s2 = i;
				
			}
		}
	}
}

//创建哈夫曼树，结点数目为n
void createHuffmanTree(HuffmanTree &HT, int n,int *weight)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;//哈夫曼树的结点个数为2n - 1
	HT = new HTNode[m + 1];//构造 m + 1 个结点，第一个结点不使用
	for (int i = 1; i <= m; i++)//将所有结点的双亲、左右孩子下标初始化为0
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (int i = 1; i <= n; i++)//输入n个叶子结点的权值
	{
		HT[i].weight = weight[i];
	}

	//构建哈夫曼树
	int s1, s2;
	for (int i = n + 1; i <= m; i++)
	{
		//在该结点的前面找权值最小的两个结点的下标分别存储到s1,s2中
		select(HT, i - 1, s1, s2);
		//将找到的权值最小的两个结点的双亲下标置为i
		HT[s1].parent = i;
		HT[s2].parent = i;
		//将i结点的左右孩子分别置为s1,s2
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i结点的权值为左右孩子s1、s2的权值之和
	}
}

//从叶子到根逆向求每个字符的哈夫曼编码，存储在编码表HC中
void createHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	HC = new char*[n + 1];
	char *cd = new char[n];
	cd[n - 1] = '\0';
	int start,par,m;
	for (int i = 1; i <= n; i++)
	{
		start = n - 1;
		m = i;//m为当前结点下标
		par = HT[m].parent;//par为m的双亲结点下标
		while (par != 0)
		{
			--start;
			if (HT[par].lchild == m)	//m是par的左孩子
				cd[start] = '0';	
			else                        //m是par的右孩子
				cd[start] = '1';
			m = par;
			par = HT[m].parent;
		}
		HC[i] = new char[n - start];
		strcpy(HC[i], &cd[start]);
	}
	delete cd;
}
//编码，利用哈夫曼编码给原码字符串编码
int bianMa(HuffmanCode HC, char *ziFu,string yuanMa,string &result)
{
	result.clear();
	int len = yuanMa.length();
	bool flag;
	for (int i = 0; i < len; i++)
	{
		flag = false;
		int j;
		for (j = 1; ziFu[j] != '\0'; j++)
			if (ziFu[j] == yuanMa[i])
			{
				flag = true;
				break;
			}
		if (!flag)
		{
			
			return 0;
		}
		result.append(HC[j]);
	}
	return 1;
}
//译码，利用哈夫曼树对密码译码
void yiMa(HuffmanTree HT,int n,char *ziFu, string miMa, string &result)
{
	result.clear();
	int i;
	int len = miMa.length();
	int root;
	//找哈夫曼的根节点的下标
	for (i = n + 1; i <= 2 * n - 1; i++)
	{
		if (HT[i].parent == 0)
		{
			root = i;
		}
	}
	i = 0;
	int p = root;
	while (true)
	{
		if (HT[p].lchild == 0 && HT[p].rchild == 0)
		{
			result.append(1,ziFu[p]);
			p = root;
		}
		if (i >= len)
			break;
		if (miMa[i++] == '0')
			p = HT[p].lchild;
		else
			p = HT[p].rchild;
	}
}

void main()
{
	HuffmanTree HT = NULL;
	int n;
	char *ziFu = NULL;
	int *weight = NULL;
	HuffmanCode HC = NULL;
	string bianMaYuan, bianMa_result = "N";
	string yiMa_result = "N";
	string yiMaYuan;
	/*
	测试用例：
	结点个数：8
	字符和对应否权值：a 5 b 29 c 7 d 8 e 14 f 23 g 3 h 11   （调试可以复制粘贴）
	编码：ceaghbd   对应的编码为：   111011000010000001101111
	*/
	char ch = 'y';
	int b;
	while (ch == 'y')
	{
		cout << endl << "\t\t1、构建哈夫曼树" << endl;
		cout << "\t\t2、构建哈夫曼编码" << endl;
		cout << "\t\t3、输出哈夫曼树表" << endl;
		cout << "\t\t4、输出哈夫曼编码" << endl;
		cout << "\t\t5、编码" << endl;
		cout << "\t\t6、译码" << endl;
		cout << "\t\t0、退出" << endl;
		cout << "请输入：" ;
		cin >> b;
		switch (b)
		{
		case 1://构造哈夫曼树
			cout << "请输入叶结点个数：";
			cin >> n;
			ziFu = new char[n + 1];
			weight = new int[n + 1];
			
			//输入字符和对应的权值
			cout << "请输入 " << n << " 个字符和其对应的权值：" << endl;
			for (int i = 1; i <= n; i++)
				cin >> ziFu[i] >> weight[i];

			//构建哈夫曼树
			createHuffmanTree(HT, n, weight);
			cout << "构造哈夫曼树完成" << endl;
			break;
		case 2:
			//构建哈夫曼编码
			if (HT)
			{
				createHuffmanCode(HT, HC, n);
				cout << "哈夫曼编码构建完成" << endl;
			}
			else
				cout << "哈夫曼树没有构建，无法构建哈夫曼编码！" << endl;
			break;
		case 3:
			//输出哈夫曼树表
			if (HT)
			{
				cout << "序号\t权值\t双亲\t左\t右" << endl;
				for (int i = 1; i <= 2 * n - 1; i++)
				{
					cout << i << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
				}
			}
			else
				cout << "哈夫曼树未构建，无法输出哈夫曼树表！" << endl;
			break;
		case 4:
			//输出哈夫曼编码
			if (HC)
				for (int i = 1; i <= n; i++)
					cout << ziFu[i] << " : " << HC[i] << endl;
			else
				cout << "哈夫曼编码未构建，无法输出哈夫曼编码！" << endl;
			break;
		case 5:
			//编码
			if (HC)
			{
				int a;
				cout << "1、使用6的译码结果进行编码\t2、手动输入需要编码的字符串：";
				cin >> a;
				if (a == 1)
					if (yiMa_result != "N")
						bianMaYuan = yiMa_result;
					else
					{
						cout << "6的译码结果为空！" << endl;
						break;
					}
				else if (a == 2)
				{
					cout << "请输入需要转换为哈夫曼编码的字符串：";
					cin >> bianMaYuan;
				}
				else
				{
					cout << "输入错误！" << endl;
					break;
				}

				if (bianMa(HC, ziFu, bianMaYuan, bianMa_result) == 1)
					cout << bianMaYuan << " 对应的编码 " << bianMa_result << endl;
				else
					cout << "原码有错！" << endl;
			}
			else
				cout << "哈夫曼编码未构建，无法编码！" << endl;
			break;
		case 6:
			//译码
			if (HT)
			{
				int a;
				cout << "1、使用5的编码字符串结果进行译码\t2、自己输入编码字符串:";
				cin >> a;
				if (a == 1)
					if(bianMa_result != "N")
						yiMaYuan = bianMa_result;
					else
					{
						cout << "5的编码结果为空！" << endl;
						break;
					}
				else if (a == 2)
					cin >> yiMaYuan;
				else
				{
					cout << "输入错误" << endl;
					break;
				}
				yiMa(HT, n, ziFu, yiMaYuan, yiMa_result);
				cout << yiMaYuan << "对应的原字符串为 ： " << yiMa_result << endl;
				break;
			}
			else
				cout << "哈夫曼树为构建，无法译码！" << endl;
			break;
		case 0:
			ch = 'n'; break;
		default:
			cout << "输入错误！" << endl;
			break;
		}
	}
}