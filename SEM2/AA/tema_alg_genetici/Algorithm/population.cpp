#include <chrono>
#include <algorithm>
#include <random>

#include "chromosome.cpp"

class Population {
private:
    std::vector<Chromosome> population;

    std::vector<long double> maxim_evolution;

    bool afisare;

    std::ostream &out;

    // We defined the domain where we are searching for maximum fitness
    static domainType domain;

    // Precision means the no of zecimals after the "," and the number n means dimensio of the population
    static int precision, n;

    // for crossing over;
    static long double probability_of_crossing_over, probability_of_gena_mutation;

public:
    static void set_p_n_crossing_over_gena(int p, int nr, long double prob1, long double prob2);

    static void set_domain(int a, int b);

    Population(std::ostream &ou) : out(ou) {}

    void generate_population();

    std::vector<long double> generate_interval_of_probabilities();

    int binary_search(std::vector<long double>, long double);

    void cross_over(std::vector<int> &, std::vector<Chromosome> &);

    void handle_gena_mutation();

    void print_max_evolution();

    void print_vector_of_chromosome(std::vector<Chromosome> &);

    friend std::ostream &operator<<(std::ostream &, Population &);
};

void Population::set_domain(int a, int b) {
    domain.a = a;
    domain.b = b;
    Chromosome::set_domain(a, b);
}

void Population::set_p_n_crossing_over_gena(int p, int nr, long double prob1, long double prob2) {
    precision = p;
    n = nr;
    probability_of_crossing_over = prob1;
    probability_of_gena_mutation = prob2;
}

void Population::generate_population() {
    if (population.empty()) {
        //that means we have to generate the population for the first time
        for (int i = 0; i < n; i++) {
            population.emplace_back(Chromosome(true));
        }
        afisare = true;
    } else {
        //luam populatia si incepem sa o transformam
        std::vector<Chromosome> next_population;

        std::vector<long double> probabilities_of_choosing = generate_interval_of_probabilities();

        //dam cu banul de n - 1 ori pentru ca trebuie sa punem si fitul

        for (int i = 0; i < n - 1; i++) {
            long double rand_number = ((long double) rand() / (RAND_MAX));
            int index = binary_search(probabilities_of_choosing, rand_number);

            if (afisare)
                out << "\n\t random = \t" << rand_number << "\t\t selectam cromozomul \t" << index << "\n";

            next_population.emplace_back(population[index - 1]);
        }

        if (afisare) {
            out << "Populatia dupa selectie : \n";
            print_vector_of_chromosome(next_population);
        }

        // selectam cine face parte din incrucisare

        std::vector<int> crossing_over_idx;

        if (afisare)
            out << "\n\tProbabilitatea de incrucisare este " << probability_of_crossing_over << "\n";

        for (int i = 0; i < next_population.size(); i++) {
            long double rand_number = ((long double) rand() / (RAND_MAX));

            if (afisare)
                out << "\n\t " << i + 1 << ") \t" << rand_number;

            if (rand_number <= probability_of_crossing_over) {
                crossing_over_idx.push_back(i);
                if (afisare)
                    out << "\t <" << probability_of_crossing_over
                              << " deci selectam cromozomul curent pentru incrucisare";
            }
        }

        int position_fit_max = 0;
        long double max_val = 0.0;

        for (int i = 0; i < Population::n; i++) {
            if (population[i].fitness() > max_val) {
                max_val = population[i].fitness();
                position_fit_max = i;
            }
        }
        next_population.emplace_back(population[position_fit_max]);
        this->population.clear();
        this->population = next_population;
        next_population.clear();

        //facem crossing overul
        cross_over(crossing_over_idx, population);

        if (afisare) {
            out << "\n\n\tDupa recombinare : \n";
            print_vector_of_chromosome(population);
        }

        handle_gena_mutation();

        if (afisare) {
            out << "\n\n\tDupa mutatia genelor : \n";
            print_vector_of_chromosome(population);
        }
        afisare = false;
    }

    long double max_val = 0.0;

    for (int i = 0; i < Population::n; i++) {
        if (population[i].fitness() > max_val) {
            max_val = population[i].fitness();
        }
    }

    maxim_evolution.push_back(max_val);
}

void Population::print_max_evolution() {
    out << "\n-----------------------------------\n\t\t Evolutia maximului :\n";
    for (int i = 0; i < maxim_evolution.size(); i++) {
        out <<"\t"<< i + 1 << ") " << maxim_evolution[i] << "\n";
    }
}

