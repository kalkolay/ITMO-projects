//
//  TurtleCellStylized.swift
//  Turtles
//
//  Created by usher on 2/17/19.
//  Copyright © 2019 My. All rights reserved.
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
