#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <iomanip>
int main() {
    std::ifstream inputFile("ModEM_NLCG.log"); // 
    std::ofstream outputFile("Logfile.dat"); // 

    if (!inputFile.is_open()) {
        std::cerr << "Error opening inputfile" << std::endl;
        return 1;
    }
    outputFile  << "iteration   f   m2   rms   lambda   alpha"<< std::endl;

    std::string line;
    std::regex iterationRegex("Completed NLCG iteration\\s+(\\d+)");
    std::regex fRegex("f=([\\d.E+-]+)");
    std::regex m2Regex("m2=([\\d.E+-]+)");
    std::regex rmsRegex("rms=\\s+([\\d.]+)");
    std::regex lambdaRegex("lambda=([\\d.E+-]+)");
    std::regex alphaRegex("alpha=([\\d.E+-]+)");

    while (std::getline(inputFile, line)) {
        std::smatch match;
        if (std::regex_search(line, match, iterationRegex)) {
            int iteration = std::stoi(match[1]);
            std::string fValue, m2Value, rmsValue, lambdaValue, alphaValue;

            //  f, m2, rms, lambda, alpha
            std::getline(inputFile, line);
            std::smatch fMatch, m2Match, rmsMatch, lambdaMatch, alphaMatch;
            if (std::regex_search(line, fMatch, fRegex)) {
                fValue = fMatch[1];
            }
            if (std::regex_search(line, m2Match, m2Regex)) {
                m2Value = m2Match[1];
            }
            if (std::regex_search(line, rmsMatch, rmsRegex)) {
                rmsValue = rmsMatch[1];
            }
            if (std::regex_search(line, lambdaMatch, lambdaRegex)) {
                lambdaValue = lambdaMatch[1];
            }
            if (std::regex_search(line, alphaMatch, alphaRegex)) {
                alphaValue = alphaMatch[1];
            }

            // check
            if (!fValue.empty() && !m2Value.empty() && !rmsValue.empty() && !lambdaValue.empty() && !alphaValue.empty()) {
                outputFile << iteration << " " << fValue << " " << m2Value
                    << " " << rmsValue << " " << lambdaValue
                    << " " << alphaValue << std::endl;
            }
            else {
                std::cerr << "Something Error!" << std::endl;
            }
        }
    }


    inputFile.close();
    outputFile.close();

    std::cout << "Logfile.dat extracted successfully" << std::endl;


    return 0;
}