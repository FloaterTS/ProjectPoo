#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Masina
{
protected:
	int nr_usi, pret, viteza;
	char model[20];

public:
	Masina()
	{
		strcpy(model, "Empty");
		nr_usi = 0;
		pret = 0;
		viteza = 0;
	};
	Masina(const char mdl[20], int usi, int pr, int vit) : nr_usi(usi), pret(pr), viteza(vit) { strcpy(model, mdl); };
	Masina(const Masina& m) : nr_usi(m.nr_usi), pret(m.pret), viteza(m.viteza) { strcpy(this->model, m.model); };
	virtual ~Masina() {};

	virtual const char* Clasa() { return "Stock"; }
	virtual bool Decap() { return false; };

	void operator = (const Masina& m)
	{
		this->nr_usi = m.nr_usi;
		this->pret = m.pret;
		this->viteza = m.viteza;
		strcpy(this->model, m.model);
	};

	friend istream& operator >> (istream& is, Masina& m);
	friend ostream& operator << (ostream& os, Masina& m);
	friend void Afis(Masina* m);
};

class Coupe : public Masina
{
private:
	static const char clasa[20];

public:
	Coupe() : Masina() {};
	Coupe(const char mdl[20], int usi, int pr, int vit) : Masina(mdl, usi, pr, vit) {};
	Coupe(const Coupe& c) : Masina(c) {};
	~Coupe() {};

	const char* Clasa() { return Coupe::clasa; }
};

class Hot_Hatch : public Masina
{
private:
	static const char clasa[20];

public:
	Hot_Hatch() : Masina() {};
	Hot_Hatch(const char mdl[20], int usi, int pr, int vit) : Masina(mdl, usi, pr, vit) {};
	Hot_Hatch(const Hot_Hatch& c) : Masina(c) {};
	~Hot_Hatch() {};

	const char* Clasa() { return Hot_Hatch::clasa; }
};

class Cabrio : public Masina
{
private:
	static const char clasa[20];
	char mat_acop[20];

public:
	Cabrio() : Masina() { strcpy(mat_acop, "metalic"); };
	Cabrio(const char mdl[20], int usi, int pr, int vit, const char acop[20] = "metalic") : Masina(mdl, usi, pr, vit) { strcpy(mat_acop, acop); };
	Cabrio(const Cabrio& c) : Masina(c) { strcpy(this->mat_acop, c.mat_acop); };
	~Cabrio() {};

	const char* Clasa() { return Cabrio::clasa; }
	bool Decap() { return true; };
};

class Supersport : public Masina
{
private:
	static const char clasa[20];

public:
	static char expuse, vandute;

	Supersport() : Masina() {};
	Supersport(const char mdl[20], int usi, int pr, int vit) : Masina(mdl, usi, pr, vit) {};
	Supersport(const Supersport& c) : Masina(c) {};
	~Supersport() {};

	const char* Clasa() { return Supersport::clasa; }

	void operator -= (int nr_vandute)
	{
		Supersport::expuse -= nr_vandute;
		Supersport::vandute += nr_vandute;
	}
};

const char Coupe::clasa[] = "Coupe";
const char Hot_Hatch::clasa[] = "Hot-Hatch";
const char Cabrio::clasa[] = "Cabrio";
const char Supersport::clasa[] = "Supersport";
char Supersport::expuse = 0;
char Supersport::vandute = 0;

istream& operator >> (istream& is, Masina& m)
{
	cout << "Model: ";
	is >> m.model;
	cout << "Nr usi: ";
	is >> m.nr_usi;
	cout << "Pret: ";
	is >> m.pret;
	cout << "Viteza maxima(kmph): ";
	is >> m.viteza;
	cout << endl;
	return is;
}

ostream& operator << (ostream& os, Masina& m)
{
	os << "Clasa: " << m.Clasa() << "\nModel: " << m.model << "\nNr usi: " << m.nr_usi;
	os << "\nPret: " << m.pret << "\nViteza maxima(kmph): " << m.viteza << "\nDecapotabila: ";
	if (m.Decap())
		os << "Da";
	else
		os << "Nu";
	os << endl;
	return os;
}

template <class T>
class Expozitie
{
private:
	vector<T*> masini;

public:
	int nr_total_masini;

