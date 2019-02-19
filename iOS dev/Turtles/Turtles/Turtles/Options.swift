//
//  Options.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation

struct TurtleOptions {
    var baseMultiplier: Float = 1
    var userMultiplier: Float = 1
    
    public func getDuration() -> Float {
        var timeToTravel = Options.BaseSpeed
        
        if Options.EnableRandomizedMultipliers {
            timeToTravel *= baseMultiplier
        }
        
        timeToTravel -= userMultiplier
        
        return timeToTravel
    }
}

class Options {
    
    static let BaseSpeed: Float = 3.0
    
    static var EnableRandomizedMultipliers = true

    // four turtles
    public static var Turtles: [TurtleOptions] = [
        TurtleOptions(),
        TurtleOptions(),
        TurtleOptions(),
        TurtleOptions(),
        ]

}
