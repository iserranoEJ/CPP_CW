#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"
#include <queue>
#include <memory>
using std::unique_ptr;
using std::priority_queue;
class BestFirstSearch {

protected:
    class Comparator
    {
    public:
        bool operator() (unique_ptr<Searchable> const& lhs, unique_ptr<Searchable> const& rhs)
        {
            return lhs->heuristicValue() < rhs->heuristicValue();
        }
    };

    priority_queue<unique_ptr<Searchable>,vector<unique_ptr<Searchable>>, Comparator > Q;
    /// Make sure you increment this every time you 'expand' a node, by getting it successors and putting them on the queue        
    int nodes = 0;
    
    
public:

     BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        // TODO Put startFrom onto the queue:
        Q.push(std::move(startFrom));
        
    }
    
    int getNodesExpanded() const {
        return nodes;
    }

    Searchable * solve() {


        // If there are still incomplete solutions on the queue
        while (!Q.empty()) {

            // If the solution on the front of the queue is a solution
            if (Q.top()->isSolution()) {
                return Q.top().get(); // return the pointer
            }

            ++nodes; // we've now looked at one more node, increment our counter

            // Steal the pointer to the board at the front of the queue, by moving it into a unique_ptr here
            // After this, the pointer on the front of the queue is `nullptr`...
            auto& ptr(const_cast<unique_ptr<Searchable>&>(Q.top()));
            unique_ptr<Searchable> current(ptr.get());
            ptr.release();

            // ...which can then be popped off the front of the queue
            Q.pop();

            // Get the successors...
            vector<unique_ptr<Searchable>> successors = current->successors();

            for (auto & successor : successors) {
                // and push each one onto the back of queue.
                auto * ptr2 = successor.get();
                successor.release();
                Q.push(unique_ptr<Searchable>(ptr2));
            }
        }

        return nullptr;
    }
};


// Do not edit below this line

#endif
