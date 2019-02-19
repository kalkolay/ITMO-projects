//
//  CountryInfo.swift
//  MyWeather
//
//  Created by Nikolay Fedotenko on 16/2/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class CountryInfo {
    
    struct Item : Decodable {
        let code: String        // ISO code
        let name: String        // full name
        let phone_code: String  // phone code, +xxx
    }
    
    typealias LoadCallback = (_ err: Errors?, _ result: [Item]?) -> ()
    typealias LoadMapCallback = (_ err: Errors?, _ result: [String:Item]?) -> ()
    
    static func Load(callback: LoadCallback) {
        
        guard let asset = NSDataAsset(name: "CountryInfoJSON") else {
            callback(Errors.generic("CountryInfoJSON asset was not found"), nil)
            return
        }
        
        do {
            let infoList = try JSONDecoder().decode([Item].self, from: asset.data)
            callback(nil, infoList)
        } catch {
            callback(Errors.generic("CountryInfoJSON decode failed"), nil)
        }
    }
    
    static func LoadMap(callback: LoadMapCallback) {
        
        Load(callback: {
            ( err, result ) in
            var asMap: [String:Item] = [:]
            if let result = result {
                for item in result {
                    asMap[item.code] = item
                }
            }
            callback(err, asMap)
        })
        
    }
}
