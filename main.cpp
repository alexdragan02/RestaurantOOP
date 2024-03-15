#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Ingredient {
private:
	char* denumire;
	float cantitate;
	string unitateMasura;
public:
	Ingredient() {
	
	}

	Ingredient(const char* denumire, float cantitate, string unitateMasura) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->cantitate = cantitate;
		this->unitateMasura = unitateMasura;

	}

	Ingredient(const Ingredient& i) {
		this->denumire = new char[strlen(i.denumire) + 1];
		strcpy(this->denumire, i.denumire);
		this->cantitate = i.cantitate;
		this->unitateMasura = i.unitateMasura;
	}
	~Ingredient() {
		delete[] this->denumire;
	}

	const char* getDenumire(){
		return denumire;
	}
	void setDenumire(const char* denumNoua) {
		if (denumNoua != nullptr) {
			delete[]denumire;
			denumire = new char[strlen(denumNoua) + 1];
			strcpy(denumire, denumNoua);	
		}
	}
	void setCantitate(float cantitate) {
		this->cantitate = cantitate;
	}
	float getCantitate() {
		return cantitate;
	}
	void setUnitateMasura(string unitateMasura) {
		this->unitateMasura = unitateMasura;
	}
	string getUnitateMasura() {
		return unitateMasura;
	}

	void afisare() {
		cout << "Denumire ingredient:  " << denumire << ", Cantitate:  " << cantitate << ", Unitate de masura: " << unitateMasura<<endl;

	}
	
	void cantitateMeniuri(string tipMeniu) {
		if (tipMeniu == "mare") {
			cantitate += 100;
		}
		else if(tipMeniu=="mic") {
			cantitate -= 100;
		}
	}
	
	friend ostream& operator<<(ostream& os, const Ingredient& ingredient) {
		os << "Denumire ingredient: " << ingredient.denumire
			<< ", Cantitate: " << ingredient.cantitate
			<< ", Unitate de masura: " << ingredient.unitateMasura;
		return os;
	}

	friend istream& operator>>(istream& is, Ingredient& ingredient) {
		cout << "Introduceti denumirea: ";
		char denum[256];
		is >> denum;
		ingredient.setDenumire(denum);
		cout << "Introduceti cantitatea: ";
		is >> ingredient.cantitate;
		cout << "Introduceti unitatea de masura: ";
		is >> ingredient.unitateMasura;

		return is;
	}
};
enum Alergeni {
	Gluten, Lactoza, Arahide, FructeDeMare, Nuci
};

class Preparate {
private:
	string nume;
	float pret;
	Ingredient** ingrediente=NULL;
	int numarIngrediente;
	const int idPreparat;
	Alergeni alergeni;
public:
	Preparate():idPreparat(0) {
		nume = ""; 
		pret = 0.0;
		ingrediente = NULL; 
		numarIngrediente = 0;
	}

	
	Preparate(const string& nume, float pret, Ingredient** ingrediente, int numarIngrediente, Alergeni alergeni, int id):idPreparat(id) 
	{
		this->nume = nume;
		this->pret = pret;
		this->ingrediente = new Ingredient * [numarIngrediente];
		for (int i = 0; i < numarIngrediente; ++i) {
			this->ingrediente[i] = new Ingredient(*ingrediente[i]);
		}
		this->numarIngrediente = numarIngrediente;
		this->alergeni = alergeni;
	}

	
	Preparate(const Preparate& p):idPreparat(p.idPreparat){
		nume = p.nume;
		pret = p.pret;
		alergeni = p.alergeni;
		numarIngrediente = p.numarIngrediente;
		ingrediente = new Ingredient*[numarIngrediente];
		for (int i = 0; i < numarIngrediente; ++i) {
			ingrediente[i] = new Ingredient(*p.ingrediente[i]);
		}
	}
	Preparate& operator=(const Preparate& altPreparat) {
		if (this != &altPreparat) {
			nume = altPreparat.nume;
			pret = altPreparat.pret;
			alergeni = altPreparat.alergeni;
			for (int i = 0; i < numarIngrediente; ++i) {
				delete ingrediente[i];
			}
			delete[] ingrediente;
			numarIngrediente = altPreparat.numarIngrediente;
			ingrediente = new Ingredient*[numarIngrediente];
			for (int i = 0; i < numarIngrediente; ++i) {
				ingrediente[i] = new Ingredient(*altPreparat.ingrediente[i]);
			}
		}
		return *this;
	}
	~Preparate() {
		for (int i = 0; i < numarIngrediente; i++) {
			delete ingrediente[i];
		}
		delete[] ingrediente;
	}
	string getNume() const {
		return nume;
	}

