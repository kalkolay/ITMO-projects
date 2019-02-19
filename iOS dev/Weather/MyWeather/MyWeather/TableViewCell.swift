//
//  TableViewCell.swift
//  MyWeather
//
//  Created by Nikolay Fedotenko on 16/2/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class TableViewCell: UITableViewCell {
    
    private static var starImageAsset: UIImage?
    
    var city: WeatherAPI.City? = nil
    var sender: MainViewController? = nil
    
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var weatherImage: UIImageView!
    @IBOutlet weak var starImage: UIImageView!
    
    var isFavoriteCity: Bool = false {
        didSet {
            guard let img = starImage else { return }
            let val = isFavoriteCity
            
            if val {
                if TableViewCell.starImageAsset == nil {
                    TableViewCell.starImageAsset = UIImage(named: "Star_Icon")
                }
                img.image = TableViewCell.starImageAsset
            } else {
                img.image = nil
            }
        }
    }
    
    var displayWeather: WeatherAPI.WeatherCase? = nil {
        didSet {
            guard let img = weatherImage else { return }
            guard let val = displayWeather else {
                img.image = nil
                return
            }
            img.image = WeatherPresenter.LoadWeatherPic(forCase: val)
        }
    }
}
