#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class GrafOr
{
private:

	int n, m;

	vector <vector <int>> vfAdiac;

public:

	GrafOr();
	GrafOr(int x) { this->reSetGrOr(x); };

	int getN() { return this->n; };
	int getM() { return this->m; };

	int **getMat();

	void addNod();
	void bfs(int x);
	void dfs(int x);
	void reSetGrOr(int x);
	void addDrum(int x, int y);
	void dfsUtil(int x, bool viz[]);

	bool isTareConex();
	bool drumFromTo(int x, int y);

	vector <int> getDrumuri(int i) { return vfAdiac[i]; };
	vector <vector <int>> compTareConexe();

	///friend istream &operator >> (istream &is, GrafOr &grO);
	///friend ostream &operator << (ostream &os, GrafOr &grO);
	///friend GrafOr &operator + (GrafOr &grO1, GrafOr &grO2);
};

GrafOr::GrafOr()
{
	this->n = 0;
	this->m = 0;

	vector <int> v;
	vfAdiac.push_back(v);
}

int **GrafOr::getMat()
{
	int **matAdiac;
	matAdiac = new int*[this->n + 1];

	for (int i = 1; i <= this->n; i++)
	{
		matAdiac[i] = new int[this->n + 1];

		for (int j = 1; j <= this->n + 1; j++)
			matAdiac[i][j] = 0;

		for (int j = 0; j < vfAdiac[i].size(); j++)
			matAdiac[i][vfAdiac[i][j]] = 1;
	}
	return matAdiac;
}

void GrafOr::addNod()
{
	this->n++;

	vector <int> v;
	vfAdiac.push_back(v);
}

void GrafOr::bfs(int x)
{
	cout << "BFS din nodul nr " << x << ": ";

	bool *viz = new bool[this->n + 1];
	for (int i = 1; i <= this->n; i++)
		viz[i] = 0;

	viz[x] = 1;
	queue <int> qu;
	qu.push(x);

	while (!qu.empty())
	{
		x = qu.front();
		cout << x << " ";
		qu.pop();

		for (int i = 0; i < vfAdiac[x].size(); i++)
			if (!viz[vfAdiac[x][i]])
			{
				viz[vfAdiac[x][i]] = 1;
				qu.push(vfAdiac[x][i]);
			}
	}
	cout << endl;
}

void GrafOr::dfs(int x)
{
	bool *viz = new bool[this->n + 1];
	for (int i = 1; i <= this->n; i++)
		viz[i] = 0;

	cout << "DFS din nodul nr " << x << ": ";
	dfsUtil(x, viz);
	cout << endl;
}

void GrafOr::reSetGrOr(int x)
{
	this->n = x;
	this->m = 0;

	for (int i = 0; i < vfAdiac.size(); i++)
		vfAdiac[i].clear();
	vfAdiac.clear();

	vector <int> v;
	for (int i = 0; i <= x; i++)
		vfAdiac.push_back(v);
};

void GrafOr::addDrum(int x, int y)
{
	if (x > this->n || y > this->n || x == y)
	{
		cout << "\nEroare la adaugarea drumului\n";
		return;
	}
	for (int i = 0; i < this->vfAdiac[x].size(); i++)
		if (this->vfAdiac[x][i] == y)
			return;

	this->m++;
	this->vfAdiac[x].push_back(y);
}

void GrafOr::dfsUtil(int x, bool viz[])
{
	viz[x] = 1;
	cout << x << " ";

	for (int i = 0; i < vfAdiac[x].size(); i++)
		if (!viz[vfAdiac[x][i]])
			dfsUtil(vfAdiac[x][i], viz);
}

bool GrafOr::isTareConex()
{
	if (compTareConexe().size() == 1)
		return true;
	else
		return false;
}

bool GrafOr::drumFromTo(int x, int y)
{
	if (x == y)
		return false;

	bool *viz = new bool[this->n];
	for (int i = 1; i <= this->n; i++)
		viz[i] = 0;

	viz[x] = 1;
	queue <int> qu;
	qu.push(x);

	while (!qu.empty())
	{
		x = qu.front();
		qu.pop();

		for (int i = 0; i < vfAdiac[x].size(); i++)
			if (!viz[vfAdiac[x][i]])
			{
				if (vfAdiac[x][i] == y)
					return true;
				viz[vfAdiac[x][i]] = 1;
				qu.push(vfAdiac[x][i]);
			}
	}
	return false;
}

