//
//  Calc.swift
//  MyCalc
//
//  Created by Nikolay Fedotenko on 15/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation

enum CalcError : Error {
    case generic(String)    // format error
    case math(String)       // reserved
    case nan                // not a number, infinity, division by zero
    case system(String)     // NSException OR any unrecognized, unclear catch
}

class Calc
{
    
    static func FilterToMathExpression(_ str: String) -> String {
        
        var nsstr: String = str
        
        let replace: [String: String] = [
            "−": "-",   // non-standard symbols to normal variants
            "⋅": "*",
            "×": "*",
            "÷": "/",
            " ": "",
            ]
        
        for v in replace {
            nsstr = nsstr.replacingOccurrences(of: v.key, with: v.value)
        }
        
        return nsstr
    }
    
    static func EvalTextAsMathExpression(_ str: String, floatingPointRound: Int, floatingPointTruncate: Int) throws -> Decimal {
        
        let nsstr: String = FilterToMathExpression(str)
        
        let nsexpr = try createNSExpression(nsstr)
        
        guard var result = try evalExpression(nsexpr) as? Double else {
            throw CalcError.generic("Was not able to cast NSExpression result to Double")
        }
        
        // division by zero: causes result to be positive infinity for Double
        if result.isInfinite || result.isNaN {
            throw CalcError.nan
        }
        
        if floatingPointRound >= 0 {
            result = result.rounded(toPlaces: floatingPointRound)
        }
        
        if floatingPointTruncate >= 0 {
            result = result.truncate(places: floatingPointTruncate)
        }
        
        return Decimal(result)
    }
    
    static func createNSExpression(_ str: String) throws -> NSExpression {
        
        var nsexpr: NSExpression?
        
        // will raise NSException for bad format / syntax error of an expression
        do {
            try ObjC.catchException {
                
               nsexpr = NSExpression(format: str)
            }
        }
        catch {
            throw CalcError.system("NSException is encountered")
        }
        
        guard let result = nsexpr else { throw CalcError.math("Failed to initialize NSExpression") }
        
        return result
    }
    
    static func evalExpression(_ nsexpr: NSExpression) throws -> Any? {
        
        var result: Any?
        
        // will raise NSException if NSExpression cannot be evaluated, like if it contains vars/functions that are unknown or etc
        do {
            try ObjC.catchException {
                result = nsexpr.toFloatingPoint().expressionValue(with: nil, context: nil)
            }
        }
        catch {
            throw CalcError.system("NSException is encountered")
        }
        
        guard let ret = result else {
            throw CalcError.math("Nil result from NSExpression or catchException block failed")
        }
        
        return ret
        
    }
    
    static func IsFunctionCommand(_ str: String) -> Bool {
        switch str {
        case "cos", "sin", "sqrt", "pow2", "pow3", "pow4", "log2":
            return true
        default:
            return false
        }
    }
    
    static func EvalExpressionWithFunction(name: String, argumentExpression: String, floatingPointRound: Int, floatingPointTruncate: Int) throws -> Double {
        
        // do not use rounded/truncate for precision here
        let argumentValue = try EvalTextAsMathExpression(argumentExpression, floatingPointRound: -1, floatingPointTruncate: -1)
        
        return try EvalFunction(name: name, argument: argumentValue, floatingPointRound: floatingPointRound, floatingPointTruncate: floatingPointTruncate)
        
    }
    
    static func EvalFunction(name: String, argument: Decimal, floatingPointRound: Int, floatingPointTruncate: Int) throws -> Double {
        
        
        var result = Double(truncating: argument as NSNumber)
        
        switch name {
        case "sin":
            result = sin(result)
        case "cos":
            result = cos(result)
        case "sqrt":
            result = sqrt(result)
        case "pow2":
            result = pow(result, 2)
        case "pow3":
            result = pow(result, 3)
        case "pow4":
            result = pow(result, 4)
        case "log2":
            result = log2(result)
        default:
            throw CalcError.system("function not implemented or unknown")
        }
        
        if floatingPointRound >= 0 {
            result = result.rounded(toPlaces: floatingPointRound)
        }
        if floatingPointTruncate >= 0 {
            result = result.truncate(places: floatingPointTruncate)
        }
        
        return result
        
    }
    
}
