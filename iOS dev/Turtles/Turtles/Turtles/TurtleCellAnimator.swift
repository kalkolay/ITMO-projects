//
//  TurtleCellAnimator.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class TurtleCellAnimator : TurtleCellStyle
{
    @IBOutlet weak var turtleImage: UIImageView!
    
    var xStart: CGFloat = 0
    var xEnd: CGFloat = 0
    
    public func prepare(name: String, id: Int) {
        turtleName = name
        turtleId = id
        applyStyle(turtleImage: turtleImage)
        
        let singleTap = UITapGestureRecognizer(target: self, action: #selector(tapDetected))
        turtleImage.isUserInteractionEnabled = true
        turtleImage.addGestureRecognizer(singleTap)
        
        xStart = self.frame.minX + self.turtleImage.frame.width
        xEnd = self.frame.maxX - self.turtleImage.frame.width
        
        turtleImage.center.x = xStart
    }
    
    //Action
    @objc func tapDetected() {
        
        if isTurtleTurnedToRight && self.turtleImage.center.x == self.xStart {
            travelOut()
        }
        
        if !isTurtleTurnedToRight && self.turtleImage.center.x == self.xEnd {
            travelHome()
        }
        
    }
    
    public func travelOut() {
        
        let options = Options.Turtles[turtleId]
        
        let duration = options.getDuration()
        
        self.isTurtleTurnedToRight = true
        UIImageView.animate(withDuration: Double(duration), delay: 0, options: .curveEaseIn, animations: {
            self.turtleImage.center.x = self.xEnd
        }, completion: { _ in
            self.isTurtleTurnedToRight = false
        })
        
    }
    
    public func travelHome() {
        
        let options = Options.Turtles[turtleId]
        
        let duration = options.getDuration()
        
        self.isTurtleTurnedToRight = false
        UIImageView.animate(withDuration: Double(duration), delay: 0, options: .curveEaseOut, animations: {
            self.turtleImage.center.x = self.xStart
        }, completion: { _ in
            self.isTurtleTurnedToRight = true
        })
        
    }
    
    public func stopTravel() {
        turtleImage.layer.removeAllAnimations()
    }
}
