//
//  TokenTableCell.swift
//  MyQR
//
//  Created by Nikolay Fedotenko on 18/02/19.
//  Copyright © 2019 Nikolay Fedotenko. All rights reserved.
//

import Foundation
import UIKit

class TokenTableCell: UITableViewCell {
    
    public var tokenId: Int = -1
    
    private var token: String? = nil
    public var Token: String {
        get { return token ?? "" }
        set {
            token = newValue
            guard
                let label = passwordLabel
                else {
                    print("passwordLabel is nil")
                    return
            }
            label.text = newValue
        }
    }
    
    public var host: ViewController? = nil
    
    @IBOutlet weak var passwordLabel: UILabel!
    
    @IBAction func removePressed(_ sender: Any) {
        print("remove token ", Token)
        guard let host = host else {
            print("host is nil")
            return
        }
        host.removeToken(tokenId)
    }
    
    @IBAction func showQRPressed(_ sender: Any) {
        print("show QR for token ", Token)
        guard let host = host else {
            print("host is nil")
            return
        }
        host.showQRFor(tokenId)
    }
}
