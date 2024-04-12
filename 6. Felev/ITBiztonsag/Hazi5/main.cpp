#include <armadillo>
#include <sqlite3.h>
#include <vector>

using namespace std;

//a valtozok
static std::vector<int> b;
static std::vector<int> x;
std::vector<std::string> commands;
//arma::Mat<int> A;
std::vector<std::vector<int>> A;
std::vector<int> ACounts;

static int callback(void* out_data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	return 0;
}

//callback fuggveny az x vektor feltoltesehez
static int callback1(void* out_data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
		x.push_back(std::stoi(argv[i]));
		//cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	return 0;
}

//callback fuggveny az A matrix feltoltesehez
static int callback2(void* out_data, int argc, char** argv, char** azColName)
{
	A[A.size() - 1][std::stoi(argv[0])] = 1;
	ACounts[ACounts.size() - 1] += 1;
	//std::vector<int> l(1000, 0);
	//for (int i = 0; i < argc; i++)
		//l[std::stoi(aaColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
	//A.push_back(l);
	//std::cout << argv[0] << std::endl;
	//ACounts.push_back(argc);
	return 0;
}

//sql parancsok beolvasasa. Ebbol lesz meg a b vektor
void readSqlFile()
{
	string sqlfile = "queries.sql";
	ifstream sql;
	sql.open(sqlfile);
	

	for (std::string line; getline(sql, line); )
	{
		commands.push_back(line.substr(0, line.find(";") + 1));
		b.push_back(std::stoi(line.substr(line.find(";") + 2, line.length())));
	}
}

//az elso feladat megoldasa
int f1()
{
	readSqlFile(); // beolvassa az sql filet

	int min = b[0];
	for (unsigned int i = 0; i < b.size(); i++) //megkeresei b ertekei kozul a legkisebbet
	  if (b[i] < min)
	    min = b[i];
	//std::cout << "b_min: " << min << std::endl;

	
	sqlite3* db;
	char* zErrMsg = 0;

	if (sqlite3_open("adult.db", &db) != SQLITE_OK) //adatbazis megnyitasa
	{
		cerr << "Can’t open database: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return 1;
	}
	
	if (sqlite3_exec(db, "SELECT salary FROM adult;", callback1, 0, &zErrMsg) != SQLITE_OK) //lekeredezes vegrehejtasa
	{
		cerr << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	

	//minimum es maximum ertekek meghatarozasa
	int m = x[0];
	for (unsigned int i = 0; i < x.size(); i++)
	  if (x[i] < m)
	    m = x[i];
	std::cout << "x_min: " << m << std::endl;
	m = 0;
	for (unsigned int i = 0; i < x.size(); i++)
	  if (x[i] > m)
	    m = x[i];
	std::cout << "x_max: " << m << std::endl;
	std::cout << "x_size: " << x.size() << std::endl;


	for(std::string cmd : commands) //A matrix felepitese
	{
		std::string c = "SELECT idx FROM adult " + cmd.substr(cmd.find("adult") + 6, cmd.length());
		std::vector<int> l(1000, 0);
		A.push_back(l);
		ACounts.push_back(0);
		//std::cout << c << std::endl;
		if (sqlite3_exec(db, c.c_str(), callback2, 0, &zErrMsg) != SQLITE_OK)
		{
			cerr << "SQL error: " << zErrMsg << endl;
			sqlite3_free(zErrMsg);
		}
	}


	sqlite3_close(db);

	int mi = ACounts[0];
	int ma = 0;
	int sum = 0;
	for (unsigned int i = 0; i < ACounts.size(); i++)
	{
		//std::cout << ACounts[i] << std::endl;
		if (ACounts[i] < mi)
			mi = ACounts[i];
		if (ACounts[i] > ma)
			ma = ACounts[i];
		sum += ACounts[i];
	}
	std::cout << "A_min: " << mi << std::endl;
	std::cout << "A_max: " << ma << std::endl;
	std::cout << "A_avg: " << sum / A.size() << std::endl;
}

//az elso n sorbol kapott matrix rangjanak megszamolasa
arma::uword getRank(int numOfRows)
{
	arma::mat M(numOfRows, 1000, arma::fill::zeros);
	for(int l = 0; l < numOfRows; ++l)
	{
		for(int i = 0; i < 1000; ++i)
			M(l, i) = A[l][i];
	}

	return arma::rank(M);
}

void f2()
{
	std::cout << "1000: " << getRank(1000) << std::endl;
	std::cout << "2000: " << getRank(2000) << std::endl;
	std::cout << "3000: " << getRank(3000) << std::endl;
	std::cout << "4000: " << getRank(4000) << std::endl;
}

//az ols algoritmus vegrehajtasa az elso n soron, a sikeresseggel ter vissza
int OLS(int rows)
{
	arma::mat M(rows, 1000, arma::fill::zeros);
	for(int l = 0; l < rows; ++l)
	{
		for(int i = 0; i < 1000; ++i)
			M(l, i) = A[l][i];
	}
	
	arma::vec v(4000, arma::fill::zeros);
	for(int i = 0; i < 4000; ++i)
		v(i) = b[i];
	
	arma::vec x_ = arma::pinv(M) * v.subvec(0, rows - 1);

	int same = 0;
	for(int idx = 0; idx < 1000; ++idx)	
		if(x[idx] == round(x_(idx)))
			++same;
	return same;
}

void f3()
{
	std::cout << "1000: " << OLS(1000) << std::endl;
	std::cout << "2000: " << OLS(2000) << std::endl;
	std::cout << "3000: " << OLS(3000) << std::endl;
	std::cout << "4000: " << OLS(4000) << std::endl;
}

int main(int argc, char** argv)
{
	f1();
	f2();
	f3();
	return 0;
}
