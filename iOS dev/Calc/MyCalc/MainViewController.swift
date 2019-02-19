//
//  MainViewController.swift
//  MyCalc
//
//  Created by Nikolay Fedotenko on 14/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class MainViewController : UIViewController {
    
    // top text
    @IBOutlet weak var expressionInput: UILabelExtended!
    
    // panels
    @IBOutlet weak var numpadLayout: UIStackView!
    @IBOutlet weak var advancedLayout: UIStackView!
    
    // Numpad (portrait) panel
    @IBOutlet weak var btnAC: UICalcButton!
    @IBOutlet weak var btnPlusMinus: UICalcButton!
    @IBOutlet weak var btnPercent: UICalcButton!
    @IBOutlet weak var btnDivide: UICalcButton!
    
    // other buttons as rows
    @IBOutlet weak var btnRow2: UIStackView!
    @IBOutlet weak var btnRow3: UIStackView!
    @IBOutlet weak var btnRow4: UIStackView!
    @IBOutlet weak var btnRow5: UIStackView!
    
    @IBOutlet weak var numpadSizeConstraint: NSLayoutConstraint!
    @IBOutlet weak var numpadSizeConstraint2: NSLayoutConstraint!
    
    @IBOutlet weak var advancedSizeConstraint2: NSLayoutConstraint!
    @IBOutlet weak var advancedSizeConstraint: NSLayoutConstraint!
    
    override func viewDidLoad() {
        super.viewDidLoad();
        
        let cmdTo = expressionInput!;
        
        btnAC.setStyleOptions(DBCalcButtonType.Secondary, cmdOut: cmdTo);
        btnPlusMinus.setStyleOptions(DBCalcButtonType.Secondary, cmdOut: cmdTo);
        btnPercent.setStyleOptions(DBCalcButtonType.Secondary, cmdOut: cmdTo);
        btnDivide.setStyleOptions(DBCalcButtonType.Primary, cmdOut: cmdTo);
        
        for i in 0...2 {
            (btnRow2.subviews[i] as! UICalcButton).setStyleOptions(DBCalcButtonType.Dark, cmdOut: cmdTo);
            (btnRow3.subviews[i] as! UICalcButton).setStyleOptions(DBCalcButtonType.Dark, cmdOut: cmdTo);
            (btnRow4.subviews[i] as! UICalcButton).setStyleOptions(DBCalcButtonType.Dark, cmdOut: cmdTo);
        }
        
        (btnRow2.subviews[3] as! UICalcButton).setStyleOptions(DBCalcButtonType.Primary, cmdOut: cmdTo);
        (btnRow3.subviews[3] as! UICalcButton).setStyleOptions(DBCalcButtonType.Primary, cmdOut: cmdTo);
        (btnRow4.subviews[3] as! UICalcButton).setStyleOptions(DBCalcButtonType.Primary, cmdOut: cmdTo);
        
        (btnRow5.subviews[0] as! UICalcButton).setStyleOptions(DBCalcButtonType.DoubleDark, cmdOut: cmdTo);
        (btnRow5.subviews[1] as! UICalcButton).setStyleOptions(DBCalcButtonType.Dark, cmdOut: cmdTo);
        (btnRow5.subviews[2] as! UICalcButton).setStyleOptions(DBCalcButtonType.Primary, cmdOut: cmdTo);
        
        for row in advancedLayout.subviews {
            let style = row.subviews.count == 4 ? DBCalcButtonType.Secondary : DBCalcButtonType.DoubleSecondary
            for btn in row.subviews {
                (btn as! UICalcButton).setStyleOptions(style, cmdOut: cmdTo);
            }
        }
        
        if UIDevice.current.orientation != .portrait {
            DispatchQueue.main.async {
                self.adaptToOrientation()
            }
        }
        
        expressionInput.text = "0"
    }
    
    override func willTransition(to newCollection: UITraitCollection, with coordinator: UIViewControllerTransitionCoordinator) {
        adaptToOrientation()
    }
    
    func adaptToOrientation() {
        
        let o = UIDevice.current.orientation;
        let isLandscape = o == .landscapeLeft || o == .landscapeRight

        advancedLayout.isHidden = !isLandscape;
        var buttonSize: CGFloat = 80
        
        var fontSize: CGFloat = 42.0
        
        if isLandscape {
            buttonSize *= 0.6   // 40% smaller buttons
            fontSize *= 0.7     // 30% smaller text
        } else {
            buttonSize *= 1.0
            fontSize *= 1.0
        }
        
        if expressionInput.font!.pointSize != fontSize {
            expressionInput.font = UIFont(name: "Arial", size: fontSize)!
        }
        
        numpadSizeConstraint.constant = buttonSize;
        numpadSizeConstraint2.constant = buttonSize;
        advancedSizeConstraint.constant = buttonSize
        advancedSizeConstraint2.constant = buttonSize
        
        expressionInput.sizeToFit()
        advancedLayout.layoutSubviews()
        numpadLayout.layoutSubviews()
    }
}
