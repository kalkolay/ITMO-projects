//
//  TurtleCellStylized.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class TurtleCellStyle: UITableViewCell
{
    
    @IBOutlet weak var turtleImage: UIImageView!
    
    func prepare(name: String, id: Int) {
        
        layer.backgroundColor = UIColor.clear.cgColor
        contentView.backgroundColor = UIColor.clear
        
        guard
            let img = UIImage(named: name)
            else {
                print("Cannot find image named ", name, " for turtle")
                return
        }
        
        turtleImage.image = img
        turtleImage.transform = CGAffineTransform(scaleX: -1, y: 1); //Flipped
    }
}
