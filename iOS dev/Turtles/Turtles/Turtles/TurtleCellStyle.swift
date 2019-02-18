//
//  TurtleCellStyle.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class TurtleCellStyle : UITableViewCell
{
    
    var turtleName: String = ""
    var turtleId: Int = -1
    
    private var turtleImage: UIImageView? = nil
    
    // assume images are "to left" originally
    private var isToRight = false
    var isTurtleTurnedToRight: Bool {
        get { return isToRight }
        set {
            
            guard let turtleImage = turtleImage else { return }
            
            turtleImage.transform = CGAffineTransform(scaleX: newValue ? -1 : 1, y: 1);
            
            isToRight = newValue
        }
    }
    
    func applyStyle(turtleImage: UIImageView) {
        self.turtleImage = turtleImage
        
        layer.backgroundColor = UIColor.clear.cgColor
        contentView.backgroundColor = UIColor.clear
        
        guard
            let img = UIImage(named: turtleName)
            else {
                print("Cannot find image named ", turtleName, " for turtle")
                return
        }
        
        turtleImage.image = img
        isTurtleTurnedToRight = true
        
        selectionStyle = .none
    }
}
