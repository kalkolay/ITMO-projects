//
//  Extension.swift
//  MyWeather
//
//  Created by Nikolay Fedotenko on 16/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation

extension Sequence where Iterator.Element: Hashable {
    func unique() -> [Iterator.Element] {
        var seen: [Iterator.Element: Bool] = [:]
        return self.filter { seen.updateValue(true, forKey: $0) == nil }
    }
}
