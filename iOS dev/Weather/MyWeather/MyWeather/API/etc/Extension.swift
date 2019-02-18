//
//  Extension.swift
//  MyWeather
//
//  Created by usher on 2/16/19.
//  Copyright © 2019 My. All rights reserved.
//

import Foundation

extension Sequence where Iterator.Element: Hashable {
    func unique() -> [Iterator.Element] {
        var seen: [Iterator.Element: Bool] = [:]
        return self.filter { seen.updateValue(true, forKey: $0) == nil }
    }
}
