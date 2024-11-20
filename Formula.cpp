#include "Formula.h"
#include "cmath"
#include "random"
#include <iostream>

////////////////////////Class Invariants//////////////////
//inputs and Outputs Must Not Be Empty: The inputs and outputs maps must contain at least one valid entry.
// If either is empty, the constructor will throw an exception.
//Input and Output Quantities Must Be Non-Negative: Each quantity in the inputs and outputs maps must be greater than
// or equal to 0. Negative values are not allowed.
//Input and Output Resource Names Must Not Be Empty: The keys in the inputs and outputs maps
// (representing resource names) must not be empty strings.
//Proficiency Level Must Be Between 0 and maxProficiencyLevel: The proficiencyLevel must always be within the valid
// range, from 0 up to maxProficiencyLevel. Any attempt to exceed this range is disallowed.
//Inputs and Outputs Are Immutable After Initialization: Once the Formula object is created, the inputs and outputs
// cannot be modified by external code, preserving the integrity of the object's state.


using namespace std;

// Constructor for formula class
Formula::Formula(const unordered_map<string, int> inputs,
                 const unordered_map<string, int> outputs) {
    if (inputs.empty() || outputs.empty()) {
        throw invalid_argument("inputs and outputs can not be null");
    }
    for (const auto &quantity: inputs) {
        if (quantity.first.empty()) {
            throw invalid_argument("Input resource names can not be empty");
        }
        if (quantity.second < 0) {
            throw invalid_argument("Input quantities can not be neg");
        }
    }

    for (const auto &quantity: outputs) {
        if (quantity.first.empty()) {
            throw invalid_argument("Output resource names can not be empty");
        }
        if (quantity.second < 0) {
            throw invalid_argument("Output quantities can not be neg");
        }
    }

    this->inputs = inputs;
    this->outputs = outputs;
    proficiencyLevel = 0;  // Initial proficiency level set to 0
}

// Get the inputs
// Preconditions: None
// Postconditions: Returns the inputs map
unordered_map<string, int> Formula::getInputs() const {
    return inputs;
}

// Get the outputs
// Preconditions: None
// Postconditions: Returns the outputs map
unordered_map<string, int> Formula::getOutputs() const {
    return outputs;
}

// Apply the formula and adjust based on proficiency
// Preconditions: inputs and outputs must be properly initialized.
// Postconditions: Returns a map of adjusted output resources.
unordered_map<string, int> Formula::apply() const {
    random_device generator;
    double chance = uniform_real_distribution<double>(0.0, 1.0)(generator);
    double multiplier = getMultiplierBasedOnProficiencyLevel(chance);

    unordered_map<string, int> result;

    for (const auto &output: outputs) {
        int newQuantity = static_cast<int>(round(output.second * multiplier));
        result[output.first] = newQuantity;
    }
    return result;
}

// Increase proficiency level
void Formula::increaseProficiencyLevel() {
    if (proficiencyLevel < maxProficiencyLevel) {
        proficiencyLevel++;
    }
}

// Get current proficiency level
int Formula::getProficiencyLevel() {
    return proficiencyLevel;
}

// Private method to determine multiplier based on chance
double Formula::getMultiplierBasedOnProficiencyLevel(double chance) const {
    if (proficiencyLevel == 0) {
        if (chance < 0.25) return 0;
        if (chance < 0.50) return 0.75;
        if (chance < 0.95) return 1.0;
        return 1.1;
    } else if (proficiencyLevel == 1) {
        if (chance < 0.25) return 0;
        if (chance < 0.45) return 0.75;
        if (chance < 0.95) return 1.0;
        return 1.1;
    } else if (proficiencyLevel == 2) {
        if (chance < 0.15) return 0;
        if (chance < 0.30) return 0.75;
        if (chance < 0.85) return 1.0;
        return 1.2;
    }

    return 1.0;  // Default to 1
}

//////////////////Implementation Invariants////////////////////
//Proficiency Level Remains Between 0 and maxProficiencyLevel: The increaseProficiencyLevel method ensures the
// proficiencyLevel does not exceed the allowed maximum.
//Inputs and Outputs Remain Immutable After Object Creation: The inputs and outputs maps are set during construction
// and are not modified thereafter, ensuring the consistency of these values.
//Random Chance Is Used for Output Calculations and Cannot Be Manipulated Externally: The apply method internally
// generates random values, which influence the formula's output adjustments. This randomness is managed within the
// class and cannot be directly controlled by clients

