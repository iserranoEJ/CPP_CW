#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

// Do not add any #include statements to this file


using uint = unsigned int;

class SudokuSquareSet {
private:
public:
    uint binValues;
    int nValues;

        class iterator{
        private:
            SudokuSquareSet* setPtr;
            uint itPos;

        public:


            iterator(SudokuSquareSet* setPtrIn, const uint itPos = 32)
            : setPtr(setPtrIn), itPos(itPos){
                if(itPos!=32) {
                    itBegin();
                }
            };
            void itBegin(){
                for (int i = 0; i < sizeof(setPtr->binValues) * 8 - 1 ; ++i) {
                    uint bitMask = 1 << i;
                    if ((setPtr->binValues & bitMask) == bitMask) {
                        itPos = i;
                        return;
                    }
                }
                itPos = 32;
            }
            iterator end(){
                iterator endIt(setPtr, 32);
                return endIt;
            }


            iterator operator++(){
                do {
                    ++itPos;
                    if(itPos == 32){
                        return end();
                    }
                }
                while ((setPtr->binValues & (1 << itPos)) == 0);
                return *this;
            }
            iterator operator--(){
                while ((setPtr->binValues & (1 << itPos)) == 0 && itPos != -1){
                    --itPos;
                }
                return  *this;
            }
            uint operator*() const {
                return 1+itPos;
            }
            bool operator==(const iterator & other) const{
                return itPos == other.itPos && setPtr == other.setPtr;
            }
            bool operator==(iterator & other){
                return itPos == other.itPos && setPtr == other.setPtr;
            }
            bool operator!=(const iterator & other) {
                return itPos != other.itPos || setPtr != other.setPtr;
            }
            bool operator!=(iterator & other) {
                return itPos != other.itPos || setPtr != other.setPtr;
            }

            iterator itInsert(int value){
                uint bitMask = 1<<(value-1);
                if((setPtr->binValues & bitMask) != bitMask) {
                    itPos = value;
                    setPtr->nValues++;
                    setPtr->binValues = (setPtr->binValues | bitMask);
                }else{
                    itPos = (value-1);
                }
                return *this;
            }
            void itErase(int value){
                uint bitMask = 1<<(value-1);
                if((setPtr->binValues & bitMask) == bitMask){
                    setPtr->nValues--;
                    // Self note: ^ means XOR (1->0 & 0->1)
                    setPtr->binValues = (setPtr->binValues ^ bitMask);
                    if ((value-1 < 0)){
                        itBegin();
                    }else {
                        itPos = value - 2;
                    }
                }
            }
            iterator itFind(int value){
                uint bitMask = 1<<(value-1);
                if((setPtr->binValues & bitMask) == bitMask){
                    itPos = value-1;
                    return *this;
                }
                return end();
            }


        };

    SudokuSquareSet(){
        binValues = 0;
        nValues = 0;
    }
    explicit SudokuSquareSet(const int size): nValues(size), binValues(0){
        for (int i = 0; i<size; ++i){
            binValues += (1<<i);
        }
    }

    int size() const{
        return nValues;
    }
    bool empty() const{
        return  nValues == 0;
    }
    void clear(){
        binValues = 0;
        nValues = 0;
    }
    bool operator==(const SudokuSquareSet & other) const{
        return binValues == other.binValues;
    }

    bool operator!=(const SudokuSquareSet & other) const{
        return binValues != other.binValues;
    }
    bool  operator<(const SudokuSquareSet & other) const{
        return binValues < other.binValues;
    }
    bool  operator<(SudokuSquareSet & other) {
        return binValues < other.binValues;
    }
     iterator begin(){
         iterator it(this);
        it.itBegin();
        return it;
    }
    iterator begin() const{
        // Without const cast SudokuSquareSet would loose its const qualifier.
        iterator it(const_cast<SudokuSquareSet*>(this));
        it.itBegin();
        return it;

    }
    iterator end(){
        iterator it(this,32);
        return it;
    }
    iterator end() const{
        iterator it(const_cast<SudokuSquareSet*>(this),32);
        return it;
    }

iterator insert(int value){
    iterator it(this);
    it.itInsert(value);

    return it;

}
iterator find(int value){
    iterator it(this);
    return it.itFind(value);

}
void erase(int value){
    iterator it(this);
    it.itErase(value);

}
void erase(iterator & it){
    erase(*it);
}

};


// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
