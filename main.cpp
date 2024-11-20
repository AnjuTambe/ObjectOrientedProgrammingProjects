// Author: Anjali Sambhaji Tambe
// File: Driver file for formula and plan
// Date: 10/26/2024
// Version: Mac, CLion
// Specification file for Formula class and plan class

// Purpose: The objective of this assignment is to demonstrate a solid understanding of Object-Oriented Programming
// (OOP) concepts such as composition, copy semantics, and ownership in C++. The program simulates a system that
// manages Formula objects and organizes them using a Plan class. The Formula class models the conversion of input
// resources to output resources, while the Plan class manages a collection of these Formula objects.
#include "iostream"
#include "Plan.h"
#include "Formula.h"

//displaying all the inputs and outputs which you defined.
void
displayInputsAndOutputs(const unordered_map<std::string, int> &inputs, const unordered_map<std::string, int> &outputs) {
    std::cout << "Inputs:\n";
    for (const auto &input: inputs) {
        std::cout << input.first << ": " << input.second << "\n";
    }
    std::cout << "Outputs:\n";
    for (const auto &output: outputs) {
        std::cout << output.first << ": " << output.second << "\n";
    }
}

int main() {
   // Create Formula instances with different inputs and outputs
    unordered_map<string, int> inputs1{{"iron ore", 2}};
    unordered_map<string, int> outputs1{{"iron bar", 1}};
    Formula formula1(inputs1, outputs1);

    unordered_map<string, int> inputs2{{"water", 1000}};
    unordered_map<string, int> outputs2{{"hydrogen",  999},
                                        {"deuterium", 1}};
    Formula formula2(inputs2, outputs2);

    // Display initial inputs and outputs for each formula
    cout << "Formula 1 initial values:\n";
    displayInputsAndOutputs(inputs1, outputs1);

    cout << "\nFormula 2 initial values:\n";
    displayInputsAndOutputs(inputs2, outputs2);

    // Create a Plan and add Formulas to it
    Plan plan({formula1}); // Initialize with default formula1
    plan.addFormula(formula2);

    // Apply all formulas in the plan and print results
    cout << "\nApplying all formulas in the plan:\n";
    plan.applyAll();

    //Demonstrate copy and move semantics
    cout << "\nDemonstrating copy semantics:\n";
    Plan copiedPlan = plan;  // Invokes the copy constructor
    copiedPlan.applyAll();   // Should produce the same output as `plan`

    cout << "\nDemonstrating move semantics:\n";
    Plan movedPlan = move(plan);  // Invokes the move constructor
    movedPlan.applyAll();  // The original `plan` should no longer be used after this point

    // Assignment operation
    cout << "\nTesting assignment operator:\n";
    Plan anotherPlan;
    anotherPlan = copiedPlan;  // Invokes the copy assignment operator
    anotherPlan.applyAll();

    //Demonstrate removing the last formula
    // Explanation: After calling `removeLastFormula`, the size of `formulas` vector in `copiedPlan` will be
    // reduced by one.
    cout << "\nRemoving the last formula from the copied plan:\n";
    copiedPlan.removeLastFormula();  // Should remove the last added formula (formula2)
    copiedPlan.applyAll();  // Apply remaining formulas (only formula1 should be applied)

    // Demonstrate replacing a formula
    // Explanation: `replaceFormula` will keep the size of `formulas` vector unchanged but will update the
    // formula at index 0.
    cout << "\nReplacing the first formula in the copied plan with a new one:\n";
    unordered_map<string, int> inputs3{{"copper ore", 3}};
    unordered_map<string, int> outputs3{{"copper bar", 1}};
    Formula formula3(inputs3, outputs3);

    copiedPlan.replaceFormula(0, formula3);  // Replace formula1 with formula3
    copiedPlan.applyAll();  // Apply the updated formulas

    return 0;
}
