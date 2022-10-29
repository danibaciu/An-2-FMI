#include <cmath>
#include <iostream>
#include <vector>
#include "domain.h"

class Chromosome {
private:
    long double x;
    std::vector<bool> genes;

    static int no_of_bits, precision;
    static domainType domain;
    // Parameters of grade 2 fitness function
    static std::vector<long double> parameters;

public:
    static void set_domain(int a, int b);

    static void set_no_of_bits_p(int nr, int p);

    static void set_parameters(int a, int b, int c);

    Chromosome(bool generare = false);

    Chromosome(std::vector<bool>);

    long double getX() const;

    void update_x(std::vector<bool>&);

    static int getNoOfBits();

    std::vector<bool> getGenes();

    long double fitness();

    void afis_gene(std::ostream &out);

    friend std::ostream &operator<<(std::ostream &, Chromosome &);

};

void Chromosome::set_domain(int a, int b) {
    domain.a = a;
    domain.b = b;
}

void Chromosome::set_no_of_bits_p(int nr, int p) {
    no_of_bits = nr;
    precision = p;
}

void Chromosome::set_parameters(int a, int b, int c) {
    parameters.push_back(a);
    parameters.push_back(b);
    parameters.push_back(c);
}

Chromosome::Chromosome(bool generare) {
    if (generare) {
        int interval = domain.b - domain.a;
        long long putere10 = pow(10, precision);

        long double rnd = domain.a + static_cast <long double> (rand()) /( static_cast <long double> (RAND_MAX/(interval)));

//        long long rnd = rand() % (interval * putere10) + domain.a * putere10;

        this->x = rnd;

        this->genes.resize(no_of_bits);

        int i = no_of_bits - 1;
        long long nr = rnd * putere10 - domain.a * putere10;

        while (nr > 0) {
            this->genes[i] = nr % 2;
            nr /= 2;
            i--;
        }
    }
}

long double Chromosome::getX() const {
    return x;
}

void Chromosome::afis_gene(std::ostream &out) {
    for (auto bit: this->genes) {
        out << bit;
    }
}

std::vector<bool> Chromosome::getGenes() {
    return genes;
}

void Chromosome::update_x(std::vector<bool> &new_genes) {
    int new_x = 0; int putere_2 = 1;
    for (int i = no_of_bits - 1; i >= 0; i--) {
        new_x += putere_2 * new_genes[i];
        this->genes[i] = new_genes[i];
        putere_2 *= 2;
    }

    //acum avem x ul si trb impartit la 10^p
    long long putere10 = pow(10, precision);

    this->x = (long double) new_x / putere10 + (long double)domain.a;
}

long double Chromosome::fitness() {
    if (parameters.size() < 3)
        throw std::invalid_argument("parameters vector is too small");
    return parameters[0] * x * x + parameters[1] * x + parameters[2];
}

std::ostream &operator<<(std::ostream &out, Chromosome &x) {
    out << "\tx = \t" << x.x << "\t\t genele : ";
    for (auto bit: x.genes) {
        out << bit;
    }
    return out;
}

int Chromosome::getNoOfBits() {
    return no_of_bits;
}
