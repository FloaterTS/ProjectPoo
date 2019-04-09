#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

int max(int a, int b)
{
	return (a < b) ? b : a;
}


class Nod
{

protected:
	int info;
	Nod *st;
	Nod *dr;

public:
	Nod(int x = 0) : info(x), st(NULL), dr(NULL) {}
	Nod(const Nod &n2) : info(n2.info), st(n2.st), dr(n2.dr) {}
	virtual ~Nod() { info = 0; st = NULL; dr = NULL; }

	friend class Arbore;
	friend class ABC;

	friend istream &operator >> (istream &is, ABC &abc);
	friend ostream &operator << (ostream &os, const ABC &abc);
};

class Nod_rosu_negru : Nod
{

private:
	char culoare[6];
	Nod_rosu_negru *st_rn;
	Nod_rosu_negru *dr_rn;

public:
	Nod_rosu_negru(const char cul[], int x = 0) : Nod(x), st_rn(NULL), dr_rn(NULL) { strcpy(culoare, cul); }
	Nod_rosu_negru(const Nod_rosu_negru &nrn2) : Nod(nrn2), st_rn(nrn2.st_rn), dr_rn(nrn2.dr_rn) { strcpy(culoare, nrn2.culoare); }
	~Nod_rosu_negru() { delete[] culoare; st_rn = NULL; dr_rn = NULL; }

	friend class Arbore_bicolor;
};


class Arbore
{

protected:
	int nr_noduri;

public:
	Arbore(int nr = 0) : nr_noduri(nr) {}
	Arbore(const Arbore &a2) : nr_noduri(a2.nr_noduri) {}
	virtual ~Arbore() { nr_noduri = 0; }

	virtual int height() = 0;

};


class ABC : Arbore
{

private:
	Nod *rad;

public:
	ABC() : Arbore(), rad(NULL) {}
	ABC(int x) : Arbore(1) { rad = new Nod(x); }

	~ABC()
	{
		destroy(rad);
		rad = NULL;
	}
	void destroy(Nod *n)
	{
		if (n == NULL)
			return;
		destroy(n->st);
		destroy(n->dr);
		delete n;
	}

	Nod *copy(Nod *n, const Nod *n2)
	{
		if (n2 == NULL)
			return NULL;
		if (n == NULL)
			n = new Nod();
		n->info = n2->info;
		n->st = copy(n->st, n2->st);
		n->dr = copy(n->dr, n2->dr);
		return n;
	}

	void add(int x, Nod *n)
	{
		if (x < n->info)
			if (n->st == NULL)
			{
				Nod *p = new Nod(x);
				n->st = p;
			}
			else
				add(x, n->st);
		else if (x > n->info)
			if (n->dr == NULL)
			{
				Nod *p = new Nod(x);
				n->dr = p;
			}
			else
				add(x, n->dr);
		else if (x == n->info)
			cout << "Nod deja prezent";
	}
	void srd(const Nod *n)
	{
		if (n == NULL)
			return;
		srd(n->st);
		cout << n->info << " ";
		srd(n->dr);
	}

	int height() { return heightHelp(rad); }
	int heightHelp(Nod *n)
	{
		if (n == NULL)
			return 0;

		return 1 + max(heightHelp(n->st), heightHelp(n->dr));
	}

	bool Null() { return rad == NULL ? true : false; }

	void operator = (const ABC &abc) { rad = copy(rad, abc.rad); }
	friend istream &operator >> (istream &is, ABC &abc);
	friend ostream &operator << (ostream &os, ABC &abc);
};

class Arbore_bicolor : Arbore
{

private:
	Nod_rosu_negru *rad;

public:

	Arbore_bicolor() : Arbore(), rad(NULL) {}
	Arbore_bicolor(int x) : Arbore(1) { rad = new Nod_rosu_negru("negru", x); }

	int height() { return log2(negre(rad)); }
	int negre(Nod_rosu_negru *nrn)
	{
		if (nrn == NULL)
			return 0;
		int ng = 0;

		if (strcpy(nrn->culoare, "negru") == 0)
			ng = 1;

		ng = +negre(nrn->st_rn);
		ng = +negre(nrn->dr_rn);

		return ng;
	}

	bool Null() { rad == NULL ? true : false; }
};


istream &operator >> (istream &is, ABC &abc)
{
	int x;
	char t;
	Nod *n;

	if (abc.rad != NULL)
		delete &abc;

	cout << "Cititi pana la introducerea lui 0: ";
	is >> x;
	if (!x)
		return is;
	abc.rad = new Nod(x);

	is >> x;
	while (x)
	{
		abc.add(x, abc.rad);
		cin >> x;
	}

	return is;
}

ostream &operator << (ostream &os, ABC &abc)
{
	if (abc.rad == NULL)
	{
		cout << "Arborele este nul.";
		return os;
	}

	cout << "Arborele afisat in ordine: \n";
	abc.srd(abc.rad);
	cout << endl;

	return os;
}


int main()
{
	int t, nr, nr2;
	ABC abc[10];

	do
	{
		cout << "1. Citire arbore binar de cautare\n";
		cout << "2. Afisare arbore binar de cautare\n";
		cout << "3. Copiere arbore binar de cautare\n";
		cout << "0. Exit\n";
		cin >> t;
		switch (t)
		{
		case 1:
		{
			cout << "Nr arborelui (0-9): ";
			cin >> nr;
			cin >> abc[nr];
		}
		break;
		case 2:
		{
			cout << "Nr arborelui (0-9): ";
			cin >> nr;
			if (!abc[nr].Null())
				cout << abc[nr];
			else
				cout << "Nu a fost citit inca\n";
		}
		break;
		case 3:
		{
			cout << "Nr arborelui destinatie (0-9): ";
			cin >> nr;
			cout << "Nr arborelui copiat (0-9): ";
			cin >> nr2;
			if (!abc[nr2].Null())
			{
				abc[nr] = abc[nr2];
				cout << "Arborele a fost copiat\n";
			}
			else
				cout << "Nu a fost citit inca\n";
		}
		break;
		case 0:
			break;
		default: cout << "Optiune invalida\n";
			break;
		}
		cout << "\n";
	} while (t);
	return 0;
}