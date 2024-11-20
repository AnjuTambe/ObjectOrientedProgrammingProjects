// plan.cpp
#include "Plan.h"
#include <iostream>

///////////////////////////////////////////////////Class Invariants///////////////////////////////////////////////////
// The formulas Vector Contains Only Valid Formula Objects: Each entry in the formulas vector must be a properly    //
// constructed Formula object. The addFormula method enforces this by requiring a valid Formula as input.           //
// The formulas Vector Must Not Contain Null or Invalid Entries: Each element of the formulas vector must be valid, //
// ensuring that the Plan class can operate on each Formula correctly.                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

// Default Constructor
Plan::Plan() {};

// Constructor with an initial sequence of Formulas
Plan::Plan(const vector<Formula> &formulas) {
    this->formulas = formulas;
}

// Copy Constructor for the plan class
Plan::Plan(const Plan &other) {
    this->formulas = other.formulas;
}

// Move Constructor for the plan class
Plan::Plan(Plan &&other) noexcept {
    this->formulas = std::move(other.formulas);
}

// Copy Assignment For the plan class
Plan &Plan::operator=(Plan &other) {
    if (this != &other) {
        formulas = other.formulas;
    }
    return *this;
}

// Move Assignment for the plan class
Plan &Plan::operator=(Plan &&other) noexcept {
    if (this != &other) {
        formulas = std::move(other.formulas);
    }
    return *this;
}

// Destructor for the plan class
Plan::~Plan() {
    // No explicit resource management needed since vector handles memory
}

// Add a new formula to the end of the sequence
void Plan::addFormula(const Formula &formula) {
    formulas.push_back(formula);
}

// Remove the last formula from the sequence
void Plan::removeLastFormula() {
    if (!formulas.empty()) {
        formulas.pop_back();
    }
}

// Replace a formula anywhere in the sequence
void Plan::replaceFormula(int index, const Formula &formula) {
    if (index >= 0 && index < formulas.size()) {
        this->formulas[index] = formula;
    } else {
        throw out_of_range("index out of bounds");
    }
}

// Apply all formulas in the sequence
void Plan::applyAll() const {
    for (const auto &formula: formulas) {
        auto result = formula.apply();
        for (const auto &output: result) {
            cout << output.first << ": " << output.second << endl;
        }
    }
}

/////////////////////////////////////////////////////Implementation Invariants////////////////////////////////////////////
// The formulas Vector Manages Formula Objects and Handles Copies and Moves Properly: The copy constructor,             //
// move constructor, and assignment operators ensure the formulas vector retains correct ownership and state            //
// of its elements.                                                                                                     //
// Explicit Handling of Copy and Move Semantics: Copying a Plan object creates a deep copy of the formulas vector,      //
// while moving transfers ownership without duplicating data, following best practices for resource management.         //
// The applyAll Method Sequentially Applies Each Formula in the formulas Vector: The applyAll method guarantees         //
// that all Formula objects are applied in the order they were added to the vector, ensuring consistent and predictable //
// behavior.                                                                                                            //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////