//
//  ActionButton.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class ActionButton : UIButton {
    override func layoutSubviews() {
        super.layoutSubviews()
        
        layer.borderColor = UIColor.brown.cgColor
        layer.borderWidth = 0.7
        layer.backgroundColor = UIColor.white.withAlphaComponent(0.3).cgColor
        layer.cornerRadius = 5.0
        
        contentEdgeInsets = UIEdgeInsets(top: 5, left: 50, bottom: 5, right: 100)
        
    }
}