std::vector<long double> Population::generate_interval_of_probabilities() {
    long double sum = 0.0;

    std::vector<long double> probabilities;
    if (afisare)
        out << "\n\t Probabilitati de selectie :\n";

    probabilities.push_back(0.0);

    for (int i = 0; i < this->population.size(); i++) {
        long double fit = population[i].fitness();
        probabilities.push_back(fit);
        sum += fit;
    }

    for (int i = 1; i < probabilities.size(); i++) {
        probabilities[i] = (long double) probabilities[i] / sum;
        if (afisare)
            out << "\t\t cromozomul\t" << i << "\tare probabilitatea de selectie\t\t" << probabilities[i] << "\n";
    }

    if (afisare)
        out << "\n\t Intervalul de selectie este :\n" << probabilities[0] << "   ";

    for (int i = 1; i < probabilities.size(); i++) {
        probabilities[i] += probabilities[i - 1];
        if (afisare)
            out << probabilities[i] << "   ";
    }

    if (afisare)
        out << "\n";

    return probabilities;
}

void Population::handle_gena_mutation() {
    if (afisare)
        out << "\n\tProbabilitatea de mutatie pentru fiecare gena este " << probability_of_gena_mutation << ".\n";
    bool ok = false;
    std::vector<int> position;
    for (int c = 0; c < this->population.size(); c++) {
        bool change = false;
        std::vector<bool> gene = this->population[c].getGenes();
        for (int i = 0; i < gene.size(); i++) {
            long double rand_number = ((long double) rand() / (RAND_MAX));
            if (rand_number < probability_of_gena_mutation) {
                ok = true;
                change = true;
                gene[i] = !gene[i];
            }
        }

        if (change) {
            this->population[c].update_x(gene);
            position.push_back(c);
        }
    }

    if (afisare) {
        if (ok) {
            out << "\n\t Au fost modificati cromozomii : \n";
            for (auto &x: position)
                out << "\t\t" << x + 1 << "\n";
        } else {
            out << "\n\tNu a fost modificat niciun cromozom.\n";
        }
    }
}

int Population::binary_search(std::vector<long double> probabilities, long double value) {
    int left = 0, right = probabilities.size() - 1;

    while (left <= right) {
        int middle = (left + right) / 2;

        if (probabilities[middle] == value) {
            return middle;
        } else {
            if (probabilities[middle] > value)
                right = middle - 1;
            else
                left = middle + 1;
        }
    }
    return left;
}

void Population::cross_over(std::vector<int> &cross_over_idx, std::vector<Chromosome> &next_population) {
    //dau shuffle la cromozomi
    unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(cross_over_idx.begin(), cross_over_idx.end(), std::default_random_engine(num));

    //acum iau 2 cate 2 si le fac interschimbarea

    std::vector<bool> res1(Chromosome::getNoOfBits()), res2(Chromosome::getNoOfBits());

    for (int i = 0; i < cross_over_idx.size() - 1; i += 2) {
        //fac mutatie i cu i + 1
        if (afisare) {
            out << "\n\n\tRecombinare dintre cromozomul " << cross_over_idx[i] + 1 << " si cromozomul "
                      << cross_over_idx[i + 1] + 1 << " :\n";

            next_population[cross_over_idx[i]].afis_gene(out);

            out << "\t";

            next_population[cross_over_idx[i + 1]].afis_gene(out);
        }

        int rand_position = rand() % Chromosome::getNoOfBits();

        if (afisare)
            out << "\t punct " << rand_position << "\n";

        std::vector<bool> pop1(next_population[cross_over_idx[i]].getGenes());
        std::vector<bool> pop2(next_population[cross_over_idx[i + 1]].getGenes());

        for (int j = 0; j < rand_position; j++) {
            //copiez bucata pana la pozitie
            res1[j] = pop1[j];
            res2[j] = pop2[j];
        }

        for (int j = rand_position; j < Chromosome::getNoOfBits(); j++) {
            //copiez bucata pana la pozitie
            res1[j] = pop2[j];
            res2[j] = pop1[j];
        }

        if (afisare)
            out << " Rezultat ";

        next_population[cross_over_idx[i]].update_x(res1);
        if (afisare)
            next_population[cross_over_idx[i]].afis_gene(out);

        if (afisare)
            out << "\t";
        next_population[cross_over_idx[i + 1]].update_x(res2);
        if (afisare)
            next_population[cross_over_idx[i + 1]].afis_gene(out);

        // fac update la x si genes
    }
}

void Population::print_vector_of_chromosome(std::vector<Chromosome> &x) {
    for (int i = 0; i < x.size(); i++) {
        out << "\t" << i + 1 << "." << x[i];
        out << "\t\tfit(x) = \t" << x[i].fitness() << "\n";
    }
}

std::ostream &operator<<(std::ostream &out, Population &x) {
    x.print_vector_of_chromosome(x.population);
    return out;
}
