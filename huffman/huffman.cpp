//������������Ӧ��
//     2016��11��10��14:44:28

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

typedef struct {
	int weight;		//���Ȩֵ
	int parent, lchild, rchild;//˫�ס����ӡ��Һ��ӵ��±�
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;//��̬��������洢�����������


//��HT��ǰn���������Ȩֵ��С�����������±꣬�洢��s1,s2��
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

//�������������������ĿΪn
void createHuffmanTree(HuffmanTree &HT, int n,int *weight)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;//���������Ľ�����Ϊ2n - 1
	HT = new HTNode[m + 1];//���� m + 1 ����㣬��һ����㲻ʹ��
	for (int i = 1; i <= m; i++)//�����н���˫�ס����Һ����±��ʼ��Ϊ0
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (int i = 1; i <= n; i++)//����n��Ҷ�ӽ���Ȩֵ
	{
		HT[i].weight = weight[i];
	}

	//������������
	int s1, s2;
	for (int i = n + 1; i <= m; i++)
	{
		//�ڸý���ǰ����Ȩֵ��С�����������±�ֱ�洢��s1,s2��
		select(HT, i - 1, s1, s2);
		//���ҵ���Ȩֵ��С����������˫���±���Ϊi
		HT[s1].parent = i;
		HT[s2].parent = i;
		//��i�������Һ��ӷֱ���Ϊs1,s2
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i����ȨֵΪ���Һ���s1��s2��Ȩֵ֮��
	}
}

//��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢�ڱ����HC��
void createHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	HC = new char*[n + 1];
	char *cd = new char[n];
	cd[n - 1] = '\0';
	int start,par,m;
	for (int i = 1; i <= n; i++)
	{
		start = n - 1;
		m = i;//mΪ��ǰ����±�
		par = HT[m].parent;//parΪm��˫�׽���±�
		while (par != 0)
		{
			--start;
			if (HT[par].lchild == m)	//m��par������
				cd[start] = '0';	
			else                        //m��par���Һ���
				cd[start] = '1';
			m = par;
			par = HT[m].parent;
		}
		HC[i] = new char[n - start];
		strcpy(HC[i], &cd[start]);
	}
	delete cd;
}
//���룬���ù����������ԭ���ַ�������
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
//���룬���ù�����������������
void yiMa(HuffmanTree HT,int n,char *ziFu, string miMa, string &result)
{
	result.clear();
	int i;
	int len = miMa.length();
	int root;
	//�ҹ������ĸ��ڵ���±�
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
	����������
	��������8
	�ַ��Ͷ�Ӧ��Ȩֵ��a 5 b 29 c 7 d 8 e 14 f 23 g 3 h 11   �����Կ��Ը���ճ����
	���룺ceaghbd   ��Ӧ�ı���Ϊ��   111011000010000001101111
	*/
	char ch = 'y';
	int b;
	while (ch == 'y')
	{
		cout << endl << "\t\t1��������������" << endl;
		cout << "\t\t2����������������" << endl;
		cout << "\t\t3���������������" << endl;
		cout << "\t\t4���������������" << endl;
		cout << "\t\t5������" << endl;
		cout << "\t\t6������" << endl;
		cout << "\t\t0���˳�" << endl;
		cout << "�����룺" ;
		cin >> b;
		switch (b)
		{
		case 1://�����������
			cout << "������Ҷ��������";
			cin >> n;
			ziFu = new char[n + 1];
			weight = new int[n + 1];
			
			//�����ַ��Ͷ�Ӧ��Ȩֵ
			cout << "������ " << n << " ���ַ������Ӧ��Ȩֵ��" << endl;
			for (int i = 1; i <= n; i++)
				cin >> ziFu[i] >> weight[i];

			//������������
			createHuffmanTree(HT, n, weight);
			cout << "��������������" << endl;
			break;
		case 2:
			//��������������
			if (HT)
			{
				createHuffmanCode(HT, HC, n);
				cout << "���������빹�����" << endl;
			}
			else
				cout << "��������û�й������޷��������������룡" << endl;
			break;
		case 3:
			//�������������
			if (HT)
			{
				cout << "���\tȨֵ\t˫��\t��\t��" << endl;
				for (int i = 1; i <= 2 * n - 1; i++)
				{
					cout << i << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
				}
			}
			else
				cout << "��������δ�������޷��������������" << endl;
			break;
		case 4:
			//�������������
			if (HC)
				for (int i = 1; i <= n; i++)
					cout << ziFu[i] << " : " << HC[i] << endl;
			else
				cout << "����������δ�������޷�������������룡" << endl;
			break;
		case 5:
			//����
			if (HC)
			{
				int a;
				cout << "1��ʹ��6�����������б���\t2���ֶ�������Ҫ������ַ�����";
				cin >> a;
				if (a == 1)
					if (yiMa_result != "N")
						bianMaYuan = yiMa_result;
					else
					{
						cout << "6��������Ϊ�գ�" << endl;
						break;
					}
				else if (a == 2)
				{
					cout << "��������Ҫת��Ϊ������������ַ�����";
					cin >> bianMaYuan;
				}
				else
				{
					cout << "�������" << endl;
					break;
				}

				if (bianMa(HC, ziFu, bianMaYuan, bianMa_result) == 1)
					cout << bianMaYuan << " ��Ӧ�ı��� " << bianMa_result << endl;
				else
					cout << "ԭ���д�" << endl;
			}
			else
				cout << "����������δ�������޷����룡" << endl;
			break;
		case 6:
			//����
			if (HT)
			{
				int a;
				cout << "1��ʹ��5�ı����ַ��������������\t2���Լ���������ַ���:";
				cin >> a;
				if (a == 1)
					if(bianMa_result != "N")
						yiMaYuan = bianMa_result;
					else
					{
						cout << "5�ı�����Ϊ�գ�" << endl;
						break;
					}
				else if (a == 2)
					cin >> yiMaYuan;
				else
				{
					cout << "�������" << endl;
					break;
				}
				yiMa(HT, n, ziFu, yiMaYuan, yiMa_result);
				cout << yiMaYuan << "��Ӧ��ԭ�ַ���Ϊ �� " << yiMa_result << endl;
				break;
			}
			else
				cout << "��������Ϊ�������޷����룡" << endl;
			break;
		case 0:
			ch = 'n'; break;
		default:
			cout << "�������" << endl;
			break;
		}
	}
}