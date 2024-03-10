#include "polynomial.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>

bool Polynomial::sortByDegree(std::pair<double, int> const& a, std::pair<double, int> const& b) noexcept {
    return a.second > b.second;
}

void Polynomial::sortTerms() noexcept {
    std::sort(terms.begin(), terms.end(), sortByDegree);
}

void Polynomial::applyOperation(std::vector<std::pair<double, int>> const& otherTerms,
                                char operation) noexcept {
    for (auto otherTerm : otherTerms) {
        if (operation == '-') {
            otherTerm.first *= -1;
        }
        auto i = terms.begin();
        for (auto& term : terms) {
            if (term.second < otherTerm.second) {
                terms.insert(i, otherTerm);
                break;
            } else if (term.second == otherTerm.second) {
                term.first += otherTerm.first;
                if (term.first == 0) {
                    terms.erase(i);
                }
                break;
            }
            ++i;
        }
    }
    degree = terms[0].second;
}

Polynomial::Polynomial(std::vector<std::pair<double, int>> const& terms) {
    this->terms = terms;
    sortTerms();
    degree = terms[0].second;
}

Polynomial::Polynomial(std::string const& polynomial) {
    std::istringstream iss(polynomial);
    std::string term;
    while (std::getline(iss, term, '+')) {
        term.erase(std::remove_if(term.begin(), term.end(), ::isspace), term.end());
        double coefficient = 1.0;
        int exponent = 0;
        bool isNegative = false;
        if (term[0] == '-') {
            isNegative = true;
            term = term.substr(1);
        }

        size_t pos = term.find('x');

        if (pos != std::string::npos) {
            if (pos != 0) {
                coefficient = std::stod(term.substr(0, pos));
            }
            pos = term.find('^');
            if (pos != std::string::npos) {
                exponent = std::stoi(term.substr(pos + 1));
            } else {
                exponent = 1;
            }
        } else {
            coefficient = std::stod(term);
        }

        if (isNegative) {
            coefficient *= -1;
        }

        terms.emplace_back(coefficient, exponent);
    }
    sortTerms();
    this->degree = terms[0].second;
}

void Polynomial::setTerms(const std::vector<std::pair<double, int>> &terms) noexcept {
    this->terms = terms;
    sortTerms();
    degree = terms[0].second;
}

int Polynomial::getDegree() const noexcept {
    return degree;
}

std::string Polynomial::toString() const noexcept {
    std::string result;
    for (auto const& term : terms) {
        if (term.first == 0) {
            continue;
        }
        if (term.first > 0) {
            if (!result.empty()) {
                result += "+";
            }
        } else {
            result += "-";
        }
        if (term.second == 0) {
            result += std::to_string(term.first);
        } else if (term.second == 1) {
            result += std::to_string(term.first) + "x";
        } else {
            result += std::to_string(term.first) + "x^" + std::to_string(term.second);
        }
    }
    return result;
}

void Polynomial::operator+=(Polynomial const& other) noexcept {
    applyOperation(other.terms, '+');
    degree = terms[0].second;
}

void Polynomial::operator-=(Polynomial const& other) noexcept {
    applyOperation(other.terms, '-');
    degree = terms[0].second;
}

void Polynomial::operator*=(Polynomial const& other) noexcept {
    auto termsCopy = std::move(terms);
    for (auto& otherTerm : other.terms) {
        std::vector<std::pair<double, int>> tempTerms;
        for (auto& term : termsCopy) {
            tempTerms.emplace_back(term.first * otherTerm.first, term.second + otherTerm.second);
            applyOperation(tempTerms, '+');
        }
    }
}

void Polynomial::operator*=(double const& scalar) noexcept {
    for (auto& term : terms) {
        term.first *= scalar;
    }
}

Polynomial Polynomial::operator+(Polynomial const& other) const noexcept {
    Polynomial res(*this);
    res += other;
    return res;
}

Polynomial Polynomial::operator-(Polynomial const& other) const noexcept {
    Polynomial res(*this);
    res -= other;
    return res;
}

Polynomial Polynomial::operator*(Polynomial const& other) const noexcept {
    Polynomial res(*this);
    res *= other;
    return res;
}

Polynomial Polynomial::operator*(double const& scalar) const noexcept {
    Polynomial res(*this);
    res *= scalar;
    return res;
}

Polynomial Polynomial::operator-() const noexcept {
    Polynomial res(*this);
    for (auto& term : res.terms) {
        term.first *= -1;
    }
    return res;
}

bool Polynomial::operator==(Polynomial const& other) const noexcept {
    return terms == other.terms;
}

bool Polynomial::operator!=(Polynomial const& other) const noexcept {
    return !operator==(other);
}

double Polynomial::operator()(double const& x) const noexcept {
    double result = 0;
    for (auto const& term : terms) {
        result += term.first * std::pow(x, term.second);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, Polynomial const& polynomial) {
    os << polynomial.toString();
    return os;
}