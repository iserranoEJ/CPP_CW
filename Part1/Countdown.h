#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
using std::string;
using std::to_string;
using std::stod;

#include <sstream>
using std::istringstream;
#include <utility>
#include<vector>
using std::vector;

#include <stack>
using std::stack;

#include <unordered_set>
using std::unordered_set;

#include <algorithm>
#include <map>
using std::map;
#include <iostream>
using std::cout;
using std::endl;
#include <iostream>
#include <set>
using std::set;

#include <cmath>


// this is provided code for the last part of the README

string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {

private:
    string solution;
    int value;

public:

    CountdownSolution() : solution(), value(0) {}

    CountdownSolution(string  solutionIn, const int valueIn)
            : solution(std::move(solutionIn)), value(valueIn) {
    }

    const string & getSolution() const {
        return solution;
    }

    int getValue() const {
        return value;
    }

};

// Do not edit above this line


bool is_number(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && (*it == '.' || std::isdigit(*it))) {
       //cout << *it << endl;
        ++it;
    };
    return !s.empty() && it == s.end();
}

const vector<string> op_exp = { "+", "-", "*", "/", " "};



void tokenize(std::string const &str, const char delim,
              std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

bool isCorrectRPN(const string & str) {
    vector<string> parsed;
    tokenize(str,' ', parsed);

    int ssize = 0;
    for (const string& token : parsed) {
        if (token == "+" or token == "-" or token == "*" or token == "/") {
            ssize -= 1;
        }
            //is a number
        else if (token != " ") {
            ssize += 1;
        }
    }
    return ssize == 1;
}



double evaluateCountdown(string str) {
    vector<string> parsedInput;
    tokenize(str, ' ', parsedInput);

    stack<double> expression={};

    for (const auto& token : parsedInput) {
        if (is_number(token)) {
            expression.push(stod(token));
        }

        else if (token != " ") {
            double x = expression.top();
            //cout << expression.top()<< endl;
            expression.pop();
                double y = expression.top();
                expression.pop();
                if (token == "+") {
                    expression.push(x + y);
                }
                if (token == "-") {
                    expression.push(y - x);
                }
                if (token == "*") {
                    expression.push(x * y);
                }
                if (token == "/") {
                    expression.push(y / x);
                }
            }
        }


    return expression.top();

}
string vectorToString(const vector<string> & v){
    std::string s;
    for (const auto &piece : v) {
        if(piece != " ") {
            s += piece;
            s += " ";
        }
    }
    //cout << s << endl;
    return s;
}
string attempt;
double choices(const vector<string>& inp, vector<string>& current, uint& nValues,
             unordered_set<int>& inUse, const int target, bool& found) {


    if (!found) {
        if (!current.empty() and evaluateCountdown(vectorToString(current)) == target) {

            found = true;
            attempt = vectorToString(current);
            return  evaluateCountdown(attempt);
        }

        else if (nValues < inp.size()) {
            for (int i = 0; i < inp.size(); i++) {
                for (const auto& op : op_exp) {
                    if (inUse.find(i) == inUse.end()) {
                        inUse.insert(i);
                        current.push_back(inp[i]);
                        current.push_back(op);
                        nValues++;
                        if (isCorrectRPN(vectorToString(current))) {
                            choices(inp, current, nValues, inUse, target, found);
                        }
                        nValues--;
                        inUse.erase(i);
                        current.pop_back();
                        current.pop_back();
                    }
                }
            }
        }
    }
}
CountdownSolution solveCountdownProblem(vector<int> & v, int target) {
    vector<string> vs;
    vector<string> current;
    unordered_set<int> inUse;
    uint nValues = 0;
    bool found = false;
    vs.reserve(v.size());
for(auto e: v){
        vs.push_back(intToString(e));
    }

    if(choices(vs,current, nValues, inUse, target, found) == target ) {
    }
        return CountdownSolution(attempt, choices(vs, current, nValues, inUse, target, found));


}


// Do not edit below this line


#endif

