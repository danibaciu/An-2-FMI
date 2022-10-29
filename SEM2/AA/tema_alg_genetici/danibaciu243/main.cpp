#include <cstdlib>
#include <ctime>
#include <fstream>

#include "Algorithm/population.cpp"

void citire(int &a, int &b, int &p, int &n, long double &probability_of_crossing_over, long double &probability_gena_mut, int &nr_etape) {
    std::cout << "a este : ";
    std::cin >> a;
    std::cout << "b este : ";
    std::cin >> b;
    std::cout << "nr de zecimale este : ";
    std::cin >> p;
    std::cout << "nr de indivizi : ";
    std::cin >> n;
    std::cout << "probabilitatea de incrucisare : ";
    std::cin >> probability_of_crossing_over;
    std::cout << "prob mutatie pt fiecare gena:";
    std::cin >> probability_gena_mut;
    std::cout << "Numarul de etape pentru evolutie este:";
    std::cin >> nr_etape;
}

// static variables
int Population::n, Population::precision, Chromosome::no_of_bits, Chromosome::precision;
domainType Population::domain, Chromosome::domain;
std::vector<long double> Chromosome::parameters;
long double Population::probability_of_crossing_over, Population::probability_of_gena_mutation;

int main() {
    srand(time(nullptr));

    std::ofstream fout("Evolutie3.txt");

    // Aici vom seta in cod functia de fitness, care este ax^2 + bx + c
    Chromosome::set_parameters(-1, 1, 2);

    int a, b, p, n, nr_etape;
    long double probability_of_crossing_over, probability_gena_mut;

    citire(a, b, p, n, probability_of_crossing_over, probability_gena_mut, nr_etape);

    int putere_10 = pow(10, p);
    int interval = (b - a) * putere_10;
    int nr_biti = 1 + (int) log2(interval);

//    std::cout<<a<< " "<<b<<" "<<p<<" "<<n<<" "<<interval<<" "<<putere_10<<" "<<nr_biti;

    Population::set_p_n_crossing_over_gena(p, n, probability_of_crossing_over, probability_gena_mut);
    Population::set_domain(a, b);
    Chromosome::set_no_of_bits_p(nr_biti, p);

    // pana aici e partea de initializare si citire a datelor

    Population population(fout);

    population.generate_population();

    fout << "\n\t Populatia initiala : \n";
    fout << population;

    for (int i = 1; i < nr_etape; i++) {
        population.generate_population();
    }

    fout << "\n\n------------------------------------------------\n\n\t Populatia finala : \n";
    fout << population;

    population.print_max_evolution();


    return 0;
}
