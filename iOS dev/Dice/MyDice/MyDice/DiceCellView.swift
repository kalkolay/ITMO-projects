//
//  DiceCellView.swift
//  MyDice
//
//  Created by Nikolay Fedotenko on 18/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class DiceCellView: UICollectionViewCell {
    
    @IBOutlet weak var diceLabel: UILabel!
    
    var timer: Timer? = nil
    
    let impulseInterval: Double = 0.01
    let reductionRange: ClosedRange = 0.0001 ... 0.09
    let stopInterval: Double = 1.5
    
    var nextInterval: Double = 1.0
    var reductionFactor: Double = 1.0
    var rollIteration: Int = 0
    
    public func prepare() {
        self.backgroundColor = UIColor.white
        diceLabel.layer.cornerRadius = 20.0
        diceLabel.layer.borderColor = UIColor.gray.cgColor
        diceLabel.layer.borderWidth = 15.0
        
        diceLabel.clipsToBounds = true
    }
    
    public func roll() {
        nextInterval = impulseInterval
        reductionFactor = Double.random(in: reductionRange)
        rollIteration = 1
        resetTimer()
        self.backgroundColor = UIColor.lightGray
    }
    
    @objc func rollHappens() {
        
        print("ROLL HAPPENS")
        
        diceLabel.text = String(Int.random(in: 1 ... 12))
        
        guard let timer = timer else { return }
        
        rollIteration += 1
        
        let mustStop = nextInterval >= 1.1
        
        nextInterval += nextInterval * reductionFactor * Double(rollIteration)
        
        if nextInterval >= stopInterval || mustStop {
            print("ROLL END")
            self.backgroundColor = UIColor.white
            timer.invalidate()
        } else {
            resetTimer()
        }
    }
    
    func resetTimer() {
        timer?.invalidate()
        self.timer = Timer.scheduledTimer(timeInterval: nextInterval, target: self, selector: #selector(rollHappens), userInfo: nil, repeats: true)
    }
    
}
