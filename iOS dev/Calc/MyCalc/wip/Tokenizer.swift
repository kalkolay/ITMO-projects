//
//  Tokenizer.swift
//  MyCalc
//
//  Created by Nikolay Fedotenko on 14/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation

enum TokenType {
    
    case Literal        // 1
    case Variable       // x
    case Operator       // +
    
    case LeftPara       // (
    case RightPara      // )
    
    case Function       // cos
    case ArgSep         // ,
}

enum TokenErrors: Error {
    case parseError(String)
    case evalError(String)
}

class Token {
    var type: TokenType
    var str: String
    
    init(type: TokenType, str: String) {
        self.type = type
        self.str = str
    }
    
    convenience init(_ type: TokenType, str: String) {
        self.init(type: type, str: str)
    }
    
    convenience init(_ type: TokenType, uchar: Unicode.Scalar) {
        self.init(type: type, char: Character(uchar))
    }
    
    convenience init(type: TokenType, char: Character) {
        self.init(type: type, str: String(char))
    }
    
    func isMinus() -> Bool {
        if type == TokenType.Operator {
            for char in str.unicodeScalars {
                if !Tokenizer.isMinus(char) {
                    return false
                }
            }
            return true
        }
        return false
    }
    
    func isLiteral() -> Bool {
        return type == TokenType.Literal
    }
}

class Tokenizer {
    
    static func StringFromScalars(_ letters: [Unicode.Scalar]) -> String {
        var s: String = ""
        
        for unicodeScalar in letters {
            s = s + unicodeScalar.escaped(asASCII: true)
        }
        
        return s
    }
    
    static func isLetter(_ char: Unicode.Scalar) -> Bool {
        let letters = CharacterSet.letters
        
        if letters.contains(char) {
            return true
        }
        
        return false
    }
    
    static func isDigit(_ char: Unicode.Scalar) -> Bool {
        let digits = CharacterSet.decimalDigits
        
        if digits.contains(char) {
            return true
        }
        
        return false
    }
    
    static func isOperator(_ char: Unicode.Scalar) -> Bool {
        let operators: [Unicode.Scalar] = ["+", "/", "÷", "*", "⋅", "×"]
        
        if isMinus(char) || operators.contains(char) {
            return true
        }
        
        return false
    }
    
    static func isLeftParanthesis(_ char: Unicode.Scalar) -> Bool {
        return char == "("
    }
    
    static func isRightParanthesis(_ char: Unicode.Scalar) -> Bool {
        return char == ")"
    }
    
    static func isComma(_ char: Unicode.Scalar) -> Bool {
        return char == ","
    }
    
    static func isMinus(_ char: Unicode.Scalar) -> Bool {
        let minus: [Unicode.Scalar] = ["−", "-"]
        if minus.contains(char) {
            return true
        }
        return false
    }
    
    var tokens: [Token]
    
    init() {
        tokens = []
    }
    
    func reset() {
        tokens.removeAll()
    }
    
    func loadString(_ str: String) throws {
        
        var numbers: [Unicode.Scalar] = []
        var letters: [Unicode.Scalar] = []
        
        let emptyNumberBufferAsLiteral: () -> () = {
            if !numbers.isEmpty {
                let number = Tokenizer.StringFromScalars(numbers)
                let t = Token(TokenType.Literal, str: number)
                self.tokens.append(t)
                numbers = []
            }
        }
        
        
        let emptyLetterBufferAsVariables: () -> () = {
            
            for (i, c) in letters.enumerated() {
                let tVar = Token(TokenType.Variable, uchar: c)
                self.tokens.append(tVar)
                if i < letters.count - 1 {
                    let tMul = Token(TokenType.Variable, uchar: "*")
                    self.tokens.append(tMul)
                }
            }
            
            letters = []
            
        }
        
        // space doesn't matter
        let parseString = str.replacingOccurrences(of: " ", with: "")
        
        for char in parseString.unicodeScalars {
            
            if Tokenizer.isDigit(char) {
                numbers.append(char)
            } else if Tokenizer.isLetter(char) {
                if !numbers.isEmpty {
                    emptyNumberBufferAsLiteral();
                    tokens.append(Token(type: TokenType.Operator, char: "*"))
                }
                letters.append(char)
            } else if Tokenizer.isOperator(char) {
                emptyNumberBufferAsLiteral();
                emptyLetterBufferAsVariables();
                tokens.append(Token(TokenType.Operator, uchar: char))
            } else if Tokenizer.isLeftParanthesis(char) {
                if !letters.isEmpty {
                    let fname = Tokenizer.StringFromScalars(letters)
                    tokens.append(Token(type: TokenType.Function, str: fname))
                    letters = []
                } else if !numbers.isEmpty {
                    emptyNumberBufferAsLiteral();
                    tokens.append(Token(TokenType.Operator, uchar: "*"))
                }
                tokens.append(Token(TokenType.LeftPara, uchar: char));
            } else if Tokenizer.isRightParanthesis(char) {
                emptyLetterBufferAsVariables();
                emptyNumberBufferAsLiteral();
                tokens.append(Token(TokenType.RightPara, uchar: char));
            } else if Tokenizer.isComma(char) {
                emptyNumberBufferAsLiteral();
                emptyLetterBufferAsVariables();
                tokens.append(Token(TokenType.ArgSep, uchar: char))
            }
            else {
                throw TokenErrors.parseError("Parse error")
            }
        }
        
        if !numbers.isEmpty {
            emptyNumberBufferAsLiteral();
        }
        
        if !letters.isEmpty {
            emptyLetterBufferAsVariables();
        }
    }
}
