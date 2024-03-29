#pragma once
#include <vector>
#include <string>


class Polynomial {
private:
    int degree = 0;
    std::vector<std::pair<double, int>> terms = {};
    static bool sortByDegree(std::pair<double, int> const& a, std::pair<double, int> const& b) noexcept;
    void sortTerms() noexcept;
    void applyOperation(std::vector<std::pair<double, int>> const& otherTerms, char operation) noexcept;
    void processTerm(std::string const& term, bool const& isNegative) noexcept;
    void formatDouble(std::string& number) const noexcept;
public:
    Polynomial() = default;
    explicit Polynomial(std::vector<std::pair<double, int>> const& terms);
    explicit Polynomial(std::string const& polynomial);
    Polynomial(Polynomial const& other) = default;
    ~Polynomial() = default;
    [[nodiscard]] std::string toString() const noexcept;
    [[nodiscard]] int getDegree() const noexcept;
    void setTerms(std::vector<std::pair<double, int>> const& terms) noexcept;
    void operator+=(Polynomial const& other) noexcept;
    void operator-=(Polynomial const& other) noexcept;
    void operator*=(Polynomial const& other) noexcept;
    void operator*=(double const& scalar) noexcept;
    Polynomial operator+(Polynomial const& other) const noexcept;
    Polynomial operator-(Polynomial const& other) const noexcept;
    Polynomial operator*(Polynomial const& other) const noexcept;
    Polynomial operator*(double const& scalar) const noexcept;
    Polynomial operator-() const noexcept;
    bool operator==(Polynomial const& other) const noexcept;
    bool operator!=(Polynomial const& other) const noexcept;
    double operator()(double const& x) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, Polynomial const& polynomial);
};
