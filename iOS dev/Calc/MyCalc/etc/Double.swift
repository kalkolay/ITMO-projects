//
//  Double.swift
//  MyCalc
//
//  Created by Nikolay Fedotenko on 15/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation

extension Double
{

    func truncate(places : Int)-> Double
    {
        return Double(floor(pow(10.0, Double(places)) * self)/pow(10.0, Double(places)))
    }
    
    func rounded(toPlaces places:Int) -> Double {
        let divisor = pow(10.0, Double(places))
        return (self * divisor).rounded() / divisor
    }
    
}
