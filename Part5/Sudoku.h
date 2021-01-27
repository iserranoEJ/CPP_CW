#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include "SudokuSquare.h"
#include <vector>
#include <set>
#include <math.h>
#include <iostream>
#include <unordered_map>
using std::cout;
using std::vector;
using std::set;

using SudokuMatrix = vector<vector<SudokuSquareSet>>;

class Sudoku : public Searchable {
private:
    const int SIZE;
    SudokuMatrix board;
public:
    Sudoku(const int n) : SIZE(n), board (SudokuMatrix(n, vector<SudokuSquareSet>(n))) {
        for (auto &row : board) {
            for (auto &col : row) {
                for (int i = 1; i <= SIZE; i++) {
                    col.insert(i);
                }
            }
        }
    }



    void write(ostream& o) const override {
        for (const auto& row : board) {
            for (const auto& s : row) {
                if (s.size() == 1) o << *s.begin();
                else o << " ";
            }
            o << "\n";
        }
        o << "\n";
    }


    int getSquare(int row, int col){
        if (board[row][col].size() == 1) {
            return *board[row][col].begin();
        }
        return -1;
    }
    //Unable to push?

    bool setSquare(int row, int col, int value) {
        vector<vector<bool>> done = vector<vector<bool>>(SIZE,  vector<bool>(SIZE, false));

        return setSquareAux(row, col, value, done);


    }


    bool setSquareAux(int row, int col, int value, vector<vector<bool>>& done) {
        board[row][col].clear();
        board[row][col].insert(value);

        if(eraseCol(row,col,value,done) && eraseRow(row,col,value,done) && eraseSquare(row,col,value,done)){

            return true;
        }
        return false;
    }
    bool eraseCol(int row, int col, int value, vector<vector<bool>>& done){
        for (int i = 0; i < SIZE; i++) {
            if (i != col) board[row][i].erase(value);
            if (board[row][i].empty()) return false;
            if (board[row][i].size() == 1 and not done[row][i]) {
                done[row][i] = true;
                if (!setSquareAux(row, i, *board[row][i].begin(), done)) return false;
            }

        }
        return true;
    }
    bool eraseRow(int row, int col, int value, vector<vector<bool>>& done){
        for (int i = 0; i < SIZE; i++) {
            if (i != row) board[i][col].erase(value);
            if (board[i][col].empty()) return false;
            //eraseDuplicates(done);
            if (board[i][col].size() == 1 and not done[i][col]) {
                done[i][col] = true;
                if (!setSquareAux(i, col, *board[i][col].begin(), done)) return false;
            }


        }
        return true;
    }

    bool eraseSquare(int row, int col, int value, vector<vector<bool>>& done){
        int row_start = row - (row % int(sqrt(SIZE)));
        int col_start = col - (col % int(sqrt(SIZE)));
        for (int i = 0; i < int(sqrt(SIZE)); i++) {
            for (int j = 0; j < int(sqrt(SIZE)); j++) {
                if (row_start + i != row and col_start + j != col) {
                    auto it = board[row_start + i][col_start + j].find(value);
                    if (it != board[row_start + i][col_start + j].end()) {
                        board[row_start + i][col_start + j].erase(it);
                        if (board[row_start + i][col_start + j].empty()) return false;
                        if (board[row_start + i][col_start + j].size() == 1 and
                            not done[row_start + i][col_start + j]) {
                            done[row_start + i][col_start + j] = true;
                            if (!setSquareAux(row_start + i, col_start + j,
                                              *board[row_start + i][col_start + j].begin(), done))
                                return false;
                        }
                    }
                }
            }
        }
        return true;
    }


    int heuristicValue() const override{
        int nSetsGTZ = 0;
        for (const auto& r : board) {
            for (const auto& v : r) {
                if (v.size() == 1) {
                    nSetsGTZ++;
                }
            }
        }
        return nSetsGTZ;
    }

    //Override

    bool isSolution() const override {
        for (const auto& row : board) {
            for (const auto& s : row) {
                if (s.size() != 1) return false;
            }
        }
        return true;
    }

    std::pair<int , int> getFirstNonUnitary()const {
        std::pair<int,int> rowCol;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                if (board[i][j].size() > 1) {
                    rowCol.first = i;
                    rowCol.second = j;
                    return rowCol;
                }
            }
        }
        return {0,0};
    }

    vector<unique_ptr<Searchable>> successors() const override {
        vector<unique_ptr<Searchable>> res;
        std::pair<int,int> nonUnitary = getFirstNonUnitary();
        if(isSolution()){
            res.clear();
            res.emplace_back(new Sudoku(*this));
            return res;
        }
        for (auto val : board[nonUnitary.first][nonUnitary.second]) {
            auto* current = new Sudoku(*this);
            if (current->setSquare(nonUnitary.first, nonUnitary.second, val)){
                res.emplace_back(unique_ptr<Searchable> (current));
            }
            else {
                delete current;
            }


        }
        if(res.size() == 1){
            return res[0].get()->successors();
        }
        return res;
    }


    Sudoku(const Sudoku& s):
            SIZE(s.SIZE), board(s.board){};

};

#endif