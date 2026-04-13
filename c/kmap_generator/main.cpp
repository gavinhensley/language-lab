/*
 * File: main.cpp
 * 
 * Title: Karnaugh Map Generator
 *
 * Description:
 * This program constructs and displays a Karnaugh map based on a set of 
 * minterms or maxterms. It converts between minterms and maxterms as needed 
 * and fills the K-map using Gray code ordering.
 *
 * Inputs:
 * - Number of variables (>1)
 * - Choice of minterms (0) or maxterms (1)
 * - A comma-separated list of terms (e.g. 0,1,3,5)
 *
 * Outputs:
 * - Displays the generated Karnaugh map with correctly placed 1s and 0s
 *
 * Dependencies:
 * <iostream>, <cmath>, <vector>, <sstream>, <algorithm>
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>

// gray code function
// desc: Converts any binary number into gray code.
// pre:  Input must be an int.
// post: Returns the gray code equivalent of the input.
unsigned int decimalToGray(int decimalNum) {
    return decimalNum ^ (decimalNum >> 1); // The operator >> is shift right. The operator ^ is exclusive or.
}

// k-map function
// desc: Converts min/maxterms into a k-map.
// pre:  numVariables > 1, the length of terms[] must be <= 2^numVariables.
// post: Prints the k-map for the input terms.
void karnaughMap(int numVariables, int maxNumTerms, bool termType, std::vector<int> vterms) {
    // the value of numVariables determines the number of rows and columns for the k-map
    int rows;
    int columns;
    int varsLeft;
    int varsRight;
    if (numVariables % 2 == 0) {
        rows = pow(2, numVariables/2);
        columns = pow(2, numVariables/2);
        varsLeft = numVariables / 2;
        varsRight = numVariables / 2;
    } else {
        rows = pow(2, (numVariables - 1)/2);
        columns = pow(2, (numVariables + 1)/2);
        varsLeft = (numVariables - 1) / 2;
        varsRight = (numVariables + 1) / 2;
    }

    // when termType is 0, the vterms vector contains the minterms
    std::vector<int> minterms;
    std::vector<int> maxterms;
    if (termType == 0) {
        minterms = vterms;
        for (int i = 0; i < maxNumTerms; i++) {
            if (not (std::find(minterms.begin(), minterms.end(), i) != minterms.end()))
                maxterms.push_back(i);
        }
    } else {
        maxterms = vterms;
        for (int i = 0; i < maxNumTerms; i++) {
            if (std::find(maxterms.begin(), maxterms.end(), i) != maxterms.end())
                minterms.push_back(i);
        }
    }

    unsigned int aterms[rows][columns];
    unsigned int grayRow;
    unsigned int grayCol;
    unsigned int decimalTerm;
    std::vector<std::string> vSOP;
    std::vector<std::string> vPOS;
    std::string sSOP;
    std::string sPOS;

    // print the first 9 columns or so
        std::cout << "  ";
    if (columns > 9) {
        for (int i = 0; i <= 9; i++) {
            std::cout << i << " ";
        }
    } else {
        for (int i = 0; i < columns; i++) {
            std::cout << i << " ";
        }
    }
        std::cout << std::endl;

    for (int currentRow = 0; currentRow < rows; currentRow++) {
        
        // print the first 9 rows
        if (rows > 9) {
            if (currentRow <= 9)   
                std::cout << currentRow << " ";
            else
                std::cout << "  ";
        } else {
            if (currentRow <= rows)   
                std::cout << currentRow << " ";
            else
                std::cout << "  ";
        }
        for (int currentColumn = 0; currentColumn < columns; currentColumn++) {
            grayRow = decimalToGray(currentRow);
            grayCol = decimalToGray(currentColumn);
            grayRow = grayRow << varsRight;
            decimalTerm = grayRow | grayCol;
            if (termType == 0) {
                // if decimalTerm is in the vector minterms, put a 1 at aterms[currentRow][currentColumn]
                if (std::find(minterms.begin(), minterms.end(), decimalTerm) != minterms.end()) {
                    aterms[currentRow][currentColumn] = 1;
                    std::cout << "1 ";
                } else { 
                    aterms[currentRow][currentColumn] = 0;
                    std::cout << "0 ";
                }
            } else {
                // if decimalTerm is in the vector maxterms, put a 0 at aterms[currentRow][currentColumn]
                if (std::find(maxterms.begin(), maxterms.end(), decimalTerm) != maxterms.end()) {
                    aterms[currentRow][currentColumn] = 0;
                    std::cout << "0 ";
                } else { 
                    aterms[currentRow][currentColumn] = 1;
                    std::cout << "1 ";
                }
            }
        }
        std::cout << std::endl;
    }

}


int main() {
    int numVariables;
    bool termType;
    std::string vtermsInput;
    
    do {
        std::cout << "Number of variables (>1): ";
        std::cin >> numVariables;
    } while (numVariables <= 1);

    int maxNumTerms = pow(2, numVariables);

    do {
        std::cout << "Minterms (0) or maxterms (1): ";
        std::cin >> termType;
    } while ((termType != 0) and (termType != 1));
    
    // input terms in as a comma seperated list
    if (termType == 0)
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

    // print vector
    std::cout << "[";
    for (size_t i = 0; i < vterms.size(); i++) {
        std::cout << vterms[i];
        if (i < vterms.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n" << std::endl;
    
    karnaughMap(numVariables, maxNumTerms, termType, vterms);
    std::cout << std::endl;

    // std::cout << "\ncode is working" << std::endl;
    return 0;
}