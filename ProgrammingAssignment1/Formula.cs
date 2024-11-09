// Author: Anjali Sambhaji Tambe
// File: Formula.cs
// Date: 12/11/2024
// Version: Mac , Rider
// Specification file for Formula class

// Purpose: The Formula class converts given input resources into output
//          resources. It uses a proficiency level and probability mechanism
//          to modify output resources.
//          The class allows clients to simulate different outcome according to
//          predefined probabilities and proficiency level. 
using System;
using System.Collections.Generic;

namespace FormulaProject;

//class Invariants :
//Inputs and outputs must not be null.
//Input and output quantities must be non-negative.
//Proficiency level must always be between 0 and maxProficiencyLevel which defined
//Random chance determines the output multiplier for each formula application.
//Once initialized, inputs and outputs cannot be modified by external code.

public enum FormulaOutcome
{
    Fail,    // Represents a failure (0 output)
    Partial, // Represents partial output (e.g., 75% output)
    Normal,   // Represents normal output (100% output)
    Bonus   // Represents bonus output (e.g., 110% or 120% output)
}

public class Formula
{
    private const int MaxProficiencyLevel = 2; // MaxProficiencyLevel is set as 2 
    private readonly Dictionary<string, int> _inputs; // Dictionary to store input resources
    private readonly Dictionary<string, int> _outputs;// Dictionary to store output resources
    private int _proficiencyLevel; // proficiencyLevel can influence the output of applying formula
    private static Random random = new Random(); // create an instance random so it will create random numbers
    private readonly FormulaOutcome? _outcomeOverride;  // optional outcome override to control the outcome
    
    //constructor for the Formula class with the optional outcomeOverride parameter
    //Precondition: input and output quantities must not be null
    //postcondition: the formula object is initialized with validated inputs and outputsÏ
    public Formula(Dictionary<string, int> inputs, Dictionary<string, int> outputs, FormulaOutcome? outcomeOverride=null)
    {
        if (inputs == null || outputs == null)
        {
            throw new ArgumentException("Inputs and outputs can not be null");
        }

        foreach (var quantity in inputs.Values)
        {
            if (quantity < 0)
            {
                throw new ArgumentException(" input Quantities can not be negative");
            }
        }
        
        foreach (var quantity in outputs.Values)
        {
            if (quantity < 0)
            {
                throw new ArgumentException(" output Quantities can not be negative");
            }
        }
    
        _inputs = new Dictionary<string ,int> (inputs); //Assigning the inputs values
        _outputs = new Dictionary<string, int> (outputs);// Assigning the output values
        _proficiencyLevel = 0;   // firstly initializing the proficiency level to 0
        _outcomeOverride = outcomeOverride;   //assign he optional outcome override
    }
    //public method GetInputs() to query inputs
    //Postcondition : return the dictionary of inputs means name and quantity of resource
    public Dictionary<string, int> GetInputs()
    {
        return new Dictionary<string, int> (_inputs);
    }

    //public method GetOutputs() to query outputs
    //Postcondition : return the dictionary of outputs means name and quantity of resource
    public Dictionary<string, int> GetOutputs()
    {
        return new Dictionary<string, int> (_outputs);
    }
    
    //Apply the formula to determine the result based on proficiency level and random chance
    //Postcondition: Returns the transformed output with adjusted quantities based on the formula's chance
    public Dictionary<string, int> Apply()
    {
        Double multiplier;
        
        //use the outcomeOverride if it is set
       if(_outcomeOverride.HasValue) 
       {
            multiplier = GetMultiplier(_outcomeOverride.Value);
       }
       else
       {
           double chance = random.NextDouble();  // generate the number between 0 and 1
           multiplier = GetMultiplier(GetMultiplierBasedOnProficiencyLevel(chance));
       }

       Dictionary<string, int> result = new Dictionary<string, int>();  // newDictionary to hold calculated output 

       foreach (var output in _outputs)
       {
           int newQuantity = (int)Math.Round(output.Value * multiplier); // it will give whole number
           result[output.Key] = newQuantity;
       }
       return result;     //Return final output result
    }

    // Determines the output multiplier based on the proficiency level and chance
    // Precondition: Chance must be between 0 and 2.
    // Postcondition: Returns the multiplier (0, 0.75, 1, or bonus multiplier) based on proficiencyLevel
    private FormulaOutcome GetMultiplierBasedOnProficiencyLevel(double chance)
    {
        if (_proficiencyLevel == 0)
        {
            if (chance < 0.25) return FormulaOutcome.Fail;
            if (chance < 0.50) return FormulaOutcome.Partial;
            if (chance < 0.95) return FormulaOutcome.Normal;
            return FormulaOutcome.Bonus;
        }

        if (_proficiencyLevel == 1)
        {
            if (chance < 0.25) return FormulaOutcome.Fail;
            if(chance < 0.45) return FormulaOutcome.Partial;
            if (chance < 0.95) return FormulaOutcome.Normal;
            return FormulaOutcome.Bonus;
        }
        
        if (_proficiencyLevel == 2)
        {
            if (chance < 0.15) return FormulaOutcome.Fail;
            if(chance < 0.30) return FormulaOutcome.Partial;
            if (chance < 0.85) return FormulaOutcome.Normal;
            return FormulaOutcome.Bonus;
        }

        return FormulaOutcome.Normal;
    }

    // Increases the proficiency level by 1, up to the maximum level
    // Precondition: Proficiency level must not exceed maxProficiencyLevel.
    // Postcondition: Proficiency level is incremented by 1, unless already at max level.
    public void IncreaseProficiencyLevel()
    {
        if (_proficiencyLevel <= MaxProficiencyLevel)
        {
            _proficiencyLevel++;
        }
        else
        {
            throw new InvalidOperationException("proficiency is already at maximum level");
        }
    }

    // Returns the current proficiency level
    // Postcondition: The current proficiency level is returned
    public int GetProficiencyLevel()
    {
        return _proficiencyLevel;
    }
    
    // Returns double mapped to outcome enum
    //precondition: methods excepts the valid formulaOutcome enum value as input
    //postcondition: returns the double alue corresponding o the given formulaOutcome
    private double GetMultiplier(FormulaOutcome outcome)
    {
        switch (outcome)
        {
            case FormulaOutcome.Fail:
                return 0.0;    // Fail = 0 output
            case FormulaOutcome.Partial:
                return 0.75;   // 75% output
            case FormulaOutcome.Normal:
                return 1.0;    // 100% output
            case FormulaOutcome.Bonus:
                return 1.1;    // 110% output
            default:
                return 1.0;    // Default
        }
    }
    
    // Implementation Invariants:
    // - The proficiency level must always remain between 0 and maxProficiencyLevel.
    // - Inputs and outputs remain immutable after object creation.
    // - Random chance is used for output calculations and cannot be manipulated directly by clients.
}