	void setNume(const string& newNume) {
		nume = newNume;
	}

	float getPret() const {
		return pret;
	}

	void setPret(float newPret) {
		pret = newPret;
	}

	Ingredient** getIngrediente() const {
		return ingrediente;
	}

	void setIngrediente(Ingredient** newIngrediente, int newNumarIngrediente) {
		for (int i = 0; i < numarIngrediente; ++i) {
			delete ingrediente[i];
		}
		delete[] ingrediente;
		numarIngrediente = newNumarIngrediente;
		ingrediente = new Ingredient * [numarIngrediente];
		for (int i = 0; i < numarIngrediente; ++i) {
			ingrediente[i] = new Ingredient(*newIngrediente[i]);
		}
	}
	int getNumarIngrediente() const {
		return numarIngrediente;
	}
	int getIdPreparat() const {
		return idPreparat;
	}
	Alergeni getAlergeni() const {
		return alergeni;
	}
	void setAlergeni(Alergeni newAlergeni) {
		alergeni = newAlergeni;
	}
	
	void adaugaIngredient(Ingredient* ingredientNou) {
		Ingredient** ingredienteNoi = new Ingredient * [numarIngrediente + 1];
		for (int i = 0; i < numarIngrediente; ++i) {
			ingredienteNoi[i] = ingrediente[i];
		}
		ingredienteNoi[numarIngrediente] = ingredientNou;

		delete[] ingrediente;
		ingrediente = ingredienteNoi;
		numarIngrediente++;
	}

	friend ostream& operator<<(ostream& out, const Preparate& preparat) {
		out << "Nume: " << preparat.getNume() << "\n";
		out << "Pret: " << preparat.getPret() << "\n";
		out << "Numar Ingrediente: " << preparat.getNumarIngrediente() << "\n";
		out << "Ingrediente: ";
		for (int i = 0; i < preparat.getNumarIngrediente(); ++i) {
			if (i > 0) out << ", ";
			out << *(preparat.getIngrediente()[i]); 
		}
		out << "\n";
		return out;
	}
};
class Comanda {
private:
	vector<Preparate> preparate;
	int* numarPreparate;

public:
	Comanda() {
		numarPreparate = new int(0);
	}

	Comanda(const vector<Preparate>& preparate) {
		this->preparate = preparate;
		numarPreparate = new int(preparate.size());
	}
	Comanda(const Comanda& comanda) {
		preparate = comanda.preparate;
		numarPreparate = new int(*comanda.numarPreparate);
	}
	~Comanda() {
		delete numarPreparate;
	}
	Comanda& operator=(const Comanda& comanda) {
		if (this != &comanda) {
			preparate = comanda.preparate;
			*numarPreparate = *comanda.numarPreparate;
		}
		return *this;
	}
	void adaugaPreparat(const Preparate& preparat) {
		preparate.push_back(preparat);
		(*numarPreparate)++;
	}
	int getNumarPreparate() const {
		return *numarPreparate;
	}

	void setNumarPreparate(int numar) {
		*numarPreparate = numar;
	}

	const vector<Preparate>& getPreparate() const {
		return preparate;
	}

