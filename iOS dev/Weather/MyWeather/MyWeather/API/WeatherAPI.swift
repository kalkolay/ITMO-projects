//
//  WeatherAPI.swift
//  MyWeather
//
//  Created by Nikolay Fedotenko on 16/2/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

enum Errors: Error {
    case generic(String)
    case request(String)
    case response(String)
}

class WeatherAPI {
    
    // https://openweathermap.org/weather-data for units 
    
    struct City : Decodable  {
        let id: UInt
        let country: String
        let name: String
        let coord: Coord?
    }
    
    struct Coord : Decodable  {
        let lan: Float?
        let lon: Float?
    }
    
    struct CityWeather : Decodable  {
        let coord: Coord?
        let base: String?
        let wind: Wind?
        let sys: Sys?
        let weather: [Weather]?
        let main: WeatherMain?
        let visibility: Float?
        let clouds: Clouds?
    }
    
    struct Clouds: Decodable {
        let all: Float?
    }
    
    struct Weather : Decodable  {
        let main: WeatherCase?
        let description: String?
        let icon: String?
    }
    
    struct WeatherMain: Decodable {
        let temp: Float?
        let pressure: Float?
        let humidity: Float?
        let temp_min: Float?
        let temp_max: Float?
    }
    
    enum WeatherCase : String, Decodable {
        case sun = "Sun"
        case clear = "Clear"
        case snow = "Snow"
        case haze = "Haze"
        case clouds = "Clouds"
        case fog = "Fog"
        case mist = "Mist"
        case rain = "Rain"
        case thunder = "Thunder" // ??
        case sunRain = "Sun Rain" // ??
        case unknown
    }
    
    struct Wind : Decodable {
        let speed: Float?
        let deg: Float?
    }
    
    struct Sys : Decodable  {
        let country: String?
        let sunrize: UInt64?
        let sunset: UInt64?
    }
    
    // api.openweathermap.org
    static private let APIKey = "cc75f7f3b1e1cf0cd74fe04cf2043808" // "APPID"
    
    static private let units = "metric" // "metric" for C* not F* temp
    
    typealias LoadCityListCallback = (_ err: Errors?, _ result: [City]?) -> ()
    
    // Gets city list from Assetss.xcassets "CityListJSON
    // https://stackoverflow.com/questions/36070509/can-we-find-list-of-cities-using-openweather-api
    // And filter by city if needed
    static func LoadCityList(filterByCountryCode: [String]?, callback: LoadCityListCallback) {
        
        guard let asset = NSDataAsset(name: "CityListJSON") else {
            callback(Errors.generic("CityListJSON asset was not found"), nil)
            return
        }
        
        do {
            var cityList = try JSONDecoder().decode([City].self, from: asset.data)
            
            if let countryCodes = filterByCountryCode {
                print("filtering cities by country codes...")
                cityList = cityList.filter { countryCodes.contains($0.country)  }
            }
            
            callback(nil, cityList)
        } catch {
            callback(Errors.generic("CityListJSON decode failed"), nil)
        }
    }
    
    typealias GetWeatherCallback = (_ err: Errors?, _ result: CityWeather?) -> ()
    
    static func GetWeather(cityById: UInt, callback: @escaping GetWeatherCallback) {
        let urlString: String = "https://api.openweathermap.org/data/2.5/weather"
        
        var urlComponents = URLComponents(string: urlString)!
        urlComponents.queryItems = [
            URLQueryItem(name: "APPID", value: APIKey),
            URLQueryItem(name: "units", value: units),
            URLQueryItem(name: "id", value: String(cityById)),
        ]
        urlComponents.percentEncodedQuery = urlComponents.percentEncodedQuery?.replacingOccurrences(of: "+", with: "%2B")
        
        guard let url = urlComponents.url else {
            return
        }
        let request = URLRequest(url: url)
        
        let session = URLSession.shared
        
        let task = session.dataTask(with: request) {
            (data, response, error) in
            
            if error != nil {
                callback(Errors.request("Request/response error"), nil)
                return
            }
            
            guard let data = data else {
                callback(Errors.request("No response"), nil)
                return
            }
            
            do {
                let result = try JSONDecoder().decode(CityWeather.self, from: data)
                callback(nil, result)
            } catch {
                callback(Errors.response("JSON decoder error"), nil)
            }
            
        }
        task.resume()
    }
    
    
}
