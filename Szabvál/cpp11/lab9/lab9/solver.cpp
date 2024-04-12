#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <stdexcept>

template <typename VALUETYPE>
class Solver 
{
  public:
    /* VariableFunc: ez azt a változót reprezentálja, amely tesztelés
     * közben különféle értékeket vesz fel. Ha meghívjuk a függvényt,
     * megkapjuk az értéket. */
    using VariableFunc = std::function<VALUETYPE const &()>;
    /* ConstraintFunc: egy olyan paraméter nélküli függvény, amely megmondja,
     * hogy az elvárt összefüggések épp teljesülnek-e. */
    using ConstraintFunc = std::function<bool()>;
    /* ActivityFunc: ilyen függvényt fog meghívni a Solver, amikor tesztelés
     * közben talál egy megoldást. */
    using ActivityFunc = std::function<void()>;


  private:
    /* Ezeket a változókat kell vizsgálni */
    std::vector<std::vector<VALUETYPE>> variables_;
    /* Ez meg a vizsgálat közben fog kelleni */
    std::vector<typename std::vector<VALUETYPE>::const_iterator> iterators_;
    /* Ezen feltételek szerint fog futni a vizsgálat */
    std::vector<ConstraintFunc> constraints_;
  
  public:
    /* Egy változó lehetséges értékeit tartalmazó tárolót várja.
     * Ad egy olyan függvényt vissza, amelyet meghívva
     * lekérdezhető, hogy a tesztelés közben az adott változónak éppen
     * mi az értéke. A használó ezekre a függvényekre tud majd építeni.
     * Az iterátorok egyelőre nem léteznek, úgyhogy nem tudjuk az iterátor
     * referenciáját eltárolni. */
    VariableFunc add_variable(std::vector<VALUETYPE> values) {
        if (values.empty())
            throw std::runtime_error("add_variable: a lehetseges ertekek halmaza nem lehet ures");
        for (size_t i = 0; i < values.size() - 1; ++i)
            for (size_t j = i+1; j < values.size(); ++j)
                if (values[i] == values[j])
                    throw std::runtime_error("add_variable: egyforma elemek is vannak a taroloban");
        variables_.push_back(std::move(values));
        size_t pos = variables_.size()-1;
        return [this, pos] () -> VALUETYPE const & {
            if (iterators_.empty())
                throw std::runtime_error("variable_func: csak a solve-on keresztul hivhato a fuggveny");
            return *iterators_[pos];
        };
    }

    /* Feltétel hozzáadása. A feltétel egy függvény, amely igaz értéke
     * esetén az aktuális állapot elfogadható. */
    void add_constraint(ConstraintFunc constraint) {
        constraints_.push_back(std::move(constraint));
    }

    /* Teszteli az összes lehetséges értéket, és amikor olyan
     * állapotban vannak az iterátorok, amik épp egy elfogadható
     * kombinációra mutatnak, akkor meghívja a függvényt. */
    void solve(ActivityFunc do_what) {
        /* iterátorok inicializálása */
        iterators_.clear();
        for (auto & v : variables_)
            iterators_.push_back(v.begin());

        /* A Variable-k current iterátorait már mind begin-re
         * állítottuk, szóval most az elején áll az összes. */
        bool end = false;
        while (!end) {
            /* Jó az aktuális állapot? Ha mindegyik igazat ad. */
            bool satisfied = std::all_of(
                constraints_.begin(), constraints_.end(),
                [] (ConstraintFunc const & cons) { return cons(); }
            );
            /* Ha mindegyik Constraint szerint jó az aktuális megoldás: */
            if (satisfied)
                do_what();

            /* Következőre ugrás: a digit teljes összeadója kódban. */
            bool carry = true;
            for (size_t i = 0; i < variables_.size(); ++i) {
                ++iterators_[i];
                carry = iterators_[i] == variables_[i].end();
                if (carry)
                    iterators_[i] = variables_[i].begin();
                else
                    break;
            }
            /* Ha vége lett, és még mindig carry=true, körbeértünk. */
            end = carry;
        }
        
        /* ezek már nem kellenek */
        iterators_.clear();
    }
};


/*int main() 
{
    Solver<int> t;

    // Baker, Cooper, Fletcher, Miller és Smith egy ötemeletes ház
    auto baker = t.add_variable({1, 2, 3, 4, 5});
    auto cooper = t.add_variable({1, 2, 3, 4, 5});
    auto fletcher = t.add_variable({1, 2, 3, 4, 5});
    auto miller = t.add_variable({1, 2, 3, 4, 5});
    auto smith = t.add_variable({1, 2, 3, 4, 5});
    
    // különböző emeletein laknak.
    auto guys = { baker, cooper, fletcher, miller, smith };
    t.add_constraint([=] () -> bool {
        for (auto first = guys.begin(); first != guys.end(); ++first)
            for (auto second = first+1; second != guys.end(); ++second)
                if ((*first)() == (*second)())
                    return false;
        return true;
    });
    // Baker nem a legfölső emeleten lakik,
    t.add_constraint([=] () { return baker() != 5; });
    // Cooper pedig nem az alsó szinten.
    t.add_constraint([=] { return cooper() != 1; });
    // Fletcher lakhelye sem a legalsó szinten van, de nem is a legfölsőn.
    t.add_constraint([=] { return fletcher() != 1 && fletcher() != 5; });
    // Miller magasabban lakik, mint Cooper. 

    t.add_constraint([=] { return miller() > cooper(); });
    // Smith nem Fletcherrel szomszédos emeleten lakik,
    t.add_constraint([=] { return abs(smith() - fletcher()) != 1; });
    // ahogy Cooper és Fletcher sem emelet-szomszédok.
    t.add_constraint([=] { return abs(cooper() - fletcher()) != 1; });

    // A kérdés: melyik emelet kié?
    auto print_all = [=] {
        std::cout << "Baker " << baker() << std::endl
                  << "Cooper " << cooper() << std::endl
                  << "Fletcher " << fletcher() << std::endl
                  << "Miller " << miller() << std::endl
                  << "Smith " << smith() << std::endl;
    };
    t.solve(print_all);
}*/

