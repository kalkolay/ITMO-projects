//
//  CityDetailViewController.swift
//  MyWeather
//
//  Created by Nikolay Fedotenko on 16/2/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class CityDetailViewController : UIViewController, UITableViewDelegate, UITableViewDataSource {
    
    
    struct State {
        var city: WeatherAPI.City? = nil
        var countryInfo: CountryInfo.Item? = nil
        var weather: WeatherAPI.CityWeather? = nil
    }
    
    private static var stashed: [UInt:State] = [:]
    private static var current: State = State()
    
    var task: (CountryInfo.Item?, WeatherAPI.City, MainViewController)? = nil
    
    @IBOutlet weak var spinner: UIActivityIndicatorView!
    @IBOutlet weak var mainPanel: UIView!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var detailTableView: UITableView!
    @IBOutlet weak var weatherImage: UIImageView!
    @IBOutlet weak var descriptionLabel: UILabel!
    @IBOutlet weak var tempLabel: UILabel!
    @IBOutlet weak var countryImage: UIImageView!
    @IBOutlet weak var countryLabel: UILabel!
    
    private func updateUI() {
        
        details = []
        
        guard
            let city = CityDetailViewController.current.city,
            let weather = CityDetailViewController.current.weather
            else {

            mainPanel.isHidden = true
            spinner.startAnimating()

            return
        }
        
        countryImage.isHidden = true
        countryLabel.isHidden = true
        if let country = CityDetailViewController.current.countryInfo {
            countryImage.image = UIImage(named: city.country.lowercased())
            countryLabel.text = "\(country.name) (code \(country.phone_code))"
            countryImage.isHidden = false
            countryLabel.isHidden = false
        }
    
        nameLabel.text = city.name
        
        if let weathers = weather.weather {
            if weathers.count > 0 {
                let w = weathers[0]
                
                if let main = w.main {
                    weatherImage.image = WeatherPresenter.LoadWeatherPic(forCase: main)
                } else {
                    weatherImage.image = nil
                }
                
                if let descr = w.description {
                    descriptionLabel.text = descr
                } else {
                    descriptionLabel.text = "openweathermap.org"
                }
            }
        }
        
        // +X or -X formatting
        let temperatureString: (Float) -> String = {
            temp in
            if temp > 0 {
                return String(format: "+%d", Int(temp))
            }
            
            return String(Int(temp))
        }
        
        if let main = weather.main {
            
            let dummyTemp: Float = -99 // considered out of real range
            let temp = main.temp ?? dummyTemp
            let maxTemp = main.temp_max ?? dummyTemp
            let minTemp = main.temp_min ?? dummyTemp
            
            tempLabel.text = String(format: "%@ °C", temperatureString(temp))
            
            // max & min are known and are different from main
            if maxTemp != dummyTemp && minTemp != dummyTemp {
                if maxTemp != minTemp {
                    details.append(("Range", String(format: "%@...%@ °C", temperatureString(minTemp), temperatureString(maxTemp))))
                }
            }
            
            // max OR min is known and one of these is different from main
            else if (maxTemp != dummyTemp && maxTemp != temp) || (minTemp != dummyTemp && minTemp != temp)
            {
                if minTemp != dummyTemp {
                    details.append(("Min", String(format: "%@ °C", temperatureString(minTemp))))
                }
                
                if  maxTemp != dummyTemp {
                    details.append(("Max", String(format: "%@ °C", temperatureString(maxTemp))))
                }
            }
            
            if let clouds = weather.clouds {
                if let all = clouds.all {
                    details.append(("Clouds", String(format: "%d %%", Int(all))))
                }
            }
            
            if let wind = weather.wind {
                if let speed = wind.speed {
                    details.append(("Wind Speed", String(format: "%d m/s", Int(speed))))
                }
            }
            
            if let vis = weather.visibility {
                details.append(("Visibility", String(format: "%d km", Int(vis / 1000))))
            }
            
            if let pre = main.pressure {
                details.append(("Pressure", String(format: "%d atn", Int(pre))))
            }
            
            if let hum = main.humidity {
                details.append(("Humidity", String(format: "%d %%", Int(hum))))
            }
        }
        
        detailTableView.reloadData()
        
        spinner.stopAnimating()
        mainPanel.isHidden = false
        
        CityDetailViewController.stashed[city.id] = CityDetailViewController.current
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        
        CityDetailViewController.stashed = [:]
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        // do we have city to show?
        guard let task = task else { return }
        
        // do we need to update UI for that new city?
        if let currentCity = CityDetailViewController.current.city {
            if currentCity.id == task.1.id {
                updateUI() // ensure state is displayed
                return
            }
        }
        
        // do we have stashed state for this city?
        var weather: WeatherAPI.CityWeather? = nil
        if let stashedState = CityDetailViewController.stashed[task.1.id] {
            print("taking from stash, city id: ", task.1.id)
            weather = stashedState.weather
        }
        
        // reset state to nothing and show spinner, etc
        CityDetailViewController.current = State()
        updateUI()
        
        // set to this city
        CityDetailViewController.current.countryInfo = task.0
        CityDetailViewController.current.city = task.1
        
        // do we need to download weather?
        if weather != nil {
            
            CityDetailViewController.current.weather = weather
            
            // no need to download weather, updateUI now
            updateUI()
            return
        }
        
        print("fetching weather for city ID ", task.1.id)
        
        WeatherAPI.GetWeather(cityById: task.1.id, callback: {
            (error, result) in
            
            if let error = error {
                
                print("error: ", error.localizedDescription)
                
                let alert = UIAlertController(title: "Error", message: error.localizedDescription, preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
                    switch action.style{
                    case .default:
                        print("default")
                        
                    case .cancel:
                        print("cancel")
                        
                    case .destructive:
                        print("destructive")
                        
                    }}))
                
                self.present(alert, animated: true, completion: nil)
                return
            }
            
            guard let result = result else {
                
                print("error: no result")
                
                let alert = UIAlertController(title: "Error", message: "no result", preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
                    switch action.style{
                    case .default:
                        print("default")
                        
                    case .cancel:
                        print("cancel")
                        
                    case .destructive:
                        print("destructive")
                        
                    }}))
                
                self.present(alert, animated: true, completion: nil)
                return
                
            }
            
            print("success, weather downloaded.")
            
            DispatchQueue.main.async {
                // weather downloaded, updateUI on main thread
                // checks for safety
                guard let currentCity = CityDetailViewController.current.city else { return }
                if currentCity.id == task.1.id {
                    CityDetailViewController.current.weather = result
                    self.updateUI()
                }
            }
            
        })
    }
    
    @IBAction func favoritePressed(_ sender: Any) {
        guard let task = task else { return }
        let sender = task.2
        sender.toggleCityIsFavorite(CityDetailViewController.current.city!)
        navigationController?.popViewController(animated: true)
    }
    
    @IBAction func webSearchPressed(_ sender: Any) {
        
        guard let task = task else { return }
        
        var query = String(format: "weather now in %@, %@", task.1.name, task.1.country)
        if let country = task.0 {
            query = String(format: "weather now in %@, %@", task.1.name, country.name)
        }
        
        guard var urlComponents = URLComponents(string: "https://www.google.com/search") else { return }
        urlComponents.queryItems = [
            URLQueryItem(name: "source", value: "hp"),
            URLQueryItem(name: "channel", value: "ipad_bm"),
            URLQueryItem(name: "client", value: "safari"),
            URLQueryItem(name: "q", value: query),
        ]
        urlComponents.percentEncodedQuery = urlComponents.percentEncodedQuery?.replacingOccurrences(of: "+", with: "%2B")
        
        guard let url = urlComponents.url else { return }
        
        UIApplication.shared.open(url, options: [:])
        
        print("default browser was successfully opened")
        
    }
    
    var details: [(String, String)] = []
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return details.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        guard let cell = detailTableView.dequeueReusableCell(withIdentifier: "infoCellProto") as? DetailTableCell else { return UITableViewCell() }
        
        cell.text1 = details[indexPath.row].0
        cell.text2 = details[indexPath.row].1
        
        return cell
    }
}

class DetailTableCell: UITableViewCell {
    
    @IBOutlet weak var label1: UILabel!
    
    @IBOutlet weak var label2: UILabel!
    
    public var text1: String = "" {
        didSet {
            label1.text = text1
        }
    }
    
    public var text2: String = "" {
        didSet {
            label2.text = text2
        }
    }
    
}
