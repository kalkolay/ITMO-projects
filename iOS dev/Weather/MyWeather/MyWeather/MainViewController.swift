//
//  ViewController.swift
//  MyWeather
//
//  Created by Nikolay Fedotenko on 16/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import UIKit

class MainViewController: UITableViewController, UISearchBarDelegate {
    
    // static data loaded from assets
    var CountryInfoList: [String: CountryInfo.Item]? = nil
    var CitiesList: [WeatherAPI.City]? = nil
    
    // TOP cities from interesting countries to show as favorites
    static var TopCities: [String: [String]] = [
        "US": [ // isoAlpha2
            "New York", // name in CitiesList
            "Los Angeles",
        ],
        "FR": [
            "Paris",
        ],
        "BE": [
            "Brussels"
        ],
        "CA": [
            "Montreal",
        ],
        "RU": [
            "Saint Petersburg",
            "Moscow",
        ],
    ]
    
    // What is being displayed at this moment
    private var DisplayedCountries: [String] = []
    private var DisplayedCities: [String: [WeatherAPI.City]] = [:]
    
    // needed to pass data between performSegue() and prepare() to populate destination view with [city] to show data for
    var nextCity: WeatherAPI.City? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.searchBar.delegate = self
        
        // Load static data (JSONs from xcassets)
        
