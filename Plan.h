#ifndef PLAN_H

#include "Formula.h"
#include "vector"

using namespace std;

class Plan {
private:
    vector<Formula> formulas; // Collection of formulas

public:
    // Constructor without arguments
    // Preconditions: None
    // Postconditions: Initializes an empty Plan object.
    Plan();

    // constructor with argument
    // Preconditions: None
    // Postconditions: Initializes the Plan with the provided formulas.
    Plan(const vector<Formula> &formulas);

    // copy constructor
    // Precondition: other must be   a valid Plan object.
    // Postconditions: Creates a new Plan object as a copy of the given Plan.
    Plan(const Plan &other);

    // move Constructor
    // Preconditions: other must be a valid Plan object.
    // Postconditions: Moves the contents from the other Plan to this Plan.
    Plan(Plan &&other) noexcept;

    // copy assignment operator
    // Preconditions: other must be a valid Plan object.
    // Postconditions: Assigns the contents of other to this Plan, replacing its current contents.
    Plan &operator=(Plan &other);

    // move assignment operator
    // Preconditions: other must be a valid Plan object.
    // Postconditions: Moves the contents from the other Plan to this Plan, replacing its current contents.
    Plan &operator=(Plan &&other) noexcept;

    // Destructor
    // Preconditions: None
    // Postconditions: Cleans up resources used by the Plan (handled automatically).
    ~Plan();

    // Add a new formula to the end of the sequence
    // Preconditions: formula must be a valid Formula object.
    // Postconditions: Adds the formula to the end of the formulas vector.
    void addFormula(const Formula &formula);

    // Remove the last formula from the sequence
    // Preconditions: The formulas vector must not be empty.
    // Postconditions: Removes the last formula from the formulas vector.
    void removeLastFormula();

    // Replace a formula at a specified index
    // Preconditions: index must be within the bounds of the formulas vector.
    // Postconditions: Replaces the formula at the specified index with the given formula.
    void replaceFormula(int index, const Formula &formula);

    // Apply all formulas in the sequence
    // Preconditions: None
    // Postconditions: Applies each formula in the sequence and outputs the results to the console.
    void applyAll() const;
};

#endif
