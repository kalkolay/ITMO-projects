//
//  DBExpression.swift
//  MyCalc
//
//  Created by Nikolay Fedotenko on 14/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class UILabelExtended : UILabel {
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    private var prevCommand: String = ""
    
    func pushTextInput(_ command: String) {
        
        var newText = self.text!
        var commandSuccess = true
        
        let isDigits = CharacterSet.decimalDigits.isSuperset(of: CharacterSet(charactersIn: command))
        let isFunction = Calc.IsFunctionCommand(command)
        
        switch(command) {
        case "AC":
            newText = "0"
        case "=":
            do {
                let result = try Calc.EvalTextAsMathExpression(newText, floatingPointRound: -1, floatingPointTruncate: 6)
                newText = result.description
            } catch let err {
                newText = "err"
                print(err.localizedDescription)
                commandSuccess = false
            }
        case "⁺∕₋": // invert sign
            if newText.hasPrefix("-(") && newText.hasSuffix(")") {
                let l = newText.count - 1
                newText = String(newText[2..<l])
            } else {
                newText = String(format: "-(%@)", newText)
            }
        default:
            
            // if user types in new digit AFTER previous expression is evaluated with "=",
            // clear the result and start with black expression
            // otherwise, he is adding some operator to the result of previous expression and we keep it
            if prevCommand == "=" {
                if isDigits {
                    newText = ""
                }
            }
            
            // only strip leading zeroes if any
            if command != "." && !newText.isEmpty {
                
                while newText.starts(with: "0") {
                    if newText == "0" {
                        newText = ""
                    } else {
                        newText = String(newText[1...])
                    }
                }
                
            }
            
            if isFunction { // if it is a function call, we get current result and execute function on it
                do {
                    let result = try Calc.EvalExpressionWithFunction(name: command, argumentExpression: newText, floatingPointRound: -1, floatingPointTruncate: 6)
                    newText = result.description
                } catch let err {
                    newText = "err"
                    print(err.localizedDescription)
                    commandSuccess = false
                }
            } else  {
                
                if isDigits {
                    
                    // consider ...)X ... => ...) * X ...
                    if newText.hasSuffix(")") {
                        newText += "×"
                    } else if newText == "err" { // there was an error..
                        newText = ""
                    }
                    
                }
                
                newText = newText + command
            }
        }
        
        if commandSuccess {
            prevCommand = command
        }
        
        self.text = newText
        self.sizeToFit()
    }
    
}