        if CountryInfoList == nil {
            
            print("loading countryInfos...")
            
            CountryInfo.LoadMap(callback: {
                (error, result) in
                if let error = error {
                    WeatherPresenter.ErrorBox(self, error: error)
                    exit(EXIT_FAILURE)
                }
                else if let result = result {
                    print("success")
                    self.CountryInfoList = result
                    
                    print("loading allCities...")
                    
                    if CitiesList == nil {
                        WeatherAPI.LoadCityList(filterByCountryCode: nil, callback: {
                            (error, result) in
                            if let error = error {
                                WeatherPresenter.ErrorBox(self, error: error)
                            } else if let result = result {
                                print("success")
                                self.CitiesList = result
                                loadCities("")
                            } else {
                                WeatherPresenter.ErrorBox(self, error: Errors.generic("no cities"))
                                exit(EXIT_FAILURE)
                            }
                        })
                    }
                }
                else {
                    WeatherPresenter.ErrorBox(self, error: Errors.generic("no country infos"))
                    exit(EXIT_FAILURE)
                }
                
            })
        }
    }

    @IBOutlet weak var searchBar: UISearchBar!
    
    private var searched = false, searching = false
    
    func setToResults(query: String?) {
        
        if searching {
            return // search in dispatchQueue is working
        }
        
        searched = true
        searching = true
        DispatchQueue.main.async {
            self.loadCities(query ?? "")
            self.tableView.reloadData()
            self.searching = false
        }
        
    }
    
    func searchBar(_ searchBar: UISearchBar, textDidChange searchText: String) {
        setToResults(query: searchBar.text)
    }
    
    func loadCities(_ query: String) {
        
        // we need all cities to be loaded
        guard var cities = CitiesList else { return }
        
        // based on query, filter cities by first letters of the name
        if query.count > 3 {
            cities = cities.filter() {
                $0.name.lowercased().starts(with: query.lowercased())
            }
        } else {
            let topCities = MainViewController.TopCities
            cities = cities.filter() {
                topCities[$0.country] != nil && topCities[$0.country]!.contains($0.name)
            }
        }

        // we need country info list to be loaded
        guard let countryInfoList = CountryInfoList else { return }
        DisplayedCountries = [] // reset
        DisplayedCities = [:]
        
//        // from our cities array, we get dictionary where country name is a key, and value is cities array
//        DisplayedCities = cities.reduce(into: [String: [WeatherAPI.City]]()) {
//
//            guard let country = countryInfoList[$1.country] else { return }
//            let countryName = country.name
//
//            if $0[countryName] != nil {
//                $0[countryName]?.append($1)
//            } else {
//                $0[countryName] = [$1]
//                DisplayedCountries.append(countryName)
//            }
//        }
        
        // should be faster -> branch prediction:
        
        var fixDuplications: [String] = []
        for city in cities.sorted(by: { $0.country > $1.country }) {
            
            guard let country = countryInfoList[city.country] else { continue }
            let key = country.name
            
            if DisplayedCities[key] == nil {
                DisplayedCities[key] = [city]
                DisplayedCountries.append(key)
                fixDuplications = [city.name]
            } else if !fixDuplications.contains(city.name) {
                DisplayedCities[key]!.append(city)
                fixDuplications.append(city.name)
            }
        }
        
        DisplayedCountries.sort()
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return DisplayedCountries.count
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let countryName = DisplayedCountries[section]
        guard let cities = DisplayedCities[countryName] else { return 0 }
        return cities.count
    }
    
    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return DisplayedCountries[section]
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell: TableViewCell
        if let cellProto = tableView.dequeueReusableCell(withIdentifier: "myProtoCell") as? TableViewCell {
            cell = cellProto
        } else {
            cell = TableViewCell()
        }
        
        let countryName = DisplayedCountries[indexPath.section]
        guard let cities = DisplayedCities[countryName] else { return cell }
        let city = cities[indexPath.row]
        
        cell.nameLabel.text = city.name
        
        cell.isFavoriteCity = false
        if let byCountry = MainViewController.TopCities[city.country] {
            if byCountry.contains(city.name) {
                cell.isFavoriteCity = true
            }
        }
        
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        let countryName = DisplayedCountries[indexPath.section]
        guard let cities = DisplayedCities[countryName] else { return }
        nextCity = cities[indexPath.row]
        
        self.performSegue(withIdentifier: "cityDetailSegue", sender: self)
        
    }
    
    override func shouldPerformSegue(withIdentifier identifier: String, sender: Any?) -> Bool {
        if identifier == "cityDetailSegue" {
            // just check if segue will display any city (set at prepare method)
            if nextCity == nil {
                return false
            }
        }
        
        return true
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "cityDetailSegue" {
            
            // set nextCity as task for next view to load and display weather & info
            
            guard let nextCity = nextCity else { return }
            guard let cityDetail = segue.destination as? CityDetailViewController else { return }
            guard let allInfo = CountryInfoList else { return }
            
            var countryInfo: CountryInfo.Item? = nil
            if let info = allInfo[nextCity.country] {
                countryInfo = info
            }
            
            cityDetail.task = (countryInfo, nextCity, self)
        }
    }
    
    func toggleCityIsFavorite(_ city: WeatherAPI.City) {
        
        guard let info = CountryInfoList else { return }
        guard let country = info[city.country] else { return }
        let countryName = country.name
        
        // assume city is already in list
        // find its section/row
        
        guard let sectionId = DisplayedCountries.firstIndex(of: countryName) else { return }
        guard let row = DisplayedCities[countryName]!.firstIndex(where: { $0.name == city.name }) else {
            return // confusion in country?
        }
        
        // get the cell
        guard let _cell = tableView.cellForRow(at: IndexPath.init(row: row, section: sectionId)) else { return }
        guard let cell = _cell as? TableViewCell else { return }
        
        // set isFavoriteCity attribute
        let isFavorite = !cell.isFavoriteCity
        cell.isFavoriteCity = isFavorite
        
        // now add or remote from TopCities
        if !MainViewController.TopCities.contains(where: { $0.key == city.country }) {
            MainViewController.TopCities[city.country] = []
        }
        
        let i = MainViewController.TopCities[city.country]!.firstIndex(of: city.name)
        
        if i == nil {
            if isFavorite {
                MainViewController.TopCities[city.country]!.insert(city.name, at: 0)
            }
        } else if !isFavorite {
            MainViewController.TopCities[city.country]!.remove(at: i!)
        }
    }
    
}

