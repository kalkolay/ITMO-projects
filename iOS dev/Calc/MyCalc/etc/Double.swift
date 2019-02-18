//
//  Double.swift
//  MyCalc
//
//  Created by nameunknown on 2/15/19.
//  Copyright © 2019 My. All rights reserved.
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
