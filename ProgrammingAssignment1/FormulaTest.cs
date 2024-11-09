// Author: Anjali Sambhaji Tambe
// File: FormulaTest.cs
// Date: 12/11/24
// Version: Mac , Rider
// Unit tests for Formula class

using System;
using NUnit.Framework;
using System.Collections.Generic;
namespace FormulaProject;

[TestFixture]
public class FormulaTest
{
    [Test]
    // Test to verify failure outcome
    public void Apply_Outcome_Fail()
    {
        //create a formula with 2 iron ore input and expecting 1 iron bar output
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 1 } };
        Formula formula = new Formula(inputs, outputs, FormulaOutcome.Fail);
        var result = formula.Apply();
        
        Assert.That(result["Iron bar"], Is.EqualTo(0));
    }

    [Test]
    // Test to verify partial outcome
    public void Apply_Outcome_Partial()
    {
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 10 } };
        Formula formula = new Formula(inputs, outputs, FormulaOutcome.Partial);
        var result = formula.Apply();
        
        Assert.That(result["Iron bar"], Is.LessThan(10));
        Assert.That(result["Iron bar"], Is.GreaterThan(0));
    }

    [Test]
    // Test to verify normal outcome
    public void Apply_Outcome_Normal()
    {
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 10 } };
        Formula formula = new Formula(inputs, outputs, FormulaOutcome.Normal);
        var result = formula.Apply();
        
        Assert.That(result["Iron bar"], Is.EqualTo(10));
    }

    [Test]
    // Test to verify bonus outcome
    public void Apply_Outcome_Bonus()
    {
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 10 } };
        Formula formula = new Formula(inputs, outputs, FormulaOutcome.Bonus);
        var result = formula.Apply();
        
        Assert.That(result["Iron bar"], Is.GreaterThan(10));
    }
    
    [Test]
    // Test to verify random outcome based on the generated chance at runtime
    public void Apply_Outcome_Random()
    {
        //create a formula with 2 iron ore input and expecting 1 iron bar output
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 1 } };
        Formula formula = new Formula(inputs, outputs);
        
        //Apply the formula
        var result = formula.Apply();
    
        // Output quantity can be anything greater than or equal
        // We can not directly measure for exact quantities since chance is generated randomly
        // and can be anything at a give a point, but we do know its constraints.
       Assert.That(result["Iron bar"], Is.GreaterThanOrEqualTo(0));  
       
       formula.IncreaseProficiencyLevel();
       var result1 = formula.Apply();
       Assert.That(result1["Iron bar"], Is.GreaterThanOrEqualTo(0));  
       
       formula.IncreaseProficiencyLevel();
       var result2 = formula.Apply();
       Assert.That(result2["Iron bar"], Is.GreaterThanOrEqualTo(0));
    }
    
    [Test]
    // Test that verifies ArgumentException is thrown after null input
    public void ConstructorShouldThrowExceptionIfInputsIsNull()
    {
        var outputs = new Dictionary<string, int> { { "Iron bar", 1 } };
        Assert.Throws<ArgumentException>(() => new Formula(null, outputs));
    }

    [Test]
    // Test that verifies constructor throws an exception if input quantity is negative
    public void ConstructorShouldThrowExceptionIWhenInputQuantIsNegative()
    {
        var inputs = new Dictionary<string, int> { { "Iron Ore", -2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 1 } };
        Assert.Throws<ArgumentException>(() => new Formula(inputs, outputs));
    }
    
    [Test]
    // Test that verifies constructor throws an exception if output quantity is negative
    public void ConstructorShouldThrowExceptionIWhenOutputQuantIsNegative()
    {
        var inputs = new Dictionary<string, int> { { "Iron Ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", -1 } };
        
        Assert.Throws<ArgumentException>(() => new Formula(inputs, outputs));
    }

    [Test]
    // Test that verifies GetInputs method returns the correct input values
    public void CheckGetInputsReturnsCorrectInputs()
    {
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 1 } };
        Formula formula = new Formula(inputs, outputs);

        var result = formula.GetInputs();
        Assert.That( result, Is.EqualTo(inputs));
    }
    
    [Test]
    // Test that verifies GetOutputs method returns the correct output values
    public void CheckGetOutputsReturnsCorrectOutputs()
    {
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 1 } };
        Formula formula = new Formula(inputs, outputs);

        var result = formula.GetOutputs();
        Assert.That( result, Is.EqualTo(outputs));
    }
    
    [Test]
    // Test applying a formula that converts water to hydrogen and deuterium
    // Test expects two different structure output quantities to be produced
    public void TestApply_WaterToHydrogenAndDeuterium()
    {
        //create a formula with 1000Water -> 999 Hydrogen,1 Deuterium
        var inputs = new Dictionary<string, int> { { "Water", 1000 } };
        var outputs = new Dictionary<string, int> { { "Hydrogen", 999 } , {"Deuterium" , 1} };
        Formula formula = new Formula(inputs, outputs);

        //Apply the formula
        var result = formula.Apply();
        
        //check that the output includes the expected result
        //We can not directly measure for exact quantities since chance is generated randomly
        //and can be anything at a give a point, but we do know its constraints.
        Assert.That(result["Hydrogen"], Is.GreaterThanOrEqualTo(0));
        Assert.That(result["Deuterium"], Is.GreaterThanOrEqualTo(0));
    }
    
    [Test]
    // Test increasing proficiency level for a formula and its effect on the output
    public void TestIncreaseProficiency()
    {
        //create a formula with 2 iron ore -> 1 iron bar
        var inputs = new Dictionary<string, int> { { "Iron ore", 2 } };
        var outputs = new Dictionary<string, int> { { "Iron bar", 1 } };
        Formula formula = new Formula(inputs, outputs);
        
        //increase proficiency and check if the level has increased
        Assert.That( formula.GetProficiencyLevel(), Is.EqualTo(0) );
        
        //increase proficiency level again and check level
        formula.IncreaseProficiencyLevel();
        Assert.That( formula.GetProficiencyLevel(), Is.EqualTo(1) );
        
        //increase proficiency level again and check level
        formula.IncreaseProficiencyLevel();
        Assert.That( formula.GetProficiencyLevel(), Is.EqualTo(2) );
        
        //Default case
        formula.IncreaseProficiencyLevel();
        Assert.That( formula.GetProficiencyLevel(), Is.EqualTo(3) );
        
        //Invalid proficiency level since proficiency level can not be greater than or equal to 3;
        Assert.Throws<InvalidOperationException>(() => formula.IncreaseProficiencyLevel());
    }
}