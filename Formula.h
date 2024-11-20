#ifndef FORMULA_H
#define FORMULA_H

#include <unordered_map>
#include <vector>

using namespace std;

class Formula {
private:
    unordered_map<string, int> inputs;   //  store Input resources and their quantities
    unordered_map<string, int> outputs;   //  store Output resources and their quantities
    int maxProficiencyLevel = 2;         // Maximum proficiency level

    double getMultiplierBasedOnProficiencyLevel(double chance) const; //Calculate multiplier based on proficiency level

public:
    //constructor for Formula class
    // Preconditions:
    //   - inputs must not be empty.
    //   - outputs must not be empty.
    // Postconditions:
    //   - A Formula object is constructed with initialized inputs and outputs.
    Formula(const unordered_map<string, int> inputs, const unordered_map<string, int> outputs);

    //getters for inputs resources
    // Preconditions: None
    // Postconditions: Returns a map of input resources.
    unordered_map<string, int> getInputs() const;

    //getters for output resources
    // Preconditions: None
    // Postconditions: Returns a map of output resources.
    unordered_map<string, int> getOutputs () const;

    // Apply method
    // Preconditions: inputs and outputs must be properly initialized.
    // Postconditions: Returns a map of output resources after applying the formula.
    unordered_map<string, int> apply() const;

    // Increase proficiency level
    // Preconditions: Proficiency level is less than maxProficiencyLevel.
    // Postconditions :Proficiency level is incremented by 1.
    void increaseProficiencyLevel();


    // Get current proficiency level
    // Preconditions: None
    // Postconditions: Returns the current proficiency level.
    int getProficiencyLevel();

    // Current proficiency level
    int proficiencyLevel;

    //Destructor for formula
    ~Formula() = default;
};

#endif
