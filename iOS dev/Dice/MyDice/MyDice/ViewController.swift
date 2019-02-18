//
//  ViewController.swift
//  MyDice
//
//  Created by Nikolay Fedotenko on 18/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UICollectionViewDelegate, UICollectionViewDataSource {
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        guard let slider = diceCountSlider else { return 0 }
        let count = Int(slider.value)
        
        return count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let prototype = collectionView.dequeueReusableCell(withReuseIdentifier: "dicePrototype", for: indexPath)
        guard let dice = prototype as? DiceCellView else {
            print("cast error")
            return prototype
        }
        
        dice.prepare()
        
        return dice
    }
    
    @IBAction func diceCountChanged(_ sender: Any) {
        let count = Int(diceCountSlider.value)
        diceCountLabel.text = String(count)
        diceCollection.reloadData()
    }
    

    @IBOutlet weak var diceCountLabel: UILabel!
    @IBOutlet weak var diceCountSlider: UISlider!
    @IBOutlet weak var diceCollection: UICollectionView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.becomeFirstResponder() // To get shake gesture
    }

    
    @IBAction func rollTapped(_ sender: Any) {
        rollDices()
    }
    
    // We are willing to become first responder to get shake motion
    override var canBecomeFirstResponder: Bool {
        get {
            return true
        }
    }
    
    func collectionView(_ collectionView: UICollectionView, shouldSelectItemAt indexPath: IndexPath) -> Bool {
        return false
    }
    
    func rollDices() {
        let count = Int(diceCountSlider.value)
        for i in 0 ... count {
            let cell = diceCollection.cellForItem(at: IndexPath(row: i, section: 0))
            guard let dice = cell as? DiceCellView else { continue }
            dice.roll()
        }
    }
    
    // Enable detection of shake motion
    override func motionEnded(_ motion: UIEvent.EventSubtype, with event: UIEvent?) {
        if motion == .motionShake {
            print("Why are you shaking me?")
            
            rollDices()
            
        }
    }
    
}

