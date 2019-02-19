//
//  TurtleCellSpeedSlider.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class TurtleCellSpeedSlider : TurtleCellStyle
{
    @IBOutlet weak var turtleImage: UIImageView!
    
    @IBOutlet weak var slider: UISlider!
    
    @IBAction func sliderChange(_ sender: Any) {
        Options.Turtles[turtleId].userMultiplier = slider.value
    }
    
    public func prepare(name: String, id: Int) {
        turtleName = name
        turtleId = id
        applyStyle(turtleImage: turtleImage)
    }
}