	void setPreparate(const vector<Preparate>& noiPreparate) {
		preparate = noiPreparate;
		*numarPreparate = preparate.size();
	}
	void afiseazaComanda() const {
		cout << "Comanda contine " << *numarPreparate << " preparate:\n";
		for (const auto& preparat : preparate) {
			cout << preparat << "\n";
		}
	}
	friend ostream& operator<<(ostream& os, const Comanda& comanda) {
		os << "Comanda contine " << *(comanda.numarPreparate) << " preparate:\n";
		for (const auto& preparat : comanda.preparate) {
			os << preparat << "\n";
		}
		return os;
	}
};
class Meniu {
private:
	string numeMeniu;
	string descriere;
	vector<Preparate> preparate;

public:
	Meniu() {
		
	}
	Meniu(const string& numeMeniu, const string& descriere, const vector<Preparate>& preparate) {
		this->numeMeniu = numeMeniu;
		this->descriere = descriere;
		this->preparate = preparate;
	}
	Meniu(const Meniu& altMeniu) {
		numeMeniu = altMeniu.numeMeniu;
		descriere = altMeniu.descriere;
		preparate = altMeniu.preparate;
	}
	Meniu& operator=(const Meniu& altMeniu) {
		if (this != &altMeniu) {
			numeMeniu = altMeniu.numeMeniu;
			descriere = altMeniu.descriere;
			preparate = altMeniu.preparate;
		}
		return *this;
	}
	~Meniu() {

	}
	void afisare() const {
		cout << "Nume Meniu: " << numeMeniu << endl;
		cout << "Descriere: " << descriere << endl;
		cout << "Preparate:" << endl;
		for (const auto& preparat : preparate) {
			cout << preparat;  
		}
	}
	friend ostream& operator<<(ostream& out, const Meniu& meniu) {
		out << "Nume Meniu: " << meniu.numeMeniu << "\n";
		out << "Descriere: " << meniu.descriere << "\n";
		out << "Preparate:\n";
		for (const auto& preparat : meniu.preparate) {
			out << preparat << "\n";
			out << "-------------------------------------------" << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Meniu& meniu) {
		cout << "Introduceti numele meniului: ";
		getline(in, meniu.numeMeniu);
		cout << "Introduceti descrierea meniului: ";
		getline(in, meniu.descriere);
		return in;
	}
};

class Chelner {
private:
	string nume;
	vector<Comanda> comenziPreluate;

public:
	Chelner(const string& nume) : nume(nume) {}

	Chelner(const Chelner& altChelner) : nume(altChelner.nume), comenziPreluate(altChelner.comenziPreluate) {}

	~Chelner() {}

	Chelner& operator=(const Chelner& altChelner) {
		if (this != &altChelner) {
			nume = altChelner.nume;
			comenziPreluate = altChelner.comenziPreluate;
		}
		return *this;
	}
	void preiaComanda(const Comanda& comanda) {
		comenziPreluate.push_back(comanda);
		cout << "Comanda a fost adaugata cu succes.\n";
	}

	void afiseazaComenziPreluate() const {
		cout << "Comenzile preluate de chelnerul " << nume << " sunt:\n";
		for (const auto& comanda : comenziPreluate) {
			cout << comanda << "\n";
		}
	}
	friend ostream& operator<<(ostream& os, const Chelner& chelner) {
		os << "Nume Chelner: " << chelner.nume << "\n";
		os << "Comenzi preluate:\n";
		for (const auto& comanda : chelner.comenziPreluate) {
			os << comanda << "\n";
		}
		return os;
	}