void Pitagoras()
{
    Solver<int> s;

    int n = 0;

    std::vector<int> numbers;
    for (int idx = 0; idx < 100; ++idx)
        numbers.push_back(idx + 1);

    /* változók hozzáadása */
    auto a = s.add_variable(numbers);
    auto b = s.add_variable(numbers);
    auto c = s.add_variable(numbers);

    /* feltételek hozzáadása */
    s.add_constraint([=] { return a() < b(); });
    s.add_constraint([=] { return b() < c(); });
    s.add_constraint([=] { return a() * a() +  b() * b() == c() * c(); });

    /* keresés és megoldások kiírása */
    s.solve([&n] {++n; });
    std::cout << n << std::endl;
}

void Euler()
{
    Solver<int> s;

    int n = 0;

    std::vector<int> numbers;
    for (int idx = 0; idx < 101; ++idx)
        numbers.push_back(idx);

    /* változók hozzáadása */
    auto sertes = s.add_variable(numbers);
    auto kecske = s.add_variable(numbers);
    auto juh = s.add_variable(numbers);

    /* feltételek hozzáadása */
    s.add_constraint([=] { return sertes() + kecske() + juh() == 100; });
    s.add_constraint([=] { return sertes() * 21 + kecske() * 8 + juh() * 3 == 600; });

    /* keresés és megoldások kiírása */
    s.solve([=, &n] {++n; std::cout << sertes() << "  " << kecske() << "  " << juh() << "  " << std::endl; });
    std::cout << n << std::endl;
}

void Map()
{
    Solver<std::string> s;

    /* változók hozzáadása */
    auto A = s.add_variable({ "kek", "sarga", "piros"});
    auto B = s.add_variable({ "kek", "sarga", "piros"});
    auto C = s.add_variable({ "kek", "sarga", "piros"});
    auto D = s.add_variable({ "kek", "sarga", "piros" });
    auto E = s.add_variable({ "kek", "sarga", "piros" });

   

    /* feltételek hozzáadása */
    s.add_constraint([=] { return A() != B(); });
    s.add_constraint([=] { return A() != C(); });
    s.add_constraint([=] { return A() != D(); });
    s.add_constraint([=] { return A() != E(); });
    s.add_constraint([=] { return B() != C(); });
    s.add_constraint([=] { return E() != C(); });
    s.add_constraint([=] { return E() != D(); });
    s.add_constraint([=] { return B() != D(); });
    s.add_constraint([=] { return B() != C(); });
    s.add_constraint([=] { return B() < A(); });
    s.add_constraint([=] { return D() < E(); });

    /* keresés és megoldások kiírása */
    s.solve([=] {std::cout << A() << "  " << B() << "  " << C() << "  " << D() << "  " << E() << std::endl; });
}

void Queens()
{
    Solver<int> s;

    const int n = 7;
    int count = 0;

    std::vector<int> numbers;
    for (int idx = 0; idx < n; ++idx)
        numbers.push_back(idx + 1);

    std::vector<std::function<int const& ()>> queens;

    for (int idx = 0; idx < n; ++idx)
        queens.push_back(s.add_variable(numbers));

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            s.add_constraint([=] {return queens[i]() != queens[j](); });
            int l = j - i;
            s.add_constraint([=] {return  queens[i]() + l != queens[j](); });
            s.add_constraint([=] {return  queens[i]() - l != queens[j](); });
        }
    }

    s.solve([&count] {++count; });
    std::cout << count << std::endl;
}

void SendMoreMoney()
{
    Solver<int> solver;

    std::vector<int> numbers;
    for (int idx = 0; idx <= 9; ++idx)
        numbers.push_back(idx);

    std::vector<std::function<int const& ()>> letters;

    for (int idx = 0; idx < 8; ++idx)
        letters.push_back(solver.add_variable(numbers));

    for (int i = 0; i < 8; ++i)
    {
        for (int j = i + 1; j < 8; ++j)
        {
            solver.add_constraint([=] {return letters[i]() != letters[j](); });
        }
    }

    //1 s
    //2 e
    //3 n
    //4 d
    //5 m
    //6 o
    //7 r
    //8 y

    solver.add_constraint([=] {return (letters[3]() + 10 * letters[2]() + 100 * letters[1]() + 1000 * letters[0]() +
        letters[1]() + 10 * letters[6]() + 100 * letters[5]() + 1000 * letters[4]()) == letters[7]() + 10 * letters[1]() + 100 * letters[2]() + 1000 * letters[5]() + 10000 * letters[4](); });


    solver.solve([=] {std::cout << letters[3]() + 10 * letters[2]() + 100 * letters[1]() + 1000 * letters[0]() << " + " << letters[1]() + 10 * letters[6]() + 100 * letters[5]() + 1000 * letters[4]()
        << " = " << letters[7]() + 10 * letters[1]() + 100 * letters[2]() + 1000 * letters[5]() + 10000 * letters[4]() << std::endl; });
    
}

int main() 
{
    //Pitagoras();
    //Euler();
    //Map();
    //Queens();
    //SendMoreMoney();
}
