//
//  WeatherPresenter.swift
//  MyWeather
//
//  Created by Nikolay Fedotenko on 16/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class WeatherPresenter {
    
    static func LoadWeatherPic(forCase: WeatherAPI.WeatherCase) -> UIImage? {
        switch forCase {
        case .sun:
            return UIImage(named: "icon-sunny")
        case .snow:
            return UIImage(named: "icon-snow")
        case .clear:
            return UIImage(named: "icon-sunny")
        case .clouds:
            return UIImage(named: "icon-cloudy")
        case .rain:
            return UIImage(named: "icon-rain")
        case .sunRain:
            return UIImage(named: "icon-sun-rain")
        case .fog:
            return UIImage(named: "icon-fog")
        case .mist:
            return UIImage(named: "icon-mist")
        case .haze:
            return UIImage(named: "icon-haze")
        case .thunder:
            return UIImage(named: "icon-thunder")
        case .unknown:
            return UIImage(named: "Weather")
        }
    }
    
    static func ErrorBox(_ view: UIViewController, error: Errors) {
        
        let messageTitle = "Error"
        let messageText = error.localizedDescription
        
        let alert = UIAlertController(title: messageTitle, message: messageText, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
            switch action.style{
            case .default:
                print("default")

            case .cancel:
                print("cancel")

            case .destructive:
                print("destructive")


            }}))
        view.present(alert, animated: true, completion: nil)
    }
    
}
