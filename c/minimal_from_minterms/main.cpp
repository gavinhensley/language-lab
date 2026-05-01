/*
 * File: main.cpp
 * 
 * Title: Quine-McCluskey Algorithm
 *
 * Description:
 * This program finds the minimal boolean expression from a set of minterms 
 * or maxterms using the Quine-McCluskey boolean minimization technique.
 *
 * Inputs:
 * - Number of variables (>1)
 * - Choice of minterms (0) or maxterms (1)
 * - A comma-separated list of terms (e.g. 0,1,3,5)
 *
 * Outputs:
 * - Displays the minimal sum of products (SOP) 
 *   and product of sums (POS) boolean expressions.
 *
 * Dependencies:
 * <iostream>, <cmath>, <vector>, <sstream>, <algorithm>
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>

enum {
    MINTERMS = 0,
    MAXTERMS = 1
};

int get_numVariables() {
    int numVariables;
    do {
        std::cout << "Number of variables (>1): ";
        std::cin >> numVariables;
    } while (numVariables <= 1);
    return numVariables;
}

bool get_termType() {
    bool termType;
    do {
        std::cout << "Minterms (0) or maxterms (1): ";
        std::cin >> termType;
    } while ((termType != MINTERMS) and (termType != MAXTERMS));
    return termType;
}

std::vector<int> get_vterms(bool termType) {
    std::string vtermsInput;
// input terms in as a comma seperated list
    if (termType == MINTERMS)
        std::cout << "Enter minterms as a comma seperated list (i.e. 0, 1, 3, 5, 7): ";
    else
        std::cout << "Enter maxterms as a comma seperated list (i.e. 2, 4, 6): ";

    std::cin.ignore();
    getline(std::cin, vtermsInput);

    // filter input
    std::vector<int> vterms;
    std::stringstream ss(vtermsInput);
    std::string token;

    while (std::getline(ss, token, ',')) {
        vterms.push_back(std::stoi(token));
    }
    return vterms;
}

void printVector(std::vector<int> vterms) {
    // print vector
    std::cout << "[";
    for (size_t i = 0; i < vterms.size(); i++) {
        std::cout << vterms[i];
        if (i < vterms.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n" << std::endl;
    return;
}

std::vector<int> getTerms(bool termRequested, int maxNumTerms, bool termType, std::vector<int> vterms) {
    // when termType is 0, the vterms vector contains the minterms
    std::vector<int> minterms;
    std::vector<int> maxterms;
    if (termType == MINTERMS) {
        minterms = vterms;
        for (int i = 0; i < maxNumTerms; i++) {
            if (not (std::find(minterms.begin(), minterms.end(), i) != minterms.end()))
                maxterms.push_back(i);
        }
    } else {
        maxterms = vterms;
        for (int i = 0; i < maxNumTerms; i++) {
            if (std::find(maxterms.begin(), maxterms.end(), i) == maxterms.end())
                minterms.push_back(i);
        }
    }

    if (termRequested == MINTERMS) {return minterms;}
    else {return maxterms;}
}

void QuineMcCluskey(int numVariables, int maxNumTerms, bool termType, std::vector<int> vterms) {
    std::vector<int> minterms = getTerms(MINTERMS, maxNumTerms, termType, vterms);
    std::vector<int> maxterms = getTerms(MAXTERMS, maxNumTerms, termType, vterms);

    std::cout << "code is working" << std::endl;
    return;
}


int main() {
    int numVariables = get_numVariables();
    bool termType = get_termType();
    std::vector<int> vterms = get_vterms(termType);

    int maxNumTerms = pow(2, numVariables);
    
    std::cout << "Minterms: ";
    printVector(getTerms(MINTERMS, maxNumTerms, termType, vterms));    

    QuineMcCluskey(numVariables, maxNumTerms, termType, vterms);
    std::cout << std::endl;

    return 0;
}