	friend istream& operator>>(istream& is, Chelner& chelner) {
		cout << "Introduceti numele chelnerului: ";
		is >> chelner.nume;
		return is;
	}
};

Ingredient proceseazaLinieIngredient(const string& linie) {
	stringstream ss(linie);
	string denumire, unitateMasura;
	float cantitate;
	getline(ss, denumire, ',');
	ss >> cantitate;
	ss.ignore();
	getline(ss, unitateMasura);
	return Ingredient(denumire.c_str(), cantitate, unitateMasura);
}

Preparat proceseazaLiniePreparat(const string& linie) {
	stringstream ss(linie);
	string nume, ingredient, unitateMasura, token;
	float pret, cantitate;
	int numarIngrediente;
	vector<Ingredient>ingrediente;
	getline(ss, nume, ',');
	ss >> pret;
	ss.ignore();
	ss >> numarIngrediente;
	ss.ignore();

	for (int i = 0; i < numarIngrediente; ++i) {
		getline(ss, ingredient, ',');
		ss >> cantitate;
		ss.ignore();
		getline(ss, unitateMasura, ',');
		ingrediente.push_back(Ingredient(ingredient.c_str(), cantitate, unitateMasura));
	}

	// Presupunem că alergenul este ultimul token
	getline(ss, token);
	Alergeni alergen = Gluten; // Sau o altă valoare implicită
	if (token == "Gluten") alergen = Gluten;
	else if (token == "Lactoza") alergen = Lactoza;
	// ... continuă pentru alți alergeni

	return Preparat(nume, pret, ingrediente.data(), numarIngrediente, alergen);
}
int main(int argc,char* argv[]) {
	Ingredient i;
	i.setDenumire("Cartofi");
	cout << i.getDenumire();
	Ingredient i1("Cartofi", 5.3, "kilograme");
	i1.afisare();
	cout << i1<<endl;
	cout << "================================================" << endl;

	Ingredient* pui = new Ingredient("piept de pui", 200, "grame");
	Ingredient* rosii = new Ingredient("rosii", 70, "grame");
	Ingredient* ciuperci = new Ingredient("ciuperci", 70, "grame");
	Ingredient* smantana = new Ingredient("smantana", 200, "ml");
	Ingredient* ingrediente[2] = { pui,rosii };
	Ingredient* ingrediente1[4] = { pui,rosii,ciuperci,smantana };
	Preparate puiCuRosii("Pui Cu Rosii", 50, ingrediente, 2, Alergeni::Gluten, 1);
	Preparate puiCuCiuperci("Pui Cu Sos Alb si Ciuperci", 45, ingrediente1, 2, Alergeni::Lactoza, 2);
	cout << puiCuRosii<<endl;
	cout << "================================================" << endl;
	Comanda comanda1;
	comanda1.adaugaPreparat(puiCuRosii);
	comanda1.afiseazaComanda();
	cout << "================================================" << endl;
	vector<Preparate> listaPreparate;
	listaPreparate.push_back(puiCuRosii);
	listaPreparate.push_back(puiCuCiuperci);
	Meniu meniu1("Meniu de Zi", "Un meniu special pentru pranz", listaPreparate);

	cout << "Detalii Meniu 1:" << endl;
	//meniu1.afisare();
	cout << meniu1;
	cout << "================================================" << endl;
	cout << "----------------------aici incepe chelnerul-------------------------------"<<endl;
	Chelner chelner("Alexandru");
	chelner.preiaComanda(comanda1);
	cout << "Detalii Chelner:\n";
	chelner.afiseazaComenziPreluate();


	delete pui;
	delete rosii;
	delete ciuperci;
	delete smantana;


	if (argc != 3) {
		cout << "Utilizare: " << argv[0] << " ingrediente.txt meniu.txt" << endl;
		return 1;
	}
	ifstream fisierIngrediente(argv[1]);
	ifstream fisierMeniu(argv[2]);

	if (!fisierIngrediente.is_open() || !fisierMeniu.is_open()) {
		cerr << "Eroare la deschiderea fișierelor" << endl;
		return 1;
	}

	string linie;
	vector<Ingredient> stocIngrediente;
	vector<Preparat> meniuPreparate;

	while (getline(fisierIngrediente, linie)) {
		stocIngrediente.push_back(proceseazaLinieIngredient(linie));
	}

	while (getline(fisierMeniu, linie)) {
		meniuPreparate.push_back(proceseazaLiniePreparat(linie));
	}

	fisierIngrediente.close();
	fisierMeniu.close();
	cout << "Ingrediente:\n";
	for (const auto& ingredient : stocIngrediente) {
		cout << ingredient << endl;
	}

	cout << "\nMeniu:\n";
	for (const auto& preparat : meniuPreparate) {
		cout << preparat << endl;
	}

	return 0;
}