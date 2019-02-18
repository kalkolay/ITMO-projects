//
//  SecondViewController.swift
//  Turtles
//
//  Created by Nikolay Fedotenko on 17/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import UIKit

class SecondViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {
    
    @IBOutlet weak var tableView: UITableView!
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        guard let cellProto = tableView.dequeueReusableCell(withIdentifier: "tortleTrackCell") else {
            return UITableViewCell()
        }
        
        guard let cell = cellProto as? TurtleCellSpeedSlider else {
            print("Error: cannot cast cell prototype.")
            return cellProto
        }
        
        let turtleId = indexPath.row
        let turtleName = String(format: "Turtle%u", turtleId + 1)
        
        cell.prepare(name: turtleName, id: turtleId)
        
        return cell
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        tableView.backgroundColor = UIColor.clear
        
    }
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        UIGraphicsBeginImageContext(view.frame.size)
        UIImage(named: "Forest")?.draw(in: self.view.bounds)
        let image = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        
        view.backgroundColor = UIColor.init(patternImage: image!)
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return Options.Turtles.count
    }

    @IBOutlet weak var randomnessOption: UISwitch!
    @IBAction func toggleRandomness(_ sender: Any) {
        Options.EnableRandomizedMultipliers = randomnessOption.isOn
    }
    
}

