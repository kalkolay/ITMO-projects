//
//  Float.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation


public extension Float {
    /// SwiftRandom extension
    public static func random(lower: Float = 0, _ upper: Float = 100) -> Float {
        return (Float(arc4random()) / 0xFFFFFFFF) * (upper - lower) + lower
    }
}