	Expozitie() { nr_total_masini = 0; };
	~Expozitie()
	{
		while (!masini.empty())
			masini.pop_back();
	};

	void add(T& toAdd);
	void show();

	Supersport* sell(int toSell);
};

template <class T> void Expozitie<T>::add(T& toAdd)
{
	masini.push_back(&toAdd);
	cout << *(masini.back()) << endl;
	nr_total_masini++;
}

void Afis(Masina* m)
{
	cout << "Clasa: " << m->Clasa() << "\nModel: " << m->model << "\nNr usi: " << m->nr_usi;
	cout << "\nPret: " << m->pret << "\nViteza maxima(kmph): " << m->viteza << "\nDecapotabila: ";
	if (m->Decap())
		cout << "Da";
	else
		cout << "Nu";
	cout << endl;
}

template <class T> void Expozitie<T>::show()
{
	cout << "\nNr masini expuse: " << nr_total_masini << endl << endl;
	for (int i = 0; i < nr_total_masini; i++)
	{
		cout << "Masina nr " << i + 1 << ":\n";
		//cout << *(masini[i]);
		Afis(masini[i]);
		cout << endl;
	}
}

template <class T> Supersport* Expozitie<T>::sell(int toSell)
{
	/*try {
		if (strcmp(masini[toSell - 1]->Clasa(), "Supersport"))
			throw(masini[toSell - 1]);
	}
	catch (Masina * m) {
		cout << "Pot fi vandute doar masini supersport.\n";
		return NULL;
	}*/
	Supersport* aux = (Supersport*)masini[toSell - 1];
	masini[toSell - 1] = masini[nr_total_masini - 1];
	masini[nr_total_masini - 1] = aux;
	masini.pop_back();
	nr_total_masini--;

	*(aux) -= 1;
	return (Supersport*)aux;
}

int main()
{
	int t;
	Expozitie<Masina> exp;
	vector<Supersport*> stoc, vandute;

	do
	{
		cout << "1. Adaugare masina in expozitie\n";
		cout << "2. Vizualizare expozitie\n";
		cout << "3. Vanzare masina supersport\n";
		cout << "4. Vector supersport stoc/vandute\n";
		cout << "0. Exit\n";
		cin >> t;
		switch (t)
		{
		case 1:
		{
			int cl;
			cout << "Clasa masinii?\n";
			cout << "1. Coupe\n2. Hot-Hatch\n3. Cabrio\n4. Supersport\n";
			cin >> cl;
			switch (cl)
			{
			case 1:
			{
				Coupe co;
				cin >> co;
				exp.add(co);
				//Masina* m = &co;
				//cout << *m;
				//Afis(m);
			}
			break;
			case 2:
			{
				Hot_Hatch h;
				cin >> h;
				exp.add(h);
			}
			break;
			case 3:
			{
				Cabrio ca;
				cin >> ca;
				exp.add(ca);
			}
			break;
			case 4:
			{
				Supersport s;
				cin >> s;
				exp.add(s);
				stoc.push_back(&s);
				Supersport::expuse++;
			}
			break;
			default: "Optiune invalida.";
				break;
			}
		}
		break;
		case 2:
			exp.show();
			break;
		case 3:
		{
			int nrv;
			cout << "Nr masinii vandute: ";
			cin >> nrv;
			try {
				if (nrv < 1 || nrv > exp.nr_total_masini)
					throw(nrv);
			}
			catch (int nr) {
				cout << "Nr invalid\n\n";
				break;
			}
			Supersport* s = exp.sell(nrv);
			if (s != NULL)
				vandute.push_back(s);
			for (int i = 0; i < stoc.size(); i++)
				if (vandute.back() == stoc[i])
				{
					stoc[i] = stoc[stoc.size() - 1];
					stoc.pop_back();
					break;
				}
		}
		break;
		case 4:
		{
			cout << "Nr masini supersport in stoc: " << (int)Supersport::expuse << endl;
			for (int i = 0; i < stoc.size(); i++)
				cout << *(stoc[i]) << endl;
			cout << "\nNr masini supersport vandute: " << (int)Supersport::vandute << endl;
			for (int i = 0; i < vandute.size(); i++)
				cout << *(vandute[i]) << endl;
			cout << endl;
		}
		break;
		case 0:
			break;
		default: "Optiune invalida.\n";
			break;
		}

	} while (t);


	return 0;
}

