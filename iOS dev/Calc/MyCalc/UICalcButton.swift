//
//  DBCalcButton.swift
//  MyCalc
//
//  Created by Nikolay Fedotenko on 14/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

enum DBCalcButtonType {
    case Primary
    case Secondary
    case Dark
    case DoubleSecondary
    case DoubleDark
}

private struct MyColors {
    static let Primary: UInt        = 0xFFB800;
    static let PrimaryHigh: UInt    = 0xffdd59;
    static let Secondary: UInt      = 0xD8D8D8;
    static let SecondaryHigh: UInt  = 0xe8e3e3;
    static let Dark: UInt           = 0x646464;
    static let DarkHigh: UInt       = 0x898989;
}

extension UIColor {
    convenience init(rgb: UInt) {
        self.init(
            red: CGFloat((rgb & 0xFF0000) >> 16) / 255.0,
            green: CGFloat((rgb & 0x00FF00) >> 8) / 255.0,
            blue: CGFloat(rgb & 0x0000FF) / 255.0,
            alpha: CGFloat(1.0)
        )
    }
}

class UICalcButton : UIButton {
    
    private var dbType: DBCalcButtonType = .Dark
    private var cmdOut: UILabelExtended? = nil
    
    private var normalColor = UIColor.black
    private var highlightColor = UIColor.gray
    
    @objc func buttonPress(sender: UIButton) {
        
        guard let selfText = self.titleLabel?.text, let textInput = cmdOut else {
            return
        }
        
        textInput.pushTextInput(selfText)
    }
    
    func setStyleOptions(_ type : DBCalcButtonType, cmdOut: UILabelExtended) {
        self.cmdOut = cmdOut
        self.dbType = type
        addTarget(self, action: #selector(buttonPress), for: .touchUpInside)
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        
        // shape
        
        layer.borderWidth = 0
        layer.masksToBounds = false
        layer.cornerRadius = frame.height/2
        clipsToBounds = true
        
        let widthStandard: CGFloat = 80.0;
        let scale: CGFloat = frame.width / widthStandard;
        
        // colors
        
        var backColorHex, colorHex : UInt;
        
        switch dbType {
        case .Primary:
            backColorHex = MyColors.Primary
            //backColorHighHex = MyColors.PrimaryHigh
            colorHex = 0xFFFFFF
        case .Secondary, .DoubleSecondary:
            backColorHex = MyColors.Secondary
            //backColorHighHex = MyColors.SecondaryHigh
            colorHex = 0x000000
        case .Dark, .DoubleDark:
            backColorHex = MyColors.Dark
            //backColorHighHex = MyColors.DarkHigh
            colorHex = 0xFFFFFF
        }
        
        let backColor = UIColor(rgb: backColorHex)
        layer.backgroundColor = backColor.cgColor
        layer.borderColor = backColor.cgColor
        
        let color = UIColor(rgb: colorHex);
        setTitleColor(color, for: .normal);
        setTitleColor(color, for: .highlighted);
        titleLabel?.textColor = color
        
        // typography
        
        var fontSizeStandard: CGFloat = 24.0
        
        if dbType == .DoubleDark || dbType == .DoubleSecondary {
            contentHorizontalAlignment = .left
            titleEdgeInsets = UIEdgeInsets(top: 8, left: 30, bottom: 8, right: 30)
            fontSizeStandard = 12.0;
        }
        
        let fontSize = fontSizeStandard * scale
        if titleLabel?.font.pointSize != fontSize {
            titleLabel?.font = UIFont(name: "Arial", size: fontSize)!
        }
    }
}