vector <vector <int>> GrafOr::compTareConexe()
{
	bool *check = new bool[this->n + 1];

	vector <vector <int>> comp;
	vector <int> v;

	for (int i = 1; i <= n; i++)
		check[i] = 0;

	int checking = 1;
	int numC = 0;

	while (checking)
	{
		comp.push_back(v);
		comp[numC].push_back(checking);
		check[checking] = 1;
		for (int i = 1; i <= this->n; i++)
		{
			if (!check[i] && drumFromTo(checking, i) && drumFromTo(i, checking))
			{
				comp[numC].push_back(i);
				check[i] = 1;
			}
		}
		checking = 0;
		for (int i = 1; i <= this->n; i++)
		{
			if (check[i] == 0)
			{
				checking = i;
				break;
			}
		}
		numC++;
	}

	return comp;
}

istream &operator >> (istream &is, GrafOr &grO)
{
	int n, m, x, y;

	is >> n >> m;

	grO.reSetGrOr(n);

	for (int i = 0; i < m; i++)
	{
		is >> x >> y;
		grO.addDrum(x, y);
	}
	return is;
}

ostream &operator << (ostream &os, GrafOr &grO)
{
	os << grO.getN() << " noduri si " << grO.getM() << " muchii\n";

	for (int i = 1; i <= grO.getN(); i++)
	{
		os << "nodul " << i << " are drum catre: ";

		for (int j = 0; j < grO.getDrumuri(i).size(); j++)
			os << grO.getDrumuri(i)[j] << " ";

		os << "\n";
	}
	return os;
}

GrafOr operator + (GrafOr &grO1, GrafOr &grO2)
{
	GrafOr rez(max(grO1.getN(), grO2.getN()));

	for (int i = 1; i <= grO1.getN(); i++)
		for (int j = 0; j < grO1.getDrumuri(i).size(); j++)
			rez.addDrum(i, grO1.getDrumuri(i)[j]);

	for (int i = 1; i <= grO2.getN(); i++)
		for (int j = 0; j < grO2.getDrumuri(i).size(); j++)
			rez.addDrum(i, grO2.getDrumuri(i)[j]);

	return rez;
}

int main()
{
	int t = 1, x;
	ifstream f("date.txt");
	GrafOr graf;
	cout << "Cititi graful (nr noduri, nr muchii, legaturi intre noduri):\n";
	cin >> graf;
	//f >> graf;
	cout << "Graf citit.\n\n";
	while (t)
	{
		cout << "1. Afisare graf\n2. DFS\n3. BFS\n";
		cout << "4. Matrice de adiacenta\n5. Componente tare conexe\n";
		cout << "6. Graf tare conex?\n7. Adunare cu alt graf + afisare\n";
		cout << "8. Adaugare nod\n9. Adaugare arc\n0. Exit\n";
		cin >> t;
		switch (t)
		{
		case 1:
		{
			cout << graf;
		}
		break;
		case 2:
		{
			cout << "Nodul din care sa inceapa: ";
			cin >> x;
			if (x > 0 && x <= graf.getN())
				graf.dfs(x);
		}
		break;
		case 3:
		{
			cout << "Nodul din care sa inceapa: ";
			cin >> x;
			if (x > 0 && x <= graf.getN())
				graf.bfs(x);
		}
		break;
		case 4:
		{
			int **mat = graf.getMat();
			for (int i = 1; i <= graf.getN(); i++)
			{
				for (int j = 1; j <= graf.getN(); j++)
					cout << mat[i][j] << " ";
				cout << endl;
			}
		}
		break;
		case 5:
		{
			vector <vector <int>> ctc = graf.compTareConexe();
			for (int i = 0; i < ctc.size(); i++)
			{
				cout << "Componenta nr " << i+1 << ": ";
				for (int j = 0; j < ctc[i].size(); j++)
					cout << ctc[i][j] << " ";
				cout << endl;
			}
		}
		break;
		case 6:
		{
			if (graf.isTareConex())
				cout << "Graful este tare conex.\n";
			else
				cout << "Graful nu este tare conex\n";
		}
		break;
		case 7:
		{
			GrafOr graf2;
			cout << "Cititi graful 2:\n";
			cin >> graf2;
			//f >> graf2;
			GrafOr graf3 = graf + graf2;
			cout << "Graful 1 + Graful 2 = \n";
			cout << graf3;
		}
		break;
		case 8:
		{
			graf.addNod();
			x = graf.getN();
			cout << "Nodul nr " << x << " a fost adaugat.\n";
		}
		break;
		case 9:
		{
			int y;
			cout << "Nodul sursa si nodul destinatie: ";
			cin >> x >> y;
			graf.addDrum(x, y);
			cout << "Arcul a fost adaugat.\n";
		}
		break;
		case 0:
			break;
		default: cout << "Optiune invalida.\n";
			break;
		}
		cout << endl;
	}
	f.close();
	return 0;
}